//
// Created by lerogo on 2021/6/8.
//

#ifndef IMAGE_PROCESSING_BMP_FILE_PROCESS_HPP
#define IMAGE_PROCESSING_BMP_FILE_PROCESS_HPP

#include <fstream>
#include <cmath>
#include "bmp_file_info.h"
#include "bmp_file.hpp"

namespace hhl {
    // 只和处理相关 类  一些接口
    class bmp_file_process {
    private:

        bmp_file_process() = default;

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
        void getHistogram(bmp_file *bmp);

        ///得到亮度和对比度
        void getBrightContrast(bmp_file *bmp);

        ///图片压缩 用到fast0123
        void compressBmp(const bmp_file *bmp, const int &_fast0123 = -1);

        ///积分图
        void getSumGryGraphBySumCol(bmp_file *bmp);

        ///sobel算子
        void sobelProcess(const bmp_file *bmp = nullptr);

        ///给bmp画框
        bmp_file *
        drawImg(const u_int &x, const u_int &y, const u_int &w, const u_int &h, const bmp_file *bmp = nullptr);

        ///文本定位
        bmp_file *textPositioningByWindow(const bmp_file *bmp, const int &o_w, const int &o_h,
                                          const int &_fast0123 = -1);

        ///获取任意大小的积分
        int getWindowsSumGraph(const bmp_file *bmp, const int &s_x, const int &s_y, const int &x_len, const int &y_len);
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
        clock_t t_start = clock();
        assert(-2 < _fast0123 && _fast0123 < 4);
        if (_fast0123 != -1) {
            fast0123 = _fast0123;
        }
        assert(-1 < fast0123 && fast0123 < 4);
        //压缩
        this->compressBmp(bmp, _fast0123);
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
        for (int x = w_2, end_x = width - w_2 * 3, end_y = height - h_2 * 3; x < end_x; ++x) {
            for (int y = 0; y < end_y; ++y) {
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

    /// 获取任意窗口大小的积分
    int bmp_file_process::getWindowsSumGraph(const bmp_file *bmp, const int &s_x, const int &s_y, const int &x_len,
                                             const int &y_len) {
        if (bmp->sumGraph == nullptr) {
            throw;
        }
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

}

#endif //IMAGE_PROCESSING_BMP_FILE_PROCESS_HPP
