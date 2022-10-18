#include <thread>
#include <QMessageBox>
#include <QTimer>

#include <osgQOpenGL/osgQOpenGLWidget>
#include <vector>

#include "qOsgWidget.h"


using namespace std;


QOsgWidget::QOsgWidget(const std::string& modelPath, QWidget* parent) {
    // init the osgQOpenGLWidget

    pWidget = new osgQOpenGLWidget(parent);
    pWidget->show();

    // init the manipulators
    this->InitManipulators();

    // init Scene Graph, that is to load the model
    this->InitModel(modelPath, this->mRoot);

    // init camera config
    this->InitCameraConfig();

    // add skyBox
    // this->mRoot->addChild(createSkyBox());

    std::cout<<"qOsgWidget init end"<<std::endl;

    // init the editting bounding box
    // this->InitEditingBox(EDIT_BBOX_RES);
}

QOsgWidget::~QOsgWidget() {
    // end the render thread and destroy the osgOpenglWidget
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    mViewer->setDone(true);
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    mViewer->stopThreading();

    ////////////////////////////////////////////////////////////////////////
    /// without folowing post process, u will crash with the bellowing warning when: delete pWidget
    /// Warning: deleting still referenced object 000002433CA59BB0 of type 'class osg::Referenced * __ptr64'
    ///     the final reference count was 1, memory corruption possible.
    ///
    /// the reason i guess is:
    /// the bellowing vars can not be automatically set to null when delete pWidget, because they does
    /// not belong to the pWidget, so u need to set them to null manually, otherwise when delete pWidget,
    /// the destructor of pWidget will try to free the bellowing vars, but their ref != 0
    ////////////////////////////////////////////////////////////////////////
        mRoot = nullptr;
        mViewer = nullptr;
        camera = nullptr;
        trackball = nullptr;
        keyswitchManipulator = nullptr;
    ////////////////////////////////////////////////////////////////////////
    //delete hlHandler;

    delete pWidget; // call the destructor of the osgOpenglWidge
}

void QOsgWidget::InitManipulators() {
    // Create a trackball manipulator
    trackball = new osgGA::TrackballManipulator();

    // Create a Manipulator Switcher
    keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator();

    // Add our trackball manipulator to the switcher
    keyswitchManipulator->addMatrixManipulator( '1', "Trackball", trackball.get());

    // Init the switcher to the first manipulator (in this case the only manipulator)
    keyswitchManipulator->selectMatrixManipulator(0);  // Zero based index Value
}

void QOsgWidget::InitModel(const std::string& modelPath, osg::ref_ptr<osg::Group>& mRoot) {
    // Init the main Root Node/Group
    mRoot = new osg::Group;

    osg::ref_ptr<osg::MatrixTransform> modelMat = new osg::MatrixTransform();
    osg::ref_ptr<osg::PositionAttitudeTransform> modelPAT = new osg::PositionAttitudeTransform();

    osgDB::Options* opt = new osgDB::Options(std::string("noRotation")); // turn of the auto rotation


    // init with file // never used
    if(modelPath.find_first_of('.') != std::string::npos)
    {
        osg::ref_ptr<osg::Node> Model = osgDB::readNodeFile(modelPath, opt);

        // Model->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF); // turn of the lighting to avoid wrong normal lighting
        Model->setName("rawModel");
        modelMat->addChild(Model);
        modelPAT->addChild(modelMat);
        // terrain->setPosition( osg::Vec3(0, 0, 0) );
        // terrain->setAttitude(
        // 	osg::Quat(osg::DegreesToRadians(0.0), osg::Vec3(0,1,0) )
        // 	*osg::Quat(osg::DegreesToRadians(0.0), osg::Vec3(1,0,0) )
        // 	*osg::Quat(osg::DegreesToRadians(0.0), osg::Vec3(0,0,1) ));
        // TerrainM->setMatrix(osg::Matrix::scale(1000, 1000, 1000));
        modelPAT->setName("patModel");
        mRoot->addChild(modelPAT);
    }

    // init with Dir
//    else
//    {
//        fstream metaFP;
//        metaFP.open(modelPath + "\\meta.txt");
//        double xBlocklen;
//        metaFP.read((char *)&xBlocklen, sizeof(double));
//        double yBlocklen;
//        metaFP.read((char *)&yBlocklen, sizeof(double));
//        double zBlocklen;
//        metaFP.read((char *)&zBlocklen, sizeof(double));
//        metaFP.close();
//        cout<<"xlen: "<<xBlocklen<<" ylen: "<<yBlocklen<<" zlen: "<<zBlocklen<<endl;

//        vector<string> files;
//        int count = readPCDFileDir(modelPath, files);
//        cout<<"file num: "<<count<<endl;
//        if(count == -1)
//            QMessageBox::critical(this->pWidget, "error", "file path error\n");
//        else
//        {
//            for(int i = 0; i < count; i++)
//            {
//                cout<<"reading "<<files[i]<<endl;
//                std::string file = modelPath + "\\divideFilter\\" + files[i];
//                mydef::MyPointCloud* pointCloudPtr = readPCDFile(file);
//                if(pointCloudPtr == nullptr)
//                {
//                    QMessageBox::critical(this->pWidget, "error", "file reading error\n");
//                    break;
//                }
//                osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();
//                osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array();
//                for(int j = 0; j < pointCloudPtr->points.size(); j++)
//                {
//                    coords->push_back(osg::Vec3(pointCloudPtr->points[j].x, pointCloudPtr->points[j].y, pointCloudPtr->points[j].z));
//                    color->push_back(osg::Vec4(0, 0, 0, 1));
//                }
//                osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
//                geometry->setVertexArray(coords.get());
//                geometry->setColorArray(color.get());
//                geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
//                geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, pointCloudPtr->points.size()));

//                osg::ref_ptr<osg::Geode> modelBlock = new osg::Geode;
//                modelBlock->addDrawable(geometry.get());

//                //modelBlock->setName("Model"+to_string(i));
//                modelBlock->setName("Model"+files[i]);
//                osg::ref_ptr<osg::Point> pointSize = new osg::Point;
//                pointSize->setSize(3.3);
//                modelBlock->getOrCreateStateSet()->setAttribute(pointSize.get(), osg::StateAttribute::PROTECTED | osg::StateAttribute::ON);

//                mRoot->addChild(modelBlock);
//                //modelMat->addChild(modelBlock);
//                //modelPAT->addChild(modelMat);


//                //adding BBox
//                osg::ref_ptr<osg::Geode> box = new osg::Geode;
//                osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();
//                hints->setDetailRatio(2.0f);

//                osg::Vec3 initCenterXYZ = (pointCloudPtr->maxPoint + pointCloudPtr->minPoint)/2.0;
//                osg::Vec3 initDeltaXYZ = pointCloudPtr->maxPoint - pointCloudPtr->minPoint;
//                osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(new osg::Box(
//                    initCenterXYZ,
//                    initDeltaXYZ.x(),
//                    initDeltaXYZ.y(),
//                    initDeltaXYZ.z()), hints.get());
//                shape->setColor(osg::Vec4(0.0f, 0.7f, 0.5f, 0.0f));
//                box->addDrawable(shape.get());
//                std::cout<<initCenterXYZ.x()<<" "<<initCenterXYZ.y()<<" "<<initCenterXYZ.z()<<std::endl;
//                std::cout<<" "<<initDeltaXYZ.x()<<" "<<initDeltaXYZ.y()<<" "<<initDeltaXYZ.z()<<std::endl;

//                // set the editing boudingbox mode
//                osg::ref_ptr<osg::PolygonMode> polygonMode = new osg::PolygonMode();
//                polygonMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
//                // osg::StateAttribute::PROTECTED => so that the attribute not override from above
//                box->getOrCreateStateSet()->setAttribute(polygonMode.get(), osg::StateAttribute::PROTECTED | osg::StateAttribute::ON);
//                // set the box to be transparent
//                box->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON); // turn on blend
//                //close lighting and depth-test
//                box->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
//                box->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);

//                box->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN); // set render mode
//                box->getOrCreateStateSet()->setRenderBinDetails(11, "RenderBin"); // setting rendering priority, otherwise is -1, -1 means always first to be rendered

//                //osg::ref_ptr<osg::Material> material = new osg::Material;
//                //material->setAmbient(osg::Material::FRONT, osg::Vec4(0.0f, 0.7f, 0.5f, 0.3f));
//                //box->getOrCreateStateSet()->setAttributeAndModes(material, osg::StateAttribute::ON);


//                string textName = getFileXYZIndex(files[i]);
//                box->setName(textName);
//                selectedItem2Block[textName] = box;

//                mRoot->addChild(box);
//                //box->setNodeMask(0);

//                //adding label
//                osg::ref_ptr<osgText::Text> text = new osgText::Text;
//                text->setFont("arial.ttf");
//                //string textName = getFileXYZIndex(files[i]);
//                text->setText(textName);
//                //text->setCharacterSize(0.05, 1.0);
//                text->setCharacterSize((xBlocklen + yBlocklen) * 0.035, 1.0);

//                //text->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);
//                //text->setMaximumWidth(minScale);
//                //text->setPosition(osg::Vec3(initCenterXYZ));
//                text->setPosition(osg::Vec3(0.0,0.0,0.0));

//                //close depth-test
//                text->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
//                text->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
//                // or set always pass depth-test
//                //osg::ref_ptr<osg::Depth> dep = new osg::Depth;
//                //dep->setFunction(osg::Depth::Function::ALWAYS);
//                //text->getOrCreateStateSet()->setAttribute(dep.get(), osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
//                //text->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);


//                //osg::ref_ptr<osg::Billboard> billBoard = new osg::Billboard;
//                //billBoard->addDrawable(text);
//                //billBoard->setMode(osg::Billboard::AXIAL_ROT);
//                //billBoard->setAxis(initCenterXYZ);
//                //billBoard->setNormal(initCenterXYZ ^ osg::Vec3(1.0,0.0,0.0));

//                osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
//                pat->setScale(osg::Vec3(1.0f,1.0f,1.0f));
//                //pat->setPivotPoint(initCenterXYZ);
//                pat->setPosition(initCenterXYZ);
//                //pat->addChild(text);
//                osg::ref_ptr<osg::AutoTransform> nodeAT = new osg::AutoTransform;//自动缩放矩阵
//                nodeAT->setAutoRotateMode(osg::AutoTransform::AutoRotateMode::ROTATE_TO_CAMERA);
//                nodeAT->setMinimumScale(1.3);
//                nodeAT->setMaximumScale(4.3);
//                //double minScale = (initDeltaXYZ.x() + initDeltaXYZ.y())/8.0;
//                //nodeAT->setMinimumScale(minScale);
//                //nodeAT->setMaximumScale(minScale);
//                nodeAT->setAutoScaleToScreen(true);
//                nodeAT->addChild(text);
//                pat->addChild(nodeAT);

//                mRoot->addChild(pat);

//            }
//            //modelPAT->setName("patModel");
//            //mRoot->addChild(modelPAT);

//        }
//    }
    // Optimize the model
    osgUtil::Optimizer optimizer;
    optimizer.optimize(mRoot.get());
    optimizer.reset();
}

void QOsgWidget::InitCameraConfig() {
    std::cout<<"checkcamera"<<std::endl;
    // Create the viewer for this window
    mViewer = this->pWidget->getOsgViewer();

    // Add a Stats Handler to the viewer
    stats = new osgViewer::StatsHandler;

    // Add the Camera to the Viewer
    osg::ref_ptr<osg::Camera> camera = mViewer->getCamera();
    // Set projection matrix and camera attribtues
    std::cout<<"check"<<std::endl;
    camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
    // mViewer->addSlave(camera.get());
    mViewer->setCamera(camera.get());

    // Add the Camera Manipulator to the Viewer
    // mViewer->setCameraManipulator(keyswitchManipulator.get());
    trackball = new osgGA::TrackballManipulator();
    mViewer->setCameraManipulator(trackball.get());

    // Set the Scene Data
    mViewer->setSceneData(mRoot.get());

    // hlHandler = new OsgHighLight;
    // mViewer->addEventHandler(hlHandler);
    // mViewer->addEventHandler(new OsgHighLight);
    cout<<"debug\n";

    const osg::GraphicsContext::Traits *traits = camera->getGraphicsContext()->getTraits();
    camera->setViewport(0, 0, traits->width, traits->height);
    // avoid the traits's w/h to make the view distortion
    double aspect = static_cast<double>(traits->width) / static_cast<double>(traits->height);
    // fovy aspect near far
    camera->setProjectionMatrixAsPerspective(30.0, aspect, 1.0, 1000.0);

    // // Realize the Viewer's graphics context, which already done in the default pWidget
    // mViewer->realize();
}


osg::ref_ptr<osg::Node> QOsgWidget::addDraggerToScene(osg::ref_ptr<osg::Node> scene, osg::BoundingBox& bBoxOfScene) {
    scene->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);

    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
    transform->addChild(scene);

    //osgManipulator::TabBoxDragger* d = new osgManipulator::TabBoxDragger();
    //d->setupDefaultGeometry();
    //osgManipulator::Dragger* dragger = d;

    //osg::Group* root = new osg::Group;
    osg::ref_ptr<osgManipulator::TabBoxDragger> dragger = new osgManipulator::TabBoxDragger();
    dragger->setupDefaultGeometry();
    //osgManipulator::Dragger* dragger = d;

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(transform);

    root->addChild(dragger);

    // initial the dragger to be of the same size with the scene's bounding box
    //float scale = scene->getBound().radius() * 1.155;
    float x = bBoxOfScene.xMax() - bBoxOfScene.xMin();
    float y = bBoxOfScene.yMax() - bBoxOfScene.yMin();
    float z = bBoxOfScene.zMax() - bBoxOfScene.zMin();
    dragger->setMatrix(osg::Matrix::scale(x, y, z) *
        osg::Matrix::translate(bBoxOfScene.center()));

    dragger->addTransformUpdating(transform);

    // we want the dragger to handle it's own events automatically
    dragger->setHandleEvents(true);

    // if we don't set an activation key or mod mask then any mouse click on
    // the dragger will activate it, however if do define either of ActivationModKeyMask or
    // and ActivationKeyEvent then you'll have to press either than mod key or the specified key to
    // be able to activate the dragger when you mouse click on it.  Please note the follow allows
    // activation if either the ctrl key or the 'a' key is pressed and held down.
    dragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);
    dragger->setActivationKeyEvent('a');

    return root;
}
