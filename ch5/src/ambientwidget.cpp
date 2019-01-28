#include <ambientwidget.hpp>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <marcoslider.hpp>
#include <utils.hpp>
AmbientWidget::AmbientWidget(QWidget* parent) 
    : QWidget(parent)
{
    m_rSlider = new MarcoSlider("红色:    ",this);
    m_gSlider = new MarcoSlider("绿色:    ",this);
    m_bSlider = new MarcoSlider("蓝色:    ",this);
    m_indensitySlider = new MarcoSlider("光照强度:",this);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_rSlider);
    layout->addWidget(m_gSlider);
    layout->addWidget(m_bSlider);
    layout->addWidget(m_indensitySlider);
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addLayout(layout);
    setLayout(m_mainLayout);
    setMinimumSize(QSize(280,200));
    setMaximumSize(QSize(340,210));
    std::string qss = Utils::readFile("../res/ambient.qss");
    m_rSlider->setObjectName("m_rSlider");
    m_gSlider->setObjectName("m_gSlider");
    m_bSlider->setObjectName("m_bSlider");
    m_indensitySlider->setObjectName("m_indensitySlider");
    setStyleSheet(QString(qss.c_str()));
    initSignals();
}

AmbientWidget::~AmbientWidget() {

}
void AmbientWidget::setAmbient() {
    float r = m_rSlider->getSliderValue();
    float g = m_gSlider->getSliderValue();
    float b = m_bSlider->getSliderValue();
    float idensity = m_indensitySlider->getSliderValue();
    emit ambientChanged(glm::vec4(r,g,b,idensity));
    return;
}
void AmbientWidget::initSignals() {
    connect(m_rSlider,SIGNAL(sliderValueChanged()),this,SLOT(setAmbient()));
    connect(m_gSlider,SIGNAL(sliderValueChanged()),this,SLOT(setAmbient()));
    connect(m_bSlider,SIGNAL(sliderValueChanged()),this,SLOT(setAmbient()));
    connect(m_indensitySlider,SIGNAL(sliderValueChanged()),this,SLOT(setAmbient()));
}