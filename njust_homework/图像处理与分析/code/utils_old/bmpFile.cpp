//
// Created by lerogo on 2021/5/13.
//

#include "bmpFile.h"

/// 创建一个bmp的文件
BmpFile *BmpFile::createGrayBmp(unsigned int width, unsigned int height) {
    BmpFile *bmp = new BmpFile();
    bmp->paletteNum = bmp->char_express;
    unsigned headerSize = bmp->fileHeaderSize + bmp->infoHeaderSize + bmp->paletteSize * bmp->paletteNum;
    unsigned dataSize = width * height;
    dataSize += 4 - ((headerSize + dataSize) % 4);

    bmp->isRgb = false;

    //"BM" 文件头
    bmp->fileHeader.file_type = 19778;
    bmp->fileHeader.offset_bits = headerSize;
    bmp->fileHeader.file_size = headerSize + dataSize;

    // 图片信息头
    bmp->infoHeader.bitmap_info_size = 40;
    bmp->infoHeader.bitmap_width = width;
    bmp->infoHeader.bitmap_height = height;
    bmp->infoHeader.planes = 1;
    bmp->infoHeader.image_depth = 8;
    bmp->infoHeader.compression = 0;
    bmp->infoHeader.image_size = dataSize;
    bmp->infoHeader.x_pels_permeter = bmp->infoHeader.y_pels_permeter = 1000;
    bmp->infoHeader.color_used = bmp->infoHeader.color_important = 0;

    bmp->palette = new bitmap_palette[bmp->paletteNum];
    for (unsigned i = 0; i < bmp->paletteNum; ++i) {
        bmp->palette[i].red = bmp->palette[i].blue = bmp->palette[i].green = bmp->palette[i].reserved = i;
    }

    return bmp;
}

///把数据存入bmp
void BmpFile::writeBitData(unsigned int width, unsigned int height, unsigned char *_data) const {
    // 将数据按照响应格式储存
    auto *pDesCur = this->data;
    for (auto *pRowCur = _data + (height - 1) * width; pRowCur >= _data; pRowCur -= width) {
        for (auto *pCur = pRowCur, *pEnd = pCur + width; pCur < pEnd; pCur++) {
            *(pDesCur++) = *pCur;
        }
    }
}

/// 将图片的数据 在写入文件时 写入header
void BmpFile::copyHeader2Men() {
    // 写入文件的header
    if (headerSize != fileHeader.offset_bits) {
        delete[] header;
        headerSize = fileHeader.offset_bits;
        header = new unsigned char[headerSize];
    }
    // 复制到写入的内存
    memcpy(header, &fileHeader, fileHeaderSize);
    memcpy(header + fileHeaderSize, &infoHeader, infoHeaderSize);
    memcpy(header + fileHeaderSize + infoHeaderSize, palette, paletteSize * paletteNum);
}

/// 加载图片
void BmpFile::load(const std::string &fileName) {
    // 释放空间
    this->~BmpFile();
    // 读取文件
    std::ifstream infile(fileName, std::ios::in | std::ios::binary);
    if (!infile) {
        std::cerr << "Open file failed." << std::endl;
        throw;
    }
    // 读取文件头
    infile.seekg(0, std::ios::beg).read(reinterpret_cast<char *>(&fileHeader), fileHeaderSize);
    // 再次读取一次 所有数据
    auto fileData = new unsigned char[fileHeader.file_size];
    infile.seekg(0, std::ios::beg).read(reinterpret_cast<char *>(fileData), fileHeader.file_size);
    infile.close();

    // 储存用 header
    header = new unsigned char[fileHeader.offset_bits];
    memcpy(header, fileData, fileHeader.offset_bits);
    headerSize = fileHeader.offset_bits;

    // 文件信息头
    memcpy(&infoHeader, header + fileHeaderSize, infoHeaderSize);

    // 调色板数量
    paletteNum = (fileHeader.offset_bits - fileHeaderSize - infoHeaderSize) / paletteSize;
    if (paletteNum > 0) {
        palette = new bitmap_palette[paletteNum];
        // 调色板
        memcpy(palette, header + fileHeaderSize + infoHeaderSize,
               fileHeader.offset_bits - fileHeaderSize - infoHeaderSize);
        this->isRgb = false;
    }
    // 矫正图片所占大小
    if (infoHeader.image_size == 0) {
        infoHeader.image_size = fileHeader.file_size - fileHeader.offset_bits;
    }
    // 真正文件 数据
    data = new unsigned char[infoHeader.image_size];
    memcpy(data, fileData + fileHeader.offset_bits, infoHeader.image_size);

    // 删除读出来的临时文件数据
    delete[] fileData;
}

/// 保存图片
void BmpFile::save(const std::string &fileName) {
    // 读取文件
    std::ofstream outfile(fileName, std::ios::out | std::ios::binary);
    if (!outfile) {
        std::cerr << "Open file failed." << std::endl;
        throw;
    }
    // 将文件信息写入header
    this->copyHeader2Men();
    // 写入头
    outfile.write(reinterpret_cast<const char *>(header), fileHeader.offset_bits);
    // 写入文件
    outfile.write(reinterpret_cast<const char *>(data), infoHeader.image_size);
    outfile.close();
}

////////////其他操作////////////
///图片反向
void BmpFile::Invert() const {
    // 换成int 一次4个字节
    for (int *pCurImg = reinterpret_cast<int *>(data), *pEndImg =
            pCurImg + infoHeader.image_size / sizeof(int) * sizeof(unsigned char);
         pCurImg != pEndImg; ++pCurImg) {
        *pCurImg = ~*pCurImg;
    }
}

///灰度图像假彩色 这里用蓝色
bool BmpFile::gryPseudoColor() const {
    if (isRgb) {
        return false;
    }
    memset(palette, 0, paletteNum * paletteSize);
    for (unsigned i = 0; i < paletteNum; ++i) {
        palette[i].blue = i;
    }
    return true;
}

///rgb图像转灰度图像
bool BmpFile::rgb2Gray() {
    if (!isRgb) {
        return false;
    }
    // char表达的最大值 每一个存查找表
    const unsigned &size = char_express;
    auto *red = new double[size];
    auto *blue = new double[size];
    auto *green = new double[size];
    memset(red, 0, size << 3);
    memset(blue, 0, size << 3);
    memset(green, 0, size << 3);

    // 删除已经有的调色板 重新建立256色调色板
    delete[] this->palette;
    palette = new bitmap_palette[size];
    // 调色板数量 默认 256
    paletteNum = size;
    // 初始化0 默认黑色
    memset(palette, 0, sizeof(bitmap_palette) << 8);
    for (unsigned i = 0; i < size; ++i) {
        // 查找表
        red[i] = 0.299 * i;
        green[i] = 0.587 * i;
        blue[i] = 0.114 * i;
        // 调色板 正常色彩 亮度
        palette[i].red = i;
        palette[i].blue = i;
        palette[i].green = i;
    }

    // 真实图片大小
    unsigned newImgSize = infoHeader.bitmap_width * infoHeader.bitmap_height;
    // 修正对齐
    unsigned img_size = newImgSize;
    unsigned tmpHeaderSize = fileHeaderSize + infoHeaderSize + paletteSize * paletteNum;
    img_size += 4 - ((tmpHeaderSize + img_size) % 4);

    // 开始赋值
    auto *grayData = new unsigned char[img_size];
    memset(grayData, 0, img_size);

//    clock_t t_start = clock();
//    for (unsigned times = 0; times < 1000; ++times) {
    auto *pCurImg = data;
    //查表法 BGR 顺序
    for (auto *pGrayImg = grayData, *pEndGrayImg = pGrayImg + newImgSize; pGrayImg < pEndGrayImg;) {
        *(pGrayImg++) = int(blue[*(pCurImg++)] + green[*(pCurImg++)] + red[*(pCurImg++)]);
    }
    //非查表法
//        for (auto *pGrayImg = grayData, *pEndGrayImg = pGrayImg + newImgSize; pGrayImg < pEndGrayImg;) {
//            *(pGrayImg++) = 0.114 * (*(pCurImg++)) + 0.587 * (*(pCurImg++)) + 0.299 * (*(pCurImg++));
//        }
//    }
//    clock_t t_end = clock();
//    std::cout << (t_end - t_start);


    // 修正data
    delete[] this->data;
    this->data = grayData;

    // 修正图片信息
    fileHeader.offset_bits = tmpHeaderSize;
    fileHeader.file_size = tmpHeaderSize + img_size;
    infoHeader.image_size = img_size;
    infoHeader.planes = 1;
    infoHeader.image_depth = 8;
    this->isRgb = false;

    // 释放临时内存
    delete[] red;
    delete[] blue;
    delete[] green;

    return true;
}

///均值方差规定化（针对于灰度图像）
bool BmpFile::MVR(const double &_bright, const double &_contrast) {
    if (this->isRgb) {
        return false;
    }

    // 获取亮度
    this->getBrightContrast();

    auto *LUT = new unsigned char[char_express];
    for (unsigned i = 0; i < char_express; ++i) {
        LUT[i] = fmax(0, fmin(255, (i - this->bright) * _contrast / this->contrast + _bright));
    }

    for (auto *pCur = data, *pEnd = pCur + infoHeader.image_size; pCur < pEnd; pCur++) {
        *pCur = LUT[*pCur];
    }
    delete[] LUT;
    return true;
}

/// 获取直方图
void BmpFile::getHistogram() {
    delete[] histogram;
    histogram = new unsigned[char_express];
    memset(histogram, 0, sizeof(unsigned) << 8);
    for (auto *pCur = data, *pEnd = pCur + infoHeader.image_size; pCur < pEnd;) {
        histogram[*(pCur++)]++;
    }
}

/// 获取亮度对比度
void BmpFile::getBrightContrast() {
    if (histogram == nullptr) {
        this->getHistogram();
    }
    unsigned sum = 0;
    for (unsigned i = 0; i < char_express; ++i) {
        sum += histogram[i] * i;
    }
    bright = double(sum) / infoHeader.image_size;

    contrast = 0.0;
    for (unsigned i = 0; i < char_express; ++i) {
        contrast += histogram[i] * (i - bright) * (i - bright);
    }
    contrast = sqrt(contrast / (infoHeader.image_size - 1));
}

/// 直方图均衡化
bool BmpFile::histogramEqualization() {
    // 获取直方图
    if (histogram == nullptr) {
        this->getHistogram();
    }
    auto *LUT = new unsigned char[char_express];

    for (unsigned i = 0, sum = 0; i < char_express; ++i) {
        sum += histogram[i];
        LUT[i] = ((sum << 8) - sum) / infoHeader.image_size;
    }

    // 修改后
//    LUT[0] = ((histogram[0] << 8) - histogram[0]) / infoHeader.image_size;
//    for (unsigned i = 1; i < char_express; ++i) {
//        histogram[i] += histogram[i - 1];
//        LUT[i] = ((histogram[i] << 8) - histogram[i]) / infoHeader.image_size;
//    }

    for (auto *pCur = data, *pEnd = pCur + infoHeader.image_size; pCur < pEnd; pCur++) {
        *pCur = LUT[*pCur];
    }

    delete[] LUT;
    return true;
}

/// 加载一个 14位raw 图像
BmpFile *BmpFile::load14Raw(const std::string &path, unsigned int width, unsigned int height) {
    std::ifstream infile(path, std::ios::in | std::ios::binary);
    if (!infile) {
        std::cerr << "Open file failed." << std::endl;
        throw;
    }
    auto size = width * height;
    auto *data = new short int[size];
    // 读取文件
    infile.seekg(0, std::ios::beg).read(reinterpret_cast<char *>(data), size * sizeof(short int));
    infile.close();
    // 新建一个bmp文件
    auto *bmp = createGrayBmp(width, height);
    // 初始化bmp的数据
    bmp->data = new unsigned char[bmp->infoHeader.image_size];
    memset(bmp->data, 0, bmp->infoHeader.image_size);

    // 获取 14位图 直方图
    unsigned short_int_express = 1 << 14;
    auto *histogram = new unsigned[short_int_express];
    memset(histogram, 0, sizeof(unsigned) << 14);
    for (auto *pCur = data, *pEnd = pCur + size; pCur < pEnd;) {
        histogram[*(pCur++)]++;
    }
    // 计算得到查找表 （直方图均衡化）
    auto *LUT = new unsigned char[short_int_express];
    for (unsigned i = 0, sum = 0; i < short_int_express; ++i) {
        sum += histogram[i];
        LUT[i] = ((sum << 8) - sum) / size;
    }

    // 将数据按照响应格式储存
    auto *resImg = new unsigned char[bmp->infoHeader.image_size];
    auto *pDesCur = resImg;
    for (auto *pCur = data, *pEnd = pCur + size; pCur < pEnd; pCur++) {
        *(pDesCur++) = LUT[*pCur];
    }
    bmp->writeBitData(width, height, resImg);

    delete[] resImg;
    delete[] data;
    delete[] histogram;
    delete[] LUT;

    return bmp;
}

///彩色灰度图像 浮点乘 到 整数乘 测试
bool BmpFile::rgb2Gray_test1() {
    if (!isRgb) {
        return false;
    }
    // char表达的最大值 每一个存查找表
    const unsigned &size = char_express;

    // 删除已经有的调色板 重新建立256色调色板
    delete[] this->palette;
    palette = new bitmap_palette[size];
    // 调色板数量 默认 256
    paletteNum = size;
    // 初始化0 默认黑色
    memset(palette, 0, sizeof(bitmap_palette) << 8);
    for (unsigned i = 0; i < size; ++i) {
        // 调色板 正常色彩 亮度
        palette[i].red = i;
        palette[i].blue = i;
        palette[i].green = i;
    }

    // 真实图片大小
    unsigned newImgSize = infoHeader.bitmap_width * infoHeader.bitmap_height;
    // 修正对齐
    unsigned img_size = newImgSize;
    unsigned tmpHeaderSize = fileHeaderSize + infoHeaderSize + paletteSize * paletteNum;
    img_size += 4 - ((tmpHeaderSize + img_size) % 4);

    // 开始赋值
    auto *grayData = new unsigned char[img_size];
    memset(grayData, 0, img_size);

    clock_t t_start = clock();
    for (unsigned times = 0; times < 3000; ++times) {
        auto *pCurImg = data;
        //非查表法 1
        for (auto *pGrayImg = grayData, *pEndGrayImg = pGrayImg + newImgSize; pGrayImg < pEndGrayImg;) {
            *(pGrayImg++) = 0.114 * (*(pCurImg++)) + 0.587 * (*(pCurImg++)) + 0.299 * (*(pCurImg++));
        }
        //非查表法 2
//        for (auto *pGrayImg = grayData, *pEndGrayImg = pGrayImg + newImgSize; pGrayImg < pEndGrayImg;) {
//            *(pGrayImg++) = (116 * (*(pCurImg++)) + 601 * (*(pCurImg++)) + 306 * (*(pCurImg++))) >> 10;
//        }
    }
    clock_t t_end = clock();
    std::cout << (t_end - t_start) / 1000.0;


    // 修正data
    delete[] this->data;
    this->data = grayData;

    // 修正图片信息
    fileHeader.offset_bits = tmpHeaderSize;
    fileHeader.file_size = tmpHeaderSize + img_size;
    infoHeader.image_size = img_size;
    infoHeader.planes = 1;
    infoHeader.image_depth = 8;
    this->isRgb = false;

    return true;
}

/// 均值滤波列积分
bool BmpFile::avrFilterBySumCol(unsigned M, unsigned N) {
    // 窗口 M列 N行
    unsigned half_x = M >> 1;
    unsigned half_y = N >> 1;
    M = (half_x << 1) | 0x0001;
    N = (half_y << 1) | 0x0001;
    unsigned C = (1 << 23) / (M * N);
    unsigned width = infoHeader.bitmap_width;
    unsigned height = infoHeader.bitmap_height;
    auto *sumCol = new unsigned[width];
    memset(sumCol, 0, width << 2);

    // 初始化sumCol
    auto *pAdd = data, *pDel = data;
    for (auto *pEnd = data + N * width; pAdd < pEnd;) {
        for (unsigned x = 0; x < width; ++x) {
            sumCol[x] += *(pAdd++);
        }
    }
    auto *resData = new unsigned char[infoHeader.image_size];
    memcpy(resData, data, infoHeader.image_size);
    // 进行滤波 跳过边缘的处理
    for (auto *pCur = resData + half_y * width, *pEnd = resData + (height - half_y) * width; pCur < pEnd;) {
        // 初始化sum
        unsigned sum = 0;
        for (unsigned x = 0; x < M; ++x) {
            sum += sumCol[x];
        }
        pCur += half_x;
        for (unsigned x = half_x, end_x = width - half_x; x < end_x; ++x) {
            // 乘法换除法
            *(pCur++) = (sum * C) >> 23;
            // 更新sum
            sum -= sumCol[x - half_x];
            sum += sumCol[x + half_x + 1];
        }
        pCur += half_x;
        for (unsigned x = 0; x < width; ++x) {
            sumCol[x] -= *(pDel++);
            sumCol[x] += *(pAdd++);
        }
    }
    delete[] data;
    data = resData;

    delete[] sumCol;

    return true;
}

///基于列积分的积分图实现
void BmpFile::getSumGryGraphBySumCol() {
    delete[] sumGraph;
    unsigned width = infoHeader.bitmap_width;
    auto *sumCol = new unsigned[width];
    memset(sumCol, 0, width << 2);
    sumGraph = new unsigned[infoHeader.image_size];
    auto *pRes = sumGraph;
    for (auto *pCur = data, *pEnd = data + infoHeader.image_size; pCur < pEnd;) {
        sumCol[0] += *(pCur++);
        *(pRes++) = sumCol[0];
        for (unsigned x = 1; x < width; ++x, ++pRes) {
            sumCol[x] += *(pCur++);
            *pRes = *(pRes - 1) + sumCol[x];
        }
    }
    delete[] sumCol;
}

/// 用指令集获取积分图  有错误 还需要调试...
void BmpFile::getSumGryGraphBySSE() {
    delete[] sumGraph;
    sumGraph = new unsigned[infoHeader.image_size];
    unsigned width = infoHeader.bitmap_width;
    auto *sumCol = new unsigned[width];
    auto *pRes = sumGraph;
    memset(sumCol, 0, width << 2);
//    auto *p = std::align(1 << 8, width, reinterpret_cast<void *&>(sumCol), reinterpret_cast<size_t &>(width));

    __m128i *pSumSSE, A;
    for (auto *pCur = data, *pEnd = data + infoHeader.image_size; pCur < pEnd;) {
        sumCol[0] += *(pCur++);
        *(pRes++) = sumCol[0];
        for (unsigned x = 1; x <= 3; ++x, ++pRes) {
            sumCol[x] += *(pCur++);
            *pRes = *(pRes - 1) + sumCol[x];
        }
        pSumSSE = (__m128i *) (sumCol + 4);
        for (unsigned x = 4; x < width; pCur += 4) {
            A = _mm_cvtepi16_epi64(_mm_loadl_epi64((__m128i *) pCur));
            *(pSumSSE++) = _mm_add_epi32(*pSumSSE, A);
            for (unsigned i = 0; i < 4; ++i, ++pRes) {
                *(pRes) = *(pRes - 1) + sumCol[x++];
            }
        }
    }
    delete[] sumCol;
}

///均值滤波积分图
bool BmpFile::avrFilterByGraph(unsigned int M, unsigned int N) {
    if (sumGraph == nullptr) {
        this->getSumGryGraphBySumCol();
    }
    // 窗口 M列 N行
    unsigned half_x = M >> 1;
    unsigned half_y = N >> 1;
    M = (half_x << 1) | 0x0001;
    N = (half_y << 1) | 0x0001;
    unsigned C = (1 << 23) / (M * N);
    unsigned width = infoHeader.bitmap_width;
    unsigned height = infoHeader.bitmap_height;

    auto *resData = new unsigned char[infoHeader.image_size];
    memcpy(resData, data, infoHeader.image_size);
    // 进行滤波 跳过边缘的处理
    auto *pRes = resData + half_y * width;
    auto *pSmallSumGraph = sumGraph;
    auto *pBigSumGraph = sumGraph + N * width;

    // +1 是确保 算sum的公式为正确的（4个值），否则应该为一个值或者两个值 但这样会少处理一行一列像素
    for (unsigned y = half_y + 1, end_y = height - half_y;
         y < end_y; ++y, pSmallSumGraph += width, pBigSumGraph += width) {
        pRes += half_x + 1;
        unsigned sum = 0;
        for (unsigned x = half_x + 1, end_x = width - half_x, x1 = 0, x2 = M; x < end_x; ++x, ++x1, ++x2) {
            sum = *(pBigSumGraph + x2) + *(pSmallSumGraph + x1) - *(pBigSumGraph + x1) - *(pSmallSumGraph + x2);
            *(pRes++) = (sum * C) >> 23;
        }
        pRes += half_x;
    }

    delete[] data;
    data = resData;

    return true;
}

///图片反向 SSE
void BmpFile::InvertBySSE() const {
    // F1 高位会自动补1
    __m128i F1 = _mm_set1_epi8(0xff);
    __m128i *pSSE = (__m128i *) data;
    for (auto *pCur = data, *pEnd = data + infoHeader.image_size; pCur < pEnd; pCur += 16) {
        *(pSSE++) = _mm_xor_si128(*pSSE, F1);
    }
}

///中值滤波
double BmpFile::medianFilter(unsigned int M, unsigned int N) {
    // 窗口 M列 N行
    unsigned half_x = M >> 1;
    unsigned half_y = N >> 1;
    M = (half_x << 1) | 0x0001;
    N = (half_y << 1) | 0x0001;
    unsigned wSize = M * N;
    unsigned width = infoHeader.bitmap_width;
    unsigned height = infoHeader.bitmap_height;
    unsigned tmp_histogram[char_express];
    // 领域内像素总个数
    unsigned dbgCmpTimes = 0;
    auto *resData = new unsigned char[infoHeader.image_size];
    memcpy(resData, data, infoHeader.image_size);
    auto *pRes = resData + half_y * width;
    for (unsigned y = half_y, end_y = height - half_y; y < end_y; ++y) {
        // 初始化直方图 每一行
        unsigned y1 = y - half_y;
        unsigned y2 = y + half_y;
        memset(tmp_histogram, 0, char_express << 2);
        auto *pCur = data + y1 * width;
        // 领域内的计算
        for (unsigned i = y1; i <= y2; ++i, pCur += width) {
            for (unsigned j = 0, end_j = (half_x << 1) + 1; j < end_j; ++j) {
                ++tmp_histogram[*(pCur + j)];
            }
        }
        // 计算中值
        unsigned num = 0;
        unsigned med = -1;
        for (unsigned i = 0; i < char_express; ++i) {
            num += tmp_histogram[i];
            if ((num << 1) > wSize) {
                med = i;
                break;
            }
        }
        // 进行滤波
        pRes += half_x;
        for (unsigned x = half_x, end_x = width - half_x; x < end_x; ++x) {
            *(pRes++) = med;
            // 更新直方图
            unsigned j1 = x - half_x;
            unsigned j2 = x + half_x + 1;
            pCur = data + y1 * width;
            // 对每一行
            for (unsigned i = y1; i <= y2; ++i, pCur += width) {
                unsigned v = *(pCur + j1);
                // 减左边
                --tmp_histogram[v];
                if (v <= med) {
                    --num;
                }
                // 加右边
                v = *(pCur + j2);
                ++tmp_histogram[v];
                if (v <= med) {
                    ++num;
                }
            }
            if ((num << 1) < wSize) {
                for (med++; med < char_express; ++med) {
                    dbgCmpTimes += 2;
                    num += tmp_histogram[med];
                    if ((num << 1) > wSize) { break; }
                }
                ++dbgCmpTimes;
            } else {
                while (((num - tmp_histogram[med]) << 1) > wSize) {
                    ++dbgCmpTimes;
                    num -= tmp_histogram[med];
                    --med;
                }
                dbgCmpTimes += 2;
            }
        }
        pRes += half_x;
    }
    delete[] data;
    data = resData;

    return double(dbgCmpTimes) / (width - (half_x << 1)) / (height - (half_y << 1));
}

///计算高斯公式
double calTj(double const &j, double const &sigma) {
    double sigma_2 = sigma * sigma;
    return exp(-(j * j) * 0.5 / sigma_2) / sqrt(2 * M_PI * sigma_2);
}

///高斯滤波
bool BmpFile::GaussianFilter(int const &sigma) {
    int wSize = 3 * sigma + 1;
    auto *T = new double[wSize];
    auto *T_1 = new unsigned[wSize];
    const unsigned &width = infoHeader.bitmap_width;
    const unsigned &height = infoHeader.bitmap_height;
    auto *resData = new unsigned char[infoHeader.image_size];
    memcpy(resData, data, infoHeader.image_size);
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
    for (auto *pCur = data + wSize, *pEnd = data + width * height - wSize, *pRes = resData + wSize;
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
    auto *resData2 = new unsigned char[infoHeader.image_size];
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            *((resData2 + x * height) + y) = *((resData + y * width) + x);
        }
    }
    // 重新计算resData
    memcpy(resData, resData2, infoHeader.image_size);
    // 开始计算
    for (auto *pCur = resData + wSize, *pEnd = resData + width * height - wSize, *pRes = resData2 + wSize;
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
            *((resData + x * width) + y) = *((resData2 + y * height) + x);
        }
    }
    delete[] resData2;

    delete[] data;
    data = resData;

    delete[] T;
    delete[] T_1;
    return true;
}

/// 一阶微分算子 sobel
bool BmpFile::sobelProcess() {
    if (isRgb) {
        return false;
    }
    auto *resData = new unsigned char[infoHeader.image_size];
    memset(resData, 0, infoHeader.image_size);
    const unsigned &width = infoHeader.bitmap_width;
    const unsigned &height = infoHeader.bitmap_height;
    auto *pRes = resData + width;
    for (auto *pCur = data + width, *pEnd = data + width * (height - 1); pCur < pEnd;) {
        ++pCur, ++pRes;
        for (auto *pWidthEnd = pCur + width - 2; pCur < pWidthEnd; pCur++) {
            auto lastRow = pCur - width;
            auto nextRow = pCur + width;
            int dx = *(lastRow - 1) + *(pCur - 1) * 2 + *(nextRow - 1);
            dx -= *(lastRow + 1) + *(pCur + 1) * 2 + *(nextRow + 1);
            int dy = *(lastRow - 1) + *(lastRow) * 2 + *(lastRow + 1);
            dy -= *(nextRow - 1) + *(nextRow) * 2 + *(nextRow + 1);
            *(pRes++) = fmin(255, abs(dx) + abs(dy));
        }
        ++pCur, ++pRes;
    }
    delete[] data;
    data = resData;
    return true;
}

///沈俊算子
bool BmpFile::ShenJunProcess(const double &alpha) {
    assert(0.0 < alpha && alpha < 1.0);
    if (isRgb) {
        return false;
    }
    const unsigned &width = infoHeader.bitmap_width;
    const unsigned &height = infoHeader.bitmap_height;

    // 查找表
    auto *T_LUT = new int[1 << 9], *LUT = T_LUT + 256;
    *LUT = 0;
    for (int i = 1; i < 256; ++i) {
        LUT[i] = int(i * alpha + 0.5);
        LUT[-i] = -LUT[i];
    }
    // 递推滤波
    int pre;
    auto *resData = new unsigned char[infoHeader.image_size], *pRes = resData;
    // 按行
    for (auto *pCur = data, *pEnd = data + infoHeader.image_size; pCur < pEnd;) {
        *(pRes++) = pre = *(pCur++);
        // 从左到右 p1(y,x)=p1(y,x-1)+a*[p(y,x)-p1(y,x-1)]
        for (auto *pRowEnd = pCur + width - 1; pCur < pRowEnd; ++pCur) {
            *(pRes++) = pre = pre + LUT[(*pCur) - pre];
        }
        pRes -= 2;
        // 从右到左 p2(y,x)=p2(y,x+1)-a*[p1(y,x)-p2(y,x+1)]
        for (auto *pRowEnd = pRes - width + 1; pRes > pRowEnd;) {
            *(pRes--) = pre = pre + LUT[*(pRes) - pre];
        }
        pRes += width + 1;
    }
    // 按列
    pRes = resData;
    for (unsigned x = 0; x < width; ++x, pRes = resData + x) {
        pre = *pRes;
        //从上向下 p3(y,x)=p3(y-1,x)+a*[p2(y,x)-p3(y-1,x)]
        pRes += width;
        for (auto *pColEnd = pRes + width * (height - 1); pRes < pColEnd; pRes += width) {
            *pRes = pre = pre + LUT[*(pRes) - pre];
        }
        pRes -= width << 1;
        for (auto *pColEnd = pRes - width * (height - 1); pRes > pColEnd; pRes -= width) {
            *pRes = pre = pre + LUT[*(pRes) - pre];
        }
    }

    // 计算导数 大于才为1 否则为0
    pRes = resData;
    for (auto *pCur = data, *pEnd = data + infoHeader.image_size; pCur < pEnd; ++pCur, ++pRes) {
        *pRes = *pRes > *pCur;
    }
    // 过零点检测
    auto *tmpData = resData;
    resData = new unsigned char[infoHeader.image_size];
    memset(resData, 0, infoHeader.image_size);
    pRes = resData + width + 1;
    for (auto *pCur = tmpData + width + 1, *pEnd = tmpData + width * (height - 1); pCur < pEnd;) {
        for (auto *pRowEnd = pCur + width - 2; pCur < pRowEnd; ++pCur, ++pRes) {
            if (*pCur) {
                // 上下左右 有小于等于0的
                if (!*(pCur - 1) || !*(pCur + 1) || !*(pCur - width) || !*(pCur + width)) {
                    *pRes = 0xff;
                }
            }
        }
        pCur += 2, pRes += 2;
    }

    delete[] tmpData;
    delete[] data;
    data = resData;
    return true;
}

/// 例子 米检测
void BmpFile::riceEdgeDetector(double const &alpha, int const &grd) {
    // 备份原来的data
    auto *srcData = new unsigned char[infoHeader.image_size];
    memcpy(srcData, data, infoHeader.image_size);
    // sobel处理
    sobelProcess();
    // 拿回原来的data
    auto *sobelData = data;
    data = srcData;
    // 沈俊处理
    ShenJunProcess(alpha);

    // 融合
    for (int i = 0; i < infoHeader.image_size; i++) {
        data[i] = (data[i] && (sobelData[i] > grd)) ? 0xff : 0x0;
    }
    delete[] sobelData;

    // 伪彩色
    palette[255].red = 255;
    palette[255].blue = 0;
    palette[255].green = 0;
}

/// 一个更快的文本定位 也许也许精度小一点
/// 压缩后 获取亮度最高的一个部分 再利用行积分找到波谷 然后截取 即可获得
__attribute__((unused)) void BmpFile::textPositioning() {
    clock_t t_start = clock();

    // 首先保存原始数据图像
    auto *orgImgBak = new unsigned char[infoHeader.image_size];
    memcpy(orgImgBak, data, infoHeader.image_size);
    auto orgWidth = infoHeader.bitmap_width;
    auto orgHeight = infoHeader.bitmap_height;
    auto orgImgSize = infoHeader.image_size;
    // 图片压缩
    compressImg(4, 4);
    // 使用sobel算子计算边缘强度 用边缘强度去寻找 而非原始图像的亮度
    sobelProcess();
    // 计算得到的边缘图 的 积分图
    getSumGryGraphBySumCol();

    int drawRow = 0;
    int drawCol = 0;
    int drawRowLen = 0;
    int drawColLen = 0;

    // 大致圈出边缘信息多的地方
    int width = infoHeader.bitmap_width;
    int height = infoHeader.bitmap_height;
    // 变分辨率 首先是 行列各1/2 粗定位
    int sRow = 0, sCol = 0, maxSRow = 0, maxSCol = 0;
    const int width_2 = width >> 1;
    const int height_2 = height >> 1;
    auto sumGraph_2 = sumGraph + width * height_2 - 1;
    // 找到行
    for (unsigned row = 1, endRow = height_2; row < endRow; ++row) {
        unsigned offset = width * row;
        unsigned tmp = *(sumGraph_2 + offset) - *(sumGraph + offset - 1);
        if (maxSRow < tmp) {
            maxSRow = tmp;
            sRow = row;
        }
    }
    sumGraph_2 = sumGraph + width * (height - 1);
    // 找到列
    for (unsigned col = 0, endCol = width_2; col < endCol; ++col) {
        unsigned tmp = *(sumGraph_2 + col + width_2) - *(sumGraph_2 + col);
        if (maxSCol < tmp) {
            maxSCol = tmp;
            sCol = col;
        }
    }
    drawRow += sRow, drawCol += sCol;
    // 截取 大致的地方
    cutImg(sRow, sCol, height_2, width_2);

    // 重新计算积分图
    getSumGryGraphBySumCol();
    // 计算每一行的积分
    width = infoHeader.bitmap_width;
    height = infoHeader.bitmap_height;
    auto *sumRow = new unsigned[height], *pSumRow = sumRow;
    auto *pCurSumGraph = sumGraph + width - 1;
    *(pSumRow++) = *pCurSumGraph;
    pCurSumGraph += width;
    for (auto *pEndSumGraph = sumGraph + width * height; pCurSumGraph < pEndSumGraph; pCurSumGraph += width) {
        *(pSumRow++) = *pCurSumGraph - *(pCurSumGraph - width);
    }
    // 平滑 前面平滑的数据影响后面 并找到最大的值
    int maxInd = 1;
    for (int i = 1; i < height - 1; ++i) {
        sumRow[i] = (sumRow[i - 1] + sumRow[i] + sumRow[i + 1]) / 3;
        if (sumRow[i] > sumRow[maxInd]) {
            maxInd = i;
        }
    }
    for (int i = maxInd; i < height - 2; ++i) {
        if (sumRow[i - 1] < sumRow[i] && sumRow[i] < sumRow[i + 1] && sumRow[i] < sumRow[i + 2]) {
            sRow = i;
            break;
        }
    }
    getBrightContrast();
    int eRow = height;
    int _bright = int(bright) << 5;
    // 忽略掉一部分末尾数据
    for (int i = height - 3; i > sRow; --i) {
        if (sumRow[i] < sumRow[i - 1] && sumRow[i] < sumRow[i - 2] &&
            sumRow[i] > sumRow[i + 1] && sumRow[i] > sumRow[i + 2] && sumRow[i] > sumRow[i + 3]
            && sumRow[i] > _bright) {
            eRow = i;
            break;
        }
    }
    drawRow += sRow;
    int rowLen = 4 + eRow - sRow - (eRow - sRow) % 4;
    cutImg(sRow, 0, rowLen, width);
//    drawImg(sRow, 0, rowLen, width - 1);
    // 重新计算积分图
    getSumGryGraphBySumCol();
    // 计算每一列的积分
    width = infoHeader.bitmap_width;
    height = infoHeader.bitmap_height;
    auto *tmpSumCol = new unsigned[width], *pSumCol = tmpSumCol;
    pCurSumGraph = sumGraph + width * (height - 1);
    *(pSumCol++) = *(pCurSumGraph++);
    for (auto pEndSumGraph = pCurSumGraph + width; pCurSumGraph < pEndSumGraph; ++pCurSumGraph) {
        *(pSumCol++) = *pCurSumGraph - *(pCurSumGraph - 1);
    }
    sCol = 0;
    int eCol = width;
    for (int i = 1, eWidth = width - 1; i < eWidth; ++i) {
        if (tmpSumCol[i - 1] != 0 && tmpSumCol[i - 1] < tmpSumCol[i] && tmpSumCol[i] < tmpSumCol[i + 1]) {
            sCol = i;
            break;
        }
    }
    for (int i = width - 1, eWidth = 1; i > eWidth; --i) {
        if (tmpSumCol[i + 1] != 0 && tmpSumCol[i + 1] < tmpSumCol[i] && tmpSumCol[i] < tmpSumCol[i - 1] &&
            tmpSumCol[i] > _bright) {
            eCol = i;
            break;
        }
    }
    drawColLen = 4 + eCol - sCol - (eCol - sCol) % 4;
    cutImg(0, sCol, height, drawColLen);
//    return;
//    drawCol += sCol;
//    drawRowLen = rowLen;
//    drawColLen = eCol - sCol + (eCol - sCol) % 4;
//
//    drawRow <<= 2;
//    drawCol <<= 2;
//    drawRowLen <<= 2;
//    drawColLen <<= 2;
//    delete[] data;
//    data = orgImgBak;
//    fileHeader.file_size = fileHeader.offset_bits + orgImgSize;
//
//    infoHeader.image_size = orgImgSize;
//    infoHeader.bitmap_width = orgWidth;
//    infoHeader.bitmap_height = orgHeight;
//
//    drawImg(drawRow, drawCol, drawRowLen, drawColLen);
//    delete[] tmpSumCol;
//    delete[] sumRow;
//    delete[] orgImgBak;

//    drawImg(sRow, sCol, height_2, width_2);
    clock_t t_end = clock();
    std::cout << (t_end - t_start) / 1000.0;
}

/// 画图
void BmpFile::drawImg(unsigned sRow, unsigned sCol, unsigned const &rowLen, unsigned const &colLen) {
    // 把原图的255变成254
    for (auto *pCur = data, *pEnd = data + infoHeader.image_size; pCur < pEnd; ++pCur) {
        if (*pCur == 0xff) {
            *pCur = 0xfe;
        }
    }
    // 画线框
    auto *pCur = data + sRow * infoHeader.bitmap_width + sCol;
    // "_"
    for (auto *pRes = pCur, *pEnd = pRes + colLen; pRes < pEnd; ++pRes) {
        *pRes = 0xff;
    }
    // "| "
    for (auto *pRes = pCur, *pEnd = pRes + rowLen * infoHeader.bitmap_width;
         pRes < pEnd; pRes += infoHeader.bitmap_width) {
        *pRes = 0xff;
    }
    // " |"
    for (auto *pRes = pCur + colLen, *pEnd = pRes + rowLen * infoHeader.bitmap_width;
         pRes < pEnd; pRes += infoHeader.bitmap_width) {
        *pRes = 0xff;
    }
    // "-"
    for (auto *pRes = pCur + rowLen * infoHeader.bitmap_width, *pEnd = pRes + colLen + 1; pRes < pEnd; ++pRes) {
        *pRes = 0xff;
    }

    // 伪彩色
    palette[255].red = 255;
    palette[255].blue = 0;
    palette[255].green = 0;
}


///压缩图片
void BmpFile::compressImg(const unsigned &widthSlope, const unsigned &heightSlope) {
    unsigned const width = infoHeader.bitmap_width / widthSlope;
    unsigned const height = infoHeader.bitmap_height / heightSlope;
    unsigned widthSlope_2 = widthSlope >> 1;
    unsigned heightSlope_2 = heightSlope >> 1;
    unsigned img_size = width * height;
    img_size += 4 - ((fileHeader.offset_bits + img_size) % 4);
    auto *newData = new unsigned char[img_size];
    memset(newData, 0, img_size);
    for (auto *pCur = data, *pEnd = data + infoHeader.image_size, *pRes = newData; pCur < pEnd;) {
        pCur += infoHeader.bitmap_width * heightSlope_2;
        auto *pRowEnd = pCur + infoHeader.bitmap_width;
        while (pCur < pRowEnd) {
            *(pRes++) = *(pCur + widthSlope_2);
            pCur += widthSlope;
        }
        pCur = pRowEnd + infoHeader.bitmap_width * (heightSlope_2 - 1);
    }
    fileHeader.file_size = fileHeader.offset_bits + img_size;

    infoHeader.image_size = img_size;
    infoHeader.bitmap_width = width;
    infoHeader.bitmap_height = height;
    delete[]  data;
    data = newData;
}

///切割图片
void BmpFile::cutImg(const unsigned int sRow, const unsigned int sCol, const int &rowLen,
                     const int &colLen) {
    int const &height = rowLen;
    int const &width = colLen;
    unsigned img_size = width * height;
    img_size += 4 - ((fileHeader.offset_bits + img_size) % 4);
    auto *newImg = new unsigned char[img_size];
    memset(newImg, 0, img_size);
    auto *pRes = newImg;

    for (auto *pCur = data + sRow * infoHeader.bitmap_width + sCol, *pEnd =
            pCur + infoHeader.bitmap_width * rowLen + colLen; pCur < pEnd;) {
        for (auto *pRowEnd = pCur + colLen; pCur < pRowEnd; ++pCur) {
            *(pRes++) = *pCur;
        }
        pCur += infoHeader.bitmap_width - colLen;
    }

    fileHeader.file_size = fileHeader.offset_bits + img_size;

    infoHeader.image_size = img_size;
    infoHeader.bitmap_width = width;
    infoHeader.bitmap_height = height;
    delete[] data;
    data = newImg;
}

/// 文本定位
void BmpFile::textPositioningByWindow(const int &o_w, const int &o_h, const int &slope) {
    clock_t t_start = clock();
    const int w = o_w >> 2;
    const int h = o_h >> 2;
    // 首先保存原始数据图像
    auto *orgImgBak = new unsigned char[infoHeader.image_size];
    memcpy(orgImgBak, data, infoHeader.image_size);
    auto orgWidth = infoHeader.bitmap_width;
    auto orgHeight = infoHeader.bitmap_height;
    auto orgImgSize = infoHeader.image_size;
    // 图片压缩
    compressImg(slope, slope);
    // 使用sobel算子计算边缘强度 用边缘强度去寻找 而非原始图像的亮度
    sobelProcess();
    // 计算得到的边缘图 的 积分图
    getSumGryGraphBySumCol();
    const int &width = infoHeader.bitmap_width;
    const int &height = infoHeader.bitmap_height;
    int maxNum = 0, max_x = 0, max_y = 0;
    int w_2 = w / 2;
    int h_2 = h / 2;
//    for(int times = 0;times<1000;++times){
    for (int x = w_2, end_x = width - w_2 * 3, end_y = height - h_2 * 3; x < end_x; ++x) {
        for (int y = 0; y < end_y; ++y) {
            int tmpSum = getWindowsSumGraph(x, y, w, h);
            // 阈值选取目前最大的那个矩形框
            if (tmpSum < maxNum) {
                continue;
            }
            // 更新
            tmpSum = tmpSum - getWindowsSumGraph(x + w, y, w_2, h) - getWindowsSumGraph(x - w_2, y, w_2, h) -
                     getWindowsSumGraph(x, y + h, w, h_2);
            if (maxNum < tmpSum) {
                maxNum = tmpSum;
                max_x = x;
                max_y = y;
            }
        }
    }
//    }
    max_x <<= 2;
    max_y <<= 2;
    delete[] data;
    data = orgImgBak;
    infoHeader.bitmap_width = orgWidth;
    infoHeader.bitmap_height = orgHeight;
    infoHeader.image_size = orgImgSize;
    fileHeader.file_size = fileHeader.offset_bits + orgImgSize;
    drawImg(max_y, max_x, o_h, o_w);
    clock_t t_end = clock();
    std::cout << (t_end - t_start) / 1000.0;
}


/// 获取任意窗口大小的积分
int BmpFile::getWindowsSumGraph(const int &s_x, const int &s_y, const int &x_len, const int &y_len) {
    if (sumGraph == nullptr) {
        getSumGryGraphBySumCol();
    }
    const int &width = infoHeader.bitmap_width;
    const int &height = infoHeader.bitmap_height;
    auto *p_s = sumGraph + (s_y * width) + s_x;
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

// canny算子
void BmpFile::cannyProcess(const int &sigma, const int &maxVal, const int &minVal) {
    const unsigned &width = infoHeader.bitmap_width;
    const unsigned &height = infoHeader.bitmap_height;

    // 高斯滤波
    GaussianFilter(sigma);

    // sobel算子 计算得到梯度大小 和 方向（只需要 x 还是 y）
    // 梯度大小
    auto *resData = new unsigned char[infoHeader.image_size];
    memset(resData, 0, infoHeader.image_size);
    // 梯度方向 默认为0 -> x   1 -> y  2 -> 右上  3 -> 左上
    auto *resPos = new int[infoHeader.image_size];
    memset(resPos, -1, infoHeader.image_size << 2);
    auto *pRes = resData + width;
    auto *pResPos = resPos + width;
    double rate = 2.414213562373095;
    for (auto *pCur = data + width, *pEnd = data + width * (height - 1); pCur < pEnd;) {
        ++pCur, ++pRes, ++pResPos;
        for (auto *pWidthEnd = pCur + width - 2; pCur < pWidthEnd; ++pCur) {
            auto lastRow = pCur - width;
            auto nextRow = pCur + width;
            int dx = *(lastRow - 1) + *(pCur - 1) * 2 + *(nextRow - 1);
            dx -= *(lastRow + 1) + *(pCur + 1) * 2 + *(nextRow + 1);
            int dy = *(lastRow - 1) + *(lastRow) * 2 + *(lastRow + 1);
            dy -= *(nextRow - 1) + *(nextRow) * 2 + *(nextRow + 1);
            // 储存大小
            *(pRes++) = fmin(255, sqrt(dx * dx + dy * dy));
//            *(pRes++) = fmin(255, abs(dx) + abs(dy));
            // 储存方向
            // 正方向 只可能x y 右上
            if ((dx > 0 && dy > 0) || (dx < 0 && dy < 0)) {
                dx = abs(dx);
                dy = abs(dy);
                if (dx > dy) {
                    // "/"
                    if (rate * dy > dx) { *pResPos = 2; }
                    else { *pResPos = 0; }// "-"
                } else {
                    // "|"
                    if (dy > dx * rate) { *pResPos = 1; }
                    else { *pResPos = 2; } // "/"
                }
            } else {
                // 反方向 只可能x y 左上
                dx = abs(dx);
                dy = abs(dy);
                if (dx > dy) {
                    // "\"
                    if (rate * dy > dx) { *pResPos = 3; }
                    else { *pResPos = 0; }// "-"
                } else {
                    // "|"
                    if (dy > dx * rate) { *pResPos = 1; }
                    else { *pResPos = 3; } // "\"
                }
            }
            pResPos++;
        }
        ++pCur, ++pRes, ++pResPos;
    }

    //非最大值抑制 NMS
    auto *pCurPos = resPos + width;
    for (auto *pCur = resData + width, *pEnd = resData + width * (height - 1); pCur < pEnd;) {
        ++pCur, ++pCurPos;
        for (auto *pWidthEnd = pCur + width - 2; pCur < pWidthEnd; ++pCur, ++pCurPos) {
            if (*pCurPos == 0) {
                // '-'
                if (*pCur < *(pCur - 1) || *pCur < *(pCur + 1)) {
                    *pCur = 0x0;
                }
            } else if (*pCurPos == 1) {
                // '｜'
                if (*pCur < *(pCur - width) || *pCur < *(pCur + width)) {
                    *pCur = 0x0;
                }
            } else if (*pCurPos == 2) {
                // '/'
                if (*pCur < *(pCur - width + 1) || *pCur < *(pCur + width - 1)) {
                    *pCur = 0x0;
                }
            } else if (*pCurPos == 3) {
                // '\'
                if (*pCur < *(pCur - width - 1) || *pCur < *(pCur + width + 1)) {
                    *pCur = 0x0;
                }
            } else {
                *pCur = 0x0;
            }
        }
        ++pCur, ++pCurPos;
    }
    //双阈值
    for (auto *pCur = resData + width, *pEnd = resData + width * (height - 1); pCur < pEnd;) {
        ++pCur;
        for (auto *pWidthEnd = pCur + width - 2; pCur < pWidthEnd; ++pCur) {
            if (*pCur <= minVal) {
                *pCur = 0x0;
                continue;
            }
            if (minVal < *pCur && *pCur < maxVal) {
                auto *pLastRowCur = pCur - width;
                auto *pNextRowCur = pCur + width;
                if (*(pCur - 1) == 0 && *(pCur + 1) == 0 && *(pLastRowCur - 1) == 0 && *(pLastRowCur + 1) == 0 &&
                    *(pNextRowCur - 1) == 0 && *(pNextRowCur + 1) == 0 && *pLastRowCur == 0 && *pNextRowCur == 0) {
                    *pCur = 0x0;
                } else {
                    *pCur = 0xff;
                }
            } else if (*pCur >= maxVal) {
                *pCur = 0xff;
            }
        }
        ++pCur;
    }

    delete[] data;
    data = resData;
    delete[] resPos;
}

