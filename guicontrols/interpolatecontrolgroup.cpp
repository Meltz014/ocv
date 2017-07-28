#include "interpolatecontrolgroup.h"

#define MAX_INTERP_FRAMES ( 10 )

InterpolateGroup::InterpolateGroup( const QString &title, QWidget *parent )
   : QGroupBox( title, parent )
{

   checkbox = new QCheckBox( "Interpolate Frames" );
   checkbox->setFocusPolicy( Qt::NoFocus );

   slider = new QSlider( Qt::Horizontal );
   slider->setFocusPolicy( Qt::NoFocus );
   slider->setTickPosition( QSlider::TicksBothSides );
   slider->setFixedSize( 100, 20 );
   slider->setTickInterval( 2 );
   slider->setSingleStep( 1 );
   slider->setMinimum( 0 );
   slider->setMaximum( MAX_INTERP_FRAMES );
   slider->setEnabled( false );

   label = new QLabel( "Interpolated Frames: 0" );

   connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
   connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeText(int)));
   connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(enableDisable(int)));

   QBoxLayout *slidersLayout = new QBoxLayout( QBoxLayout::TopToBottom );
   slidersLayout->addWidget(checkbox);
   slidersLayout->addWidget(slider);
   slidersLayout->addWidget(label);
   setLayout(slidersLayout);
}

void InterpolateGroup::enableDisable( int new_state )
{
   slider->setEnabled( new_state );
   if ( new_state )
   {
      slider->setValue( stored_value );
   }
   else
   {
      slider->setValue( 0 );
   }
}

void InterpolateGroup::changeText( int value )
{
   if ( checkbox->isChecked( ) )
   {
      stored_value = value;
   }
   label->setText( QString( "Interpolated Frames: %1" ).arg( value ) );
}
