#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "commontypes.h"
#include "vid.h"

class QLabel;

class MainWindow : public QWidget
{
  Q_OBJECT

 public:
   MainWindow( );

 private slots:
   void loadFileButtonCallback( );

 protected:
  void resizeEvent( QResizeEvent *event ) override;
  void keyPressEvent( QKeyEvent *event ) override;

 private:
   void updateGui( );
   void loadVid( QString file_name );

   QLabel *current_frame_display;
   QLabel *generated_img_display;
   QPushButton *file_button;
   cv::Mat orig_img;
   cv::Mat disp_img;
   cv::Mat generated_img;
   Vid video_obj;
};

#endif // MAINWINDOW_H

