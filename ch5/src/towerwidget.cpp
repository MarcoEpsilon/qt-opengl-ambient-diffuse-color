#include <towerwidget.hpp>
#include <utils.hpp>
#include <QDebug>
#include <glm/gtc/matrix_transform.hpp>
#include <QTimer>
TowerWidget::TowerWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_vbo(0)
    , m_ibo(0)
    , m_texture(0)
    , m_rotateAngle(0.0f)
    , m_light()
{
    setFixedSize(400,400);
    QTimer* t = new QTimer();
    connect(t,SIGNAL(timeout()),this,SLOT(update()));
    t->start(1000);
}

TowerWidget::~TowerWidget() {

}

void TowerWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    initBuffer();
    initProgram();
    initTexture("../res/img/tex.jpg");
    glEnable(GL_DEPTH_TEST);
}

void TowerWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,width(),height());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(const void*)0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,8 * sizeof(float),(const void*)(3 * sizeof(float)));
    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(const void*)(5 * sizeof(float)));
    glBindTexture(GL_TEXTURE_2D,m_texture);
    setWorldMatrix();
    setLight();
    glDrawElements(GL_TRIANGLES,18,GL_UNSIGNED_INT,0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glFlush();
}

void TowerWidget::resizeGL(int width,int height) {

}

void TowerWidget::initBuffer() {
    Vertex verts[5] = {
        //顶点
        Vertex(glm::vec3(0.0f,0.5f,0.0f),glm::vec2(0.5f,1.0f)),
        //下底面
        Vertex(glm::vec3(-0.5f,-0.5f,-0.5f),glm::vec2(0.0f,1.0f)),
        Vertex(glm::vec3(-0.5f,-0.5f,0.5f),glm::vec2(0.0f,0.0f)),
        Vertex(glm::vec3(0.5f,-0.5f,0.5f),glm::vec2(1.0f,0.0f)),
        Vertex(glm::vec3(0.5f,-0.5f,-0.5f),glm::vec2(1.0f,1.0f))
    };
    unsigned int indicates[] = {
        //正面
        0,2,3,
        //背面
        0,1,4,
        //左
        0,1,2,
        //右
        0,4,3,
        //底面
        1,2,3,
        3,4,1
    };
    int indicatesCount = sizeof(indicates) / sizeof(unsigned int);
    //初始化法向量
    for (int i = 0; i < indicatesCount; i += 3) {
        unsigned int index1 = indicates[i];
        unsigned int index2 = indicates[i + 1];
        unsigned int index3 = indicates[i + 2];
        glm::vec3 vert1 = Utils::getVec3f(verts[index1].vertPos);
        glm::vec3 vert2 = Utils::getVec3f(verts[index2].vertPos);
        glm::vec3 vert3 = Utils::getVec3f(verts[index3].vertPos);
        glm::vec3 dir1 = vert2 - vert1;
        glm::vec3 dir2 = vert3 - vert1;
        glm::vec3 normal = glm::normalize(cross(dir1,dir2));
        verts[index1].addNormal(normal);
        verts[index2].addNormal(normal);
        verts[index3].addNormal(normal);
    }
    glGenBuffers(1,&m_vbo);
    glGenBuffers(1,&m_ibo);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ibo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indicates),indicates,GL_STATIC_DRAW);
}
GLuint TowerWidget::initVertexShader(const char* source) {
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    assert(vertexShaderId != 0);
    std::string s = Utils::readFile(source);
    const char* sourceCode = s.c_str();
    GLint size = strlen(sourceCode);
    glShaderSource(vertexShaderId,1,&sourceCode,&size);
    glCompileShader(vertexShaderId);
    GLint success;
    char errText[4092];
    glGetShaderiv(vertexShaderId,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderId,sizeof(errText) - 1,NULL,errText);
        qDebug() << errText;
        exit(-1);
    }
    return vertexShaderId;
}
GLuint TowerWidget::initFragmentShader(const char* source) {
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    assert(fragmentShaderId != 0);
    std::string s = Utils::readFile(source);
    const char* sourceCode = s.c_str();
    GLint size = strlen(sourceCode);
    glShaderSource(fragmentShaderId,1,&sourceCode,&size);
    glCompileShader(fragmentShaderId);
    GLint success;
    char errText[4092];
    glGetShaderiv(fragmentShaderId,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderId,sizeof(errText) - 1,NULL,errText);
        qDebug() << errText;
        exit(-1);
    }
    return fragmentShaderId;
}
void TowerWidget::initProgram() {
    GLuint programId = glCreateProgram();
    assert(programId != 0);
    GLuint vertexShaderId = initVertexShader("../res/tower.vert");
    GLuint fragmentShaderId = initFragmentShader("../res/tower.frag");
    glAttachShader(programId,vertexShaderId);
    glAttachShader(programId,fragmentShaderId);
    glLinkProgram(programId);
    GLint success;
    char errText[4092];
    glGetProgramiv(programId,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(fragmentShaderId,sizeof(errText) - 1,NULL,errText);
        qDebug() << errText;
        exit(-1);
    }
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glUseProgram(programId);
    m_worldLocation = glGetUniformLocation(programId,"worldMatrix");
    assert(m_worldLocation != 0xFFFFFFFF);
    m_modelMatrixLocation = glGetUniformLocation(programId,"modelMatrix");
    assert(m_modelMatrixLocation != 0xFFFFFFFF);
    setWorldMatrix();
    m_textureLocation = glGetUniformLocation(programId,"tex");
    assert(m_textureLocation != 0xFFFFFFFF);
    glUniform1i(m_textureLocation,0);
    //得到灯光的Location
    m_lightLocation.ambientLightQualityLocation = glGetUniformLocation(programId,"fLight.ambientLightQuality");
    assert(m_lightLocation.ambientLightQualityLocation != 0xFFFFFFFF);
    m_lightLocation.ambientLightIntensityLocation = glGetUniformLocation(programId,"fLight.ambientLightIntensity");
    assert(m_lightLocation.ambientLightIntensityLocation != 0xFFFFFFFF);
    m_lightLocation.diffuseLightQualityLocation = glGetUniformLocation(programId,"fLight.diffuseLightQuality");
    assert(m_lightLocation.diffuseLightQualityLocation != 0xFFFFFFFF);
    m_lightLocation.diffuseLightIntensityLocation = glGetUniformLocation(programId,"fLight.diffuseLightIntensity");
    assert(m_lightLocation.diffuseLightIntensityLocation != 0xFFFFFFFF);
    m_lightLocation.diffuseLightDirectionLocation = glGetUniformLocation(programId,"fLight.diffuseLightDirection");
    assert(m_lightLocation.diffuseLightDirectionLocation != 0xFFFFFFFF);
    setLight();
}
void TowerWidget::setWorldMatrix() {
    glm::mat4 model = glm::scale(glm::mat4(1.0f),glm::vec3(1.5f,1.5f,1.5f));
    glm::mat4 viewPort = glm::translate(model,glm::vec3(0.0f,0.0f,-3.0f));
    model = glm::rotate(model,m_rotateAngle * glm::pi<float>() / 180.0f,glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 projection = glm::perspective(glm::pi<float>() / 4,1.0f,1.0f,100.0f);
    glm::mat4 world = projection * viewPort * model;
    glUniformMatrix4fv(m_worldLocation,1,GL_FALSE,&world[0][0]);
    glUniformMatrix4fv(m_modelMatrixLocation,1,GL_FALSE,&model[0][0]);
    m_rotateAngle += 1.0f;
    if (m_rotateAngle >= 360.0f) {
        m_rotateAngle = 0.0f;
    }
}
void TowerWidget::initTexture(const char* imgFile) {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&m_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    QImage* img = Utils::readImage(imgFile);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->width(),img->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,img->mirrored().bits());
    Utils::freeImage(img);
}

void TowerWidget::setAmbient(const glm::vec4& ambient) {
    qDebug() << ambient[0] << " " << ambient[1] << " " << ambient[2] << " " << ambient[3];
    for (int i = 0; i < 3; ++i) {
        m_light.ambientLightQuality[i] = ambient[i];
    }
    m_light.ambientLightIntensity = ambient[3];
    update();
}

void TowerWidget::setDiffuse(const std::pair<glm::vec4,glm::vec3>& diffuse) {
    qDebug() << diffuse.first[0] << " " << diffuse.first[1] << " " << diffuse.first[2] << " "<< diffuse.first[3];
    qDebug() << diffuse.second[0] << " " << diffuse.second[1] << " " << diffuse.second[2];
    for (int i = 0; i < 3; ++i) {
        m_light.diffuseLightQuality[i] = diffuse.first[i];
        m_light.diffuseLightDirection[i] = diffuse.second[i];
    }
    m_light.diffuseLightIntensity = diffuse.first[3];
    update();
}
void TowerWidget::setLight() {
    glUniform3fv(m_lightLocation.ambientLightQualityLocation,1,&m_light.ambientLightQuality[0]);
    glUniform1f(m_lightLocation.ambientLightIntensityLocation,m_light.ambientLightIntensity);
    glUniform3fv(m_lightLocation.diffuseLightQualityLocation,1,&m_light.diffuseLightQuality[0]);
    glUniform1f(m_lightLocation.diffuseLightIntensityLocation,m_light.diffuseLightIntensity);
    glUniform3fv(m_lightLocation.diffuseLightDirectionLocation,1,&m_light.diffuseLightDirection[0]);
}