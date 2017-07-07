#include "mainwindow.h"
using namespace cv;

/**
 * Constructor for MainWindow class
 * 
 * @author David Melton (7/7/2017)
 */
MainWindow::MainWindow( )
{
   qDebug( ) << "Hello";

   video_obj = Vid( );

   current_frame_display = new QLabel(tr("Insert image here"));
   generated_img_display = new QLabel(tr("Insert image here"));

   file_button = new QPushButton( "Select File", this );
   file_button->setFocusPolicy( Qt::NoFocus );
   file_button->setGeometry( QRect( QPoint( 100, 100 ), QSize( 200, 50 ) ) );
   connect( file_button, SIGNAL( released( ) ), this, SLOT( loadFileButtonCallback(  ) ) );

   // create layout
   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->setColumnStretch( 0, 1 );
   mainLayout->addWidget( current_frame_display, 0, 0, 1, 1 );
   mainLayout->addWidget( generated_img_display, 0, 1, 1, 1 );
   mainLayout->addWidget( file_button, 1, 0, 1, 1 );
   setLayout( mainLayout );

   setWindowTitle( tr( "The Window" ) );

   updateGui( );
}

/**
 * Callback for Load File button press
 * 
 * @author David Melton (7/7/2017)
 */
void MainWindow::loadFileButtonCallback( )
{
   QString file_name = QFileDialog::getOpenFileName( this,
                                                     tr("Open Video File"),
                                                     "C:/Users/501219/Videos",
                                                     tr("All Files (*.*)"));
   qDebug( ) << file_name;
   if ( !file_name.isEmpty( ) )
   {
      loadVid( file_name );
      qDebug( ) << video_obj.getCurrentFrame( generated_img );
      qDebug( ) << generated_img.rows;
      updateGui( );
   }
}

/**
 * Loads a video object and loads the first frame into
 * this->disp_img
 * 
 * @author David Melton (7/7/2017)
 * @param file_name
 * 
 */
void MainWindow::loadVid( QString file_name )
{
   video_obj = Vid( file_name );
   video_obj.getNextFrame( disp_img );
}

/**
 * Updates the two image labels and adjusts the window size to 
 * fit 
 * 
 * @author David Melton (7/7/2017)
 */
void MainWindow::updateGui( )
{
   current_frame_display->setPixmap( QPixmap::fromImage( QImage( disp_img.data,
                                                    disp_img.cols,
                                                    disp_img.rows,
                                                    disp_img.step,
                                                    QImage::Format_RGB888
                                                   )
                                           )
                       );
   generated_img_display->setPixmap( QPixmap::fromImage( QImage( generated_img.data,
                                                    generated_img.cols,
                                                    generated_img.rows,
                                                    generated_img.step,
                                                    QImage::Format_RGB888
                                                   )
                                           )
                       );
   this->adjustSize( );
}

/**
 * Callback for resizeEvent
 * 
 * @author David Melton (7/7/2017)
 */
void MainWindow::resizeEvent( QResizeEvent * /* event */ )
{
   //QSize new_img_qsize = event->size( ) - QSize( 22, 51 );
   //cv::Size new_img_size = cv::Size( new_img_qsize.width( ), new_img_qsize.height( ) );
   //
   //// Scale image to new size
   //cv::resize( orig_img, disp_img, new_img_size, 0, 0, INTER_LINEAR );
   //updateGui( );
}

/**
 * Callback for keyPressEvent.  Handles arrow keys
 * 
 * @author David Melton (7/7/2017)
 * 
 * @param event 
 */
void MainWindow::keyPressEvent( QKeyEvent * event )
{
   switch ( event->key( ) )
   {
      // Step to next frame
      case Qt::Key_Right:
         if ( !video_obj.isEmpty( ) )
         {
            video_obj.getNextFrame( disp_img );
            updateGui( );
         }
         break;
      // Step to previous frame
      case Qt::Key_Left:
         if ( !video_obj.isEmpty( ) )
         {
            video_obj.getPrevFrame( disp_img );
            updateGui( );
         }
         break;
      // Scale video size down
      case Qt::Key_Down:
         if ( !video_obj.isEmpty( ) )
         {
            video_obj.scaleDown( );
            video_obj.getCurrentFrame( disp_img );
            updateGui( );
         }
         break;
      // Scale video size up
      case Qt::Key_Up:
         if ( !video_obj.isEmpty( ) )
         {
            video_obj.scaleUp( );
            video_obj.getCurrentFrame( disp_img );
            updateGui( );
         }
         break;
      default:
         break;
   }
}
