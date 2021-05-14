#include <iostream>
#include "utils/bmpFile.h"

int main() {
    try {
        std::string orgFileName = "H0101Gry.bmp";
        std::string desImgFileName = "H0101Gry1_bak.bmp";

        BmpFile bmpFile;
        bmpFile.load(orgFileName);
        if(bmpFile.gryPseudoColor()){
            bmpFile.save(desImgFileName);
        }else{
            std::cerr<<"err";
        }
    } catch (...) {
        std::cerr << "错误";
        exit(-1);
    }
    return 0;
}