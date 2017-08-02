#include "simpleflowpane.h"

SimpleFlowPane::SimpleFlowPane( )
{
   qDeleteAll( this->children( ) );
   this->initUI( );
}

void SimpleFlowPane::initUI( )
{
   qDebug( ) << "SimpleFlowPane initUI";

   layers = new IntSetting( "Layers", 3, "Number of layers" );
   avg_block = new IntSetting( "Averaging Block Size", 2, "Size of block through which we sum up when calculate cost function for pixel" );
   max_flow = new IntSetting( "Max Flow", 4, "maximal flow that we search at each level" );
   sigma_dist = new DoubleSetting( "Sigma Dist", 4.1, "vector smooth spatial sigma parameter" );
   sigma_color = new DoubleSetting( "Sigma Color", 25.5, "vector smooth color sigma parameter" );
   postp_window = new IntSetting( "PostProcess Window", 18, "window size for postprocess cross bilateral filter" );
   sigma_dist_fix = new DoubleSetting( "Sigma Dist Fix", 55.0, "spatial sigma for postprocess cross bilateral filter" );
   sigma_color_fix = new DoubleSetting( "Sigma Color Fix", 25.5, "color sigma for postprocess cross bilateral filter" );
   occ_thr = new DoubleSetting( "Occlustion Threshold", 0.35, "threshold for detecting occlusions" );
   up_avg_rad = new IntSetting( "Upscale Averaging Radius", 18, " window size for bilateral upscale operation" );
   up_sigma_dist = new DoubleSetting( "Upscale Sigma Dist", 55.0, "spatial sigma for bilateral upscale operation" );
   up_sigma_color = new DoubleSetting( "Upscale Sigma Color", 25.5, "color sigma for bilateral upscale operation" );
   speed_thr = new DoubleSetting( "Speed Up Threshold", 10.0, "threshold to detect point with irregular flow - where flow should be recalculated after upscale" );

   QBoxLayout *layout = new QBoxLayout( QBoxLayout::TopToBottom );
   layout->addWidget( layers );
   layout->addWidget( avg_block );
   layout->addWidget( max_flow );
   layout->addWidget( sigma_dist );
   layout->addWidget( sigma_color );
   layout->addWidget( postp_window );
   layout->addWidget( sigma_dist_fix );
   layout->addWidget( sigma_color_fix );
   layout->addWidget( occ_thr );
   layout->addWidget( up_avg_rad );
   layout->addWidget( up_sigma_dist );
   layout->addWidget( up_sigma_color );
   layout->addWidget( speed_thr );
   this->setLayout( layout );
}

void SimpleFlowPane::updateSettings( )
{
   qDebug( ) << layers->getValue( );
}

void SimpleFlowPane::printSettings( )
{
   qDebug( ) << layers->getName( ) << layers->getValue( );
   qDebug( ) << avg_block->getName( ) << avg_block->getValue( );
   qDebug( ) << max_flow->getName( ) << max_flow->getValue( );
   qDebug( ) << sigma_dist->getName( ) << sigma_dist->getValue( );
   qDebug( ) << sigma_color->getName( ) << sigma_color->getValue( );
   qDebug( ) << postp_window->getName( ) << postp_window->getValue( );
   qDebug( ) << sigma_dist_fix->getName( ) << sigma_dist_fix->getValue( );
   qDebug( ) << sigma_color_fix->getName( ) << sigma_color_fix->getValue( );
   qDebug( ) << occ_thr->getName( ) << occ_thr->getValue( );
   qDebug( ) << up_avg_rad->getName( ) << up_avg_rad->getValue( );
   qDebug( ) << up_sigma_dist->getName( ) << up_sigma_dist->getValue( );
   qDebug( ) << up_sigma_color->getName( ) << up_sigma_color->getValue( );
   qDebug( ) << speed_thr->getName( ) << speed_thr->getValue( );
}

SettingsData * SimpleFlowPane::getSettings( )
{
   SettingsData * settings = new SettingsData( SIMPLE_FLOW );
   settings->setIntSetting( LAYERS, layers->getValue( ) );
   settings->setIntSetting( AVG_BLOCK_SIZE, avg_block->getValue( ) );
   settings->setIntSetting( MAX_FLOW, max_flow->getValue( ) );
   settings->setDoubleSetting( SIGMA_DIST, sigma_dist->getValue( ) );
   settings->setDoubleSetting( SIGMA_COLOR, sigma_color->getValue( ) );
   settings->setIntSetting( POSTPROC_WINDOW, postp_window->getValue( ) );
   settings->setDoubleSetting( SIGMA_DIST_FIX, sigma_dist_fix->getValue( ) );
   settings->setDoubleSetting( SIGMA_COLOR_FIX, sigma_color_fix->getValue( ) );
   settings->setDoubleSetting( OCC_THR, occ_thr->getValue( ) );
   settings->setIntSetting( UPSCALE_AVG_RAD, up_avg_rad->getValue( ) );
   settings->setDoubleSetting( UPSCALE_SIGMA_DIST, up_sigma_dist->getValue( ) );
   settings->setDoubleSetting( UPSCALE_SIGMA_COLOR, up_sigma_color->getValue( ) );
   settings->setDoubleSetting( SPEED_UP_THR, speed_thr->getValue( ) );
   return settings;
}
