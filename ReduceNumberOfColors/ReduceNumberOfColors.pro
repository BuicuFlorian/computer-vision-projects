#-------------------------------------------------
#
# Project created by QtCreator 2017-10-18T09:35:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReduceNumberOfColors
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += "D:\\OpenCV3\\mybuild\\install\\include"

LIBS += -L"D:\\OpenCV3\\mybuild\\install\\x64\\vc15\\lib" \
-lopencv_core330 \
-lopencv_highgui330 \
-lopencv_imgcodecs330 \
-lopencv_imgproc330 \
-lopencv_calib3d330 \
-lopencv_dnn330 \
-lopencv_features2d330 \
-lopencv_flann330 \
-lopencv_ml330 \
-lopencv_objdetect330 \
-lopencv_photo330 \
-lopencv_shape330 \
-lopencv_stitching330 \
-lopencv_superres330 \
-lopencv_video330 \
-lopencv_videoio330 \
-lopencv_videostab330 \
-lopencv_core330d \
-lopencv_highgui330d \
-lopencv_imgcodecs330d \
-lopencv_imgproc330d \
-lopencv_calib3d330d \
-lopencv_dnn330d \
-lopencv_features2d330d \
-lopencv_flann330d \
-lopencv_ml330d \
-lopencv_objdetect330d \
-lopencv_photo330d \
-lopencv_shape330d \
-lopencv_stitching330d \
-lopencv_superres330d \
-lopencv_video330d \
-lopencv_videoio330d \
-lopencv_videostab330d
