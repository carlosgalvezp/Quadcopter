#ifndef CRIUSGUI_H
#define CRIUSGUI_H

#include <QMainWindow>
#include <QTimer>

#include <time.h>
#include <unistd.h>

#include "serialcomm.h"
#include "timeplot.h"
#include "telemetry.h"
#include "utils.h"

#include <GL/glu.h>


#define REFRESH_RATE    60      // FPS
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
    void receiveData();

signals:
    void toggleSerial();

private slots:
    void on_pushButton_clicked();



    void refresh();

private:
    Ui::CriusGUI *ui;
    QTimer *refresh_timer_;
    SerialComm *serialPort_;

    TimePlot *acc_plot_;
    TimePlot *gyro_plot_;
    TimePlot *mag_plot_;

    bool active_;


    void telemetryUpdateGUI(const char* const rx_data, int n_read_bytes);

    void telemetryCmdIMU(const char* const rx_data, int n_read_bytes);
    void telemetryCmdAttitude(const char* const rx_data, int n_read_bytes);

};

#endif // CRIUSGUI_H
