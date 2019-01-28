#include <utils.hpp>
#include <QString>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <stb_image.hpp>
#include <QDebug>
#include <QImage>
Utils::Utils() {

}
Utils::~Utils() {

}
std::string Utils::readFile(const char* fileName) {
    std::string s;
    char buf[4092];
    FILE* fp = fopen(fileName,"r");
    assert(fp);
    while (!feof(fp)) {
        memset(buf,sizeof(buf),0);
        fgets(buf,sizeof(buf),fp);
        s += std::string(buf);
    }
    return s;
}
glm::vec3 Utils::getVec3f(const float* vec) {
    glm::vec3 ret;
    //assert(sizeof(vec) >= sizeof(float) * 3);
    for (int i = 0; i < 3; ++i) {
        ret[i] = vec[i];
    }
    return ret;
}
Utils::ImageInfo Utils::getImageInfo(const char* imgFile) {
    int width,height,nChannels;
    //unsigned char* data = stbi_load(imgFile,&width,&height,&nChannels,0);
    QImage img;
    Utils::ImageInfo ret;
    img.load(imgFile);
    unsigned int size = _msize(img.bits());
    ret.i_data = new unsigned char[size];
    memcpy(ret.i_data,img.bits(),size);
    qDebug() << size;
    qDebug() << _msize(ret.i_data);
    //assert(data != 0);
    ret.i_width = img.width();
    ret.i_height = img.height();
    ret.i_nChannels = 0;
    return ret;
}

void Utils::freeImageInfo(unsigned char* data) {
    assert(data != 0);
    delete [] data;
}

QImage* Utils::readImage(const char* imgFile) {
    QImage* img = new QImage();
    assert(img->load(imgFile));
    return img;
} 
void Utils::freeImage(QImage* img) {
    delete img;
}