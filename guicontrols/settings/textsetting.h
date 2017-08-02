#ifndef TEXTSETTING_H
#define TEXTSETTING_H

#include "../../commontypes.h"
#include <QIntValidator>

class TextSetting : public QWidget
{
   Q_OBJECT

 public:
   TextSetting( QString name, QString default_value, const QString tool_tip );
   QString getValue( );
   QString getName( );

 private:
   QString val;
   QString name;

 protected:
   QLineEdit *edit_box;
};


class IntSetting : public TextSetting
{
   Q_OBJECT

 public:
   IntSetting( QString name, int default_value, const QString tool_tip );
   int getValue( );
};

class DoubleSetting : public TextSetting
{
   Q_OBJECT

 public:
   DoubleSetting( QString name, double default_value, const QString tool_tip );
   double getValue( );
};

#endif
