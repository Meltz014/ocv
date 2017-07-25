#include "vid.h"

/**
 * Constructor for Vid class
 * 
 * @author David Melton (7/7/2017)
 */
Vid::Vid(  )
{
   is_empty = true;
   current_frame = -1;
   num_frames = 0;
   scale = false;
   scale_w = DEFAULT_SCALE_VID;
   scale_h = DEFAULT_SCALE_VID;
}

/**
 * Constructor for Vid class
 * 
 * @author David Melton (7/7/2017)
 * 
 * @param file_name 
 *    name of video file to load
 */
Vid::Vid( QString file_name )
{
   is_empty = true;

   if ( !file_name.isEmpty( ) )
   {
      video_cap = cv::VideoCapture( file_name.toStdString( ) );
      //Mat frame;

      if ( !video_cap.isOpened( ) )
      {
         throw "Error when reading video file!";
      }
      is_empty = false;
      current_frame = -1;
      num_frames = getNumFrames( );
      scale = false;
      scale_w = DEFAULT_SCALE_VID;
      scale_h = DEFAULT_SCALE_VID;
      qDebug( ) << "Frame Rate: " << video_cap.get( cv::CAP_PROP_FPS );
      qDebug( ) << "Num Frames: " << getNumFrames( );

   }
}

/**
 * Scales video down by SCALE_INC
 * 
 * @author David Melton (7/7/2017)
 */
void Vid::scaleDown( )
{
   scale = true;
   scale_w -= SCALE_INC;
   scale_h -= SCALE_INC;
   if ( scale_w < SCALE_INC )
   {
      scale_w = SCALE_INC;
      scale_h = SCALE_INC;
   }
}

/**
 * Scales video up by SCALE_INC
 * 
 * @author David Melton (7/7/2017)
 */
void Vid::scaleUp( )
{
   scale = true;
   scale_w += SCALE_INC;
   scale_h += SCALE_INC;
}

/**
 * Returns true if no video is loaded
 * 
 * @author David Melton (7/7/2017)
 * 
 * @return is_empty
 */
bool Vid::isEmpty( )
{
   return is_empty;
}

/**
 * Loads current frame into image
 * 
 * @author David Melton (7/7/2017)
 * 
 * @param image 
 * 
 * @return stat 
 *    True if frame was successfully loaded 
 */
bool Vid::getCurrentFrame( cv::OutputArray image )
{
   bool stat = false;
   video_cap.set( cv::CAP_PROP_POS_FRAMES, current_frame );
   stat = video_cap.read( image );
   if ( !image.empty( ) )
   {
      cv::cvtColor( image, image, CV_BGR2RGB );
      if ( scale )
      {
         cv::resize( image, image, cv::Size( ), scale_w, scale_h, cv::INTER_LINEAR );
      }
   }
   qDebug( ) << "Get frame stat" << stat << " current_frame " << current_frame;
   return stat;
}

/**
 * Loads next frame into image
 * 
 * @author David Melton (7/7/2017)
 * 
 * @param image 
 * 
 * @return stat 
 *    True if frame was successfully loaded 
 */
bool Vid::getNextFrame( cv::OutputArray image )
{
   if ( video_cap.isOpened( ) )
   {
      if ( current_frame >= num_frames - 1 )
      {
         current_frame = num_frames - 2;
      }
      current_frame++;
      return getCurrentFrame( image );
   }
   return false;
}

/**
 * Loads previous frame into image
 * 
 * @author David Melton (7/7/2017)
 * 
 * @param image 
 * 
 * @return stat 
 *    True if frame was successfully loaded 
 */
bool Vid::getPrevFrame( cv::OutputArray image )
{
   if ( video_cap.isOpened( ) )
   {
      if ( current_frame > 0 )
      {
         current_frame -= 2;
         return getNextFrame( image );
      }
   }
   return false;
}

int Vid::getFPS( )
{
   return video_cap.get( cv::CAP_PROP_FPS );
}

int Vid::getNumFrames( )
{
   return video_cap.get( cv::CAP_PROP_FRAME_COUNT );
}

QSize Vid::getQSize( )
{
   cv::Mat image;
   getCurrentFrame( image );
   return QSize( image.cols, image.rows );
}

cv::Size Vid::getCSize( )
{
   cv::Mat image;
   getCurrentFrame( image );
   return cv::Size( image.cols, image.rows );
}
