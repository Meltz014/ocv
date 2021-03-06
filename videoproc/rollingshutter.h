#ifndef ROLLSHUT_H
#define ROLLSHUT_H

#include "..\commontypes.h"
#include "..\videoproc\vid.h"
#include "..\videoproc\interpolate.h"

// seconds
#define DEFAULT_ROLL_TIME ( 1.0f )

class RollingShutter : public QObject
{
  Q_OBJECT

 public:
   RollingShutter( Vid * video );
   void generateEffect( cv::OutputArray generated_img, int interpolated_frames, SettingsData *interpolate_settings );
   void setRollTime( double time );

 signals:
   void rowProcessed( );

 private:
   Vid * video;
   double roll_time;
};

#endif // ROLLSHUT_H
