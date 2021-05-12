package com.lerogo;

import java.awt.image.BufferedImage;
import java.io.*;
import javax.imageio.ImageIO;

import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.objdetect.CascadeClassifier;

import java.awt.Rectangle;
import java.util.Iterator;
import javax.imageio.ImageReadParam;
import javax.imageio.ImageReader;
import javax.imageio.stream.ImageInputStream;

import org.opencv.core.*;
import org.opencv.imgproc.Imgproc;

import java.util.Arrays;
import java.util.HashMap;

/**
 * @author lerogo
 * @date 2021/5/12 11:23
 */

public class GLmage {
    // 读取OpenCV自带的人脸识别特征XML文件
    // OpenCV 图像识别库一般位于 opencv\sources\data 下面
    private static String faceback = "";

    static {
        // 在使用OpenCV前必须加载Core.NATIVE_LIBRARY_NAME类,否则会报错
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    }

    public static void init(String OpenCv_FaceXML) {
        faceback = OpenCv_FaceXML;
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
        faceDetector = new CascadeClassifier(faceback);
    }

    /*
     * source: 原始图片文件路径 destpath： 识别头像存储路径
     */
    public static void head(String source, String destpath) throws Exception {
        try {
            if (faceback == "") {
                throw new Exception();
            }
        } catch (Exception e) {
            System.err.println("请初始化opencvXML");
            return;
        }
        // 输入图片目录如"C:\\Users\\lerogo\\Desktop\\test\\in"
        String imgPath = source + "/";
        // 输出图片目录如C:\\Users\\lerogo\\Desktop\\test\\out
        String outPath = destpath + "/";

        File file = new File(imgPath);
        File[] tempList = file.listFiles();
        for (int i = 0; i < tempList.length; i++) {
            // System.out.println("输入文件是:");
            // System.out.println(tempList[i].toString());
            face(tempList[i].toString(), faceback, outPath);
        }
    }

    /*
     * source: 目标头像文件; allpath: 所有的头像文件 ;level: 系数：越大匹配越精确 (越慢)
     */
    public static HashMap<String, Double> search(String source, String allpath, int level) throws Exception {
        try {
            if (faceback == "") {
                throw new Exception();
            }
        } catch (Exception e) {
            System.err.println("请初始化opencvXML");
            System.exit(0);
        }
        HashMap<String, Double> map = new HashMap<>();
        // 比较的两张照片
        String pic1 = source;
        File file = new File(allpath);
        File[] tempList = file.listFiles();
        //int photoarr[]=new int [tempList.length];
        //int j=0;
        for (int i = 0; i < tempList.length; i++) {
            // System.out.println("对比文件是:");
            // System.out.println(tempList[i].toString());
            try {
                // 系数：越大匹配越精确 (越慢)
                double compareHist = compare_image(pic1, tempList[i].toString(), level);// 此处会得到一个系数
                // System.out.println("匹配度："+compareHist);
                // 获取图片的名字
                File tempFile = new File(tempList[i].toString().trim());
                String file_name = tempFile.getName();
                String fileName = file_name.substring(0, file_name.lastIndexOf("."));
                map.put(fileName, compareHist);
            } catch (Exception e) {
                System.out.println(tempList[i].toString() + "\n文件有误（移动）！\n");
                //photoarr[j++]=i;
                continue;
            }
        }
		/*
		try{
			Thread.sleep(1000);
			}catch(Exception e){
			System.exit(0);//退出程序
			}
		File newFile=new File(allpath+"\\ErrorPhoto");
		if(!newFile.exists()) {
			newFile.mkdir();
		}
		for(int i=0;i<j;++i) {
			File errorFile=new File(tempList[photoarr[i]].toString());
			System.out.println(errorFile);
			System.out.println(allpath+"\\ErrorPhoto\\"+tempList[photoarr[i]].getName());
			errorFile.renameTo(new File(allpath+"\\ErrorPhoto\\"+tempList[photoarr[i]].getName()));
		}*/
        return map;
    }

    /* 人脸匹配度----------------------------------------------------- */
    static CascadeClassifier faceDetector;

    // 灰度化人脸
    private static Mat conv_Mat(String img) {
        Mat image0 = Imgcodecs.imread(img);

        Mat image1 = new Mat();
        // 灰度化
        Imgproc.cvtColor(image0, image1, Imgproc.COLOR_BGR2GRAY);
        // 探测人脸
        MatOfRect faceDetections = new MatOfRect();
        faceDetector.detectMultiScale(image1, faceDetections);
        // rect中人脸图片的范围
        for (Rect rect : faceDetections.toArray()) {
            Mat face = new Mat(image1, rect);
            return face;
        }
        return null;
    }

    private static double compare_image(String img_1, String img_2, int level) {
        Mat mat_1 = conv_Mat(img_1);
        Mat mat_2 = conv_Mat(img_2);
        Mat hist_1 = new Mat();
        Mat hist_2 = new Mat();

        // 颜色范围
        MatOfFloat ranges = new MatOfFloat(0f, 256f);
        // 直方图大小， 越大匹配越精确 (越慢)
        MatOfInt histSize = new MatOfInt(level);

        Imgproc.calcHist(Arrays.asList(mat_1), new MatOfInt(0), new Mat(), hist_1, histSize, ranges);
        Imgproc.calcHist(Arrays.asList(mat_2), new MatOfInt(0), new Mat(), hist_2, histSize, ranges);

        // CORREL 相关系数
        double res = Imgproc.compareHist(hist_1, hist_2, Imgproc.CV_COMP_CORREL);
        return res;
    }

    /* 图像处理截取图片---------------------------------------------------------------- */
    // opencv自带图像处理
    private static void face(String imgPath, String faceback, String outPath) throws Exception {
        // 获取图片的名字
        File tempFile = new File(imgPath.trim());
        String file_name = tempFile.getName();
        String fileName = file_name.substring(0, file_name.lastIndexOf("."));

        // 读取OpenCV自带的人脸识别特征XML文件
        // OpenCV 图像识别库一般位于 opencv\sources\data 下面
        CascadeClassifier facebook = new CascadeClassifier(faceback);
        // 读取测试图片
        Mat image = Imgcodecs.imread(imgPath);
        // 特征匹配
        MatOfRect face = new MatOfRect();
        facebook.detectMultiScale(image, face);
        // 匹配 Rect 矩阵 数组
        Rect[] rects = face.toArray();
        // System.out.println("匹配到 " + rects.length + " 个人脸");
        // 输出
        for (int i = 0; i < rects.length; i++) {
            String outfile = outPath + fileName + "_" + (i + 1) + ".jpg";// 保存文件名字和目录
            cutJPG(new FileInputStream(imgPath), new FileOutputStream(outfile), rects[i].x, rects[i].y, rects[i].width,
                    rects[i].height);
            // System.out.println("输出为：" + outfile);
        }
        // System.out.println("识别输出完成\n");
    }

    /*----------------------------------------------------------------------------------------------------*/
    private static void cutJPG(InputStream input, OutputStream out, int x, int y, int width, int height)
            throws IOException {
        ImageInputStream imageStream = null;
        try {
            Iterator<ImageReader> readers = ImageIO.getImageReadersByFormatName("jpg");
            ImageReader reader = readers.next();
            imageStream = ImageIO.createImageInputStream(input);
            reader.setInput(imageStream, true);
            ImageReadParam param = reader.getDefaultReadParam();

            // 输出信息
            // System.out.println(reader.getWidth(0));
            // System.out.println(reader.getHeight(0));

            Rectangle rect = new Rectangle(x, y, width, height);
            param.setSourceRegion(rect);
            BufferedImage bi = reader.read(0, param);
            ImageIO.write(bi, "jpg", out);
        } finally {
            imageStream.close();
        }
    }

    protected static void cutPNG(InputStream input, OutputStream out, int x, int y, int width, int height)
            throws IOException {
        ImageInputStream imageStream = null;
        try {
            Iterator<ImageReader> readers = ImageIO.getImageReadersByFormatName("png");
            ImageReader reader = readers.next();
            imageStream = ImageIO.createImageInputStream(input);
            reader.setInput(imageStream, true);
            ImageReadParam param = reader.getDefaultReadParam();

            // 输出信息
            // System.out.println(reader.getWidth(0));
            // System.out.println(reader.getHeight(0));

            Rectangle rect = new Rectangle(x, y, width, height);
            param.setSourceRegion(rect);
            BufferedImage bi = reader.read(0, param);
            ImageIO.write(bi, "png", out);
        } finally {
            imageStream.close();
        }
    }

    protected static void cutImage(InputStream input, OutputStream out, String type, int x, int y, int width, int height)
            throws IOException {
        ImageInputStream imageStream = null;
        try {
            String imageType = (null == type || "".equals(type)) ? "jpg" : type;
            Iterator<ImageReader> readers = ImageIO.getImageReadersByFormatName(imageType);
            ImageReader reader = readers.next();
            imageStream = ImageIO.createImageInputStream(input);
            reader.setInput(imageStream, true);
            ImageReadParam param = reader.getDefaultReadParam();
            Rectangle rect = new Rectangle(x, y, width, height);
            param.setSourceRegion(rect);
            BufferedImage bi = reader.read(0, param);
            ImageIO.write(bi, imageType, out);
        } finally {
            imageStream.close();
        }
    }

}
