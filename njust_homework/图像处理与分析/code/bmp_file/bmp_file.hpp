//
// Created by lerogo on 2021/6/9.
//

#ifndef IMAGE_PROCESSING_BMP_FILE_HPP
#define IMAGE_PROCESSING_BMP_FILE_HPP

namespace hhl {
    typedef unsigned char u_char;

    // bmp文件类 只和文件信息相关
    class bmp_file {
    public:
        bmp_file() = default;

        ~bmp_file();

        //文件头
        bitmap_file_header fileHeader{};
        //信息头
        bitmap_info_header infoHeader{};
        //调色板
        bitmap_palette *palette = nullptr;
        //调色板数量 256
        unsigned paletteNum = 1 << 8;
        unsigned fileHeaderSize = sizeof(fileHeader);
        unsigned infoHeaderSize = sizeof(infoHeader);
        unsigned paletteSize = sizeof(bitmap_palette);

        // 是否是rgb
        bool isRgb = false;
        // 是否反向
        bool isInvert = false;
        // 数据
        u_char *data = nullptr;
        // 直方图
        int *histogram = nullptr;
        // 亮度
        double bright = 0;
        // 对比度
        double contrast = 0;
        //积分图
        int *sumGraph = nullptr;
    };

    bmp_file::~bmp_file() {
        delete[] palette;
        delete[] data;
        delete[] histogram;
        delete[] sumGraph;
    }

}


#endif //IMAGE_PROCESSING_BMP_FILE_HPP
