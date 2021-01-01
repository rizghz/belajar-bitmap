#include "image.h"

#define BYTES_PER_PIXEL  3   // RGB (Red, Green, Blue)
#define FILE_HEADER_SIZE 14  // bitmap file header size
#define INFO_HEADER_SIZE 40  // bitmap info header size

uint8_t* create_bmp_fileheader(int height, int stride) {
    
    int file_size = ( \
        FILE_HEADER_SIZE + \
        INFO_HEADER_SIZE + \
        stride * \
        height
    );

    static uint8_t file_header[] = {
        0u, 0u,          // signature
        0u, 0u, 0u, 0u,  // image file size in bytes
        0u, 0u, 0u, 0u,  // reserved
        0u, 0u, 0u, 0u   // start of pixel array
    };

    file_header[0]  = uint8_t('B');
    file_header[1]  = uint8_t('M');
    file_header[2]  = uint8_t(file_size);
    file_header[3]  = uint8_t(file_size >> 8);
    file_header[4]  = uint8_t(file_size >> 16);
    file_header[5]  = uint8_t(file_size >> 24);
    file_header[10] = uint8_t((FILE_HEADER_SIZE + INFO_HEADER_SIZE));

    return file_header;

}

uint8_t* create_bmp_infoheader(int height, int width) {
    
    static uint8_t info_header[] = {
        0u, 0u, 0u, 0u,  // header size
        0u, 0u, 0u, 0u,  // image width
        0u, 0u, 0u, 0u,  // image height
        0u, 0u,          // number of color planes
        0u, 0u,          // bits per pixel
        0u, 0u, 0u, 0u,  // compression
        0u, 0u, 0u, 0u,  // image size
        0u, 0u, 0u, 0u,  // horizontal resolution
        0u, 0u, 0u, 0u,  // vertical resolution
        0u, 0u, 0u, 0u,  // colors in color table
        0u, 0u, 0u, 0u   // important color count
    };

    info_header[0]  = uint8_t(INFO_HEADER_SIZE);
    info_header[4]  = uint8_t(width);
    info_header[5]  = uint8_t(width >> 8);
    info_header[6]  = uint8_t(width >> 16);
    info_header[7]  = uint8_t(width >> 24);
    info_header[8]  = uint8_t(height);
    info_header[9]  = uint8_t(height >> 8);
    info_header[10] = uint8_t(height >> 16);
    info_header[11] = uint8_t(height >> 24);
    info_header[12] = uint8_t(1u);
    info_header[14] = uint8_t(BYTES_PER_PIXEL * 8);

    return info_header;

}

uint8_t* create_header(int height, int width, int stride) {
    return (uint8_t*)(1);
}

void generate_bmp_img(uint8_t* img, int height, int width, const char* filename) {
    
    FILE* file = fopen(filename, "wb");

    int width_in_bytes = width * BYTES_PER_PIXEL;

    uint8_t padding[] = {
        0, 0, 0
    };

    int padding_size = (4 - (width_in_bytes) % 4) % 4;
    int stride = width_in_bytes + padding_size;

    uint8_t* file_header = create_bmp_fileheader(height, stride);
    fwrite(file_header, 1, FILE_HEADER_SIZE, file);

    uint8_t* info_header = create_bmp_infoheader(height, width);
    fwrite(info_header, 1, INFO_HEADER_SIZE, file);

    for (size_t i = 0; i < height; i++) {
        fwrite(img + (i * width_in_bytes), BYTES_PER_PIXEL, width, file);
        fwrite(padding, 1, padding_size, file);
    }

    printf("[!] gambar %s telah dibuat\n", filename);

    fclose(file);

}