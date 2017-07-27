#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "commontypes.h"

typedef enum
{
   NO_FLOW,
   SIMPLE_FLOW,
   DEEP_FLOW,
} flow_type;

class Interpolater : public QObject
{
  Q_OBJECT

 public:
   Interpolater( cv::InputArray from, cv::InputArray to, uint8 N, flow_type f_type=SIMPLE_FLOW );
   void getNextFrame( cv::OutputArray interpolatedFrame );

 private:
   cv::Mat from;
   cv::Mat to;
   cv::Mat flowxy[ 2 ];
   double ti;
   uint8 current_frame;
   bool valid_flow;
};

#endif // ROLLSHUT_H
