#include <iostream>
#include <unistd.h>
#include "bmp_file/bmp_file_process.hpp"

int main() {
    try {
        using namespace hhl;
        std::string pwd = getcwd(nullptr, 0);
        pwd += "/../data/cpt4_2/";
        bmp_file_process *p = bmp_file_process::getBmpFile();
        p->init(1000, 1000, "gry", false, 2);
        for (int i = 50; i < 100; ++i) {
            std::string orgFileName = pwd + "000" + std::to_string(i) + ".bmp";
            std::string desImgFileName = orgFileName.substr(0, orgFileName.length() - 4) + "_bak.bmp";
            std::cout << orgFileName << std::endl;
            bmp_file *b1 = p->load(orgFileName);
            bmp_file *b2 = p->textPositioningByWindow(b1, 100, 100, 2);
            p->save(b2, desImgFileName);
            delete b1;
            delete b2;
        }

        bmp_file_process::delBmpFile();
    } catch (...) {
        std::cerr << "错误";
        exit(-1);
    }
    return 0;
}
