#include <directionwidget.hpp>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <utils.hpp>
DirectionWidget::DirectionWidget(QWidget* parent) 
    : QWidget(parent)
{
    QLabel* hint = new QLabel("方向");
    QLabel* lx = new QLabel("X");
    QLabel* ly = new QLabel("Y");
    QLabel* lz = new QLabel("Z");
    m_xBox = new QSpinBox();
    m_yBox = new QSpinBox();
    m_zBox = new QSpinBox();
    m_xBox->setMinimum(-1000);
    m_xBox->setMaximum(1000);
    m_yBox->setMinimum(-1000);
    m_yBox->setMaximum(1000);
    m_zBox->setMinimum(-1000);
    m_zBox->setMaximum(1000);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(hint);
    layout->addWidget(lx);
    layout->addWidget(m_xBox);
    layout->addWidget(ly);
    layout->addWidget(m_yBox);
    layout->addWidget(lz);
    layout->addWidget(m_zBox);
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addLayout(layout);
    setLayout(m_mainLayout);
    std::string qss = Utils::readFile("../res/direction.qss");
    setStyleSheet(QString(qss.c_str()));
    initSignals();
}

DirectionWidget::~DirectionWidget() {

}

void DirectionWidget::setDirection(int) {
    emit directionChanged();
    return;
}
void DirectionWidget::initSignals() {
    connect(m_xBox,SIGNAL(valueChanged(int)),this,SLOT(setDirection(int)));
    connect(m_yBox,SIGNAL(valueChanged(int)),this,SLOT(setDirection(int)));
    connect(m_zBox,SIGNAL(valueChanged(int)),this,SLOT(setDirection(int)));
}
glm::vec3 DirectionWidget::getDirection() {
    float x = static_cast<float>(m_xBox->value());
    float y = static_cast<float>(m_yBox->value());
    float z = static_cast<float>(m_zBox->value());
    return glm::vec3(x,y,z);
}