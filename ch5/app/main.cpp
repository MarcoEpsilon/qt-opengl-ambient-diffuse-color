#include <QApplication>
#include <mainwindow.hpp>
#include <ambientwidget.hpp>
#include <directionwidget.hpp>
#include <diffusewidget.hpp>
int main(int argc,char** argv) {
    QApplication app(argc,argv);
    MainWindow* w = new MainWindow();
    w->show();
    /*AmbientWidget* w = new AmbientWidget();
    w->show();*/
    /*DirectionWidget* w = new DirectionWidget();
    w->show();*/
    /*DiffuseWidget* w = new DiffuseWidget();
    w->show();*/
    return app.exec();
}