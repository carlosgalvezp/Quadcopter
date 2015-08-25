#include "criusgui.h"
#include "ui_criusgui.h"

CriusGUI::CriusGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CriusGUI)
{
    // Setup UI
    ui->setupUi(this);

    // Setup Serial Communication
    this->serialComm_.init();

    while(1)
    {
        std::cout << "ASD" << std::endl;

    }
}

CriusGUI::~CriusGUI()
{
    delete ui;
}
