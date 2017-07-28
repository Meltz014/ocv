#ifndef EXPORTGROUP_H
#define EXPORTGROUP_H

#include "..\commontypes.h"

enum export_options {
    SOURCE_FRAME,
    OUT_FRAME
};

Q_DECLARE_METATYPE( export_options )

class ExportGroup : public QGroupBox
{
    Q_OBJECT

public:
    ExportGroup( const QString &title, QWidget *parent=0 );

signals:
    void doExport( export_options option );

private slots:
    void buttonCallback( );

private:
    QComboBox *combobox;
    QLabel *label;
    QPushButton *button;
};

#endif
