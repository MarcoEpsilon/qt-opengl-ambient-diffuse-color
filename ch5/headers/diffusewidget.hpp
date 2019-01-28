#ifndef __DIFFUSE_WIDGET_HPP__
#define __DIFFUSE_WIDGET_HPP__
#include <QWidget>
#include <utility>
#include <glm/glm.hpp>
class MarcoSlider;
class QVBoxLayout;
class DirectionWidget;
class DiffuseWidget : public QWidget {
    Q_OBJECT
public:
    explicit DiffuseWidget(QWidget* parent = 0);
    ~DiffuseWidget();
public slots:
    void setDiffuse();
signals:
    void diffuseChanged(const std::pair<glm::vec4,glm::vec3>&);
private:
    MarcoSlider* m_rSlider;
    MarcoSlider* m_gSlider;
    MarcoSlider* m_bSlider;
    MarcoSlider* m_indensitySlider;
    DirectionWidget* m_directionWidget;
    QVBoxLayout* m_mainLayout;
    void initSignals();
};
#endif /*__DIFFUSE_WIDGET_HPP__*/