#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__
#include <QWidget>
class TowerWidget;
class AmbientWidget;
class QVBoxLayout;
class DiffuseWidget;
class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow();
    ~MainWindow();
private:
    TowerWidget* m_towerWidget;
    AmbientWidget* m_ambientWidget;
    DiffuseWidget* m_diffuseWidget;
    QVBoxLayout* m_mainLayout;
    void initSignals();
};
#endif /*__MAIN_WINDOW_HPP__*/