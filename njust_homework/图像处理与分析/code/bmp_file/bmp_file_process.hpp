//
// Created by lerogo on 2021/6/8.
//

#ifndef IMAGE_PROCESSING_BMP_FILE_PROCESS_HPP
#define IMAGE_PROCESSING_BMP_FILE_PROCESS_HPP

#include <fstream>
#include <cmath>
#include <emmintrin.h>
#include "bmp_file_info.h"
#include "bmp_file.hpp"

namespace hhl {
    // 只和处理相关 类  一些接口
    class bmp_file_process {
    private:

        bmp_file_process() {
            memset(preTmp, 0, sizeof(preTmp));
        };

        ~bmp_file_process();

        static bmp_file_process *b;

        int width = 0;
        int height = 0;
        bool isRgb = false;
        bool isInvert = false;
        int fast0123 = 0;

        //处理后的图片数据
        u_char *resImg = nullptr;
        //处理后的图片梯度数据
        u_char *gdImg = nullptr;
        u_int imgSize = 0;

        //临时内存空间 避免多次delete等
        u_char *tmp = nullptr;
        u_int tmpSize = 0;

        //必要的缓存空间
        u_char preTmp[1 << 8];

        // 获得img
        bmp_file *getImg(bool _isResImg = true);

        //计算高斯的函数
        //计算高斯公式
        static double calTj(double const &j, double const &sigma) {
            double sigma_2 = sigma * sigma;
            return exp(-(j * j) * 0.5 / sigma_2) / sqrt(2 * M_PI * sigma_2);
        }

        ///hough变换
        ///给定bmp sita[0,180) ,rou 构造的数组 总长度 step 点x坐标 y坐标 以及值
        ///必须满足 len % 360 == 0
        /// 修改 数组数据
        void houghLine(int *arr, const int &length, const int &step,
                       const int &pNum, const int *xArr, const int *yArr, const int *pValArr = nullptr);

        ///轮廓跟踪算法
        /// 轮廓起点 是否外轮廓  链码数组  链码最大个数
        int traceContour(const int &x0, const int &y0, const bool &isOuter,
                         u_char *pChainCode, const int &maxChainCodeNum);

        ///计算chainCode的轮廓包含点
        int contourPixels(const u_char *pChainCode, const int &n);

        ///边界矩形像素 两个点
        void contourRect(int x0, int y0, const u_char *pCode, int N, int &x1, int &x2, int &y1, int &y2);

        ///填充图
        void fillContour(const int &x0, const int &y0, const bool &isOuter,
                         const u_char *pChainCode, const int &N, const u_char &color);

        ///画边框
        void drawContour(const int &x0, const int &y0,
                         const u_char *pChainCode, const int &N, const u_char &color);

    public:
        const static std::string GRY_MODE;
        const static std::string RGB_MODE;

        ///单例模式
        static bmp_file_process *getBmpFile();

        ///清理
        static void delBmpFile();

        ///检查处理类是否支持这个 bmp文件 并提供支持
        void cheekBmp(const bmp_file *bmp, const int &_fast0123 = -1);

        ///检查tmp临时内存是否够
        void cheekTmpSize(const u_int &size);

        ///检查img的大小
        void cheekImgSize(const u_int &size);

        ///初始化接口类
        void init(const int &_width, const int &_height,
                  const std::string &mod = GRY_MODE, const bool &invert = false, const int &_fast0123 = 0);

        ///创建一个bmp文件
        ///宽 高 rgb/gry
        bmp_file *createBmp(const int &width, const int &height, const std::string &mod);

        ///加载一个bmp图片
        bmp_file *load(const std::string &path);

        ///储存一个bmp文件
        void save(const bmp_file *bmp, const std::string &path);

        ///获得resImg的bmp图片
        bmp_file *getResImg();

        ///获得gdImg的bmp图片
        bmp_file *getGdImg();

        ///给bmp文件生成直方图
        ///处理bmp
        void getHistogram(bmp_file *bmp);

        ///得到亮度和对比度
        ///处理bmp
        void getBrightContrast(bmp_file *bmp);

        ///反向
        ///储存在resImg
        void invertBmp(const bmp_file *bmp);

        ///图片压缩 用到fast0123
        ///储存在resImg中
        void compressBmp(const bmp_file *bmp, const int &_fast0123 = -1);

        ///积分图
        ///处理bmp
        void getSumGryGraphBySumCol(bmp_file *bmp);

        ///sobel算子
        ///储存在gdImg中
        void sobelProcess(const bmp_file *bmp = nullptr);

        ///给bmp画框
        ///返回框出来的图片
        bmp_file *drawImg(const u_int &x,
                          const u_int &y, const u_int &w, const u_int &h, const bmp_file *bmp = nullptr);

        ///文本定位
        ///返回定位后框出来的图片
        bmp_file *textPositioningByWindow(const bmp_file *bmp, const int &o_w, const int &o_h,
                                          const int &_fast0123 = -1);

        ///获取任意大小的积分
        ///返回值
        inline int
        getWindowsSumGraph(const bmp_file *bmp, const int &s_x, const int &s_y, const int &x_len, const int &y_len);

        ///Otsu方法获取阈值 分割
        ///返回 阈值
        int getOtsuThreshold(const bmp_file *bmp, const int &nSize = 256);

        ///二值化图片
        ///储存在resImg
        void binaryBmp(const bmp_file *bmp, const int &threshold);

        ///高斯滤波
        ///储存在resImg
        void gaussianFilter(const bmp_file *bmp, int const &sigma);

        ///均值滤波
        ///储存在resImg
        void avrFilterByGraph(const bmp_file *bmp, int M, int N);

        ///两个bmp相减
        ///储存在resImg
        void subBmp(const bmp_file *b1, const bmp_file *b2);

        ///求两个bmp的方差
        int varianceBmp(const bmp_file *b1, const bmp_file *b2);

        ///k均值聚类
        void kMeansBmp(const bmp_file *bmp, const int &nClass, double *center);

        ///画一条直线 输入k/b 以左下角为坐标系原点
        ///color为 颜色16进制表示
        bmp_file *
        drawPicALine(const bmp_file *bmp, const double &pk, const double &pb, int color = 0x0000ff, bool isYKX = false);

        ///画一个圆 指定圆心 和 半径
        bmp_file *
        drawPicACircle(const bmp_file *bmp, const int &px, const int &py, const double &radius, int color = 0x0000ff);

        ///画一个圆的数据 分治显示用
        bmp_file *drawCircleDataImg(const bmp_file *bmp, const int *pArr, const bool &isX = true, int color = 0x0000ff);


        ///给定两个点 返回k b坐标 和 isYKX
        void getKBBy2Point(const int &x1, const int &y1, const int &x2, const int &y2,
                           double &pk, double &pb, bool &isYKX);

        ///给定 k b isYKX返回 rou(+/-) sita
        void getRouSitaByKB(const double &pk, const double &pb, const bool &isYKX, double &rou, double &sita);

        ///给定 rou(+/-) sita 返回 k b isYKX
        void getKBByRouSita(const double &rou, const double &sita, double &pk, double &pb, bool &isYKX);

        ///hough 变换应用 找四条线框出来 并画图
        bmp_file *houghLineFind1(const bmp_file *bmp, int color = 0xff0000);

        ///hough 变换应用 找一个圆框出来 并画图
        bmp_file *houghLineFind2(const bmp_file *bmp, int color = 0xff0000);

        ///应用 找到米边界 并画出来
        bmp_file *traceRice(const bmp_file *bmp, int color = 0xff0000);

        /// 找到米边界后 膨胀腐蚀
        bmp_file *eAndCRice();

        ///一条链码轮廓线是顺时针还是逆时针
        bool isClockwise(const u_char *pChainCode, const int &N);

        ///hough 变换应用 找两条线框出来 并画图
        bmp_file *houghLineFind3(const bmp_file *bmp, int color = 0xff0000);

    };

    bmp_file_process::~bmp_file_process() {
        delete[] resImg;
        delete[] gdImg;
        delete[] tmp;
        resImg = nullptr;
        gdImg = nullptr;
        tmp = nullptr;
    }

    //单例模式 初始化
    bmp_file_process *bmp_file_process::b = nullptr;
    const std::string bmp_file_process::GRY_MODE = "gry";
    const std::string bmp_file_process::RGB_MODE = "rgb";

    bmp_file_process *bmp_file_process::getBmpFile() {
        if (b == nullptr) {
            b = new bmp_file_process();
        }
        return b;
    }

    //清理
    void bmp_file_process::delBmpFile() {
        delete b;
        b = nullptr;
    }

    // 私有函数 获得img
    bmp_file *bmp_file_process::getImg(bool _isResImg) {
        u_int size = width * height;
        std::string mod = GRY_MODE;
        if (isRgb) {
            size *= 3;
            mod = RGB_MODE;
        }
        bmp_file *bmp = createBmp(width, height, mod);
        if (_isResImg) {
            memcpy(bmp->data, resImg, size);
        } else {
            memcpy(bmp->data, gdImg, size);
        }
        return bmp;
    }

    //检查处理类是否支持 bmp文件
    void bmp_file_process::cheekBmp(const bmp_file *bmp, const int &_fast0123) {
        assert(-2 < _fast0123 && _fast0123 < 4);
        if (_fast0123 != -1) {
            fast0123 = _fast0123;
        }
        assert(-1 < fast0123 && fast0123 < 4);
        width = bmp->infoHeader.bitmap_width >> fast0123;
        height = bmp->infoHeader.bitmap_height >> fast0123;
        auto size = width * height;
        isRgb = bmp->isRgb;
        isRgb && (size *= 3);
        cheekImgSize(size);
        cheekTmpSize(bmp->fileHeader.file_size);
    }


    //检查临时空间是否够
    void bmp_file_process::cheekTmpSize(const u_int &size) {
        if (tmpSize == 0 || tmpSize < size) {
            delete[] tmp;
            tmpSize = size << 1;
            tmp = new u_char[tmpSize];
            memset(tmp, 0, tmpSize);
        }
    }

    //检查图片空间是否够
    void bmp_file_process::cheekImgSize(const u_int &size) {
        if (imgSize == 0 || imgSize < size) {
            delete[] resImg;
            delete[] gdImg;
            imgSize = size << 1;
            resImg = new u_char[imgSize];
            gdImg = new u_char[imgSize];
            memset(resImg, 0, imgSize);
            memset(gdImg, 0, imgSize);
        }
    }

    //初始化接口类
    void bmp_file_process::init(const int &_width, const int &_height, const std::string &mod, const bool &invert,
                                const int &_fast0123) {
        assert(_width > 0 && _height > 0);
        assert(mod == RGB_MODE || mod == GRY_MODE);
        assert(-1 < fast0123 && _fast0123 < 4);
        isInvert = invert;
        fast0123 = _fast0123;
        isRgb = (mod == RGB_MODE);
        width = _width >> fast0123;
        height = _height >> fast0123;

        u_int size = width * height;
        // 检查图片空间
        cheekImgSize(size);
        // 检查辅助空间
        cheekTmpSize(size);
    }

    //创建一个bmp文件
    //宽 高 rgb/gry 反向 加速2^x缩小
    bmp_file *bmp_file_process::createBmp(const int &_width, const int &_height, const std::string &mod) {
        // 检查合法
        assert(_width > 0 && _height > 0 && _width % 2 == 0);
        assert(mod == GRY_MODE || mod == RGB_MODE);
        auto *bmp = new bmp_file();
        // 初始化图像大小
        u_int img_size = _width * _height;

        // 基本信息
        if (GRY_MODE == mod) {
            bmp->fileHeader.offset_bits =
                    bmp->fileHeaderSize + bmp->infoHeaderSize + bmp->paletteSize * bmp->paletteNum;
            bmp->infoHeader.image_depth = 8;
            bmp->isRgb = false;
            // 调色板 和 初始化
            bmp->palette = new bitmap_palette[bmp->paletteNum];
            for (int i = 0; i < bmp->paletteNum; ++i) {
                bmp->palette[i].red = bmp->palette[i].blue = bmp->palette[i].green = i;
                bmp->palette[i].reserved = 0;
            }
        } else {
            bmp->fileHeader.offset_bits = bmp->fileHeaderSize + bmp->infoHeaderSize;
            bmp->infoHeader.image_depth = 24;
            bmp->isRgb = true;
            // rgb
            img_size *= 3;
        }
        // 更新图像大小
        img_size += 4 - ((bmp->fileHeader.offset_bits + img_size) % 4);
        bmp->fileHeader.file_type = ('M' << 8) | 'B';
        bmp->fileHeader.file_size = bmp->fileHeader.offset_bits + img_size;
        // 更新信息头
        bmp->infoHeader.color_important = 0;
        bmp->infoHeader.planes = 1;
        bmp->infoHeader.compression = 0;
        bmp->infoHeader.x_pels_permeter = 100;
        bmp->infoHeader.y_pels_permeter = 100;
        bmp->infoHeader.color_used = 0;
        bmp->infoHeader.color_important = 0;
        bmp->infoHeader.bitmap_info_size = bmp->infoHeaderSize;
        bmp->infoHeader.bitmap_width = _width;
        bmp->infoHeader.bitmap_height = _height;
        bmp->infoHeader.image_size = img_size;
        // 数据
        bmp->data = new u_char[img_size];
        memset(bmp->data, 0, img_size);
        return bmp;
    }

    bmp_file *bmp_file_process::load(const std::string &path) {
        //创建一个新的bmp
        auto *bmp = new bmp_file();
        // 读取文件
        std::ifstream infile(path, std::ios::in | std::ios::binary);
        if (!infile) {
            std::cerr << "Open file failed." << std::endl;
            throw;
        }
        // 读取文件头
        infile.seekg(0, std::ios::beg).read(reinterpret_cast<char *>(&preTmp),
                                            bmp->fileHeaderSize + bmp->infoHeaderSize);
        memcpy(&bmp->fileHeader, &preTmp, bmp->fileHeaderSize);
        memcpy(&bmp->infoHeader, &(preTmp[bmp->fileHeaderSize]), bmp->infoHeaderSize);

        // 检查辅助空间大小
        this->cheekBmp(bmp);
        // 整个文件大小
        u_int size = bmp->fileHeader.file_size;

        infile.seekg(0, std::ios::beg).read(reinterpret_cast<char *>(tmp), size);
        infile.close();
        // 调色板数量
        bmp->paletteNum = (bmp->fileHeader.offset_bits - bmp->fileHeaderSize - bmp->infoHeaderSize) / bmp->paletteSize;
        if (bmp->paletteNum > 0) {
            bmp->palette = new bitmap_palette[bmp->paletteNum];
            u_int offset = bmp->fileHeaderSize + bmp->infoHeaderSize;
            // 调色板
            memcpy(bmp->palette, tmp + offset, bmp->fileHeader.offset_bits - offset);
            bmp->isRgb = false;
        }
        // 矫正图片所占大小
        if (bmp->infoHeader.image_size == 0) {
            bmp->infoHeader.image_size = size - bmp->fileHeader.offset_bits;
        }
        bmp->data = new u_char[bmp->infoHeader.image_size];
        // 真实数据
        memcpy(bmp->data, tmp + bmp->fileHeader.offset_bits, size - bmp->fileHeader.offset_bits);

        return bmp;
    }

    //保存一个bmp
    void bmp_file_process::save(const bmp_file *bmp, const std::string &path) {
        // 检查临时空间
        this->cheekBmp(bmp);

        // 读取文件
        std::ofstream outfile(path, std::ios::out | std::ios::binary);
        if (!outfile) {
            std::cerr << "Open file failed." << std::endl;
            throw;
        }
        memcpy(tmp, &bmp->fileHeader, bmp->fileHeaderSize);
        memcpy(tmp + bmp->fileHeaderSize, &bmp->infoHeader, bmp->infoHeaderSize);
        if (!bmp->isRgb) {
            memcpy(tmp + bmp->fileHeaderSize + bmp->infoHeaderSize, bmp->palette, bmp->paletteSize * bmp->paletteNum);
        }
        memcpy(tmp + bmp->fileHeader.offset_bits, bmp->data, bmp->infoHeader.image_size);
        // 写入文件
        outfile.write(reinterpret_cast<const char *>(tmp), bmp->fileHeader.file_size);
        outfile.close();
    }

    //获得resImg的bmp图片
    bmp_file *bmp_file_process::getResImg() {
        return getImg(true);
    }

    //获得gdImg的bmp图片
    bmp_file *bmp_file_process::getGdImg() {
        return getImg(false);
    }

    //给bmp文件生成直方图
    void bmp_file_process::getHistogram(bmp_file *bmp) {
        if (bmp->histogram == nullptr) {
            bmp->histogram = new int[1 << 8];
            memset(bmp->histogram, 0, sizeof(int) << 8);
            for (auto *pCur = bmp->data, *pEnd = pCur + bmp->infoHeader.image_size; pCur < pEnd;) {
                bmp->histogram[*(pCur++)]++;
            }
        }
    }

    //得到亮度和对比度
    void bmp_file_process::getBrightContrast(bmp_file *bmp) {
        if (bmp->histogram == nullptr) {
            this->getHistogram(bmp);
        }
        unsigned sum = 0;
        const unsigned size = 1 << 8;
        for (unsigned i = 0; i < size; ++i) {
            sum += bmp->histogram[i] * i;
        }
        bmp->bright = double(sum) / bmp->infoHeader.image_size;

        bmp->contrast = 0.0;
        for (unsigned i = 0; i < size; ++i) {
            bmp->contrast += bmp->histogram[i] * (i - bmp->bright) * (i - bmp->bright);
        }
        bmp->contrast = sqrt(bmp->contrast / (bmp->infoHeader.image_size - 1));
    }

    //反向
    void bmp_file_process::invertBmp(const bmp_file *bmp) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        // F1 高位会自动补1
        __m128i F1 = _mm_set1_epi8(0xff);
        __m128i *pSSE = (__m128i *) resImg;
        for (auto *pCur = bmp->data, *pEnd = bmp->data + bmp->infoHeader.image_size; pCur < pEnd; pCur += 16) {
            *(pSSE++) = _mm_xor_si128(*pSSE, F1);
        }
    }

    //压缩图像
    void bmp_file_process::compressBmp(const bmp_file *bmp, const int &_fast0123) {
        assert(-2 < _fast0123 && _fast0123 < 4);
        if (_fast0123 != -1) {
            fast0123 = _fast0123;
        }
        assert(-1 < fast0123 && fast0123 < 4);
        // 检查临时空间
        this->cheekBmp(bmp);
        auto size = width * height;
        isRgb && (size *= 3);
        if (fast0123 <= 0) {
            memcpy(resImg, bmp->data, size);
            return;
        }
        auto *pCur = bmp->data;
        // 步长
        auto step = 1 << fast0123;
        // 赋值 结束
        for (auto *pRes = resImg, *pEnd = resImg + size; pRes < pEnd;) {
            auto *nowPCur = pCur;
            for (auto *pRowEnd = pRes + width; pRes < pRowEnd;) {
                *(pRes++) = *nowPCur;
                nowPCur += step;
            }
            pCur += bmp->infoHeader.bitmap_width * step;
        }
    }

    //获取积分图
    void bmp_file_process::getSumGryGraphBySumCol(bmp_file *bmp) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp);
        if (bmp->sumGraph == nullptr) {
            auto *sumCol = new int[width];
            memset(sumCol, 0, width << 2);
            bmp->sumGraph = new int[bmp->infoHeader.image_size];
            auto *pRes = bmp->sumGraph;
            for (auto *pCur = bmp->data, *pEnd = bmp->data + bmp->infoHeader.image_size; pCur < pEnd;) {
                sumCol[0] += *(pCur++);
                *(pRes++) = sumCol[0];
                for (unsigned x = 1; x < width; ++x, ++pRes) {
                    sumCol[x] += *(pCur++);
                    *pRes = *(pRes - 1) + sumCol[x];
                }
            }
            delete[] sumCol;
        }
    }

    //sobel算子
    void bmp_file_process::sobelProcess(const bmp_file *bmp) {
        if (bmp != nullptr) {
            this->cheekBmp(bmp, 0);
            memcpy(tmp, bmp->data, bmp->infoHeader.image_size);
        } else {
            memcpy(tmp, resImg, imgSize);
        }
        auto *pGdRes = gdImg + width;
        for (auto *pCur = tmp + width, *pEnd = tmp + width * (height - 1); pCur < pEnd;) {
            ++pCur, ++pGdRes;
            for (auto *pWidthEnd = pCur + width - 2; pCur < pWidthEnd; pCur++) {
                auto lastRow = pCur - width;
                auto nextRow = pCur + width;
                int dx = *(lastRow - 1) + *(pCur - 1) * 2 + *(nextRow - 1);
                dx -= *(lastRow + 1) + *(pCur + 1) * 2 + *(nextRow + 1);
                int dy = *(lastRow - 1) + *(lastRow) * 2 + *(lastRow + 1);
                dy -= *(nextRow - 1) + *(nextRow) * 2 + *(nextRow + 1);
                *(pGdRes++) = fmin(255, abs(dx) + abs(dy));
            }
            ++pCur, ++pGdRes;
        }
    }

    //在bmp上画图 并返回一个新的bmp
    bmp_file *bmp_file_process::drawImg(const u_int &x, const u_int &y, const u_int &w, const u_int &h,
                                        const bmp_file *bmp) {
        if (bmp != nullptr) {
            this->cheekBmp(bmp, 0);
            memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        }

        // 把原图的255变成254
        for (auto *pCur = resImg, *pEnd = resImg + imgSize; pCur < pEnd; ++pCur) {
            if (*pCur == 0xff) {
                *pCur = 0xfe;
            }
        }
        // 画线框
        auto *pCur = resImg + x * width + y;
        // "_"
        for (auto *pRes = pCur, *pEnd = pRes + w; pRes < pEnd; ++pRes) {
            *pRes = 0xff;
        }
        // "| "
        for (auto *pRes = pCur, *pEnd = pRes + h * width;
             pRes < pEnd; pRes += width) {
            *pRes = 0xff;
        }
        // " |"
        for (auto *pRes = pCur + w, *pEnd = pRes + h * width;
             pRes < pEnd; pRes += width) {
            *pRes = 0xff;
        }
        // "-"
        for (auto *pRes = pCur + h * width, *pEnd = pRes + w + 1; pRes < pEnd; ++pRes) {
            *pRes = 0xff;
        }

        auto *newBmp = getResImg();

        // 伪彩色
        newBmp->palette[255].red = 255;
        newBmp->palette[255].blue = 0;
        newBmp->palette[255].green = 0;

        return newBmp;
    }

    //文本定位
    bmp_file *bmp_file_process::textPositioningByWindow(const bmp_file *bmp, const int &o_w, const int &o_h,
                                                        const int &_fast0123) {
        assert(bmp != nullptr);
        assert(-2 < _fast0123 && _fast0123 < 4);
        if (_fast0123 != -1) {
            fast0123 = _fast0123;
        }
        assert(-1 < fast0123 && fast0123 < 4);
        clock_t t_start = clock();
        //压缩
        this->compressBmp(bmp, fast0123);
        //sobel算子
        this->sobelProcess();
        bmp_file *cpsImg = this->getGdImg();
        //积分图
        this->getSumGryGraphBySumCol(cpsImg);
        int w = o_w >> fast0123;
        int h = o_h >> fast0123;
        int maxNum = 0, max_x = 0, max_y = 0;
        int w_2 = w >> 1;
        int h_2 = h >> 1;
        for (int y = 0, end_x = width - w_2 * 3, end_y = height - h_2 * 3; y < end_y; ++y) {
//        for (int x = 0, end_x = width - w_2 * 3, end_y = height - h_2 * 3; x < end_x; ++x) {
            //按照行的顺序来 cache起作用
            for (int x = w_2; x < end_x; ++x) {
//            for (int y = 0; y < end_y; ++y) {
                // getWindowsSumGraph 为 inline函数 编译后会将函数代码展开
                int tmpSum = getWindowsSumGraph(cpsImg, x, y, w, h);
                // 阈值选取目前最大的那个矩形框
                if (tmpSum < maxNum) {
                    continue;
                }
                // 更新
                tmpSum = tmpSum - getWindowsSumGraph(cpsImg, x + w, y, w_2, h) -
                         getWindowsSumGraph(cpsImg, x - w_2, y, w_2, h) -
                         getWindowsSumGraph(cpsImg, x, y + h, w, h_2);
                if (maxNum < tmpSum) {
                    maxNum = tmpSum;
                    max_x = x;
                    max_y = y;
                }
            }
        }
        max_x <<= fast0123;
        max_y <<= fast0123;
        delete cpsImg;
        clock_t t_end = clock();
        std::cout << (t_end - t_start) / 1000.0 << std::endl;
        return drawImg(max_y, max_x, o_h, o_w, bmp);
    }

    /// 获取任意窗口大小的积分 inline函数 使用时展开
    inline int bmp_file_process::getWindowsSumGraph(const bmp_file *bmp, const int &s_x, const int &s_y,
                                                    const int &x_len, const int &y_len) {
        assert(bmp != nullptr && bmp->sumGraph != nullptr);
        auto *p_s = bmp->sumGraph + (s_y * width) + s_x;
        auto *p_s_top = p_s + y_len * width;
        auto *p_s_right = p_s + x_len;
        auto *p_e = p_s_top + x_len;
        if (s_x == -1 && s_y == -1) {
            return *p_e;
        } else if (s_x == -1) {
            return *p_e - *p_s_right;
        } else if (s_y == -1) {
            return *p_e - *p_s_top;
        }
        return *p_e + *p_s - *p_s_top - *p_s_right;
    }

    //Otsu方法获取阈值 分割
    int bmp_file_process::getOtsuThreshold(const bmp_file *bmp, const int &nSize) {
        //检查bmp文件是否正常（这里是面向bmp文件 而不是一个直方图）
        assert(bmp != nullptr && bmp->histogram != nullptr);
        auto *histogram = bmp->histogram;
        int threshold = 0, minInd = 0, maxInd = nSize - 1;
        int s1 = 0, s2 = 0, n1 = 0, n2 = 0, n = 0;
        double maxNum = 0.0;
        //找到最大最小的有值的下标
        while (histogram[minInd] == 0) ++minInd;
        while (histogram[maxInd] == 0) --maxInd;
        if (minInd == maxInd) return minInd;
        //初始化数据
        for (auto i = minInd; i <= maxInd; ++i) {
            s2 += histogram[i] * i;
            n2 += histogram[i];
        }
        n = n2;
        //左边加 右边减
        for (auto i = minInd; i < maxInd; ++i) {
            if (histogram[i] == 0) continue;
            int tmpNum = histogram[i];
            n1 += tmpNum;
            n2 -= tmpNum;
            tmpNum *= i;
            s1 += tmpNum;
            s2 -= tmpNum;
            double dist = s1 * 1.0 / n1 - s2 * 1.0 / n2;
            dist = dist * dist * (n1 / 1.0 / n) * (n2 / 1.0 / n);
            //最大的距离
            if (maxNum < dist) {
                maxNum = dist;
                threshold = i;
            }
        }
        return threshold + 1;
    }

    //二值化图片
    void bmp_file_process::binaryBmp(const bmp_file *bmp, const int &threshold) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        auto *pRes = resImg;
        for (auto *pCur = bmp->data, *pEnd = pCur + bmp->infoHeader.image_size;
             pCur < pEnd; ++pCur) {
            *(pRes++) = ((*pCur) >= threshold) ? 0xff : 0;
        }
    }

    //高斯滤波
    void bmp_file_process::gaussianFilter(const bmp_file *bmp, const int &sigma) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        int wSize = 3 * sigma + 1;
        auto *T = new double[wSize];
        auto *T_1 = new u_int[wSize];
        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        // 计算值
        for (int j = 0; j < wSize; ++j) {
            T[j] = calTj(j, sigma);
        }
        // 将值转为整数类型的
        unsigned M = 0;
        double minNum = T[wSize - 1];
        // 即余下的值 与 原来的值相比基本无变化
        while (1e6 * (minNum - int(minNum)) > minNum) {
            minNum *= 2;
            M++;
        }
        // 避免计算时溢出
        M = fmin(24, M);
        for (int j = 0; j < wSize; ++j) {
            T_1[j] = unsigned(T[j] * (1 << M));
        }
        // 开始计算
        for (auto *pCur = bmp->data + wSize, *pEnd = bmp->data + width * height - wSize, *pRes = resImg + wSize;
             pCur < pEnd; pCur += wSize << 1, pRes += wSize << 1) {
            auto *rowEnd = pCur + width - (wSize << 1);
            while (pCur < rowEnd) {
                unsigned sum = (*pCur * T_1[0]) >> M;
                for (unsigned x = 1; x < wSize; ++x) {
                    sum += (*(pCur + x) * T_1[x]) >> M;
                    sum += (*(pCur - x) * T_1[x]) >> M;
                }
                *(pRes++) = sum;
                pCur++;
            }
        }
        // 转一下
        auto *resData2 = tmp;
        for (unsigned y = 0; y < height; ++y) {
            for (unsigned x = 0; x < width; ++x) {
                *((resData2 + x * height) + y) = *((resImg + y * width) + x);
            }
        }
        // 重新计算resData
        memcpy(resImg, tmp, bmp->infoHeader.image_size);
        // 开始计算
        for (auto *pCur = resImg + wSize, *pEnd = resImg + width * height - wSize, *pRes = resData2 + wSize;
             pCur < pEnd; pCur += wSize << 1, pRes += wSize << 1) {
            auto *rowEnd = pCur + height - (wSize << 1);
            while (pCur < rowEnd) {
                unsigned sum = (*pCur * T_1[0]) >> M;
                for (unsigned x = 1; x < wSize; ++x) {
                    sum += (*(pCur + x) * T_1[x]) >> M;
                    sum += (*(pCur - x) * T_1[x]) >> M;
                }
                *(pRes++) = sum;
                pCur++;
            }
        }
        // 再转回去
        for (unsigned y = 0; y < width; ++y) {
            for (unsigned x = 0; x < height; ++x) {
                *((resImg + x * width) + y) = *((resData2 + y * height) + x);
            }
        }

        delete[] T;
        delete[] T_1;
    }

    //两个bmp相减
    void bmp_file_process::subBmp(const bmp_file *b1, const bmp_file *b2) {
        assert(b1 != nullptr && b2 != nullptr && b1->infoHeader.image_size == b2->infoHeader.image_size);
        this->cheekBmp(b1);
        for (auto *pRes = resImg, *pB1 = b1->data, *pB2 = b2->data, *pB1End = pB1 + b1->infoHeader.image_size;
             pB1 < pB1End; ++pB1, ++pB2) {
            *(pRes++) = (*pB1 > *pB2) ? (*pB1 - *pB2) : 0;
        }
    }

    //均值滤波
    void bmp_file_process::avrFilterByGraph(const bmp_file *bmp, int M, int N) {
        assert(bmp != nullptr && bmp->sumGraph != nullptr);
        this->cheekBmp(bmp, 0);
        // 窗口 M列 N行
        int half_x = M >> 1;
        int half_y = N >> 1;
        M = (half_x << 1) | 0x0001;
        N = (half_y << 1) | 0x0001;
        int C = (1 << 20) / (M * N);

        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        // 进行滤波 跳过边缘的处理
        auto *pRes = resImg + half_y * width;
        // +1 是确保 算sum的公式为正确的（4个值），否则应该为一个值或者两个值 但这样会少处理一行一列像素
        for (int y = half_y, end_y = height - half_y, end_x = width - half_x - 1; y < end_y; ++y) {
            pRes += half_x;
            for (int x = half_x; x < end_x; ++x) {
                int sum = getWindowsSumGraph(bmp, x - half_x, y - half_y, M, N);
                *(pRes++) = (sum * C) >> 20;
//                *(pRes++) = sum / M / N;
            }
            pRes += half_x + 1;
        }
    }

    //k均值聚类
    void bmp_file_process::kMeansBmp(const bmp_file *bmp, const int &nClass, double *center) {
        assert(bmp != nullptr && bmp->histogram != nullptr);
        this->cheekBmp(bmp, 0);
        int minInd = 0, maxInd = 256;
        //找到最大最小的有值的下标
        while (bmp->histogram[minInd] == 0) ++minInd;
        while (bmp->histogram[maxInd] == 0) --maxInd;
        auto *num = new double[nClass];
        auto *sum = new double[nClass];
        auto *center_pre = new double[nClass];
        center[0] = minInd;
        int step = (maxInd - minInd) / (nClass - 1);
        //初始化聚类中心
        for (int i = 1; i < nClass; ++i) {
            center[i] = center[i - 1] + step;
        }
        bool canContinue = true;
        for (int cnt = 1 << 10; cnt > 0 && canContinue; --cnt) {
            canContinue = false;
            //初始化数据
            memset(num, 0, sizeof(double) * nClass);
            memset(sum, 0, sizeof(double) * nClass);
            memcpy(center_pre, center, sizeof(double) * nClass);
            //分配点
            for (int i = minInd; i <= maxInd; ++i) {
                if (bmp->histogram[i] != 0) {
                    //找到i最近的那一类
                    int minDist = 256, type = 0;
                    for (int j = 0; j < nClass; ++j) {
                        int dist = fabs(i - center[j]);
                        if (minDist > dist) {
                            minDist = dist;
                            type = j;
                        }
                    }
                    num[type] += bmp->histogram[i];
                    sum[type] += bmp->histogram[i] * i;
                    center[type] = sum[type] / num[type];
                }
            }
            for (int i = 0; i < nClass; ++i) {
                if (fabs(center[i] - center_pre[i]) > 0.01) {
                    canContinue = true;
                    break;
                }
            }
        }
    }

    //求两个bmp的方差
    int bmp_file_process::varianceBmp(const bmp_file *b1, const bmp_file *b2) {
        assert(b1 != nullptr && b2 != nullptr && b1->infoHeader.image_size == b2->infoHeader.image_size);
        this->cheekBmp(b1);
        int sumVal = 0;
        for (auto *pB1 = b1->data, *pB2 = b2->data, *pB1End = pB1 + b1->infoHeader.image_size;
             pB1 < pB1End; ++pB1, ++pB2) {
            sumVal += (*pB1 - *pB2) * (*pB1 - *pB2);
        }
        return sumVal;
    }

    //画一条线
    bmp_file *
    bmp_file_process::drawPicALine(const bmp_file *bmp, const double &pk, const double &pb, int color, bool isYKX) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        u_char redVal = (color & 0xff0000) >> 16;
        u_char greenVal = (color & 0x00ff00) >> 8;
        u_char blueVal = (color & 0x0000ff);
        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        if (isRgb) {
            //rgb图
            if (isYKX) {
                //如果是x = ky + b
                for (int y = 0; y < height; ++y) {
                    long x = lround(pk * y + pb);
                    if (x >= 0 && x < width) {
                        auto *pCur = resImg + y * width * 3 + x * 3;
                        *(pCur) = blueVal;
                        *(pCur + 1) = greenVal;
                        *(pCur + 2) = redVal;
                    }
                }
            } else {
                //如果是y = kx + b
                for (int x = 0; x < width; ++x) {
                    long y = lround(pk * x + pb);
                    if ((y >= 0) && (y < height)) {
                        auto *pCur = resImg + y * width * 3 + x * 3;
                        *(pCur) = blueVal;
                        *(pCur + 1) = greenVal;
                        *(pCur + 2) = redVal;
                    }
                }
            }
            bmp_file *re = b->getResImg();
            return re;
        } else {
            //gray图
            //把原来的255去掉
//            for (auto *pCur = resImg, *pEnd = pCur + bmp->infoHeader.image_size; pCur < pEnd; ++pCur) {
//                if (*pCur == 0xff) {
//                    --(*pCur);
//                }
//            }
            if (isYKX) {
                //如果是x = ky + b
                for (int y = 0; y < height; ++y) {
                    long x = lround(pk * y + pb);
                    if (x >= 0 && x < width) {
                        *(resImg + y * width + x) = 0xff;
                    }
                }
            } else {
                //如果是y = kx + b
                for (int x = 0; x < width; ++x) {
                    long y = lround(pk * x + pb);
                    if ((y >= 0) && (y < height)) {
                        *(resImg + y * width + x) = 0xff;
                    }
                }
            }
            bmp_file *re = b->getResImg();
            re->palette[255].red = redVal;
            re->palette[255].green = greenVal;
            re->palette[255].blue = blueVal;
            return re;
        }
    }

    //画一个圆
    bmp_file *
    bmp_file_process::drawPicACircle(const bmp_file *bmp, const int &px, const int &py, const double &radius,
                                     int color) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        u_char redVal = (color & 0xff0000) >> 16;
        u_char greenVal = (color & 0x00ff00) >> 8;
        u_char blueVal = (color & 0x0000ff);
        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        double A2R = M_PI / 180;
        double step = 20 / radius;
        step > 1 && (step = 1.0);
        if (isRgb) {
            for (double i = 0; i < 360.0; i += step) {
                int tx = int(px + radius * cos(i * A2R));
                int ty = int(py + radius * sin(i * A2R));
                if (tx < 0 || ty < 0) {
                    continue;
                }
                auto *pCur = resImg + ty * width * 3 + tx * 3;
                *(pCur) = blueVal;
                *(pCur + 1) = greenVal;
                *(pCur + 2) = redVal;
            }
            //rgb图
            bmp_file *re = b->getResImg();
            return re;
        } else {
            //gray图
            //把原来的255去掉
            for (auto *pCur = resImg, *pEnd = pCur + bmp->infoHeader.image_size; pCur < pEnd; ++pCur) {
                if (*pCur == 0xff) {
                    --(*pCur);
                }
            }
            for (double i = 0; i < 360.0; i += step) {
                int tx = int(px + radius * cos(i * A2R));
                int ty = int(py + radius * sin(i * A2R));
                if (tx < 0 || ty < 0) {
                    continue;
                }
                auto *pCur = resImg + ty * width + tx;
                *pCur = 0xff;
            }
            bmp_file *re = b->getResImg();
            re->palette[255].red = redVal;
            re->palette[255].green = greenVal;
            re->palette[255].blue = blueVal;
            return re;
        }
    }

    //画一个圆的数据 分治显示用
    bmp_file *bmp_file_process::drawCircleDataImg(const bmp_file *bmp, const int *pArr, const bool &isX, int color) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        u_char redVal = (color & 0xff0000) >> 16;
        u_char greenVal = (color & 0x00ff00) >> 8;
        u_char blueVal = (color & 0x0000ff);
        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        if (isRgb) {
            if (isX) {
                for (int x = 0; x < width; ++x) {
                    for (int y = 0, end_y = pArr[x]; y < end_y; ++y) {
                        auto *pCur = resImg + y * height * 3 + x * 3;
                        *(pCur) = blueVal;
                        *(pCur + 1) = greenVal;
                        *(pCur + 2) = redVal;
                    }
                }
            } else {
                for (int y = 0; y < height; ++y) {
                    for (int x = 0, end_x = pArr[y]; x < end_x; ++x) {
                        auto *pCur = resImg + y * height * 3 + x * 3;
                        *(pCur) = blueVal;
                        *(pCur + 1) = greenVal;
                        *(pCur + 2) = redVal;
                    }
                }
            }
            bmp_file *re = b->getResImg();
            return re;
        } else {
            //gray图
            //把原来的255去掉
//            for (auto *pCur = resImg, *pEnd = pCur + bmp->infoHeader.image_size; pCur < pEnd; ++pCur) {
//                if (*pCur == 0xff) {
//                    --(*pCur);
//                }
//            }
            if (isX) {
                for (int x = 0; x < width; ++x) {
                    for (int y = 0, end_y = pArr[x]; y < end_y; ++y) {
                        *(resImg + y * height + x) = 0xff;
                    }
                }
            } else {
                for (int y = 0; y < height; ++y) {
                    for (int x = 0, end_x = pArr[y]; x < end_x; ++x) {
                        *(resImg + y * height + x) = 0xff;
                    }
                }
            }
            bmp_file *re = b->getResImg();
            re->palette[255].red = redVal;
            re->palette[255].green = greenVal;
            re->palette[255].blue = blueVal;
            return re;
        }
    }

    //给定两个点 返回k b 和 isYKX
    void bmp_file_process::getKBBy2Point(const int &x1, const int &y1, const int &x2, const int &y2, double &pk,
                                         double &pb, bool &isYKX) {
        if (abs(y1 - y2) > abs(x1 - x2)) {
            isYKX = true;
            pk = (x1 - x2) * 1.0 / (y1 - y2);
            pb = ((x1 + x2) - pk * (y1 + y2)) / 2;
        } else {
            isYKX = false;
            pk = (y1 - y2) * 1.0 / (x1 - x2);
            pb = ((y1 + y2) - pk * (x1 + x2)) / 2;
        }
    }

    //给定 k b isYKX返回 rou(+/-) sita
    void bmp_file_process::getRouSitaByKB(const double &pk, const double &pb, const bool &isYKX,
                                          double &rou, double &sita) {
        double yVal;
        double xVal;
        // 特殊处理
        if (isYKX) {
            // x = ky + b
            if (abs(pk) < 1e-6) {
                // 与x轴交点的地方就是 rou
                rou = pb;
                sita = 0.0;
                return;
            } else {
                if (abs(pb) < 1e-6) {
                    rou = 0;
                    double angle = atan(1.0 / pk);
                    sita = M_PI / 2 + angle;
                    return;
                } else {
                    xVal = pb;
                    yVal = -pb / pk;
                }
            }
        } else {
            // y = kx + b
            if (abs(pk) < 1e-6) {
                // 与y轴交点的地方就是 rou
                rou = pb;
                sita = M_PI / 2;
                return;
            } else {
                if (abs(pb) < 1e-6) {
                    rou = 0;
                    double angle = atan(pk);
                    sita = M_PI / 2 + angle;
                    return;
                } else {
                    // 获得和 x 轴 y轴 交点
                    xVal = -pb / pk;
                    yVal = pb;
                }
            }
        }
        //获得与x/y轴相交的两个点之后
        rou = abs(pb) / sqrt(pk * pk + 1);
        if (xVal > 0 && yVal > 0) {
            sita = atan(xVal / yVal);
        } else if (xVal > 0 && yVal < 0) {
            sita = M_PI / 2 + atan(-yVal / xVal);
            rou = -rou;
        } else if (xVal < 0 && yVal < 0) {
            sita = atan(xVal / yVal);
            rou = -rou;
        } else if (xVal < 0 && yVal > 0) {
            sita = M_PI / 2 + atan(yVal / -xVal);
        }
    }

    ///给定 rou(+/-) sita 返回 k b isYKX
    void bmp_file_process::getKBByRouSita(const double &rou, const double &sita,
                                          double &pk, double &pb, bool &isYKX) {
        assert(0.0 <= sita && sita < M_PI);
        //sita = 0
        if (sita < 1e-6) {
            isYKX = true;
            pk = 0;
            pb = rou;
            return;
        }
        // sita = pi/2
        if (abs(sita - M_PI / 2) < 1e-6) {
            isYKX = false;
            pk = 0;
            pb = rou;
            return;
        }
        if (sita > M_PI * 3 / 4 || sita < M_PI / 4) {
            isYKX = true;
            pk = tan(M_PI - sita);
            // 求与x轴交点
            pb = rou / cos(sita);
        } else {
            isYKX = false;
            pk = tan(sita - M_PI / 2);
            // 求与y轴交点
            pb = rou / sin(sita);
        }
    }

    //hough变换
    //给定bmp sita[0,180) ,rou 构造的数组 总长度 step 点x坐标 y坐标 以及值
    //必须满足 len % 360 == 0
    //修改 数组数据
    void bmp_file_process::houghLine(int *arr, const int &length, const int &step, const int &pNum,
                                     const int *xArr, const int *yArr, const int *pValArr) {
        assert(length % 360 == 0);
        memset(arr, 0, length * sizeof(int));
        int maxRou = length / 360;
        double A2R = M_PI / 180.0;
        if (pValArr == nullptr) {
            for (int theta = 0; theta < 180; theta += step) {
                auto *pCenter = arr + maxRou * 2 * theta + maxRou;
                int cosVal = int(cos(theta * A2R) * (1 << 13));
                int sinVal = int(sin(theta * A2R) * (1 << 13));
                for (int i = 0; i < pNum; ++i) {
                    int rou = ((xArr[i] * cosVal + yArr[i] * sinVal) >> 13);
                    *(pCenter + rou) += 1;
                }
            }
        } else {
            for (int theta = 0; theta < 180; theta += step) {
                auto *pCenter = arr + maxRou * 2 * theta + maxRou;
                int cosVal = int(cos(theta * A2R) * (1 << 13));
                int sinVal = int(sin(theta * A2R) * (1 << 13));
                for (int i = 0; i < pNum; ++i) {
                    int rou = ((xArr[i] * cosVal + yArr[i] * sinVal) >> 13);
                    //此处 不是+1 而是加一个梯度值（加权）
                    *(pCenter + rou) += pValArr[i];
                }
            }
        }
    }

    bmp_file *bmp_file_process::houghLineFind1(const bmp_file *bmp, int color) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        //保存用来查找线的点
        int maxPNum = ((width > height ? width : height) << 2);
        auto *xArr = new int[maxPNum];
        auto *yArr = new int[maxPNum];
        //计算需要的点
        int pNum = 0;
        for (int y = 0; y < height; ++y) {
            int lastPNum = pNum;
            //从左到右
            for (int x = 0; x < width; ++x) {
                if (*(resImg + y * width + x) == 0) {
                    xArr[pNum] = x;
                    yArr[pNum] = y;
                    ++pNum;
                    break;
                }
            }
            //从右到左
            if (lastPNum != pNum) {
                for (int x = width - 1, end_x = xArr[lastPNum]; x >= end_x; --x) {
                    if (*(resImg + y * width + x) == 0) {
                        xArr[pNum] = x;
                        yArr[pNum] = y;
                        ++pNum;
                        break;
                    }
                }
            }
        }
        for (int x = 0; x < width; ++x) {
            //从下往上
            int lastPNum = pNum;
            for (int y = 0; y < height; ++y) {
                if (*(resImg + y * width + x) == 0) {
                    xArr[pNum] = x;
                    yArr[pNum] = y;
                    ++pNum;
                    break;
                }
            }
            //从上到下
            if (lastPNum != pNum) {
                for (int y = height - 1, end_y = yArr[lastPNum]; y > end_y; --y) {
                    if (*(resImg + y * width + x) == 0) {
                        xArr[pNum] = x;
                        yArr[pNum] = y;
                        ++pNum;
                        break;
                    }
                }
            }
        }
/*
        //画出找到的边界图
        bmp_file *b1 = this->createBmp(width, height, this->GRY_MODE);
        auto *b1Cur = b1->data;
        for (int i = 0; i < pNum; ++i) {
            *(b1Cur + yArr[i] * width + xArr[i]) = 0xff;
        }
        this->invertBmp(b1);
        return this->getResImg();
*/

        int maxRou = int(sqrt(width * width + height * height) + 2);
        int length = maxRou * 2 * 180;
        int *arr = new int[length];
        int step = 1;
        this->houghLine(arr, length, step, pNum, xArr, yArr);
        delete[] xArr;
        delete[] yArr;
        xArr = nullptr;
        yArr = nullptr;

/*        //画出sita 和 rou的大小图
        bmp_file *b1 = this->createBmp(maxRou * 2, 200, this->GRY_MODE);
        auto *b1Cur = b1->data;
        for (int i = 0; i < 180; ++i) {
            for (int rou = 0, end_rou = maxRou * 2; rou < end_rou; ++rou, ++pCur) {
                if((i==90 && rou<maxRou)||rou==maxRou){
                    *(b1Cur + (i+10) * end_rou + rou) = 0xff;
                    continue;
                }
                if (*pCur < 255/3) {
                    *(b1Cur + (i+10) * end_rou + rou) = (*pCur)*3;
                } else {
                    *(b1Cur + (i+10) * end_rou + rou) = 0xff;
                }
            }
        }
        return b1;*/

        int bestSita[4], bestRou[4], bestNum[4];
        memset(bestSita, 0, sizeof(int) * 4);
        memset(bestRou, 0, sizeof(int) * 4);
        memset(bestNum, 0, sizeof(int) * 4);
/*
        //一次性找4条边 方法1 一条一条找 找四个最亮的
        for (int times = 0; times < 4; ++times) {
            int *pCur = arr;
            //对比4次 找到最大的后 修改为0
            for (int i = 0; i < 180; ++i) {
                for (int rou = 0, end_rou = maxRou * 2; rou < end_rou; ++rou, ++pCur) {
                    if (*pCur > bestNum[times]) {
                        bestNum[times] = *pCur;
                        bestRou[times] = rou;
                        bestSita[times] = i;
                    }
                }
            }
            //找到之后 置为0 并且把领域内的也置为0 鲁棒性
            //trick处理
            for (int i = -3; i < 4; ++i) {
                // 可能越界 处理
                int h1 = (bestSita[times] + i + 180) % 180;
                for (int rou = -30; rou < 30; ++rou) {
                    int w1 = bestRou[times] + rou;
                    if (w1 < 0 || w1 > maxRou * 2) {
                        continue;
                    }
                    *(arr + h1 * maxRou * 2 + w1) = 0;
                }
            }
//            std::cout << bestNum[times] << " " << bestSita[times] << " " << bestRou[times] << std::endl;
        }
*/


        // 一次性找4条边 方法2 四条一起找
        // 抖动参数为 sita(90) +- 5   rou(230) +- 20
        int tmpMaxNum = 0;
        int sitaOff = 90;
        int rouOff = 232;
        int tsOff = 2;
        int trOff = 10;
        int *pCur = arr;
        //对比4次 找到最大的后 修改为0
        for (int i = 0; i < 180 - sitaOff; ++i) {
            for (int rou = 0, end_rou = maxRou * 2; rou < end_rou; ++rou, ++pCur) {
                bestNum[0] = *pCur;
                for (int ts = -tsOff; ts < tsOff; ++ts) {
                    // sita 抖动 +- 5
                    int h1 = (i + 180 + ts) % 180;
                    // sita 偏移90 +- 5
                    int h2 = (i + 180 + ts + sitaOff) % 180;

                    for (int tr = -trOff; tr < trOff; ++tr) {
                        int w1 = rou + ts;
                        if (w1 < 0 || w1 > maxRou * 2) {
                            continue;
                        }
                        int w2 = rou + ts + rouOff;
                        if (w2 < 0 || w2 > maxRou * 2) {
                            continue;
                        }
                        bestNum[1] = *(arr + h1 * maxRou * 2 + w2);
                        bestNum[2] = *(arr + h2 * maxRou * 2 + w1);
                        bestNum[3] = *(arr + h2 * maxRou * 2 + w2);
                        if (bestNum[0] + bestNum[1] + bestNum[2] + bestNum[3] > tmpMaxNum) {
                            bestRou[0] = rou;
                            bestSita[0] = i;
                            //右边点
                            bestSita[1] = h1;
                            bestRou[1] = w2;
                            //上边点
                            bestSita[2] = h2;
                            bestRou[2] = w1;
                            //右上点
                            bestSita[3] = h2;
                            bestRou[3] = w2;
                            tmpMaxNum = bestNum[0] + bestNum[1] + bestNum[2] + bestNum[3];
                        }
                    }
                }
            }
        }
        delete[] arr;

        //拷贝一份bmp
        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        //清除原来的255
        for (auto *pCur = resImg, *pEnd = pCur + bmp->infoHeader.image_size; pCur < pEnd; ++pCur) {
            if (*pCur == 0xff) {
                --(*pCur);
            }
        }
        bmp_file *b2 = this->getResImg();

        for (int i = 0; i < 4; ++i) {
            //开始画线 4条
            int bestRou2 = bestRou[i] - maxRou;
            double bestSita2 = bestSita[i] * M_PI / 180;
            double pk, pb;
            bool isYKX;
            this->getKBByRouSita(bestRou2, bestSita2, pk, pb, isYKX);

            bmp_file *b3 = this->drawPicALine(b2, pk, pb, color, isYKX);
            delete b2;
            b2 = b3;
            std::cout << "theta= " << bestSita2 / M_PI * 180 << "度   thro= " << bestRou2 << std::endl;
            if (isYKX) {
                std::cout << "x = " << (abs(pk) < 1e-6 ? "" : std::to_string(pk) + "y") << " " << (pb >= 0 ? "+" : "")
                          << pb << std::endl;
            } else {
                std::cout << "y = " << (abs(pk) < 1e-6 ? "" : std::to_string(pk) + "x") << " " << (pb >= 0 ? "+" : "")
                          << pb << std::endl;
            }
            std::cout << std::endl;
        }
        return b2;
    }

    //hough 变换应用 找一个圆框出来 并画图
    bmp_file *bmp_file_process::houghLineFind2(const bmp_file *bmp, int color) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);
        //保存用来查找线的点
        int maxPNum = ((width > height ? width : height) << 2);
        auto *xArr = new int[maxPNum];
        auto *yArr = new int[maxPNum];
        auto *xValArr = new int[width];
        auto *yValArr = new int[height];
        auto *rValArr = new int[maxPNum >> 2];
        memset(xValArr, 0, sizeof(int) * width);
        memset(yValArr, 0, sizeof(int) * height);
        memset(rValArr, 0, sizeof(int) * (maxPNum >> 2));
        //计算需要的点
        int pNum = 0;
        for (int y = 0; y < height; ++y) {
            int lastPNum = pNum;
            //从左到右
            for (int x = 0; x < width; ++x) {
                if (*(resImg + y * width + x) == 0) {
                    xArr[pNum] = x;
                    yArr[pNum] = y;
                    ++pNum;
                    break;
                }
            }
            //从右到左
            if (lastPNum != pNum) {
                for (int x = width - 1, end_x = xArr[lastPNum]; x >= end_x; --x) {
                    if (*(resImg + y * width + x) == 0) {
                        xArr[pNum] = x;
                        yArr[pNum] = y;
                        ++pNum;
                        break;
                    }
                }
                xValArr[(xArr[pNum - 1] + xArr[pNum - 2] + 1) / 2]++;
            }
        }
        for (int x = 0; x < width; ++x) {
            //从下往上
            int lastPNum = pNum;
            for (int y = 0; y < height; ++y) {
                if (*(resImg + y * width + x) == 0) {
                    xArr[pNum] = x;
                    yArr[pNum] = y;
                    ++pNum;
                    break;
                }
            }
            //从上到下
            if (lastPNum != pNum) {
                for (int y = height - 1, end_y = yArr[lastPNum]; y > end_y; --y) {
                    if (*(resImg + y * width + x) == 0) {
                        xArr[pNum] = x;
                        yArr[pNum] = y;
                        ++pNum;
                        break;
                    }
                }
                yValArr[(yArr[pNum - 1] + yArr[pNum - 2] + 1) / 2]++;
            }
        }
/*
        //画出找到的边界图
        bmp_file *b1 = this->createBmp(width, height, this->GRY_MODE);
        auto *b1Cur = b1->data;
        for (int i = 0; i < pNum; ++i) {
            *(b1Cur + yArr[i] * width + xArr[i]) = 0xff;
        }
        this->invertBmp(b1);
        auto *b2 = this->getResImg();
        for (auto *pCur = b2->data, *pEnd = pCur + b2->infoHeader.image_size; pCur < pEnd; ++pCur) {
            if (*pCur == 0xff) {
                --(*pCur);
            }
        }
        auto *b3 = this->drawCircleDataImg(b2, xValArr, true, color);
        return this->drawCircleDataImg(b3,yValArr, false,color);
*/
        //找到圆心
        int cx = 0, cy = 0, tmpMaxNum = 0;
        for (int x = 0; x < width; ++x) {
            if (xValArr[x] > tmpMaxNum) {
                tmpMaxNum = xValArr[x];
                cx = x;
            }
        }
        tmpMaxNum = 0;
        for (int y = 0; y < height; ++y) {
            if (yValArr[y] > tmpMaxNum) {
                tmpMaxNum = yValArr[y];
                cy = y;
            }
        }
        //找到半径
        for (int i = 0; i < pNum; ++i) {
            int tmpX = xArr[i] - cx;
            int tmpY = yArr[i] - cy;
            int tmpR = std::sqrt(tmpX * tmpX + tmpY * tmpY);
            rValArr[tmpR]++;
        }
        int cr = 0;
        tmpMaxNum = 0;
        for (int i = 0, end_i = maxPNum >> 2; i < end_i; ++i) {
            if (rValArr[i] > tmpMaxNum) {
                tmpMaxNum = rValArr[i];
                cr = i;
            }
        }
        std::cout << "圆心 x= " << cx << "   y= " << cy << "   r= " << cr << std::endl;
        return drawPicACircle(bmp, cx, cy, cr, color);

    }

    int bmp_file_process::traceContour(const int &x0, const int &y0, const bool &isOuter, u_char *pChainCode,
                                       const int &maxChainCodeNum) {
        static int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
        static int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
        static int initCode[8] = {7, 7, 1, 1, 3, 3, 5, 5};
        //地址偏移量
        int dADD[8];

        auto *pBegin = tmp + y0 * width + x0, *pCur = pBegin, *pTest = pCur;
        int code = 0, beginCode, returnCode, N = 0;
        //1.初始化
        //不同链码对应的地址偏移量
        for (code = 0; code < 8; code++) {
            dADD[code] = dy[code] * width + dx[code];
        }
        if (isOuter) {
            //外轮廓时的初始化
            *(pCur - 1) = 1;
            code = 7;
        } else {
            //内轮廓时的初始化
            *(pCur + 1) = 1;
            code = 3;
        }
        //从起点检查的第一个链码
        beginCode = initCode[code];
        int i = 0;
        do {
            //轮廓点,标记为灰度值254
            *pCur = 254;
            for (i = 0, code = initCode[code]; i < 7; ++i, code = (code + 1) % 8) {
                pTest = pCur + dADD[code];
                if (*pTest < 2) {
                    //背景点 标记为1
                    *pTest = 1;
                } else {
                    //轮廓点
                    if (N < maxChainCodeNum) {
                        //保存链码
                        pChainCode[N++] = code;
                    }
                    if (pTest == pBegin) {
                        //回到起点
                        returnCode = (code + 4) % 8;
                        i = (beginCode < returnCode) ? (returnCode - beginCode) : (returnCode + 8 - beginCode);
                        code = (returnCode + 1) % 8;
                        for (; i < 7; ++i, code = (code + 1) % 8) {
                            pTest = pBegin + dADD[code];
                            if (*pTest < 2) {
                                //背景点 标记为1
                                *pTest = 1;
                            } else {
                                if (N < maxChainCodeNum) {
                                    //保存链码
                                    pChainCode[N++] = code;
                                }
                                //从起点开始,找到了新的轮廓点pTest
                                break;
                            }
                        }
                    }
                    //找到了新的轮廓点
                    break;
                }
            }
            pCur = pTest;
        } while (i < 7);
        return N;
    }

    int bmp_file_process::contourPixels(const u_char *pChainCode, const int &n) {
        static int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
        static int typeLUT[8][8] = {1, 1, 1, 3, 3, 2, 2, 1,//0
                                    1, 1, 1, 3, 3, 3, 2, 1,//1
                                    2, 2, 2, 0, 0, 0, 0, 2,//2
                                    2, 2, 2, 0, 0, 0, 0, 3,//3
                                    3, 2, 2, 0, 0, 0, 0, 3,//4
                                    3, 3, 2, 0, 0, 0, 0, 3,//5
                                    1, 1, 1, 2, 2, 2, 2, 1,//6
                                    1, 1, 1, 3, 2, 2, 2, 1 //7
        };
        int i, ci_1, ci, type, yi;
        int num = 0;

        num = 0;
        yi = 0; //随意假定一个初值即可,因为面积与起点无关
        ci_1 = pChainCode[n - 1]; //起点的进入链码(即最末尾的链码)
        for (i = 0; i < n; i++) {
            ci = pChainCode[i]; //出发链码
            type = typeLUT[ci_1][ci]; //轮廓点类型
            if (type == 0) num -= yi;
            else if (type == 1) num += yi + 1;
            else if (type == 3) num += 1;
            yi += dy[ci]; //下一个轮廓点的坐标
            ci_1 = ci; //下一个轮廓点的进入链码
        }
        return abs(num); //在轮廓逆时针走向时为正,顺时针走向时为负,所以取绝对值
    }

    void bmp_file_process::contourRect(int x0, int y0,
                                       const u_char *pCode, int N,
                                       int &x1, int &x2, int &y1, int &y2) {
        static int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
        static int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
        int i;

        y1 = y2 = y0;
        x1 = x2 = x0;
        for (i = 0; i < N - 1; i++) {
            x0 = x0 + dx[pCode[i]];
            y0 = y0 + dy[pCode[i]];

            if (x0 > x2) x2 = x0;
            else if (x0 < x1) x1 = x0;

            if (y0 > y2) y2 = y0;
            else if (y0 < y1) y1 = y0;
        }
    }

    void bmp_file_process::drawContour(const int &x0, const int &y0,
                                       const u_char *pChainCode, const int &N, const u_char &color) {
        static int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
        static int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
        int dADD[8];
        //不同链码对应的地址偏移量
        for (int i = 0; i < 8; ++i) {
            dADD[i] = dy[i] * width + dx[i];
        }
        auto *pCur = resImg + y0 * width + x0;
        for (int i = 0; i < N; ++i) {
            *pCur = color;
            pCur += dADD[pChainCode[i]];
        }
    }

    void bmp_file_process::fillContour(const int &x0, const int &y0, const bool &isOuter, const u_char *pChainCode,
                                       const int &N, const u_char &color) {
        static int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
        static int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
        auto *tmpArr = new char[width * height];
        memset(tmpArr, 0, width * height);
        int dADD[8];
        //不同链码对应的地址偏移量
        for (int i = 0; i < 8; ++i) {
            dADD[i] = dy[i] * width + dx[i];
        }
        //计算轮廓点是起点还是终点
        auto *pBegin = resImg + y0 * width + x0;
        //用来存是否是起点终点
        auto *pTmpBegin = tmpArr + y0 * width + x0;
        //赋值
        auto *pTmpCur = pTmpBegin;
        for (int i = 0, inCode = pChainCode[N - 1]; i < N; ++i) {
            int outCode = pChainCode[i];
            *pTmpCur = dy[inCode] + dy[outCode];
            inCode = outCode;
            pTmpCur += dADD[outCode];
        }
        //上色
        int direction = isOuter ? 1 : -1;
        pTmpCur = pTmpBegin;
        auto *pCur = pBegin;
        for (int i = 0; i < N; ++i) {
            if (*pTmpCur > 0) {
                auto *t1 = pTmpCur;
                auto *t2 = pCur;
                while (*t1 >= 0) {
                    *t2 = color;
                    t2 += direction;
                    t1 += direction;
                }
                *t2 = color;
                //避免重复
                *pTmpCur = 0;
            } else if (*pTmpCur == 0) {
                *pCur = color;
            }

            pTmpCur += dADD[pChainCode[i]];
            pCur += dADD[pChainCode[i]];
        }
        delete[] tmpArr;
    }

    //应用 找到米边界 并画出来
    bmp_file *bmp_file_process::traceRice(const bmp_file *bmp, int color) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        const auto &bmp_size = bmp->infoHeader.image_size;
        auto *pChainCode = new u_char[bmp_size];
        //目标图片
        memset(resImg, 0, bmp_size);
        //原始图片
        memcpy(tmp, bmp->data, bmp_size);
        //对原始图片边框赋值0 为了避免跟踪时的超界检测,首先将图像边框赋0
        {
            auto *pCur = tmp, *pEnd = pCur + bmp_size;
            memset(pCur, 0, width);
            memset(pCur + width * (height - 1), 0, width);
            while (pCur < pEnd) {
                *pCur = 0;
                *(pCur + width - 1) = 0;
                pCur += width;
            }
        }
        //从上向下,从左向右扫描图像，寻找新的轮廓
        auto *pCur = tmp + width;
        for (int y = 1, end_y = height - 1, end_x = width - 1; y < end_y; ++y) {
            //跳过左侧点
            ++pCur;
            // 轮廓点数量
            int n = 0;
            for (int x = 1; x < end_x; ++x, ++pCur) {
                if ((*pCur) == 0xff && (*(pCur - 1) <= 1)) {
                    //发现外轮廓
                    n = this->traceContour(x, y, true, pChainCode, bmp_size);
                    int s = this->contourPixels(pChainCode, n);
                    int x1, y1, x2, y2;
                    this->contourRect(x, y, pChainCode, n, x1, x2, y1, y2);
                    if ((x1 > 1) && (y1 > 1) && (x2 < width - 2) && (y2 < height - 2) && //去掉贴边者
                        (s > 200) && //去掉残缺者
                        (s < 400) //去掉粘连者
                            ) {
                        this->fillContour(x, y, true, pChainCode, n, 255);
                    }
                    this->drawContour(x, y, pChainCode, n, 254);

//                    std::cout << "测试序列：{ ";
//                    for (int ti = 0; ti < n; ++ti) {
//                        std::cout << int(pChainCode[ti]) << " ";
//                    }
//                    std::cout << "}" << std::endl;
//                    std::cout << ((this->isClockwise(pChainCode, n)) ? "顺时针" : "逆时针")<<std::endl;

                } else if ((*pCur == 0) && (*(pCur - 1) >= 254)) {
                    //发现内轮廓
                    n = this->traceContour(x - 1, y, false, pChainCode, bmp_size);
                    this->drawContour(x, y, pChainCode, n, 254);

//                    std::cout << "测试序列：{ ";
//                    for (int ti = 0; ti < n; ++ti) {
//                        std::cout << int(pChainCode[ti]) << " ";
//                    }
//                    std::cout << "}" << std::endl;
//                    std::cout << ((this->isClockwise(pChainCode, n)) ? "顺时针" : "逆时针")<<std::endl;
                }
            }
            //跳过右侧点
            ++pCur;
        }
        bmp_file *b1 = this->getResImg();
        b1->palette[255].green = b1->palette[255].blue = 0;
        b1->palette[254].red = b1->palette[254].blue = 0;
        return b1;
    }

    bool bmp_file_process::isClockwise(const u_char *pChainCode, const int &N) {
        static int angleLUT[8][8] = {
                0, 45, 90, 135, 0, -135, -90, -45,
                -45, 0, 45, 90, 135, 0, -135, -90,
                -90, -45, 0, 45, 90, 135, 0, -135,
                -135, -90, -45, 0, 45, 90, 135, 0,
                0, -135, -90, -45, 0, 45, 90, 135,
                135, 0, -135, -90, -45, 0, 45, 90,
                90, 135, 0, -135, -90, -45, 0, 45,
                45, 90, 135, 0, -135, -90, -45, 0,
        };
        int sum = 0;
        int lastCode = pChainCode[N - 1];
        for (int i = 0; i < N; ++i) {
            sum += angleLUT[lastCode][pChainCode[i]];
            lastCode = pChainCode[i];
        }
        return sum < 0;
    }

    bmp_file *bmp_file_process::eAndCRice() {
        //膨胀 1 变 255
//        for (auto pCur = resImg, pTmpCur = tmp, pEnd = pCur + imgSize; pCur < pEnd; ++pCur, ++pTmpCur) {
//            *pCur = ((*pTmpCur > 0) ? 0xff : 0);
//        }

        //腐蚀 254 变 0
        for (auto pCur = resImg, pTmpCur = tmp, pEnd = pCur + imgSize; pCur < pEnd; ++pCur, ++pTmpCur) {
            *pCur = ((*pTmpCur == 0xff) ? 0xff : 0);
        }
    }

    bmp_file *bmp_file_process::houghLineFind3(const bmp_file *bmp, int color) {
        assert(bmp != nullptr);
        this->cheekBmp(bmp, 0);
        memcpy(resImg, bmp->data, bmp->infoHeader.image_size);


        //计算水平方向点距离最多的  最小间隔10 而非一两个像素
        int maxNumDw = 0, minDw = 20;
        {//进行查找 只得到一个数maxNumDw 加大括号是不想写函数 又要避免命名冲突
            auto *his1 = new int[width];
            memset(his1, 0, sizeof(int) * width);
            auto *pCur = resImg;
            for (int y = 0; y < height; ++y) {
                pCur = resImg + y * width;
                auto *pEnd = pCur + width;
                for (int x = 0; x < width; ++x, ++pCur) {
                    if (*pCur != 0xff) { continue; }
                    for (auto *pCur1 = pCur + minDw; pCur1 < pEnd; ++pCur1) {
                        if (*pCur1 != 0xff) { continue; }
                        ++his1[pCur1 - pCur];
                    }
                }
            }
            for (int x = 0; x < width; ++x) {
                if (his1[maxNumDw] < his1[x]) {
                    maxNumDw = x;
                }
            }
        }

        //最多有多少个点 亮
        int maxPNum = width * height;
        auto *xArr = new int[maxPNum];
        auto *yArr = new int[maxPNum];
        memset(xArr, 0, maxPNum * sizeof(int));
        memset(yArr, 0, maxPNum * sizeof(int));
        int pNum = 0;
        auto *pCur = resImg;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x, ++pCur) {
                if (*(pCur) == 0xff && *(pCur + maxNumDw) == 0xff) {
                    xArr[pNum] = x;
                    yArr[pNum] = y;
                    ++pNum;
                    xArr[pNum] = x + maxNumDw;
                    yArr[pNum] = y;
                    ++pNum;
                } else {
                    //方便画出算了哪些点的图
                    if (*(pCur - maxNumDw) != 0xff) {
                        *pCur = 0;
                    }
                }
            }
        }

        clock_t t_start = clock();
        //最多有多长
        int maxRou = int(sqrt(width * width + height * height) + 2);
        int length = maxRou * 2 * 180;
        int *arr = new int[length];
        int step = 1;
        this->houghLine(arr, length, step, pNum, xArr, yArr);

        clock_t t_end = clock();
        std::cout << (t_end - t_start) / 1000.0 << std::endl << std::endl;
/*
        {
            //画出sita 和 rou的大小图
            auto *pArrCur = arr;
            bmp_file *b1 = this->createBmp(maxRou * 2, 200, this->GRY_MODE);
            auto *b1Cur = b1->data;
            for (int i = 0; i < 180; ++i) {
                for (int rou = 0, end_rou = maxRou * 2; rou < end_rou; ++rou, ++pArrCur) {
                    if ((i == 90 && rou < maxRou) || rou == maxRou) {
                        *(b1Cur + (i + 10) * end_rou + rou) = 0xaf;
                        continue;
                    }
                    if (*pArrCur < 255 / 2) {
                        *(b1Cur + (i + 10) * end_rou + rou) = (*pArrCur) * 2;
                    } else {
                        *(b1Cur + (i + 10) * end_rou + rou) = 0xff;
                    }
                }
            }
            return b1;
        }
*/

        int tmpMaxNum = 0, bestTheta = 0, bestRou = 0;
        //两条跑道 就是两个点的距离最多的
        int bestRou_2;
        //从0到180度遍历 theta
        for (int theta = 0, end_rou = maxRou * 2; theta < 180; theta += step) {
            //偏移 也就是之前得到的最多的距离 利用公式得到跑道应该的距离
            int offRou = abs(maxNumDw * cos(theta * M_PI / 180));
            //偏移抖动 可能offRou不是那么精确 抖动 +-3的像素
            for (int offShift = -3; offShift < 4; ++offShift) {
                //必须要满足大于0 因为从左开始遍历
                if (offRou + offShift < 0) { continue; }
                //更新目前指向位置
                auto *pArrCur = arr + theta * maxRou * 2;
                //查找哪一个更大
                for (int rou = 0, end_rou2 = end_rou - offShift - offRou; rou < end_rou2; ++rou, ++pArrCur) {
                    //第二条线 大小
                    int tmpNum2 = *(pArrCur + offRou + offShift);
                    //两条线加起来 最大
                    if (*pArrCur + tmpNum2 > tmpMaxNum) {
                        bestTheta = theta;
                        bestRou = rou;
                        tmpMaxNum = *pArrCur + tmpNum2;
                        //第二条线的rou（默认theta一样，其实应该再加一个theta的抖动）
                        bestRou_2 = rou + offRou + offShift;
                    }
                }
            }
        }

        for (auto *pResCur = resImg, *pEnd = pResCur + bmp->infoHeader.image_size; pResCur < pEnd; ++pResCur) {
            if (*pResCur == 0xff) {
                --(*pResCur);
            }
        }

        bmp_file *b2 = this->getResImg();
        //开始画线 2条
        int bestRou2 = bestRou - maxRou;
        double bestSita2 = bestTheta * M_PI / 180;
        double pk, pb;
        bool isYKX;

        this->getKBByRouSita(bestRou2, bestSita2, pk, pb, isYKX);
        bmp_file *b3 = this->drawPicALine(b2, pk, pb, color, isYKX);
        delete b2;
        b2 = b3;

        std::cout << "theta= " << bestSita2 / M_PI * 180 << "度   thro= " << bestRou2 << std::endl;
        if (isYKX) {
            std::cout << "x = " << (abs(pk) < 1e-6 ? "" : std::to_string(pk) + "y") << " " << (pb >= 0 ? "+" : "")
                      << pb << std::endl;
        } else {
            std::cout << "y = " << (abs(pk) < 1e-6 ? "" : std::to_string(pk) + "x") << " " << (pb >= 0 ? "+" : "")
                      << pb << std::endl;
        }
        std::cout << std::endl;

        this->getKBByRouSita(bestRou_2 - maxRou, bestSita2, pk, pb, isYKX);
        b3 = this->drawPicALine(b2, pk, pb, color, isYKX);
        delete b2;
        b2 = b3;

        std::cout << "theta= " << bestSita2 / M_PI * 180 << "度   thro= " << bestRou_2 - maxRou << std::endl;
        if (isYKX) {
            std::cout << "x = " << (abs(pk) < 1e-6 ? "" : std::to_string(pk) + "y") << " " << (pb >= 0 ? "+" : "")
                      << pb << std::endl;
        } else {
            std::cout << "y = " << (abs(pk) < 1e-6 ? "" : std::to_string(pk) + "x") << " " << (pb >= 0 ? "+" : "")
                      << pb << std::endl;
        }
        std::cout << std::endl;
        return b2;
    }

}

#endif //IMAGE_PROCESSING_BMP_FILE_PROCESS_HPP
