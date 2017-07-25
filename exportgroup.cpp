#include "exportgroup.h"

ExportGroup::ExportGroup( const QString &title, QWidget *parent )
   : QGroupBox( title, parent )
{
   combobox = new QComboBox( );
   combobox->setFocusPolicy( Qt::NoFocus );
   combobox->addItem( "Source Frame", SOURCE_FRAME );
   combobox->addItem( "Output Frame", OUT_FRAME );

   label = new QLabel( "Choose export option" );

   button = new QPushButton( "Export", this );
   button->setFocusPolicy( Qt::NoFocus );
   connect( button, SIGNAL( released( ) ), this, SLOT( buttonCallback( ) ) );

   QBoxLayout *layout = new QBoxLayout( QBoxLayout::TopToBottom );
   layout->addWidget( label );
   layout->addWidget( combobox );
   layout->addWidget( button );
   setLayout( layout );
}

void ExportGroup::buttonCallback( )
{
   export_options data = combobox->currentData( ).value<export_options>( );
   emit doExport( data );
}
