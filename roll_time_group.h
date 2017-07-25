#ifndef ROLLTIME_H
#define ROLLTIME_H

#include "commontypes.h"

class RollTimeGroup : public QGroupBox
{
   Q_OBJECT

 public:
   RollTimeGroup( const QString &title, QWidget *parent=0 );

 signals:
   void valueChanged( int value );

 public:
   void setValue( int value );
   void setMinimum( int value );
   void setMaximum( int value );

 private slots:
   void changeText( int value );

 private:
   QSlider *slider;
   QLabel *label;
};


#endif
