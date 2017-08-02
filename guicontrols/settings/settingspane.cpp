#include "settingspane.h"

SettingsPane::SettingsPane( )
{
   this->initUI( );
}

void SettingsPane::initUI( )
{
   QLabel *label = new QLabel( "No current settings." );
   QBoxLayout *layout = new QBoxLayout( QBoxLayout::LeftToRight );
   layout->addWidget( label );
   this->setLayout( layout );
}

SettingsData* SettingsPane::getSettings( )
{
   return new SettingsData( NO_FLOW );
}

void SettingsPane::printSettings( )
{
   qDebug( ) << "Base SettingsPane: no settings";
}
