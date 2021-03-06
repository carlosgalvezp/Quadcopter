#ifndef CRIUSGUI_H
#define CRIUSGUI_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>
#include <QQueue>

#include <time.h>
#include <unistd.h>
#include <map>
#include <utility>

#include "timeplot.h"
#include "utils.h"
#include "serialdecoder.h"
#include "guidata.h"

#include "Telemetry_Protocol.h"

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
    void receiveSerialPortInfo(const QStringList &port_names);

signals:
//    void toggleSerial();
    void loadFCConfig();
    void sendFCConfig(const QByteArray &data);
    void sendSerialConfig(const QString &port_name);
    void sendSerialDisconnect();
    void sendGotACK();

private slots:
    void on_PushButton_Config_Load_clicked();
    void on_PushButton_Config_Send_clicked();
    void on_pushButton_Connect_clicked();

private:
    Ui::CriusGUI *ui_;

    TimePlot *imu_plot_, *control_plot_;

    bool active_, connected_;

    GUIData gui_data_;
    SerialDecoder serial_decoder_;
    QQueue<unsigned char> rx_data_buffer_;

    void updateGUI();

    std::map<uint8_t, const char *> flightModeMap_ =
    {
        std::make_pair(0, "POWER ON"),
        std::make_pair(1, "DISARMED"),
        std::make_pair(2, "ARMED ACRO"),
        std::make_pair(3, "PASS_THROUGH")
    };
};

#endif // CRIUSGUI_H
