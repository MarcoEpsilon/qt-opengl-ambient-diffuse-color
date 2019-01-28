#include <diffusewidget.hpp>
#include <marcoslider.hpp>
#include <QVBoxLayout>
#include <directionwidget.hpp>
#include <utils.hpp>
DiffuseWidget::DiffuseWidget(QWidget* parent) 
    : QWidget(parent)
{
    m_rSlider = new MarcoSlider("红色:    ");
    m_gSlider = new MarcoSlider("绿色:    ");
    m_bSlider = new MarcoSlider("蓝色:    ");
    m_indensitySlider = new MarcoSlider("光照强度:");
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_rSlider);
    layout->addWidget(m_gSlider);
    layout->addWidget(m_bSlider);
    layout->addWidget(m_indensitySlider);
    QVBoxLayout* allLayout = new QVBoxLayout();
    allLayout->addLayout(layout);
    m_mainLayout = new QVBoxLayout();
    m_directionWidget = new DirectionWidget();
    allLayout->addWidget(m_directionWidget);
    m_mainLayout->addLayout(allLayout);
    setLayout(m_mainLayout);
    setMaximumSize(QSize(340,215));
    m_rSlider->setObjectName("m_rSlider");
    m_gSlider->setObjectName("m_gSlider");
    m_bSlider->setObjectName("m_bSlider");
    m_indensitySlider->setObjectName("m_indensitySlider");
    std::string qss = Utils::readFile("../res/diffuse.qss");
    setStyleSheet(QString(qss.c_str()));
    initSignals();
}

DiffuseWidget::~DiffuseWidget() {

}
void DiffuseWidget::initSignals() {
    connect(m_rSlider,SIGNAL(sliderValueChanged()),this,SLOT(setDiffuse()));
    connect(m_gSlider,SIGNAL(sliderValueChanged()),this,SLOT(setDiffuse()));
    connect(m_bSlider,SIGNAL(sliderValueChanged()),this,SLOT(setDiffuse()));
    connect(m_indensitySlider,SIGNAL(sliderValueChanged()),this,SLOT(setDiffuse()));
    connect(m_directionWidget,SIGNAL(directionChanged()),this,SLOT(setDiffuse()));
}
void DiffuseWidget::setDiffuse() {
    float r = m_rSlider->getSliderValue();
    float g = m_gSlider->getSliderValue();
    float b = m_bSlider->getSliderValue();
    float idensity = m_indensitySlider->getSliderValue();
    emit diffuseChanged(std::make_pair(glm::vec4(r,g,b,idensity),m_directionWidget->getDirection()));
    return;
}