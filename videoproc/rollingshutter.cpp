#include "rollingshutter.h"

RollingShutter::RollingShutter( Vid * video )
{
   this->video = video;
   roll_time = DEFAULT_ROLL_TIME;
}

/**
 * Generates a rolling shutter effect
 * 
 * @author David Melton (7/28/2017)
 * 
 * @param generated_img output image
 * @param interpolated_frames number of frames to interpolate
 */
void RollingShutter::generateEffect( cv::OutputArray generated_img, int interpolated_frames, SettingsData *interpolate_settings )
{
   cv::Mat frame = cv::Mat( );
   cv::Mat last_frame = cv::Mat( );
   cv::Mat next_frame = cv::Mat( );
   cv::Mat interp_frame = cv::Mat( );
   cv::Mat slice;
   cv::Mat out_frame;
   int status;
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
   pixels_per_frame = ( int )std::max( (double)max_dim / ( num_frames * ( interpolated_frames + 1 ) ), 1.0 );
   qDebug( ) << "pixels_per_frame " << pixels_per_frame;

   for( int i = 0; i < num_frames; i++ )
   {
      if( interpolated_frames > 0 )
      {
         status = video->getCurrentFrame( frame ) && video->getNextFrame( next_frame );
      }
      else
      {
         status = video->getNextFrame( frame );
      }
      if( status )
      {
         // always get a slice from the real frame
         start_idx = i * ( interpolated_frames + 1 ) * pixels_per_frame;
         end_idx = ( i * ( interpolated_frames + 1 ) + 1 ) * pixels_per_frame;
         if( end_idx >= max_dim )
         {
            end_idx = max_dim - 1;
         }
         slice = frame.rowRange( start_idx, end_idx );
         out_frame.push_back( slice );
         emit rowProcessed( );

         if( interpolated_frames > 0 )
         {
            // interpolate between current frame and next frame
            Interpolater interpolater( frame, next_frame, interpolated_frames, interpolate_settings );
            for( int inter_frame_idx = 0; inter_frame_idx < interpolated_frames; inter_frame_idx++ )
            {
               start_idx = ( i * ( interpolated_frames + 1 ) + inter_frame_idx + 1 ) * pixels_per_frame;
               end_idx = ( i * ( interpolated_frames + 1 ) + inter_frame_idx + 2 ) * pixels_per_frame;
               if( end_idx >= max_dim )
               {
                  end_idx = max_dim - 1;
               }
               if( start_idx >= max_dim )
               {
                  start_idx = max_dim - 1;
               }

               interpolater.getNextFrame( interp_frame );
               slice = interp_frame.rowRange( start_idx, end_idx );
               out_frame.push_back( slice );
               emit rowProcessed( );
            }
         }
         //qDebug( ) << "out_frame rows" << out_frame.rows;
         last_frame = frame;
      }
      else
      {
         //qDebug() <<  "Error reading frame!";
         slice = last_frame.rowRange( start_idx, end_idx );
         out_frame.push_back( slice );
         emit rowProcessed( );
      }
   }
}

/**
 * Update the roll time in seconds for rolling shutter effect
 * 
 * @author David Melton (7/28/2017)
 * 
 * @param time 
 */
void RollingShutter::setRollTime( double time )
{
   this->roll_time = time;
}
