#ifndef QOSGWIDGET_H
#define QOSGWIDGET_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

#include <QApplication>
#include <QSurfaceFormat>

#include <osgQOpenGL/osgQOpenGLWidget>

#include "osgHeaders.h"

/**
 * @brief The QOsgWidget class, this class is mainly for initialize the pWidget
 */
class QOsgWidget
{
public:
    ///< essential widget, use this ptr to be the real widget
    osgQOpenGLWidget* pWidget = nullptr;

    QOsgWidget(QWidget* parent = nullptr);
    QOsgWidget(const std::string& modelPath, QWidget* parent = nullptr);
    ~QOsgWidget();

    ///< osg base vars
    osg::ref_ptr<osg::Group>                        mRoot = nullptr; // root node of the osg scene
    osg::ref_ptr<osg::Camera>                       camera = nullptr; // osg camera
    osg::ref_ptr<osgViewer::Viewer>                 mViewer = nullptr; // osg viewer
    osg::ref_ptr<osgGA::TrackballManipulator>       trackball = nullptr;
    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = nullptr;
    osg::ref_ptr<osgViewer::StatsHandler>           stats = nullptr;

    std::unordered_map<std::string, osg::ref_ptr<osg::Geode>> selectedItem2Block;

    /**
     * @brief InitManipulators: init the key switch Manipulator
     */
    void InitManipulators();

    /**
     * @brief InitModel: load model into the mRoot to have a view
     * @param modelPath: model to load
     * @param mRoot: the root node of the secne
     */
    void InitModel(const std::string& modelPath, osg::ref_ptr<osg::Group>& mRoot);

    /**
     * @brief InitCameraConfig: init the camera's config in osg
     */
    void InitCameraConfig();

    /**
     * @brief InitEditingBox: init the editting box
     * @param eBBox: where to store the edit result
     */
     //void InitEditingBox(EBBox &eBBox);

     /**
      * @brief addDraggerToScene: add dragger to the scene
      * @param scene: node who needs a dragger
      * @param bBoxOfScene: bBox to add
      * @return osg::Group* who contain the node and the dragger
      */
    osg::ref_ptr<osg::Node> addDraggerToScene(osg::ref_ptr<osg::Node> scene, osg::BoundingBox& bBoxOfScene);
    // osg::Node* addDraggerToScene(osg::Node* scene, osg::BoundingBox& bBoxOfScene);

    /**
     * @brief resetModelPos: reset the editting bounding box's pos to the initial positon
     */
     // void resetModelPos();

     /**
      * @brief saveEBBoxRes: save the editting bounding box's res to the eBBox
      * @param eBBox: where to save the res
      */
      //void saveEBBoxRes(EBBox &eBBox);

    osg::ref_ptr<osgViewer::Viewer> getViewer() { return mViewer; }
};

#endif // QOSGWIDGET_H
