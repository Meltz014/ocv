#ifndef INTERPCONTROL_H
#define INTERPCONTROL_H

#include "commontypes.h"

class InterpolateGroup : public QGroupBox
{
   Q_OBJECT

 public:
   InterpolateGroup( const QString &title, QWidget *parent=0 );

 signals:
   void valueChanged( int value );

 private slots:
   void changeText( int value );
   void enableDisable( int new_state );

 private:
   QCheckBox *checkbox;
   QSlider *slider;
   QLabel *label;
   int stored_value;
};


#endif
