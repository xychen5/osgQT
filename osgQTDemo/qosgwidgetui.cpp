#include "qosgwidgetui.h"
#include "ui_qosgwidgetui.h"

QOsgWidgetUi::QOsgWidgetUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QOsgWidgetUi)
{
    ui->setupUi(this);
}

QOsgWidgetUi::QOsgWidgetUi(QWidget *parent, std::string modelPath) :
    QWidget(parent),
    ui(new Ui::QOsgWidgetUi)
{
    ui->setupUi(this);
    initQOsgWidget(modelPath);
}

void QOsgWidgetUi::initQOsgWidget(std::string modelPath)
{
    // init the osgQOpenGLWidget
    modelInterface = new QOsgWidget(modelPath, static_cast<QWidget*>(this->parent()));

    // put hte osgQOpenGLWidget into the osgWidgetUi
    ui->verticalLayout->addWidget(modelInterface->pWidget);
    return ;
}

QOsgWidgetUi::~QOsgWidgetUi()
{
    delete ui;
}
