package com.lerogo;

import org.bytedeco.javacv.FFmpegFrameGrabber;
import org.bytedeco.javacv.Frame;
import org.bytedeco.javacv.Java2DFrameConverter;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

/**
 * @author lerogo
 * @date 2021/5/12 11:24
 */
public class Video {
    /*
     * source:需要处理的视频文件 destpath:截取图片放的位置 StartTime:开始时间 JianGe:间隔时间
     */
    public static void cut(String source, String destpath, double StartTime, double JianGe) {
        videoPath = source;
        videoFramesPath = destpath;
        grabberVideoFramer(videoPath, StartTime, JianGe);
    }

    // 视频文件路径
    private static String videoPath = "";

    // 视频帧图片存储路径
    private static String videoFramesPath = "";

    /**
     * TODO 将视频文件帧处理并以“jpg”格式进行存储。 依赖FrameToBufferedImage方法：将frame转换为bufferedImage对象
     */
    private static void grabberVideoFramer(String videoFilePath, double StartTime, double JianGe) {
        // Frame对象
        Frame frame = null;
        // 标识
        double flag = StartTime;
        double jiange = JianGe;
        /*
         * 获取视频文件
         */
        // 获取视频名字
        File tempFile = new File(videoFilePath.trim());
        String file_name = tempFile.getName();
        String videoName = file_name.substring(0, file_name.lastIndexOf("."));

        FFmpegFrameGrabber fFmpegFrameGrabber = new FFmpegFrameGrabber(videoFilePath);

        try {
            fFmpegFrameGrabber.start();
            /*
             * .getFrameRate()方法：获取视频文件信息,总帧数
             */
            double ftp = fFmpegFrameGrabber.getLengthInFrames();
            // System.out.println(fFmpegFrameGrabber.grabKeyFrame());
            double timeFlag = ftp / fFmpegFrameGrabber.getFrameRate();
            System.out.println("时长 " + timeFlag);
            System.out.println("开始时间：" + StartTime + "\t间隔时间：" + JianGe);
            // BufferedImage bImage = null;
            // System.out.println("开始运行视频提取帧，耗时较长");
            // System.out.println(timeFlag+" "+fFmpegFrameGrabber.getFrameRate());
            double ftpjiequ = jiange * fFmpegFrameGrabber.getFrameRate();
            int JGcha = (int) ftpjiequ;
            double StaticCha = ftpjiequ - JGcha;
            double cha = StaticCha;
            //跳过5帧无效图
            for (int i = 5; i < flag * fFmpegFrameGrabber.getFrameRate(); ++i) {
                frame = fFmpegFrameGrabber.grabImage();
            }
            while (flag <= timeFlag) {
                // 文件绝对路径+名字
                String fileName = videoFramesPath + "\\" + String.valueOf(flag) + ".jpg";
                // 文件储存对象
                File outPut = new File(fileName);
                // 获取帧
                frame = fFmpegFrameGrabber.grabImage();
                // System.out.println(frame);
                if (frame != null) {
                    ImageIO.write(FrameToBufferedImage(frame), "jpg", outPut);
                    System.out.println("截取：" + flag + "秒(S)成功");
                }
                for (int i = 1; i < JGcha; ++i) {
                    frame = fFmpegFrameGrabber.grabImage();
                }
                if (cha >= 1) {
                    frame = fFmpegFrameGrabber.grabImage();
                    cha -= 1;
                }
                flag += jiange;
                cha += StaticCha;
            }
            // System.out.println("============运行结束============");
            fFmpegFrameGrabber.stop();
        } catch (IOException E) {
        }
    }

    private static BufferedImage FrameToBufferedImage(Frame frame) {
        // 创建BufferedImage对象
        Java2DFrameConverter converter = new Java2DFrameConverter();
        BufferedImage bufferedImage = converter.getBufferedImage(frame);
        return bufferedImage;
    }
}