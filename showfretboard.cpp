#include "showfretboard.h"
#include "ui_showfretboard.h"

#include "dbmanager.h"

#include <QTCore>
#include <QTGui>
#include <QWidget>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ShowFretBoard::ShowFretBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowFretBoard)
{
    ui->setupUi(this);

    //get properties of the user screen and set geometry of label accordingly
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    ui->fretboardLabel->setMaximumWidth(screenGeometry.width());
    ui->fretboardLabel->setMaximumHeight(screenGeometry.width()/5);
    ui->centralwidget->setLayout(ui->verticalLayout);

    QPixmap fretboard(":/resources/Resources/fretboardnumber.png");
    ui->fretboardLabel->setScaledContents(true);
    ui->fretboardLabel->setPixmap(fretboard);
    QObject::connect(ui->okButton, SIGNAL(clicked(bool)), SLOT(cancel()));
}

void ShowFretBoard::cancel(){
    this->close();
}

void ShowFretBoard::addNoteToScale(int string, int pos, bool root, QString note){
    QSize size = ui->fretboardLabel->size();
    pos++;

    int offsetWidth = 0;
    int offsetHeight = 0;
    float boardHeight = size.rheight();
    boardHeight = boardHeight/1.19;
    float boardWidth = size.rwidth();
    offsetWidth -= boardWidth/25-10;

    offsetHeight =+ boardHeight/3.6;

    //creates a new label and sets where the label should be placed.
    QLabel *noteLabel = new QLabel(this);
    noteLabel->setGeometry(boardWidth/24.8 * pos + offsetWidth, boardHeight/6 * string + offsetHeight, size.rwidth()/53, size.rwidth()/53);
    qDebug() << boardWidth/24.8 * pos + offsetWidth;
    QString path;
    if(note.length() == 2) {
        note = note[0] + "S";
    }
    if (root){
        path = ":/notes/Resources/Notes/" + note + "R.png";
    } else {
        path = ":/notes/Resources/Notes/" + note + "nR.png";
    }
    QPixmap fret(path);
    noteLabel->setScaledContents(true);
    noteLabel->setPixmap(fret);
    noteLabel->show();


}

void ShowFretBoard::getGuitarBoard(QString key){
    QFile file(":/guitarboard.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox qbox;
        qbox.about(this, "Error", "Cannot open guitarboard.txt. Please redownload application");
        qbox.show();
    }

    QTextStream in(&file);
    int index = 0;
    //reads line by line then note by note to see if they belong in the selected mode
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList notes= line.split(",");
        for(int i = 0; i < notes.size(); i ++){
            if (notes[i] == key) {
                addNoteToScale(index, i, true, key);
            }
            else if(standardScale.contains(notes[i])){
                addNoteToScale(index, i, false, notes[i]);
            }
        }
        index++;

    }

}

void ShowFretBoard::getInfo(QString key, QString mode){
    DbManager dbmanager;
    int pos = scales.indexOf(key);
    standardScale = dbmanager.returnScales(pos + 1);
    QVector<int> scalePos;
    for (auto &it: standardScale) {
        for(int i = 0; i < scales.length(); i++){
            if(it == scales[i]) {
                scalePos.push_back(i);
            }
        }

    }
    //changes the scale so that it fits to the scale described by the user

    if(mode == "Aeolian"){
        if (scalePos[2] == 0){
            standardScale[2] = scales[11];
        } else {
            standardScale[2] = scales[scalePos[2] - 1];
        }
        if (scalePos[5] == 0){
            standardScale[5] = scales[11];
        } else {
            standardScale[5] = scales[scalePos[5] - 1];
        }
        if (scalePos[6] == 0){
            standardScale[6] = scales[11];
        } else {
            standardScale[6] = scales[scalePos[6] - 1];
        }
    }
    else if (mode == "Altered") {
        for (int i = 0; i < 6; i++){
            if (scalePos[i] == 0){
                standardScale[i] = scales[11];
            } else {
                standardScale[i] = scales[scalePos[i] - 1];
            }
        }
    }

    getGuitarBoard(key);
}

ShowFretBoard::~ShowFretBoard()
{
    delete ui;
}
