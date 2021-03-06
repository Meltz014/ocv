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
   roll_time = 1.0f;
   interpolated_frames = 0;
   interpolate_settings = new SettingsData( NO_FLOW );

   interpolate_control = new InterpolateGroup( "Frame Interpolation" );
   connect( interpolate_control, SIGNAL( valueChanged( int ) ), this, SLOT( updateInterpolatedFrames( int ) ) );
   connect( interpolate_control, SIGNAL( settingsSaved( SettingsData * ) ), this, SLOT( updateInterpolateSettings( SettingsData * ) ) );

   slider = new RollTimeGroup("Set Roll Time", this);
   slider->setMinimum( 1 );
   slider->setMaximum( 10 );
   connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateRollTime( int )));

   exportgroup = new ExportGroup( "Export", this );
   connect(exportgroup, SIGNAL(doExport(export_options)), this, SLOT(exportFrame( export_options )));

   current_frame_display = new QLabel(tr("Insert image here"));
   generated_img_display = new QLabel(tr("Insert image here"));

   file_button = new QPushButton( "Select File", this );
   file_button->setFocusPolicy( Qt::NoFocus );
   file_button->setGeometry( QRect( QPoint( 100, 100 ), QSize( 200, 50 ) ) );
   connect( file_button, SIGNAL( released( ) ), this, SLOT( loadFileButtonCallback( ) ) );

   generate_button = new QPushButton( "Generate Effect", this );
   generate_button->setFocusPolicy( Qt::NoFocus );
   generate_button->setGeometry( QRect( QPoint( 100, 100 ), QSize( 200, 50 ) ) );
   connect( generate_button, SIGNAL( released( ) ), this, SLOT( generateEffectCallback( ) ) );

   // create layout
   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->setColumnStretch( 0, 1 );

   mainLayout->addWidget( interpolate_control, 0, 0, 1, 1 );
   mainLayout->addWidget( slider, 1, 0, 1, 1 );
   mainLayout->addWidget( exportgroup, 2, 0, 1, 1 );
   mainLayout->addWidget( current_frame_display, 0, 1, 2, 1 );
   mainLayout->addWidget( generated_img_display, 0, 2, 2, 1 );
   mainLayout->addWidget( file_button, 2, 1, 1, 1 );
   mainLayout->addWidget( generate_button, 2, 2, 1, 1 );
   setLayout( mainLayout );

   setWindowTitle( tr( "The Window" ) );

   updateGui( );
}

/**
 * Callback for Load File button press
 * 
 * @author David Melton (7/7/2017)
 */
void MainWindow::generateEffectCallback( )
{
   RollingShutter *generator = new RollingShutter( &video_obj );
   connect( generator, SIGNAL( rowProcessed( ) ), this, SLOT( effectRowProcessed( ) ) );
   generator->setRollTime( roll_time );
   generator->generateEffect( generated_img, interpolated_frames, interpolate_settings );
   video_obj.getCurrentFrame( disp_img );
   updateGui( );
}

/**
 * Callback for when a row has been processed in the effects 
 * image 
 * 
 * @author David Melton (7/28/2017)
 */
void MainWindow::effectRowProcessed( )
{
   video_obj.getCurrentFrame( disp_img );
   updateGui( );
   qApp->processEvents( );
}


/**
 * callback for Load File button
 * 
 * @author David Melton (7/28/2017)
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
   if ( !disp_img.empty( ) )
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
   }
   this->adjustSize( );
   update( );
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
            video_obj.getCurrentFrame( generated_img );
            updateGui( );
         }
         break;
      // Scale video size up
      case Qt::Key_Up:
         if ( !video_obj.isEmpty( ) )
         {
            video_obj.scaleUp( );
            video_obj.getCurrentFrame( disp_img );
            video_obj.getCurrentFrame( generated_img );
            updateGui( );
         }
         break;
      default:
         break;
   }
}

/**
 * function to set the nuber of in-between frames to use 
 * for interpolation 
 *  
 * @author David Melton (7/28/2017)
 * 
 * @param value number of in-between frames to generate
 */
void MainWindow::updateInterpolatedFrames( int value )
{
   interpolated_frames = value;
}

void MainWindow::updateInterpolateSettings( SettingsData *new_settings )
{
   qDebug( ) << "new settings";
   interpolate_settings = new_settings;
}

/**
 * Callback for setting the shutter effect roll time
 * 
 * @author David Melton (7/28/2017)
 * 
 * @param value shutter roll time in seconds
 */
void MainWindow::updateRollTime( int value )
{
   roll_time = (double)value;
   qDebug( ) << value;
}

/**
 * Saves a frame as an image
 * 
 * @author David Melton (7/28/2017)
 * 
 * @param option which frame to save
 */
void MainWindow::exportFrame( export_options option )
{
   Mat out_img;
   Mat disp2;
   Mat flow;

   QString file_name = QFileDialog::getSaveFileName( this,
                                                     tr("Save Image File"),
                                                     "",
                                                     tr("All Files (*.jpg)"));
   if ( !file_name.isEmpty( ) )
   {
      switch ( option )
      {
         case SOURCE_FRAME:
            if ( !disp_img.empty( ) )
            {
               cv::cvtColor( disp_img, out_img, CV_RGB2BGR );
               cv::imwrite( file_name.toStdString( ), out_img );
               qDebug( ) << "img exported";
            }
            break;
         case OUT_FRAME:
            if ( !generated_img.empty( ) )
            {
               cv::cvtColor( generated_img, out_img, CV_RGB2BGR );
               cv::imwrite( file_name.toStdString( ), out_img );
               qDebug( ) << "img exported";
            }
            break;
         default:
            qDebug( ) << "invalid";
      }
   }
}
