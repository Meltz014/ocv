#include "roll_time_group.h"

RollTimeGroup::RollTimeGroup( const QString &title, QWidget *parent )
   : QGroupBox( title, parent )
{
   slider = new QSlider( Qt::Horizontal );
   slider->setFocusPolicy( Qt::NoFocus );
   slider->setTickPosition( QSlider::TicksBothSides );
   slider->setFixedSize( 100, 20 );
   slider->setTickInterval( 2 );
   slider->setSingleStep( 1 );

   label = new QLabel( "Shutter Roll Time: 1s" );

   connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
   connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeText(int)));

   QBoxLayout *slidersLayout = new QBoxLayout( QBoxLayout::TopToBottom );
   slidersLayout->addWidget(slider);
   slidersLayout->addWidget(label);
   setLayout(slidersLayout);
}

void RollTimeGroup::changeText( int value )
{
   label->setText( QString( "Shutter Roll Time: %1s" ).arg( value ) );
}

void RollTimeGroup::setValue( int value )
{
   slider->setValue( value );
}

void RollTimeGroup::setMinimum( int value )
{
   slider->setMinimum( value );
}

void RollTimeGroup::setMaximum( int value )
{
   slider->setMaximum( value );
}
