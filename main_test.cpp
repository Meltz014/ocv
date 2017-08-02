/****************************************************************************
** Upsample a video frame rate by interpolating in between frames
****************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "commontypes.h"
#include "videoproc\interpolate.h"
#include "videoproc\vid.h"
#include "inputparser.h"
#include "guicontrols\settings\settingswindow.h"
#include <QDebug>
#include <QEventLoop>

#define NUM_FRAMES ( 1 )
#define START_FRAME ( 15 )
#define END_FRAME ( 80 )

int main(int argc, char **argv)
{
   InputParser input( argc, argv );
   cv::Mat from;
   cv::Mat to;
   cv::Mat interp_frame;
   int start_frame = START_FRAME;
   int end_frame = END_FRAME;
   int inter_frames = NUM_FRAMES;
   int scale = 100;
   flow_type flow_option = NO_FLOW;
   const std::string &input_video = input.getCmdOption( "-i" );
   const std::string &output_video = input.getCmdOption( "-o" );
   const std::string &start_frame_arg = input.getCmdOption( "-s" );
   const std::string &end_frame_arg = input.getCmdOption( "-e" );
   const std::string &inter_frames_arg = input.getCmdOption( "-n" );
   const std::string &scale_arg = input.getCmdOption( "-x" );
   const std::string &flow_arg = input.getCmdOption( "-f" );
   if ( input_video.empty( ) )
   {
      qDebug( ) << "Please include input video";
      return 1;
   }
   qDebug( ) << "input video" << input_video.data( );
   if ( !output_video.empty( ) )
   {
      qDebug( ) << "output_video" << output_video.data( );
   }
   if ( !start_frame_arg.empty( ) )
   {
      start_frame = std::stoi( start_frame_arg, nullptr );
      qDebug( ) << "start" << start_frame;
   }
   if ( !end_frame_arg.empty( ) )
   {
      end_frame = std::stoi( end_frame_arg, nullptr );
      qDebug( ) << "end" << end_frame;
   }
   if ( !inter_frames_arg.empty( ) )
   {
      inter_frames = std::stoi( inter_frames_arg, nullptr );
      qDebug( ) << "inter_frames" << inter_frames;
   }
   if ( !scale_arg.empty( ) )
   {
      scale = std::stoi( scale_arg, nullptr );
      qDebug( ) << "scale" << scale << "%";
      if ( scale > 100 )
      {
         scale = 100;
      }
   }
   if ( !flow_arg.empty( ) )
   {
      if ( flow_arg == "N"  || flow_arg == "n" )
      {
         flow_option = NO_FLOW;
         qDebug( ) << "flow_option NO_FLOW";
      }
      else if ( flow_arg == "S"  || flow_arg == "s" )
      {
         flow_option = SIMPLE_FLOW;
         qDebug( ) << "flow_option SIMPLE_FLOW";
      }
      else if ( flow_arg == "D"  || flow_arg == "d" )
      {
         flow_option = DEEP_FLOW;
         qDebug( ) << "flow_option DEEP_FLOW";
      }
   }


   SettingsWindow *settings_window = new SettingsWindow( );
   QEventLoop loop;
   connect( settings_window, SIGNAL( settingsSaved( SettingsData * ) ), &loop, SIGNAL( quit( ) ) );
   settings_window->show( );
   loop.exec( );
   qDebug( ) << "done";

#if 0
   Vid video_obj = Vid( QString::fromStdString( input_video ) );
   video_obj.setCurrentFrameIndex( start_frame );

   while ( scale < 100 )
   {
      // scale down by 5%
      video_obj.scaleDown( );
      scale += 5;
   }

   cv::VideoWriter out_vid;
   if ( output_video.empty( ) )
   {
      out_vid.open( "C:/cygwin/home/501219/OCV/out.avi", video_obj.getCodec( ), video_obj.getFPS( ), video_obj.getCSize( ), true );
   }
   else
   {
      out_vid.open( output_video, video_obj.getCodec( ), video_obj.getFPS( ), video_obj.getCSize( ), true );
   }
   char output_name[ 50 ];

   for ( int i = start_frame; i < end_frame; i++ )
   {
      if ( video_obj.getCurrentFrame( from ) && video_obj.getNextFrame( to ) )
      {
         sprintf( output_name, "C:/cygwin/home/501219/OCV/images/frame%d.jpg", i );
         cv::cvtColor( from, from, CV_RGB2BGR );
         cv::cvtColor( to, to, CV_RGB2BGR );
         Interpolater interp( from, to, inter_frames, flow_option );
         imwrite( output_name, from );
         out_vid << from;
         for ( int j=0; j < inter_frames; j++ )
         {
            qDebug( ) << "frame " << i << "." << j;
            interp.getNextFrame( interp_frame );
            out_vid << interp_frame;
            sprintf( output_name, "C:/cygwin/home/501219/OCV/images/frame%d.%d.jpg", i, j );
            imwrite( output_name, interp_frame );
         }
      }
   }
   out_vid << to;
#endif
   return 0;
}

