#include "WaitView.h"
#include <iostream>
#include <ui_waitView.h>
#include <common/ProtocolSocket.h>

WaitView::WaitView(ProtocolSocket &ps, QWidget *parent) :
    QDialog(parent),
    ps(ps),
    ui() {
    ui.setupUi(this);
}

void WaitView::on_waitBtn_clicked() {
    QPushButton *waitBtn = findChild<QPushButton*>("waitBtn");
    waitBtn->setDisabled(true);
    std::string welcome_message(100, '\0');
    std::cout << "Waiting for the game to START \n";
    uint8_t car = 1;
    ps.send(car);

    bool continue_receiving = true;
    ps.receive(welcome_message);

    std::cout << welcome_message;
    if (welcome_message.substr(0,5) == "ERROR") {
         continue_receiving = false;
    }
    std::cout << "ESPERANDO \n";
    uint8_t flag = 0;
    ps.receive(flag);
    std::cout << flag << "\n";
    this->close();
}

WaitView::~WaitView() {}