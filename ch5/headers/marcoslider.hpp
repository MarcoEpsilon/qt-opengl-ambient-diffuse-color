#ifndef __MARCO_SLIDER_HPP__
#define __MARCO_SLIDER_HPP__
#include <QWidget>
class QSlider;
class QLabel;
class QVBoxLayout;
class MarcoSlider : public QWidget {
    Q_OBJECT
public:
    MarcoSlider(const char* hint,QWidget* parent = 0);
    ~MarcoSlider();
    float getSliderValue();
public slots:
    void whenSlider(int);
signals:
    void sliderValueChanged();
private:
    QSlider* m_slider;
    QLabel* m_hint;
    QLabel* m_lower;
    QLabel* m_higher;
    QVBoxLayout* m_mainLayout;
};
#endif /*__MARCO_SLIDER_HPP__*/