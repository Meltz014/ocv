#include "interpolate.h"

Interpolater::Interpolater( cv::InputArray from, cv::InputArray to, uint8 N )
{
   this->from = from.getMat( );
   this->to = to.getMat( );
   this->ti = 1.0 / ( double ) ( N + 1 );
   this->current_frame = 0;

   // calculate forward flow
   cv::Mat flow;
   qDebug( ) << "calculating flow";
   cv::optflow::calcOpticalFlowSF( this->from,
                                   this->to,
                                   flow,
                                   3, 2, 4);//, 4.1, 25.5, 18, 55.0, 25.5, 0.35, 18, 55.0, 25.5, 10 );
   qDebug( ) << "done";

   cv::split( flow, this->flowxy );
}

void Interpolater::getNextFrame( cv::OutputArray interpolatedFrame )
{
   cv::Mat out_frame;
   // clear generated_img and prep output
   interpolatedFrame.create( this->from.size( ), CV_8UC3 );
   out_frame = interpolatedFrame.getMat( );

   cv::Vec3b pt_0;
   cv::Vec3b pt_1;

   double current_ti = this->ti * ( ++this->current_frame );
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
         c_fw_new = c + ( int )round( ( 1.0 - current_ti ) * this->flowxy[ 0 ].at<float>( r, c ) );
         r_fw_new = r + ( int )round( ( 1.0 - current_ti ) * this->flowxy[ 1 ].at<float>( r, c ) );

         // reverse interpolation
         c_bw_new = c - ( int )round( current_ti * this->flowxy[ 0 ].at<float>( r, c ) );
         r_bw_new = r - ( int )round( current_ti * this->flowxy[ 1 ].at<float>( r, c ) );

         // limit checks
         c_fw_new = std::min( std::max( c_fw_new, 0 ), cols - 1 );
         r_fw_new = std::min( std::max( r_fw_new, 0 ), rows - 1 );
         c_bw_new = std::min( std::max( c_bw_new, 0 ), cols - 1 );
         r_bw_new = std::min( std::max( r_bw_new, 0 ), rows - 1 );

         // copy value from new pixel index to pt_0 and pt_1
         pt_0 = this->from.at<cv::Vec3b>( r_bw_new, c_bw_new );
         pt_1 = this->from.at<cv::Vec3b>( r_fw_new, c_fw_new );

         // fade between fw and bw interpolations and copy to new mat
         for ( int chan=0; chan < channels; chan++ )
         {
            row_ptr[ c*channels + chan ] = ( uchar )round( ( 1.0 - current_ti ) * pt_0[ chan ] + current_ti * pt_1[ chan ] );
         }
      }
   }
}
