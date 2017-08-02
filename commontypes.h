#pragma once

#include <math.h>
#include <map>
#include <string>

#include <QTime>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSize>
#include <QGridLayout>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QPushButton>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QApplication>
#include <QCheckBox>
#include <QLineEdit>


#include <opencv2/opencv.hpp>
#include "opencv2/optflow.hpp"
#include <opencv2/core/ocl.hpp>
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"

#define DEFAULT_SCALE_IMG ( 0.25 )
#define DEFAULT_SCALE_VID ( 1 )
#define SCALE_INC ( 0.05 )

typedef unsigned int uint32;
typedef unsigned char uint8;

typedef enum
{
   NO_FLOW,
   SIMPLE_FLOW,
   DEEP_FLOW,
} flow_type;
Q_DECLARE_METATYPE( flow_type )
