#ifndef INTERPCONTROL_H
#define INTERPCONTROL_H

#include "settings\settingswindow.h"
#include "..\commontypes.h"

class InterpolateGroup : public QGroupBox
{
   Q_OBJECT

 public:
   InterpolateGroup( const QString &title, QWidget *parent=0 );

 signals:
   void valueChanged( int value );
   void settingsSaved( SettingsData *new_settings );

 private slots:
   void changeText( int value );
   void enableDisable( int new_state );
   void buttonCallback( );

 private:
   QCheckBox *checkbox;
   QSlider *slider;
   QLabel *label;
   QPushButton *button;
   int stored_value;
};


#endif
