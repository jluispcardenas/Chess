#include "online.h"
// #include "ui_online.h"

Online::Online(MainBoard *parent) :
    QDialog(parent)//, ui(new Ui::Online)
{
  /*  this->parent = parent;

    ui->setupUi(this);

    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(ipConnect()));
    connect(ui->btnStartServer, SIGNAL(clicked()), this, SLOT(startServer()));
*/}

void Online::ipConnect()
{
    /*QString ip = ui->ipTarget->text();
    QRegExp rx("([0-9]{1,3})(\\.[0-9]{1,3}){3}");
    if (!rx.exactMatch(ip)) {
        QMessageBox::information(this, tr("Chess Server"),
                          tr("Invalid ip address"));
        return;
    }
    parent->ipConnect(ip);
*/
    close();
}

void Online::startServer()
{
    //parent->startServer();

    close();
}

Online::~Online()
{
//    delete ui;
}
