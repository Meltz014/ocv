#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "commontypes.h"
#include "rollingshutter.h"
#include "vid.h"
#include "roll_time_group.h"
#include "interpolatecontrolgroup.h"
#include "exportgroup.h"

class QLabel;

class MainWindow : public QWidget
{
  Q_OBJECT

 public:
   MainWindow( );

 private slots:
   void effectRowProcessed( );
   void loadFileButtonCallback( );
   void generateEffectCallback( );
   void updateRollTime( int value );
   void exportFrame( export_options option );
   void updateInterpolatedFrames( int value );

 protected:
  void resizeEvent( QResizeEvent *event ) override;
  void keyPressEvent( QKeyEvent *event ) override;

 private:
   void updateGui( );
   void loadVid( QString file_name );

   RollTimeGroup *slider;
   InterpolateGroup *interpolate_control;
   ExportGroup *exportgroup;
   QLabel *current_frame_display;
   QLabel *generated_img_display;
   QPushButton *file_button;
   QPushButton *generate_button;
   cv::Mat orig_img;
   cv::Mat disp_img;
   cv::Mat generated_img;
   Vid video_obj;
   int interpolated_frames;
   double roll_time;
};

#endif // MAINWINDOW_H

