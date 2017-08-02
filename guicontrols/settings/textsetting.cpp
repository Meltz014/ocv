#include "textsetting.h"

TextSetting::TextSetting( QString name, QString default_value, const QString tool_tip )
{
   QLabel *name_label = new QLabel( name );
   edit_box = new QLineEdit( default_value );

   QBoxLayout *layout = new QBoxLayout( QBoxLayout::LeftToRight );
   layout->addWidget( name_label );
   layout->addWidget( edit_box );
   this->setLayout( layout );
   this->setToolTip( tool_tip );
   this->name = name;
}

QString TextSetting::getValue( )
{
   return edit_box->displayText( );
}

QString TextSetting::getName( )
{
   return this->name;
}

IntSetting::IntSetting( QString name, int default_value, const QString tool_tip ) :
   TextSetting( name, QString::asprintf( "%d", default_value ), tool_tip )
{
   this->edit_box->setValidator( new QIntValidator( ) );
}

int IntSetting::getValue( )
{
   return edit_box->displayText( ).toInt( );
}

DoubleSetting::DoubleSetting( QString name, double default_value, const QString tool_tip ) :
   TextSetting( name, QString::asprintf( "%.4f", default_value ), tool_tip )
{
   this->edit_box->setValidator( new QDoubleValidator( ) );
}

double DoubleSetting::getValue( )
{
   return edit_box->displayText( ).toDouble( );
}
