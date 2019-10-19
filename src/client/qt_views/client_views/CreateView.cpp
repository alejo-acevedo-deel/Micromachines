#include <iostream>
#include "CreateView.h"
#include "ui_createView.h"

CreateView::CreateView(ProtocolSocket &ps, QWidget *parent) :
                        QDialog(parent),
                        ps(ps),
                        ui() {
    ui.setupUi(this);
}

void CreateView::on_btnBoxCreate_accepted() {
  std::cout << "VOY A CREAR UNA PARTIDA \n";
  std::vector<uint8_t> buffer(4096);
  std::string server_match_answer("ERROR");
  while (server_match_answer.substr(0,5) == "ERROR") {
    std::cout << "Write match name..." << "\n";
    QPlainTextEdit *matchTxtIn = findChild<QPlainTextEdit*>("matchTxtIn");
    std::string match_name = matchTxtIn->toPlainText().toStdString();
    std::cout << "EL Match " << match_name << "\n";
    ps.send(match_name);
    ps.receive(buffer);
    server_match_answer.assign(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    buffer.clear(); buffer.resize(4096);
    std::cout << server_match_answer;
  }

  std::string server_username_answer("ERROR");
  while (server_username_answer.substr(0,5) == "ERROR") {
    std::cout << "Write your username..." << "\n";
    QPlainTextEdit *usrTxtIn = findChild<QPlainTextEdit*>("usrTxtIn");
    std::string username = usrTxtIn->toPlainText().toStdString();
    std::cout << "EL usuario " << username << "\n";
    ps.send(username);
    ps.receive(buffer);
    server_username_answer.assign(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    buffer.clear(); buffer.resize(4096);
    std::cout << server_username_answer;
  }
  this->close();
}

CreateView::~CreateView() {}
