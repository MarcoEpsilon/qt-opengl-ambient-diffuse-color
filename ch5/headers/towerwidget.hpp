#ifndef __TOWER_WIDGET_HPP__
#define __TOWER_WIDGET_HPP__
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <glm/glm.hpp>
#include <utility>
class TowerWidget :public QOpenGLWidget,protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit TowerWidget(QWidget* parent = 0);
    ~TowerWidget();
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width,int height) override;
public slots:
    void setAmbient(const glm::vec4& ambient);
    void setDiffuse(const std::pair<glm::vec4,glm::vec3>&);
private:
    GLuint m_vbo;
    GLuint m_ibo;
    GLuint m_worldLocation;
    GLuint m_texture;
    GLuint m_textureLocation;
    GLuint m_modelMatrixLocation;
    float m_rotateAngle;
    void initBuffer();
    void setWorldMatrix();
    void initTexture(const char* imgFile);
    GLuint initVertexShader(const char* source);
    GLuint initFragmentShader(const char* source);
    void initProgram();
    void setLight();
    //顶点
    struct Vertex {
        float vertPos[3];
        float texCoord[2];
        float normalDirection[3];
        Vertex(const glm::vec3& vert,const glm::vec2& tex) {
            for (int i = 0; i < 3; ++i) {
                vertPos[i] = vert[i];
                normalDirection[i] = 0.0f;
                if (i < 2) {
                    texCoord[i] = tex[i];
                }
            }
        }
        void addNormal(const glm::vec3& normal) {
            for (int i = 0; i < 3; ++i) {
                normalDirection[i] += normal[i];
            }
        }
    };
    //光照
    struct Light {
        float ambientLightQuality[3];
        float ambientLightIntensity;
        float diffuseLightDirection[3];
        float diffuseLightQuality[3];
        float diffuseLightIntensity;
        Light() {
            for (int i = 0; i < 3; ++i) {
                ambientLightQuality[i] = 1.0f;
                diffuseLightDirection[i] = 0.0f;
                diffuseLightQuality[i] = 0.0f;
            }
            ambientLightIntensity = 1.0f;
            diffuseLightIntensity = 1.0f;
        }
    } m_light;
    struct LightLocation {
        GLuint ambientLightQualityLocation;
        GLuint ambientLightIntensityLocation;
        GLuint diffuseLightDirectionLocation;
        GLuint diffuseLightQualityLocation;
        GLuint diffuseLightIntensityLocation;
    } m_lightLocation;
};
#endif /*__TOWER__WIDGET_HPP__*/