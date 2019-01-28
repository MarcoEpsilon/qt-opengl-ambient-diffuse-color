#include <marcoslider.hpp>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
MarcoSlider::MarcoSlider(const char* hint,QWidget* parent)
    : QWidget(parent)
{
    m_slider = new QSlider(Qt::Horizontal);
    m_hint = new QLabel(QString(hint));
    m_lower = new QLabel("0.0");
    m_higher = new QLabel("1.0");
    m_slider->setMinimum(0);
    m_slider->setMaximum(999);
    m_slider->setTickInterval(1);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m_hint);
    layout->addWidget(m_lower);
    layout->addWidget(m_slider);
    layout->addWidget(m_higher);
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addLayout(layout);
    setLayout(m_mainLayout);
    layout->setStretch(0,0);
    layout->setStretch(2,1);
    connect(m_slider,SIGNAL(valueChanged(int)),this,SLOT(whenSlider(int)));
}
MarcoSlider::~MarcoSlider() {

}
float MarcoSlider::getSliderValue() {
    int maxi = m_slider->maximum();
    int mini = m_slider->minimum();
    int pos = m_slider->value();
    float inter = static_cast<float>(pos) / static_cast<float>(maxi - mini);
    return inter;
}
void MarcoSlider::whenSlider(int) {
    emit sliderValueChanged();
}