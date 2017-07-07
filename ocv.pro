INCLUDEPATH += . $$(OPENCV_DIR)\..\..\include
TEMPLATE = app
CONFIG += console

LIBS += C:\opencv-build\bin\libopencv_core320.dll
LIBS += C:\opencv-build\bin\libopencv_imgcodecs320.dll
LIBS += C:\opencv-build\bin\libopencv_imgproc320.dll
LIBS += C:\opencv-build\bin\libopencv_features2d320.dll
LIBS += C:\opencv-build\bin\libopencv_calib3d320.dll
LIBS += C:\opencv-build\bin\libopencv_video320.dll
LIBS += C:\opencv-build\bin\libopencv_videoio320.dll

QT += gui
QT += core
QT += widgets

HEADERS += commontypes.h mainwindow.h vid.h
SOURCES += main.cpp mainwindow.cpp vid.cpp

TARGET = ocv
INSTALLS += target

