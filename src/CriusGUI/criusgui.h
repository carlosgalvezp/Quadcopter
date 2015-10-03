#ifndef CRIUSGUI_H
#define CRIUSGUI_H

#include <QMainWindow>
#include <QTimer>
#include <QQueue>

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
    void loadFCConfig();
    void sendFCConfig(const QByteArray &data);

private slots:
    void on_pushButton_clicked();

    void on_PushButton_Config_Load_clicked();

    void on_PushButton_Config_Send_clicked();

private:
    Ui::CriusGUI *ui;

    TimePlot *imu_plot, *control_plot;

    bool active_;

    GUIData gui_data_;
    SerialDecoder serial_decoder_;
    QQueue<unsigned char> rx_data_buffer_;

    void updateGUI();
};

#endif // CRIUSGUI_H
