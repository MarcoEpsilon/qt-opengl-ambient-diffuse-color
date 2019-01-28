#ifndef __DIRECTION_WIDGET_HPP__
#define __DIRECTION_WIDGET_HPP__
#include <QWidget>
#include <glm/glm.hpp>
class QSpinBox;
class QVBoxLayout;
class DirectionWidget : public QWidget {
    Q_OBJECT
public:
    explicit DirectionWidget(QWidget* parent = 0);
    ~DirectionWidget();
    glm::vec3 getDirection();
public slots:
    void setDirection(int);
signals:
    void directionChanged();
private:
    QSpinBox* m_xBox;
    QSpinBox* m_yBox;
    QSpinBox* m_zBox;
    QVBoxLayout* m_mainLayout;
    void initSignals();
};
#endif /*__DIRECTION_WIDGET_HPP__*/