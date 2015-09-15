#ifndef CRIUSGUI_H
#define CRIUSGUI_H

#include <QMainWindow>
#include <QTimer>

#include <time.h>
#include <unistd.h>

#include "timeplot.h"
#include "utils.h"
#include "serialdecoder.h"
#include "guidata.h"

#include "../ArduinoFC/Telemetry_Protocol.h"

#include <GL/glu.h>


#define N_POINTS_TIME   500


namespace Ui {
class CriusGUI;
}

class CriusGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit CriusGUI(QWidget *parent = 0);
    ~CriusGUI();

public slots:
    void getSerialData(const QByteArray &data);

signals:
    void toggleSerial();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CriusGUI *ui;

    TimePlot *imu_plot, *control_plot;

    bool active_;

    GUIData gui_data_;
    SerialDecoder serial_decoder_;

    void updateGUI();
};

#endif // CRIUSGUI_H
