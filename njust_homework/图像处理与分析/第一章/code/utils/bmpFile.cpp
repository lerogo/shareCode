//
// Created by lerogo on 2021/5/13.
//

#include "bmpFile.h"

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
    // 再次读取一次
    auto fileData = new unsigned char[fileHeader.file_size];
    infile.seekg(0, std::ios::beg).read(reinterpret_cast<char *>(fileData), fileHeader.file_size);
    infile.close();
    // 储存用 header
    header = new unsigned char[fileHeader.offset_bits];
    memcpy(header, fileData, fileHeader.offset_bits);
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
    delete[] fileData;
}

void BmpFile::save(const std::string &fileName) const {
    // 读取文件
    std::ofstream outfile(fileName, std::ios::out | std::ios::binary);
    if (!outfile) {
        std::cerr << "Open file failed." << std::endl;
        throw;
    }
    // 写入头
    outfile.write(reinterpret_cast<const char *>(header), fileHeader.offset_bits);
    // 写入文件
    outfile.write(reinterpret_cast<const char *>(data), infoHeader.image_size);
    outfile.close();
}

bool BmpFile::Invert() const {
    try {
        for (int *pCurImg = reinterpret_cast<int *>(data), *pEndImg =
                pCurImg + infoHeader.image_size / sizeof(int) * sizeof(unsigned char);
             pCurImg != pEndImg; ++pCurImg) {
            *pCurImg = ~*pCurImg;
        }
        return true;
    } catch (...) {
        return false;
    }
}

bool BmpFile::gryPseudoColor() const {
    if (isRgb) {
        return false;
    }
    memset(palette, 0, paletteNum * paletteSize);
    for (unsigned i = 0; i < paletteNum; ++i) {
        palette[i].blue = i;
    }
    memcpy(header + fileHeaderSize + infoHeaderSize, palette, paletteSize * paletteNum);
    return true;
}
