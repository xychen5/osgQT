#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgQOpenGL/OSGRenderer>

#include <osgViewer/Viewer>
#include <osg/GL>

#include <QApplication>
#include <QKeyEvent>
#include <QInputDialog>
#include <QLayout>
#include <QMainWindow>
#include <QScreen>
#include <QWindow>

#include <iostream>

osgQOpenGLWidget::osgQOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

osgQOpenGLWidget::osgQOpenGLWidget(osg::ArgumentParser* arguments,
                                   QWidget* parent) :
    QOpenGLWidget(parent),
    _arguments(arguments)
{

}

osgQOpenGLWidget::~osgQOpenGLWidget()
{
}

osgViewer::Viewer* osgQOpenGLWidget::getOsgViewer()
{
    return m_renderer;
}

OpenThreads::ReadWriteMutex* osgQOpenGLWidget::mutex()
{
    return &_osgMutex;
}


void osgQOpenGLWidget::initializeGL()
{
    // Initializes OpenGL function resolution for the current context.
    initializeOpenGLFunctions();
    createRenderer();
    std::cout << "gl initialized!" << std::endl;
    emit initialized();
}

void osgQOpenGLWidget::resizeGL(int w, int h)
{
    Q_ASSERT(m_renderer);
    QScreen* screen = windowHandle()
                      && windowHandle()->screen() ? windowHandle()->screen() :
                      qApp->screens().front();
    m_renderer->resize(w, h, screen->devicePixelRatio());
}

void osgQOpenGLWidget::paintGL()
{
    OpenThreads::ScopedReadLock locker(_osgMutex);
	if (_isFirstFrame) {
		_isFirstFrame = false;
		m_renderer->getCamera()->getGraphicsContext()->setDefaultFboId(defaultFramebufferObject());
	}
	m_renderer->frame();
}

void osgQOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    Q_ASSERT(m_renderer);

    if(event->key() == Qt::Key_F)
    {
        static QSize g;
        static QMargins sMargins;

        if(parent() && parent()->isWidgetType())
        {
            QMainWindow* _mainwindow = dynamic_cast<QMainWindow*>(parent());

            if(_mainwindow)
            {
                g = size();

                if(layout())
                    sMargins = layout()->contentsMargins();

                bool ok = true;

                // select screen
                if(qApp->screens().size() > 1)
                {
                    QMap<QString, QScreen*> screens;
                    int screenNumber = 0;

                    for(QScreen* screen : qApp->screens())
                    {
                        QString name = screen->name();

                        if(name.isEmpty())
                        {
                            name = tr("Screen %1").arg(screenNumber);
                        }

                        name += " (" + QString::number(screen->size().width()) + "x" + QString::number(
                                    screen->size().height()) + ")";
                        screens[name] = screen;
                        ++screenNumber;
                    }

                    QString selected = QInputDialog::getItem(this,
                                                             tr("Choose fullscreen target screen"), tr("Screen"), screens.keys(), 0, false,
                                                             &ok);

                    if(ok && !selected.isEmpty())
                    {
                        context()->setScreen(screens[selected]);
                        move(screens[selected]->geometry().x(), screens[selected]->geometry().y());
                        resize(screens[selected]->geometry().width(),
                               screens[selected]->geometry().height());
                    }
                }

                if(ok)
                {
                    // in fullscreen mode, a thiner (1px) border around
                    // viewer widget
                    if(layout())
                        layout()->setContentsMargins(1, 1, 1, 1);

                    setParent(0);
                    showFullScreen();
                }
            }
        }
        else
        {
            showNormal();
            setMinimumSize(g);
            QMainWindow* _mainwindow = dynamic_cast<QMainWindow*>(parent());
            if(_mainwindow){
                _mainwindow->setCentralWidget(this);
            }

            if(layout())
                layout()->setContentsMargins(sMargins);

            qApp->processEvents();
            setMinimumSize(QSize(1, 1));
        }
    }
    else // not 'F' key
    {
        // forward event to renderer
        m_renderer->keyPressEvent(event);
    }
}

void osgQOpenGLWidget::keyReleaseEvent(QKeyEvent* event)
{
    Q_ASSERT(m_renderer);
    // forward event to renderer
    m_renderer->keyReleaseEvent(event);
}

void osgQOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    Q_ASSERT(m_renderer);
    // forward event to renderer
    m_renderer->mousePressEvent(event);
}

void osgQOpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    Q_ASSERT(m_renderer);
    // forward event to renderer
    m_renderer->mouseReleaseEvent(event);
}

void osgQOpenGLWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_ASSERT(m_renderer);
    // forward event to renderer
    m_renderer->mouseDoubleClickEvent(event);
}

void osgQOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    Q_ASSERT(m_renderer);
    // forward event to renderer
    m_renderer->mouseMoveEvent(event);
}

void osgQOpenGLWidget::wheelEvent(QWheelEvent* event)
{
    Q_ASSERT(m_renderer);
    // forward event to renderer
    m_renderer->wheelEvent(event);
}

void osgQOpenGLWidget::setDefaultDisplaySettings()
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    ds->setNvOptimusEnablement(1);
    ds->setStereo(false);
}

void osgQOpenGLWidget::createRenderer()
{
    // call this before creating a View...
    setDefaultDisplaySettings();
	if (!_arguments) {
		m_renderer = new OSGRenderer(this);
	} else {
		m_renderer = new OSGRenderer(_arguments, this);
	}
	QScreen* screen = windowHandle()
                      && windowHandle()->screen() ? windowHandle()->screen() :
                      qApp->screens().front();
    m_renderer->setupOSG(width(), height(), screen->devicePixelRatio());
}

// void osgQOpenGLWidget::changeEvent(QEvent * event)
// {
// 	std::cout << "windows size changed to (w,h): " << width() << "," << height() << std::endl;
//     resizeGL(width(), height());
//     //camera = new osg::Camera;
//     osg::ref_ptr<osg::Camera> camera = this->getOsgViewer()->getCamera();
// 
//     // Assign Graphics Context to the Camera
//     // camera->setGraphicsContext(gc);
//     osg::ref_ptr<osg::GraphicsContext> widgetGC = this->getOsgViewer()->getCamera()->getGraphicsContext();
//     camera->setGraphicsContext(widgetGC);
// 
//     // Set the viewport for the Camera
//     int h = height();
//     int w = width();
//     // camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
//     camera->setViewport(new osg::Viewport(0, 0, w, h));
// 
//     // Set projection matrix and camera attribtues
//     camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//     camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
//     camera->setProjectionMatrixAsPerspective(
//         30.0f, static_cast<double>(w) / static_cast<double>(h), 1.0, 1000.0);
//     std::cout << "reset the camera!" << std::endl;
//     // Add the Camera to the Viewer
//     this->getOsgViewer()->setCamera(camera.get());
// }

// void osgQOpenGLWidget::resizeEvent(QResizeEvent* event) {
//     if (this->windowState() == Qt::WindowMaximized) {
//         std::cout << "maxed!" << std::endl;
//         resize(this->width(), this->height());
//         resizeGL(this->width(), this->height());
//     }
// 
//     std::cout << "resize event raised!" << std::endl;
//     resize(this->width(), this->height());
// 
// }

