package com.lerogo;

import java.util.HashMap;

/**
 * @author lerogo
 * @date 2021/5/12 11:21
 */
public class Main {

    public static void main(String[] args) throws Exception {
        String face = "D:\\Programs\\Build_Program\\Opencv3\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
        String a = "C:\\Users\\lerogo\\Desktop\\test\\shoot";
        String b = "C:\\Users\\lerogo\\Desktop\\test\\new";

        //初始化参数
        GLmage.init(face);

        //视频文件，储存位置，开始时间，间隔时间
        //视频截的图命名就是截图时间
        Video.cut("C:/Users/lerogo/Desktop/123.mp4", a, 1, 1);

        //检测人脸
        GLmage.head(a, b);

        String c = "C:\\Users\\lerogo\\Desktop\\123.png";
        HashMap<String, Double> map = new HashMap<>();

        //进行对比
        map = GLmage.search(c, b, 1000);
        System.out.println(map);
    }
}