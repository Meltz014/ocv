#include "settingswindow.h"

SettingsWindow::SettingsWindow( )
{
   this->setWindowTitle( "Settings" );
   option_select = new QComboBox( );
   option_select->addItem( "No Flow", NO_FLOW );
   option_select->addItem( "Simple Flow", SIMPLE_FLOW );
   option_select->addItem( "Deep Flow", DEEP_FLOW );
   okay_btn = new QPushButton( "Okay" );
   cancel_btn = new QPushButton( "Cancel" );

   connect( option_select, SIGNAL( currentIndexChanged( int ) ), this, SLOT( changeSettingsPane( ) ) );
   connect( okay_btn, SIGNAL( clicked( ) ), this, SLOT( okayCallback( ) ) );
   connect( cancel_btn, SIGNAL( clicked( ) ), this, SLOT( cancelCallback( ) ) );

   grid_layout = new QGridLayout;
   QBoxLayout *btn_layout = new QBoxLayout( QBoxLayout::LeftToRight );
   btn_layout->addWidget( okay_btn );
   btn_layout->addSpacing( 5 );
   btn_layout->addWidget( cancel_btn );

   grid_layout->setColumnStretch( 0, 1 );
   grid_layout->addWidget( option_select, 0, 0 );
   addNewSettingsPane( NO_FLOW );
   grid_layout->addLayout( btn_layout, 2, 0 );
   setLayout( grid_layout );
}

void SettingsWindow::okayCallback( )
{
   qDebug( ) << "okay";
   // get the settings pane widget from the grid layout
   SettingsPane *pane = (SettingsPane*)grid_layout->itemAtPosition( 1, 0 )->widget( );
   SettingsData *settings = pane->getSettings( );
   pane->printSettings( );
   emit settingsSaved( settings );
   this->close( );
}

void SettingsWindow::cancelCallback( )
{
   qDebug( ) << "cancel";
   this->close( );
}

void SettingsWindow::changeSettingsPane( )
{
   // delete old pane
   QLayoutItem *old = grid_layout->itemAtPosition( 1, 0 );
   int old_index = grid_layout->indexOf( old->widget( ) );
   old = grid_layout->takeAt( old_index );
   delete old->widget( );
   delete old;

   // init new settings pane
   flow_type opt = option_select->currentData( ).value<flow_type>( );
   addNewSettingsPane( opt );
 }

void SettingsWindow::addNewSettingsPane( flow_type opt )
{
   SettingsPane *pane;
   SimpleFlowPane *simple_pane;
   switch ( opt )
   {
      case NO_FLOW:
      case DEEP_FLOW:
         pane = new SettingsPane( );
         break;
      case SIMPLE_FLOW:
      default:
         simple_pane = new SimpleFlowPane( );
         pane = simple_pane;
   }
   grid_layout->addWidget( pane, 1, 0 );
}
