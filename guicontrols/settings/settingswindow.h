#ifndef SETTINGSWIN_H
#define SETTINGSWIN_H

#include "../../commontypes.h"
#include "settingspane.h"
#include "simpleflowpane.h"


class SettingsWindow : public QWidget
{
   Q_OBJECT

 public:
      SettingsWindow( );

 signals:
      void settingsSaved( SettingsData * settings );
      void canceled( );

 private slots:
      void okayCallback( );
      void cancelCallback( );
      void changeSettingsPane( );

 private:
      void addNewSettingsPane( flow_type opt );
      QComboBox *option_select;
      QPushButton *okay_btn;
      QPushButton *cancel_btn;
      QGridLayout *grid_layout;
};

#endif
