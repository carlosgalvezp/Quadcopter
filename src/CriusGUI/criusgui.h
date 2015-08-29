#ifndef CRIUSGUI_H
#define CRIUSGUI_H

#include <QMainWindow>
#include <QTimer>

#include "serialcomm.h"
#include <time.h>
#include <unistd.h>

#define REFRESH_RATE    60      // FPS

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
    QTimer * refresh_timer_;
    SerialComm * serialPort_;

    bool active_;
};

#endif // CRIUSGUI_H
