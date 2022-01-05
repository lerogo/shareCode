//#include <stdio.h>
//#include "platform.h"
#include <memory.h>
#include "xil_printf.h"

//设置 MIO引脚地址
#define MIO_PIN_07        (*(volatile unsigned int *)0xF800071C)
#define MIO_PIN_50        (*(volatile unsigned int *)0xF80007C8)
#define MIO_PIN_51        (*(volatile unsigned int *)0xF80007CC)

//设置 GPIO端口方向寄存器地址
#define DIRM_0            (*(volatile unsigned int *)0xE000A204)
#define DIRM_1            (*(volatile unsigned int *)0xE000A244)
#define DIRM_2            (*(volatile unsigned int *)0xE000A284)
#define DIRM_3            (*(volatile unsigned int *)0xE000A2C4)
//设置 GPIO端口输出使能寄存器地址
#define OEN_0            (*(volatile unsigned int *)0xE000A208)
#define OEN_1            (*(volatile unsigned int *)0xE000A248)
#define OEN_2            (*(volatile unsigned int *)0xE000A288)
#define OEN_3            (*(volatile unsigned int *)0xE000A2C8)
//设置 GPIO端口输出寄存器地址
#define DATA_0            (*(volatile unsigned int *)0xE000A040)
#define DATA_1            (*(volatile unsigned int *)0xE000A044)
#define DATA_2            (*(volatile unsigned int *)0xE000A048)
#define DATA_3            (*(volatile unsigned int *)0xE000A04C)
//设置 GPIO端口输入寄存器地址
#define DATA_0_RO        (*(volatile unsigned int *)0xE000A060)
#define DATA_1_RO        (*(volatile unsigned int *)0xE000A064)
#define DATA_2_RO        (*(volatile unsigned int *)0xE000A068)
#define DATA_3_RO        (*(volatile unsigned int *)0xE000A06C)

//设置 UART1引脚地址的宏定义
#define rMIO_PIN_48        (*(volatile unsigned long*)0xF80007C0)
#define rMIO_PIN_49    (*(volatile unsigned long*)0xF80007C4)
#define rUART_CLK_CTRL    (*(volatile unsigned long*)0xF8000154)
#define rControl_reg0    (*(volatile unsigned long*)0xE0001000)
#define rMode_reg0        (*(volatile unsigned long*)0xE0001004)
//设置 UART1端口波特率等参数地址寄存器的宏定义
#define rBaud_rate_gen_reg0 (*(volatile unsigned long*)0xE0001018)
#define rBaud_rate_divider_reg0 (*(volatile unsigned long*)0xE0001034)
#define rTx_Rx_FIFO0 (*(volatile unsigned long*)0xE0001030)
#define rChannel_sts_reg0 (*(volatile unsigned long*)0xE000102C)

void arm(int Arm_id, int Arm_dir, int angle);

void box(void);

void plate(int Plate_ID, int Plate_dir);

void trans(int Trans_dir);

void changeLed(u32 SW);

void send_Char_9(unsigned char modbus[]);                //9字节串口发送函数
void send_Char(unsigned char data);                        //串口发送函数，一次一个字节
void RS232_Init();                                        //串口初始化函数

void delay(int i, int n, int m);                            //延时函数

int resetAngle[8];

int flagBtns[5];

int angle = 3;

int main() {
    u32 flag, flag_btn;        //变量flag用于记录SW0~SW7按键按下信息；变量flag_btn用于记录BTNU、BTND、BTNL、BTNR、BTNC按键按下信息

    //注：下面MIO引脚和EMIO引脚的序号是统一编号的，MIO序号为0~31及32~53，EMIO序号为54~85及86~117
    //配置及初始化MIO07引脚的相关寄存器，MIO07作为LED灯控制的输出引脚
    MIO_PIN_07 = 0x00003600;
    DIRM_0 = DIRM_0 | 0x00000080;
    OEN_0 = OEN_0 | 0x00000080;
    //配置及初始化MIO50、MIO51引脚的相关寄存器，MIO50、MIO51作为按键输入引脚
    MIO_PIN_50 = 0x00003600;
    MIO_PIN_51 = 0x00003600;
    DIRM_1 = DIRM_1 & 0xFFF3FFFF;
    // 端口2  54-58 对应 0-4 下面同理
    //初始化EMIO54~EMIO58的引脚，它们对应BTNU、BTND、BTNL、BTNR、BTNC按键，输入
    DIRM_2 = DIRM_2 & 0xFFFFFFE0;
    //初始化EMIO59~EMIO66的引脚，它们对应SW7~SW0拨动开关，输入
    DIRM_2 = DIRM_2 & 0xFFFFE01F;
    //初始化EMIO67~EMIO74的引脚，它们对应LED7~LED0，输出
    DIRM_2 = DIRM_2 | 0x001FE000;
    OEN_2 = OEN_2 | 0x001FE000;

    //初始化UART1
    RS232_Init();
    int i = 0;
    while (1) {
        //直接读取SW的输入信息 存放到后面后面8位 sw0-sw7
        flag = (DATA_2_RO & 0x00001FE0) >> 5;
        // 修改小灯状态
        changeLed(flag);
        //读BTNC、BTNR、BTNL、BTND、BTNU按键的输入信息
        flag_btn = DATA_2_RO & 0x0000001F;
        for (i = 0; i < 5; ++i) {
            //BTNU,BTND,BTNL,BTNR,BTNC（顺序）
            flagBtns[i] = (flag_btn >> i) & 0x01;
            if (flagBtns[i]) {
                //LED9指示灯亮
                DATA_0 = DATA_0 | 0x00000080;
            }
        }
        switch (flag & 0x03) {
            case 0x00:                    //复位模式
                for (i = 1; i <= 7; ++i) {
                    int j = 0;
                    if (resetAngle[i] > 0) {
                        for (; j < resetAngle[i]; j += angle) {
                            arm(i, 1, angle);
                        }
                    } else if (resetAngle[i] < 0) {
                        for (; j > resetAngle[i]; j -= angle) {
                            arm(i, 0, angle);
                        }
                    }
                }
                break;
            case 0x01:                    //手动控制模式
                // 读取开关状态
                // 机械臂（6）和导轨 /箱子/传送带/吸盘
                if ((flag >> 2) & 0x01) {
                    // 机械臂 6条 和 导轨
                    if (flagBtns[2]) {
                        arm((flag >> 3), 0, angle);
                        //延时约1秒，进行消抖动处理
                        delay(1000, 500, 50);
                    } else if (flagBtns[3]) {
                        arm((flag >> 3), 1, angle);
                        //延时约1秒，进行消抖动处理
                        delay(1000, 500, 50);
                    }
                } else {
                    // 箱子/传送带/吸盘
                    switch (flag >> 3) {
                        case 0x01:
                            if (flagBtns[4]) {
                                box();
                                //延时约1秒，进行消抖动处理
                                delay(1000, 500, 50);
                            }
                            break;
                        case 0x02:
                            if (flagBtns[2]) {
                                trans(0);
                                //延时约1秒，进行消抖动处理
                                delay(1000, 500, 50);
                            } else if (flagBtns[3]) {
                                trans(1);
                                //延时约1秒，进行消抖动处理
                                delay(1000, 500, 50);
                            }
                            break;
                        case 0x04:
                            break;
                    }
                }
                flag_btn = DATA_2_RO & 0x0000001F;
                while (flag_btn != 0x00) {
                    flag_btn = DATA_2_RO & 0x0000001F;
                }
                //LED9指示灯灭
                DATA_0 = DATA_0 & 0xFFFFFF7F;
                break;
            case 0x02:
                //自动控制模式
                break;
            case 0x03:
                //机械臂示教模式（该模式暂不实现）
                break;
        }
    }
    return 0;
}

void changeLed(u32 SW) {
    DATA_2 = (DATA_2 & 0xFFE01FFF) | (SW << 13);
}

//机械臂相关各部件动作函数
void arm(int Arm_ID, int Arm_dir, int angle) {
    if (Arm_ID <= 0 || Arm_ID > 7) {
        return;
    }
    if (angle <= 0 || angle > 5 || (Arm_ID == 7 && angle == 5)) {
        return;
    }
    if (Arm_dir == 0) {
        if (resetAngle[Arm_ID] + angle > 360) {
            return;
        }
        resetAngle[Arm_ID] += angle;
    } else {
        if (resetAngle[Arm_ID] - angle < -360) {
            return;
        }
        resetAngle[Arm_ID] -= angle;
    }
    unsigned char modbus_com[9];
    memset(modbus_com, '0', sizeof(modbus_com));
    modbus_com[0] = '#';                //起始符，固定为#
    modbus_com[1] = '2';                //机械臂相关

    char cmd;
    angle = angle == 5 ? 4 : angle;
    if (Arm_ID == 7 && Arm_dir == 1) {
        angle -= 1;
    }
    if (Arm_dir == 0) {
        cmd = (char) (0x30 + angle);
    } else if (Arm_dir == 1) {
        cmd = (char) (0x34 + angle);
    } else {
        return;
    }
    modbus_com[Arm_ID + 1] = cmd;
    send_Char_9(modbus_com);
}

//箱子相关函数
void box(void) {
    unsigned char modbus_com[9];
    memset(modbus_com, '0', sizeof(modbus_com));
    modbus_com[0] = '#';                //起始符，固定为#
    modbus_com[1] = '4';                //箱子
    modbus_com[3] = '1';
    send_Char_9(modbus_com);
}

//吸盘相关函数
void plate(int Plate_ID, int Plate_dir) {
    if (Plate_dir != 1 && Plate_dir != 2) {
        return;
    }
    if (Plate_ID <= 0 || Plate_ID >= 4) {
        return;
    }
    unsigned char modbus_com[9];
    memset(modbus_com, '0', sizeof(modbus_com));
    modbus_com[0] = '#';                //起始符，固定为#
    modbus_com[1] = '5';                //吸盘

    modbus_com[Plate_ID + 1] = (char) (0x30 + Plate_dir);
    send_Char_9(modbus_com);
}

//传送带相关函数
void trans(int Trans_dir) {
    if (Trans_dir != 1 && Trans_dir != 2) {
        return;
    }
    unsigned char modbus_com[9];
    memset(modbus_com, '0', sizeof(modbus_com));
    modbus_com[0] = '#';                //起始符，固定为#
    modbus_com[1] = '6';                //传送带
    //控制3号传送带
    modbus_com[3] = 0x30 + Trans_dir;

    send_Char_9(modbus_com);
}


//9个字节数据的发送函数
void send_Char_9(unsigned char modbus[]) {
    int i;
    char data;
    for (i = 0; i < 9; i++) {
        data = modbus[i];
        send_Char(data);
        delay(100, 10, 10);        //延时
    }
}

//单个字节数据的发送函数
void send_Char(unsigned char data) {
    while ((rChannel_sts_reg0 & 0x10) == 0x10);
    rTx_Rx_FIFO0 = data;
}

//UART1的初始化函数
void RS232_Init() {
    rMIO_PIN_48 = 0x000026E0;
    rMIO_PIN_49 = 0x000026E0;
    rUART_CLK_CTRL = 0x00001402;
    rControl_reg0 = 0x00000017;
    rMode_reg0 = 0x00000020;
    rBaud_rate_gen_reg0 = 62;
    rBaud_rate_divider_reg0 = 6;
}

//延时函数
void delay(int n, int m, int p) {
    int i, j, k;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            for (k = 1; k <= p; k++) {

            }
        }
    }
}
