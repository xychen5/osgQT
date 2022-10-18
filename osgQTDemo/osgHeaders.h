#ifndef OSGHEADERS_H
#define OSGHEADERS_H

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>

#include <osg/Switch>
#include <osg/Types>
#include <osg/ShapeDrawable>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/ComputeBoundsVisitor>
#include <osg/Material>
#include <osg/AutoTransform>
#include <osg/Point>
#include <osg/Depth>

#include <osgText/Text>
#include <osgUtil/Optimizer>

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
#include <osgGA/GUIEventHandler>

#include <osgManipulator/TabBoxDragger>


extern int _argc;
extern char** _argv;

#endif // OSGHEADERS_H
