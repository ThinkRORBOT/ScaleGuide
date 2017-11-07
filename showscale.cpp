#include "showscale.h"
#include "ui_showscale.h"
#include<vector>
#include<string>
#include<QVector>
#include<QString>
#include<QTCore>
#include<QTGui>

ShowScale::ShowScale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowScale)
{
    ui->setupUi(this);
    QObject::connect(ui->noteButton, SIGNAL(clicked(bool)), SLOT(openNoteWindow(QString scale)));
    QObject::connect(ui->cancelButton, SIGNAL(clicked(bool)), SLOT(cancel()));

}

void ShowScale::cancel(){
    this->close();

}

void ShowScale::openNoteWindow(QString scale){

}

void ShowScale::populateList(QVector<QString> &notes){
    for (int i = 0; i < notes.size(); i++) {
        ui->scaleList->insertItem(i, notes[i]);
    }

}

ShowScale::~ShowScale()
{
    delete ui;
}
