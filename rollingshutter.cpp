#include "rollingshutter.h"

RollingShutter::RollingShutter( Vid * video )
{
   this->video = video;
   roll_time = DEFAULT_ROLL_TIME;
}

void RollingShutter::generateEffect( cv::OutputArray generated_img )
{
   cv::Mat frame = cv::Mat( );
   cv::Mat last_frame = cv::Mat( );
   cv::Mat slice;
   cv::Mat out_frame;
   int num_frames;
   int pixels_per_frame;
   int start_idx = 0;
   int end_idx = 0;
   int max_dim = video->getQSize( ).height( );

   // clear generated_img
   generated_img.create( video->getCSize( ), generated_img.type( ) );
   out_frame = generated_img.getMat( );
   out_frame.pop_back( out_frame.rows );

   num_frames = ( int )( video->getFPS( ) * roll_time );
   qDebug( ) << "Num frames " << num_frames;
   qDebug( ) << "max_dim " << max_dim;
   pixels_per_frame = ( int )( (double)max_dim / num_frames );
   qDebug( ) << "pixels_per_frame " << pixels_per_frame;

   for( int i = 0; i < num_frames; i++ )
   {
      if( video->getNextFrame( frame ) )
      {
         start_idx = i * pixels_per_frame;
         end_idx = ( i + 1 ) * pixels_per_frame;
         if( end_idx >= max_dim )
         {
            end_idx = max_dim - 1;
         }
         slice = frame.rowRange( start_idx, end_idx );
         out_frame.push_back( slice );
         //qDebug( ) << "out_frame rows" << out_frame.rows;
         last_frame = frame;
      }
      else
      {
         //qDebug() <<  "Error reading frame!";
         slice = last_frame.rowRange( start_idx, end_idx );
         out_frame.push_back( slice );
      }
      emit rowProcessed( );
   }
}

void RollingShutter::setRollTime( double time )
{
   this->roll_time = time;
}


void interpolateFrames( cv::InputArray from, cv::InputArray to, cv::OutputArray out_img )
{
   // Wrapper for calcOpticalFlowSF
   cv::Mat flow;
   cv::Mat out_mat;
   cv::Mat dest;

   cv::Mat fwrd[ 2 ];
   cv::Mat bwrd[ 2 ];
   cv::Mat buf;

   //// clear output array and get Mat
   //out_img.create( from.size( ), out_img.type( ) );
   //out_mat = out_img.getMat( );
   //out_mat.pop_back( out_mat.rows );

   // calculate forward flow
   cv::optflow::calcOpticalFlowSF( from, to,
                                   flow,
                                   3, 2, 4);//, 4.1, 25.5, 18, 55.0, 25.5, 0.35, 18, 55.0, 25.5, 10 );
   cv::split( flow, fwrd );

   // calculate backwards flow
   cv::optflow::calcOpticalFlowSF( to, from,
                                   flow,
                                   3, 2, 4);//, 4.1, 25.5, 18, 55.0, 25.5, 0.35, 18, 55.0, 25.5, 10 );
   cv::split( flow, bwrd );


   cv::FileStorage fw( "fw.txt", cv::FileStorage::WRITE | cv::FileStorage::FORMAT_JSON );
   cv::FileStorage bw( "bw.txt", cv::FileStorage::WRITE | cv::FileStorage::FORMAT_JSON );
   fw << "fwx" << fwrd[ 0 ];
   fw << "fwy" << fwrd[ 1 ];
   bw << "bwx" << bwrd[ 0 ];
   bw << "bwy" << bwrd[ 1 ];
   fw.release( );
   bw.release( );

}
