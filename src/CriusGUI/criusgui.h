#ifndef CRIUSGUI_H
#define CRIUSGUI_H

#include <QMainWindow>

#include "serialcomm.h"

namespace Ui {
class CriusGUI;
}

class CriusGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit CriusGUI(QWidget *parent = 0);
    ~CriusGUI();

private:
    Ui::CriusGUI *ui;

    SerialComm serialComm_;
};

#endif // CRIUSGUI_H
