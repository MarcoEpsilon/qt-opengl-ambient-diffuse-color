#ifndef __AMBIENT_WIDGET_HPP__
#define __AMBIENT_WIDGET_HPP__
#include <QWidget>
#include <glm/glm.hpp>
class MarcoSlider;
class QVBoxLayout;
class AmbientWidget : public QWidget {
    Q_OBJECT
public:
    explicit AmbientWidget(QWidget* parent = 0);
    ~AmbientWidget();
public slots:
    void setAmbient();
signals:
    void ambientChanged(const glm::vec4& ambient);
private:
    MarcoSlider* m_rSlider;
    MarcoSlider* m_gSlider;
    MarcoSlider* m_bSlider;
    MarcoSlider* m_indensitySlider;
    QVBoxLayout* m_mainLayout;
    void initSignals();
};
#endif /*__AMBIENT_WIDGET_HPP__*/