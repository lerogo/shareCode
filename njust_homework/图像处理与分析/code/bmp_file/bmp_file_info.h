//
// Created by lerogo on 2021/6/8.
// 定义bmp图片文件用到的结构体
//

#ifndef IMAGE_PROCESSING_BMP_FILE_INFO_H
#define IMAGE_PROCESSING_BMP_FILE_INFO_H

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


#endif //IMAGE_PROCESSING_BMP_FILE_INFO_H
