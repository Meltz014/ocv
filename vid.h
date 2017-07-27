#ifndef VID_H
#define VID_H

#include "commontypes.h"

class Vid
{

 public:
   Vid( );
   Vid( QString file_name );
   bool getNextFrame( cv::OutputArray image );
   bool getPrevFrame( cv::OutputArray image );
   bool getCurrentFrame( cv::OutputArray image );
   void setCurrentFrameIndex( uint32 frame_num );
   int  getNumFrames( );
   int  getFPS( );
   int  getCodec( );
   QSize getQSize( );
   cv::Size getCSize( );
   void scaleDown( );
   void scaleUp( );
   bool isEmpty( );

 private:
   cv::VideoCapture video_cap;
   int current_frame;
   int num_frames;
   double scale_w;
   double scale_h;
   bool scale;
   bool is_empty;
};

#endif
