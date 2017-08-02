#ifndef SIMPLEPANE_H
#define SIMPLEPANE_H

#include "../../commontypes.h"
#include "settingspane.h"
#include "textsetting.h"

class SimpleFlowPane : public SettingsPane
{
   Q_OBJECT

 public:
   SimpleFlowPane( );
   void initUI( ) override;
   void printSettings( ) override;
   SettingsData * getSettings( ) override;

 private slots:
   void updateSettings( );

 private:
  IntSetting *layers;
  IntSetting *avg_block;
  IntSetting *max_flow;
  DoubleSetting *sigma_dist;
  DoubleSetting *sigma_color;
  IntSetting *postp_window;
  DoubleSetting *sigma_dist_fix;
  DoubleSetting *sigma_color_fix;
  DoubleSetting *occ_thr;
  IntSetting *up_avg_rad;
  DoubleSetting *up_sigma_dist;
  DoubleSetting *up_sigma_color;
  DoubleSetting *speed_thr;
};

#endif
