#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "..\commontypes.h"
#include "..\guicontrols\settings\settingsdata.h"

class Interpolater : public QObject
{
  Q_OBJECT

 public:
   Interpolater( cv::InputArray from, cv::InputArray to, uint8 N, SettingsData *settings );
   Interpolater( cv::InputArray from, cv::InputArray to, uint8 N, flow_type f_type=SIMPLE_FLOW );
   void getNextFrame( cv::OutputArray interpolatedFrame );

 private:
   cv::Mat doSimpleFlow( SettingsData *settings );

   cv::Mat from;
   cv::Mat to;
   cv::Mat flowxy[ 2 ];
   double ti;
   uint8 current_frame;
   bool valid_flow;
};

#endif // ROLLSHUT_H
