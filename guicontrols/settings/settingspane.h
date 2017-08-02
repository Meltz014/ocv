#ifndef SETTINGSPANE_H
#define SETTINGSPANE_H

#include "../../commontypes.h"
#include "settingsdata.h"

class SettingsPane : public QWidget
{
   Q_OBJECT

 public:
      SettingsPane( );
      virtual void initUI( );
      virtual SettingsData* getSettings( );
      virtual void printSettings( );
};

#endif
