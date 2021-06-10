//
// Created by lerogo on 2021/5/13.
//

#ifndef IMAGE_PROCESSING_BMP_FILE_H
#define IMAGE_PROCESSING_BMP_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <nmmintrin.h>

// 文件头
typedef struct {
    unsigned short file_type;
    unsigned int file_size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset_bits;
} __attribute__((packed)) bitmap_file_header;

//图片信息头
typedef struct {
    unsigned int bitmap_info_size;
    int bitmap_width;
    int bitmap_height;
    unsigned short planes;//位图的位面数，固定为 1。
    unsigned short image_depth;//位图的图像深度，表示位图数据中，几个二进制位表示一个像素点，如 8 bits 表示，8 个二进制位表示一个像素点。
    unsigned int compression;//位图压缩方式
    unsigned int image_size;//位图的数据大小
    int x_pels_permeter;//指定位图目标设备的水平打印分辨率
    int y_pels_permeter;//指定位图目标设备的垂直打印分辨率
    unsigned int color_used;//位图实际使用调色板的颜色数量 图像深度少于或等于 8 bits 时值有效。值为 0 表示使用了整个调色板的颜色。
    unsigned int color_important;//重要的颜色数量，值通常等于 color_used，值为 0 时表示所有颜色都重要。
} __attribute__((packed)) bitmap_info_header;

// 调色板
typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char reserved;
} __attribute__((packed)) bitmap_palette;


class BmpFile {
public:
    const unsigned char_express = 1 << 8;
    // 是否是RGB图
    bool isRgb = true;
    bitmap_file_header fileHeader;
    bitmap_info_header infoHeader;
    bitmap_palette *palette = nullptr;
    unsigned fileHeaderSize = sizeof(fileHeader);
    unsigned infoHeaderSize = sizeof(infoHeader);
    unsigned paletteSize = sizeof(bitmap_palette);
    unsigned paletteNum = 0;

    // 存文件时用的header
    unsigned char *header = nullptr;
    unsigned headerSize = 0;
    // 文件数据
    unsigned char *data = nullptr;

    // 直方图
    unsigned *histogram = nullptr;
    // 亮度
    double bright = 0;
    // 对比度
    double contrast = 0;

    //积分图
    unsigned *sumGraph = nullptr;

    ~BmpFile() {
        delete[] this->palette;
        delete[] this->header;
        delete[] this->data;
        delete[] this->histogram;
        delete[] this->sumGraph;
    }

    //新建bmp图像
    static BmpFile *createGrayBmp(unsigned width, unsigned height);

    //将数据转为8位的数据
    void writeBitData(unsigned width, unsigned height, unsigned char *_data) const;

    // 将已有的信息写入头
    void copyHeader2Men();

    // 加载图片
    void load(const std::string &);

    // 保存图片
    void save(const std::string &);

    // 反向
    void Invert() const;

    // 如果是灰色 则弄伪彩色
    bool gryPseudoColor() const;

    // rgb 到 gray 图片
    bool rgb2Gray();

    //均值方差规定化
    bool MVR(const double &bright, const double &contrast);

    //得到直方图
    void getHistogram();

    // 得到亮度和对比度
    void getBrightContrast();

    //直方图均衡化
    bool histogramEqualization();

    // 拿到彩色的Histogram
    void getHistogramRgb();

    //raw加载
    static BmpFile *load14Raw(const std::string &path, unsigned width, unsigned height);

    //彩色灰度图像 浮点乘 到 整数乘 测试
    bool rgb2Gray_test1();

    //均值滤波列积分
    bool avrFilterBySumCol(unsigned M, unsigned N);

    //积分图实现
    void getSumGryGraphBySumCol();

    //SSE实现
    void getSumGryGraphBySSE();

    //均值滤波 积分图
    bool avrFilterByGraph(unsigned M, unsigned N);

    //反向 SSE
    void InvertBySSE() const;

    //中值滤波
    double medianFilter(unsigned M, unsigned N);

    //高斯滤波
    bool GaussianFilter(int const &sigma);

    //一阶微分算子 sobel
    bool sobelProcess();

    //沈俊算子
    bool ShenJunProcess(double const &alpha);

    //米粒边缘检测 一阶微分算子 二阶微分算子（沈俊）
    void riceEdgeDetector(double const &alpha, int const &grd);

    //应用 文本窗口识别
    __attribute__((unused)) void textPositioning();

    //切割图片
    void cutImg(const unsigned int sRow, const unsigned int sCol, const int &rowLen, const int &colLen);

    //应用 文本窗口识别
    void textPositioningByWindow(const int &w, const int &h,const int &slope);

    //获取任意窗口的积分大小
    int getWindowsSumGraph(const int &s_x, const int &s_y, const int &x_len, const int &y_len);

    //压缩图片
    void compressImg(unsigned const &widthSlope, unsigned const &heightSlope);

    //文本定位画图用
    void drawImg(unsigned const sRow, unsigned const sCol, unsigned const &rowLen, unsigned const &colLen);

    //canny算子
    void cannyProcess(const int &sigma, const int &maxVal, const int &minVal);

};

#endif //IMAGE_PROCESSING_BMP_FILE_H
