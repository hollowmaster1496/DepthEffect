#-------------------------------------------------
#
# Project created by QtCreator 2017-03-18T09:35:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DepthEffect
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
        frmmain.cpp

HEADERS  += frmmain.h

FORMS    += frmmain.ui

INCLUDEPATH += C:\\Users\\Syed\\Desktop\\OpenCV-3.0.0\\opencv\\build\\include

LIBS +=-LC:\\Users\\Syed\\Desktop\\OpenCV-3.0.0\\mybuild\\lib\\Debug \
    -lopencv_calib3d300d \
    -lopencv_core300d \
    -lopencv_features2d300d \
    -lopencv_flann300d \
    -lopencv_hal300d \
    -lopencv_highgui300d \
    -lopencv_imgcodecs300d \
    -lopencv_imgproc300d \
    -lopencv_ml300d \
    -lopencv_objdetect300d \
    -lopencv_photo300d \
    -lopencv_shape300d \
    -lopencv_stitching300d \
    -lopencv_superres300d \
    -lopencv_ts300d \
    -lopencv_video300d \
    -lopencv_videoio300d \
    -lopencv_videostab300d
########################################
