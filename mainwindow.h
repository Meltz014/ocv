#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "commontypes.h"
#include "videoproc\rollingshutter.h"
#include "videoproc\vid.h"
#include "guicontrols\roll_time_group.h"
#include "guicontrols\interpolatecontrolgroup.h"
#include "guicontrols\exportgroup.h"

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
   void updateInterpolateSettings( SettingsData * new_settings );

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
   SettingsData *interpolate_settings;
   double roll_time;
};

#endif // MAINWINDOW_H

