#ifndef SETTINGSDATA_H
#define SETTINGSDATA_H

#include "../../commontypes.h"
typedef enum
{
  LAYERS,
  AVG_BLOCK_SIZE,
  MAX_FLOW,
  SIGMA_DIST,
  SIGMA_COLOR,
  POSTPROC_WINDOW,
  SIGMA_DIST_FIX,
  SIGMA_COLOR_FIX,
  OCC_THR,
  UPSCALE_AVG_RAD,
  UPSCALE_SIGMA_DIST,
  UPSCALE_SIGMA_COLOR,
  SPEED_UP_THR
} settings_names;

typedef std::map<settings_names, int> int_settings_map;
typedef std::map<settings_names, double> double_settings_map;
typedef std::map<settings_names, QString> text_settings_map;

class SettingsData
{

 public:
   SettingsData( flow_type f_type );
   void setIntSetting( settings_names name, int val );
   void setDoubleSetting( settings_names name, double val );
   void setTextSetting( settings_names name, QString val );

   bool getIntSetting( settings_names name, int &the_value );
   bool getDoubleSetting( settings_names name, double &the_value );
   bool getTextSetting( settings_names name, QString &the_value );
   flow_type getFlowtype( );

 private:
   int_settings_map i_settings;
   double_settings_map d_settings;
   text_settings_map t_settings;
   flow_type f_type;
};

#endif
