// 引入相关内核头文件
#include <linux/module.h>

// 内核模块信息，包括许可证、作者、描述和版本等
MODULE_LICENSE("MIT");
MODULE_AUTHOR("HHL");
MODULE_DESCRIPTION("An hello worlk module for demonstration");
MODULE_VERSION("1.0");

// 内核模块参数，加载时指定或者动态指定，以此控制模块行为
static char *name = "HHL";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "Whom this module say hello to");


// 初始化函数，在加载时调用，分配资源准备执行环境
// 这里只是往内核日志输出一行记录
static int __init hello_init(void)
{
        printk(KERN_INFO "HELLO: Hello %s, this is hello module speaking\n", name);
        return 0;
}


// 清理函数，在卸载时调用，回收资源销毁执行环境
static void __exit hello_exit(void)
{
        printk(KERN_INFO "HELLO: Goodbye %s", name);
}

// 登记初始化函数及清理函数
module_init(hello_init);
module_exit(hello_exit);