#include "showfretboard.h"
#include "ui_showfretboard.h"

#include "dbmanager.h"

#include <QTCore>
#include <QTGui>
#include <QWidget>
#include <QString>
#include <QVector>

ShowFretBoard::ShowFretBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowFretBoard)
{
    ui->setupUi(this);
    QObject::connect(ui->okButton, SIGNAL(clicked(bool)), SLOT(cancel()));
}

void ShowFretBoard::cancel(){
    this->close();
}

void ShowFretBoard::getInfo(QString key, QString mode){
    DbManager dbmanager;
    int pos = scales.indexOf(key);
    QVector<QString> standardScale;
    standardScale = dbmanager.returnScales(pos);
    QVector<int> scalePos;
    for (auto &it: standardScale) {
        for(int i = 0; i < scales.length(); i++){
            if(it == scales[i]) {
                scalePos.push_back(i);
            }
        }

    }
    if(mode == "Aeolian"){
        if (scalePos[2] == 0){
            standardScale[2] = scales[12];
        } else {
            standardScale[2] = scales[scalePos[3] - 1];
        }
        if (scalePos[5] == 0){
            standardScale[5] = scales[12];
        } else {
            standardScale[5] = scales[scalePos[5] - 1];
        }
        if (scalePos[6] == 0){
            standardScale[6] = scales[12];
        } else {
            standardScale[6] = scales[scalePos[6] - 1];
        }
    }
}

ShowFretBoard::~ShowFretBoard()
{
    delete ui;
}
