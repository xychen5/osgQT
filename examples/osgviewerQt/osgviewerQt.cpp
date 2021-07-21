/*  -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2010 Robert Osfield

    This application is open source and may be redistributed and/or modified
    freely and without restriction, both in commercial and non commercial applications,
    as long as this copyright notice is maintained.

    This application is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <osgQOpenGL/osgQOpenGLWidget>

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>

#include <osg/Switch>
#include <osg/Types>
#include <osgViewer/Viewer>
#include <osgText/Text>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>

#include <osgGA/Device>

#include <QApplication>
#include <QSurfaceFormat>

#include <iostream>


int main( int argc, char** argv )
{

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();

#ifdef OSG_GL3_AVAILABLE
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setOption(QSurfaceFormat::DebugContext);
#else
    format.setVersion(2, 0);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setOption(QSurfaceFormat::DebugContext);
#endif
    format.setDepthBufferSize(24);
    //format.setAlphaBufferSize(8);
    format.setSamples(8);
    format.setStencilBufferSize(8);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication app(argc, argv);

    // use an ArgumentParser object to manage the program arguments.
    osg::ArgumentParser arguments(&argc, argv);

    arguments.getApplicationUsage()->setApplicationName(
        arguments.getApplicationName());
    arguments.getApplicationUsage()->setDescription(arguments.getApplicationName() +
                                                    " is the standard OpenSceneGraph example which loads and visualises 3d models.");
    arguments.getApplicationUsage()->setCommandLineUsage(
        arguments.getApplicationName() + " [options] filename ...");
    arguments.getApplicationUsage()->addCommandLineOption("--image <filename>",
                                                          "Load an image and render it on a quad");
    arguments.getApplicationUsage()->addCommandLineOption("--dem <filename>",
                                                          "Load an image/DEM and render it on a HeightField");
    arguments.getApplicationUsage()->addCommandLineOption("--login <url> <username> <password>",
                                                          "Provide authentication information for http file access.");
    arguments.getApplicationUsage()->addCommandLineOption("-p <filename>",
                                                          "Play specified camera path animation file, previously saved with 'z' key.", 
                                                          "F:/dataSets/OpenSceneGraph-Data-3.4.0/OpenSceneGraph-Data/glider.osg");
    arguments.getApplicationUsage()->addCommandLineOption("--speed <factor>",
                                                          "Speed factor for animation playing (1 == normal speed).");
    arguments.getApplicationUsage()->addCommandLineOption("--device <device-name>",
                                                          "add named device to the viewer");

    osgQOpenGLWidget widget(&arguments);

    if (true) {

        osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile("F:/dataSets/OpenSceneGraph-Data-3.4.0/OpenSceneGraph-Data/glider.osg");

        if (!loadedModel)
        {
            std::cout << arguments.getApplicationName() << ": No data loaded" << std::endl;
            return 1;
        }

        // any option left unread are converted into errors to write out later.
        arguments.reportRemainingOptionsAsUnrecognized();

        // report any errors if they have occurred when parsing the program arguments.
        if (arguments.errors())
        {
            arguments.writeErrorMessages(std::cout);
            return 1;
        }

        // QObject::connect(&widget, &osgQOpenGLWidget::initialized, [&arguments, &widget]() {
        //     return 0;
        //     });

        widget.show();

        // std::cout << "children's num is: " << widget.getOsgViewer()->getCamera()->getNumChildren();
        // widget.getOsgViewer()->setSceneData(loadedModel);
        // std::cout << "children's num is: " << widget.getOsgViewer()->getCamera()->getNumChildren();

        // return app.exec();


        // optimize the scene graph, remove redundant nodes and state etc.
        osgUtil::Optimizer optimizer;
        optimizer.optimize(loadedModel);

        // widget.getOsgViewer()->setSceneData(loadedModel);
        // std::cout << "children's num is: " << widget.getOsgViewer()->getCamera()->getNumChildren();

        // mViewer = new osgViewer::Viewer();
        osg::ref_ptr<osgViewer::Viewer> mViewer = widget.getOsgViewer();
        // Add a Stats Handler to the viewer
        // mViewer->addEventHandler(new osgViewer::StatsHandler);

//        // // Get the current window size
//        // ::GetWindowRect(m_hWnd, &rect);
//
//        // Init the GraphicsContext Traits
//        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
//
//        // Setup the traits parameters
//        osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
//        traits->windowName = "editBBox";
//        traits->windowDecoration = false;
//        traits->x = 1000;                                  // window origin
//        traits->y = 1000;
//        traits->width = 1000;  // window size
//        traits->height = 1000;
//        traits->doubleBuffer = true;
//        traits->alpha = ds->getMinimumNumAlphaBits();
//        traits->stencil = ds->getMinimumNumStencilBits();
//        traits->sampleBuffers = ds->getMultiSamples();
//        traits->samples = ds->getNumMultiSamples();
//
//        // Create the Graphics Context
//        osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits.get());
//
//        // Init a new Camera (Master for this View)
//        //camera = new osg::Camera;
		osg::ref_ptr<osg::Camera> camera = mViewer->getCamera();

//        // Assign Graphics Context to the Camera
//        // camera->setGraphicsContext(gc);
//        osg::ref_ptr<osg::GraphicsContext> widgetGC = widget.getOsgViewer()->getCamera()->getGraphicsContext();
//        camera->setGraphicsContext(widgetGC);
//
//        // Set the viewport for the Camera
//        int h = widget.sizeHint().height();
//        int w = widget.sizeHint().width();
//        // camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
//        camera->setViewport(new osg::Viewport(0, 0, w, h));
//
//        // Set projection matrix and camera attribtues
        camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
        // camera->setProjectionMatrixAsPerspective(
        //     30.0f, static_cast<double>(w) / static_cast<double>(h), 1.0, 1000.0);
//
        // Add the Camera to the Viewer
        mViewer->setCamera(camera.get());

        // Add the Camera Manipulator to the Viewer
        // mViewer->setCameraManipulator(keyswitchManipulator.get());
        osg::ref_ptr<osgGA::TrackballManipulator> trackball = new osgGA::TrackballManipulator();
        mViewer->setCameraManipulator(trackball.get());

        mViewer->setSceneData(loadedModel);

        // // Realize the Viewer's graphics context, which already done in the default pWidget
        // mViewer->realize(); 

        return app.exec();
    }

    QObject::connect(&widget, &osgQOpenGLWidget::initialized,   [  &arguments,
                                                                   &widget ]
    {
        unsigned int helpType = 0;

        if((helpType = arguments.readHelpType()))
        {
            arguments.getApplicationUsage()->write(std::cout, helpType);
            return 1;
        }

        // report any errors if they have occurred when parsing the program arguments.
        if(arguments.errors())
        {
            arguments.writeErrorMessages(std::cout);
            return 1;
        }

        if(arguments.argc() <= 1)
        {
            arguments.getApplicationUsage()->write(std::cout,
            osg::ApplicationUsage::COMMAND_LINE_OPTION);
            return 1;
        }

        // set up the camera manipulators.
        {
            osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

            keyswitchManipulator->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator());
            keyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator());
            keyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator());
            keyswitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator());
            keyswitchManipulator->addMatrixManipulator('5', "Orbit", new osgGA::OrbitManipulator());
            keyswitchManipulator->addMatrixManipulator('6', "FirstPerson", new osgGA::FirstPersonManipulator());
            keyswitchManipulator->addMatrixManipulator('7', "Spherical", new osgGA::SphericalManipulator());

            // std::string pathfile = "F:/dataSets/OpenSceneGraph-Data-3.4.0/OpenSceneGraph-Data/glider.osg";
            std::string pathfile;
            double animationSpeed = 1.0;

            while(arguments.read("--speed", animationSpeed)) {}
            char keyForAnimationPath = '8';

            while(arguments.read("-p", pathfile))
            {
                osgGA::AnimationPathManipulator* apm = new osgGA::AnimationPathManipulator(
                    pathfile);

                if(apm || !apm->valid())
                {
                    apm->setTimeScale(animationSpeed);

                    unsigned int num = keyswitchManipulator->getNumMatrixManipulators();
                    keyswitchManipulator->addMatrixManipulator(keyForAnimationPath, "Path", apm);
                    keyswitchManipulator->selectMatrixManipulator(num);
                    ++keyForAnimationPath;
                }
            }

            widget.getOsgViewer()->setCameraManipulator(keyswitchManipulator.get());
        }

        // add the state manipulator
        widget.getOsgViewer()->addEventHandler(new osgGA::StateSetManipulator(widget.getOsgViewer()->getCamera()->getOrCreateStateSet()));

        // add the thread model handler
        widget.getOsgViewer()->addEventHandler(new osgViewer::ThreadingHandler);

        // add the window size toggle handler
        widget.getOsgViewer()->addEventHandler(new osgViewer::WindowSizeHandler);

        // add the stats handler
        widget.getOsgViewer()->addEventHandler(new osgViewer::StatsHandler);

        // add the help handler
        widget.getOsgViewer()->addEventHandler(new osgViewer::HelpHandler(arguments.getApplicationUsage()));

        // add the record camera path handler
        widget.getOsgViewer()->addEventHandler(new osgViewer::RecordCameraPathHandler);

        // add the LOD Scale handler
        widget.getOsgViewer()->addEventHandler(new osgViewer::LODScaleHandler);

        // add the screen capture handler
        widget.getOsgViewer()->addEventHandler(new osgViewer::ScreenCaptureHandler);

        // load the data
        osg::ref_ptr<osg::Node> loadedModel = osgDB::readRefNodeFiles(arguments);
        // osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile("F:/dataSets/OpenSceneGraph-Data-3.4.0/OpenSceneGraph-Data/glider.osg");

        if(!loadedModel)
        {
            std::cout << arguments.getApplicationName() << ": No data loaded" << std::endl;
            return 1;
        }

        // any option left unread are converted into errors to write out later.
        arguments.reportRemainingOptionsAsUnrecognized();

        // report any errors if they have occurred when parsing the program arguments.
        if(arguments.errors())
        {
            arguments.writeErrorMessages(std::cout);
            return 1;
        }


        // optimize the scene graph, remove redundant nodes and state etc.
        osgUtil::Optimizer optimizer;
        optimizer.optimize(loadedModel);

        widget.getOsgViewer()->setSceneData(loadedModel);
        std::cout << "children's num is: " << widget.getOsgViewer()->getCamera()->getNumChildren();

        // widget.getOsgViewer()->realize();

        return 0;
    });


    widget.show();

    return app.exec();

}
