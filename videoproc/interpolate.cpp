#include "interpolate.h"

/**
 * Class to handle frame interpolation
 * 
 * @author David Melton (7/28/2017)
 * 
 * @param from beginning frame for interpolation
 * @param to ending frame for interpolation (should be 
 *           immediately following the "from" frame)
 * @param N Number of interpolated frames to generate
 * @param f_type Type of flow to use
 */
Interpolater::Interpolater( cv::InputArray from, cv::InputArray to, uint8 N, flow_type f_type )
{
   this->from = from.getMat( );
   this->to = to.getMat( );
   this->ti = 1.0 / ( double ) ( N + 1 );
   this->current_frame = 0;
   this->valid_flow = true;

   cv::Mat from_gray;
   cv::Mat to_gray;
   cv::Ptr<cv::DenseOpticalFlow> dof;

   // calculate forward flow
   cv::Mat flow;
   qDebug( ) << "calculating flow";
   switch ( f_type )
   {
   case SIMPLE_FLOW:
      qDebug( ) << "simple flow";
      cv::optflow::calcOpticalFlowSF( this->from,
                                      this->to,
                                      flow,
                                      3, 2, 4);//, 4.1, 25.5, 18, 55.0, 25.5, 0.35, 18, 55.0, 25.5, 10 );
      break;
   case DEEP_FLOW:
      cv::cvtColor( this->from, from_gray, cv::COLOR_RGB2GRAY );
      cv::cvtColor( this->to, to_gray, cv::COLOR_RGB2GRAY );
      qDebug( ) << "deep flow";
      dof = cv::optflow::createOptFlow_DeepFlow( );
      dof->calc( from_gray, to_gray, flow );
      break;
   case NO_FLOW:
   default:
      // NO_FLOW
      this->valid_flow = false;
      flow = cv::Mat::zeros( this->from.rows, this->from.cols, CV_32FC2 );
   }
   qDebug( ) << "done";

   cv::split( flow, this->flowxy );
}

/**
 * Get the next interpolated frame
 * 
 * @author David Melton (7/28/2017)
 * 
 * @param interpolatedFrame 
 */
void Interpolater::getNextFrame( cv::OutputArray interpolatedFrame )
{
   double current_ti = this->ti * ( ++this->current_frame );
   cv::Mat out_frame;
   // clear generated_img and prep output
   interpolatedFrame.create( this->from.size( ), CV_8UC3 );
   out_frame = interpolatedFrame.getMat( );

   if ( this->valid_flow )
   {
      cv::Vec3b pt_0;
      cv::Vec3b pt_1;
      qDebug(  ) << "current_ti" << current_ti;
      double flow_x;
      double flow_y;
      int r_fw_new = 0;
      int c_fw_new = 0;
      int r_bw_new = 0;
      int c_bw_new = 0;


      int rows = this->from.rows;
      int cols = this->from.cols;
      int channels = this->from.channels( );

      // pointer to current row in output mat
      uchar * row_ptr;

      for ( int r = 0; r < rows; ++r )
      {
         row_ptr = out_frame.ptr<uchar>( r );
         for ( int c = 0; c < cols; ++c )
         {
            // forward interpolation
            flow_x = this->flowxy[ 0 ].at<float>( r, c );
            if ( std::isnan( flow_x ) )
            {
               flow_x = 0.0f;
            }
            flow_y = this->flowxy[ 1 ].at<float>( r, c );
            if ( std::isnan( flow_y ) )
            {
               flow_y = 0.0f;
            }

            c_fw_new = c + ( int )round( ( 1.0f - current_ti ) * flow_x );
            r_fw_new = r + ( int )round( ( 1.0f - current_ti ) * flow_y );

            // reverse interpolation
            c_bw_new = c - ( int )round( current_ti * flow_x );
            r_bw_new = r - ( int )round( current_ti * flow_y );

            // limit checks
            c_fw_new = std::min( std::max( c_fw_new, 0 ), cols - 1 );
            r_fw_new = std::min( std::max( r_fw_new, 0 ), rows - 1 );
            c_bw_new = std::min( std::max( c_bw_new, 0 ), cols - 1 );
            r_bw_new = std::min( std::max( r_bw_new, 0 ), rows - 1 );

            // copy value from new pixel index to pt_0 and pt_1
            pt_0 = this->from.at<cv::Vec3b>( r_bw_new, c_bw_new );
            pt_1 = this->to.at<cv::Vec3b>( r_fw_new, c_fw_new );

            // fade between fw and bw interpolations and copy to new mat
            for ( int chan=0; chan < channels; chan++ )
            {
               row_ptr[ c*channels + chan ] = ( uchar )round( ( 1.0f - current_ti ) * pt_0[ chan ] + current_ti * pt_1[ chan ] );
            }
         }
      }
   }
   else
   {
      out_frame.pop_back( out_frame.rows );
      out_frame.push_back( this->from );
   }
}
