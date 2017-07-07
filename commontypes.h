#pragma once

#include <QTime>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QPushButton>
#include <QResizeEvent>
#include <QKeyEvent>


#include <opencv2/opencv.hpp>

typedef unsigned int uint32;
typedef unsigned char uint8;

#define DEFAULT_SCALE_IMG ( 0.25 )
#define DEFAULT_SCALE_VID ( 1 )
#define SCALE_INC ( 0.05 )
