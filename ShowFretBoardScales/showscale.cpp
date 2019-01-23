#include "showscale.h"
#include "ui_showscale.h"
#include<vector>
#include<string>
#include<QVector>
#include<QString>
#include<QtCore>
#include<QtGui>
#include<QMessageBox>

ShowScale::ShowScale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowScale)
{
    ui->setupUi(this);
    QObject::connect(ui->noteButton, SIGNAL(clicked(bool)), SLOT(openNoteWindow()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked(bool)), SLOT(cancel()));

}

void ShowScale::cancel(){
    this->close();

}

void ShowScale::openNoteWindow(){
    QString scale = "";
    if (ui->scaleList->currentItem()->text() != ""){
        scale = ui->scaleList->currentItem()->text();
    } else {
         QMessageBox::about(this, tr("Error"), tr("Please select a scale first"));
         return;
    }
    showFretBoard = new ShowFretBoard();
    showFretBoard->show();
    QStringList scaleinfo = scale.split(' ');
    showFretBoard->getInfo(scaleinfo[0], scaleinfo[1]);

}

void ShowScale::populateList(QVector<QString> &notes, QString rootNote){
    for (int i = 0; i < notes.size(); i++) {
        ui->scaleList->insertItem(i, notes[i]);
    }

    ui->likelyLabel->setText("Root Note: " + rootNote);
}

ShowScale::~ShowScale()
{
    delete ui;
}
