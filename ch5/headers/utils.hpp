#ifndef __UTILS_HPP__
#define __UTILS_HPP__
#include <glm/glm.hpp>
#include <string>
class QString;
class QImage;
class Utils {
public:
    explicit Utils();
    ~Utils();
    struct ImageInfo {
        int i_width;
        int i_height;
        int i_nChannels;
        unsigned char* i_data;
    };
    static std::string readFile(const char* fileName);
    static glm::vec3 getVec3f(const float*);
    static ImageInfo getImageInfo(const char* img);
    static void freeImageInfo(unsigned char* data);
    static QImage* readImage(const char* imgFile);
    static void freeImage(QImage* img);
};
#endif /*__UTILS_HPP__*/