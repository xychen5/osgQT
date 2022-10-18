#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qOsgWidget.h"
#include "qOsgWidgetUi.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // QOsgWidget* modelInterface = new QOsgWidget(this);

    // put hte osgQOpenGLWidget into the osgWidgetUi
    // osgQOpenGLWidget is essential
    // ui->horizontalLayoutWidget = osgWidgetUi;
    // 	std::string modelPath = "D:/glider.osg";
    // 	// QGridLayout* centralGridLayout = (QGridLayout*)ui->centralWidget->layout();
    // 	std::cout<<"check2"<<std::endl;

    // 	// osgQOpenGLWidget is essential
    // 	osgWidgetUi = new QOsgWidgetUi(this, modelPath);
    // 	this->ui->horizontalLayoutWidget = osgWidgetUi;
    // this->ui->horizontalLayout->addWidget(th);

    //workspaceWidget = osgWidgetUi;

    // if(this->ui->workspaceWidget != nullptr)
    //     delete  this->ui->workspaceWidget;
    // this->ui->workspaceWidget = osgWidgetUi;
    // centralGridLayout->addWidget((QWidget*)osgWidgetUi, 0, 0, 1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    osgWidgetUi = new QOsgWidgetUi(this, "D:/glider.osg");
    this->ui->horizontalLayout->addWidget(osgWidgetUi);
    std::cout<<"check3"<<std::endl;
}

