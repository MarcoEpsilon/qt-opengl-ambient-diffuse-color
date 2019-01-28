#include <mainwindow.hpp>
#include <towerwidget.hpp>
#include <ambientwidget.hpp>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <diffusewidget.hpp>
#include <QLabel>
#include <QDebug>
MainWindow::MainWindow() 
    : QWidget()
{
    resize(800,700);
    setWindowTitle("三年二班");
    QHBoxLayout* layout = new QHBoxLayout();
    m_towerWidget = new TowerWidget();
    layout->addStretch();
    layout->addWidget(m_towerWidget);
    layout->addStretch();
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addLayout(layout);
    QHBoxLayout* bottom = new QHBoxLayout();
    m_ambientWidget = new AmbientWidget();
    m_diffuseWidget = new DiffuseWidget();
    QLabel* ambientTitle = new QLabel("环境光照");
    QLabel* diffuseTitle = new QLabel("漫反射光照");
    QHBoxLayout* ambientTitleLayout = new QHBoxLayout();
    ambientTitleLayout->addStretch();
    ambientTitleLayout->addWidget(ambientTitle);
    ambientTitleLayout->addStretch();
    QVBoxLayout* ambientLayout = new QVBoxLayout();
    ambientLayout->addLayout(ambientTitleLayout);
    ambientLayout->addWidget(m_ambientWidget);
    ambientLayout->addStretch();
    QHBoxLayout* diffuseTitleLayout = new QHBoxLayout();
    diffuseTitleLayout->addStretch();
    diffuseTitleLayout->addWidget(diffuseTitle);
    diffuseTitleLayout->addStretch();
    QVBoxLayout* diffuseLayout = new QVBoxLayout();
    diffuseLayout->addLayout(diffuseTitleLayout);
    diffuseLayout->addWidget(m_diffuseWidget);
    diffuseLayout->addStretch();
    bottom->addLayout(ambientLayout);
    bottom->addLayout(diffuseLayout);
    bottom->setContentsMargins(QMargins(0,30,0,0));
    m_mainLayout->addLayout(bottom);
    setLayout(m_mainLayout);
    initSignals();
}

MainWindow::~MainWindow() {

}

void MainWindow::initSignals() {
    connect(m_ambientWidget,SIGNAL(ambientChanged(const glm::vec4&)),m_towerWidget,SLOT(setAmbient(const glm::vec4&)));
    connect(m_diffuseWidget,SIGNAL(diffuseChanged(const std::pair<glm::vec4,glm::vec3>&)),m_towerWidget,SLOT(setDiffuse(const std::pair<glm::vec4,glm::vec3>&)));
}