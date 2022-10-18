# osgQt
本项目从[https://github.com/openscenegraph/osgQt](https://github.com/openscenegraph/osgQt)做了简单修改而来
最好从以静态库生成

## 1 其调用参考
[https://xychen5.github.io/2021/06/06/osgQT/](https://xychen5.github.io/2021/06/06/osgQT/)
本项目root目录下，有osgQTDemo这个样例，可以参考该项目的具体代码

## 2 依赖如下
```sh
# include
F:\prjs\editBBox\osgQt\build\src\osgQOpenGL;
F:\prjs\editBBox\osgQt\src\osgQOpenGL;
F:\BASE_ENV\OSG\OpenSceneGraph-3.6.5-VC2019-64-Release\include;
F:\prjs\editBBox\osgQt\include;
F:\prjs\editBBox\osgQt\build\src;
F:\prjs\editBBox\osgQt\build\include;
F:\BASE_ENV\QT\5.12.10\msvc2015_64\include;
F:\BASE_ENV\QT\5.12.10\msvc2015_64\include\QtWidgets;
F:\BASE_ENV\QT\5.12.10\msvc2015_64\include\QtGui;
F:\BASE_ENV\QT\5.12.10\msvc2015_64\include\QtANGLE;
F:\BASE_ENV\QT\5.12.10\msvc2015_64\include\QtCore;
F:\BASE_ENV\QT\5.12.10\msvc2015_64\.\mkspecs\win32-msvc;
F:\BASE_ENV\QT\5.12.10\msvc2015_64\include\QtOpenGL;
%(AdditionalIncludeDirectories)


# lib
F:\BASE_ENV\QT\5.12.10\msvc2015_64\lib\Qt5OpenGL.lib
F:\BASE_ENV\OSG\OpenSceneGraph-3.6.5-VC2019-64-Release\lib\osg.lib
F:\BASE_ENV\OSG\OpenSceneGraph-3.6.5-VC2019-64-Release\lib\osgUtil.lib
F:\BASE_ENV\OSG\OpenSceneGraph-3.6.5-VC2019-64-Release\lib\osgViewer.lib
F:\BASE_ENV\OSG\OpenSceneGraph-3.6.5-VC2019-64-Release\lib\osgGA.lib
F:\BASE_ENV\OSG\OpenSceneGraph-3.6.5-VC2019-64-Release\lib\osgDB.lib
F:\BASE_ENV\OSG\OpenSceneGraph-3.6.5-VC2019-64-Release\lib\OpenThreads.lib
opengl32.lib
F:\BASE_ENV\QT\5.12.10\msvc2015_64\lib\Qt5Widgets.lib
F:\BASE_ENV\QT\5.12.10\msvc2015_64\lib\Qt5Gui.lib
F:\BASE_ENV\QT\5.12.10\msvc2015_64\lib\Qt5Core.lib
kernel32.lib
user32.lib
gdi32.lib
winspool.lib
shell32.lib
ole32.lib
oleaut32.lib
uuid.lib
comdlg32.lib
advapi32.lib
```
