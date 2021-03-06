INCLUDEPATH += . C:\opencv-build\install\include
TEMPLATE = app
CONFIG += console warn_on


LIBS += C:\opencv-build\bin\libopencv_calib3d320.dll
LIBS += C:\opencv-build\bin\libopencv_flann320.dll
LIBS += C:\opencv-build\bin\libopencv_highgui320.dll
LIBS += C:\opencv-build\bin\libopencv_ml320.dll
LIBS += C:\opencv-build\bin\libopencv_objdetect320.dll
LIBS += C:\opencv-build\bin\libopencv_photo320.dll
LIBS += C:\opencv-build\bin\libopencv_shape320.dll
LIBS += C:\opencv-build\bin\libopencv_stitching320.dll
LIBS += C:\opencv-build\bin\libopencv_videostab320.dll
LIBS += C:\opencv-build\bin\libopencv_core320.dll
LIBS += C:\opencv-build\bin\libopencv_imgcodecs320.dll
LIBS += C:\opencv-build\bin\libopencv_imgproc320.dll
LIBS += C:\opencv-build\bin\libopencv_features2d320.dll
LIBS += C:\opencv-build\bin\libopencv_superres320.dll
LIBS += C:\opencv-build\bin\libopencv_video320.dll
LIBS += C:\opencv-build\bin\libopencv_videoio320.dll
LIBS += C:\opencv-build\bin\libopencv_optflow320.dll


QT += gui
QT += core
QT += widgets

HEADERS += commontypes.h mainwindow.h \
           videoproc\interpolate.h \
           videoproc\vid.h \
           videoproc\rollingshutter.h \
           guicontrols\roll_time_group.h \
           guicontrols\exportgroup.h \
           guicontrols\interpolatecontrolgroup.h \
           guicontrols\settings\settingswindow.h \
           guicontrols\settings\settingspane.h \
           guicontrols\settings\simpleflowpane.h \
           guicontrols\settings\textsetting.h \
           guicontrols\settings\settingsdata.h

SOURCES += main.cpp mainwindow.cpp \
           videoproc\interpolate.cpp \
           videoproc\vid.cpp \
           videoproc\rollingshutter.cpp \
           guicontrols\roll_time_group.cpp \
           guicontrols\exportgroup.cpp \
           guicontrols\interpolatecontrolgroup.cpp \
           guicontrols\settings\settingswindow.cpp \
           guicontrols\settings\settingspane.cpp \
           guicontrols\settings\simpleflowpane.cpp \
           guicontrols\settings\textsetting.cpp \
           guicontrols\settings\settingsdata.cpp


TARGET = ocv
INSTALLS += target

