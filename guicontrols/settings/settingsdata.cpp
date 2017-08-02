#include "settingsdata.h"

SettingsData::SettingsData( flow_type f_type )
{
   this->f_type = f_type;
}

void SettingsData::setIntSetting( settings_names name, int val )
{
   i_settings[ name ] = val;
}

void SettingsData::setDoubleSetting( settings_names name, double val )
{
   d_settings[ name ] = val;
}

void SettingsData::setTextSetting( settings_names name, QString val )
{
   t_settings[ name ] = val;
}

bool SettingsData::getIntSetting( settings_names name, int &the_value )
{
   bool success = false;
   if ( i_settings.find( name ) != i_settings.end( ) )
   {
      success = true;
      the_value = i_settings[ name ];
   }
   return success;
}

bool SettingsData::getDoubleSetting( settings_names name, double &the_value )
{
   bool success = false;
   if ( d_settings.find( name ) != d_settings.end( ) )
   {
      success = true;
      the_value = d_settings[ name ];
   }
   return success;
}

bool SettingsData::getTextSetting( settings_names name, QString &the_value )
{
   bool success = false;
   if ( t_settings.find( name ) != t_settings.end( ) )
   {
      success = true;
      the_value = t_settings[ name ];
   }
   return success;
}

flow_type SettingsData::getFlowtype( )
{
   return this->f_type;
}
