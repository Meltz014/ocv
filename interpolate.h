#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "commontypes.h"

class Interpolater : public QObject
{
  Q_OBJECT

 public:
   Interpolater( cv::InputArray from, cv::InputArray to, uint8 N );
   void getNextFrame( cv::OutputArray interpolatedFrame );

 private:
   cv::Mat from;
   cv::Mat to;
   cv::Mat flowxy[ 2 ];
   double ti;
   uint8 current_frame;
};

#endif // ROLLSHUT_H
