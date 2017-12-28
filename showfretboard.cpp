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

    createActions();

    viewMenu = menuBar()->addMenu(tr("&View"));
    fretBoardMenu = viewMenu->addMenu(tr("FretBoardSelect"));
    fretBoardMenu->addAction(fretB1);
    fretBoardMenu->addAction(fretB2);
    fretBoardMenu->addAction(fretB3);


    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);

    setupFretBoard("1");

}

void ShowFretBoard::cancel(){
    this->close();
}

void ShowFretBoard::createActions() {
    //sets up the actions for the menus
    aboutAct = new QAction(tr("&Help"), this);
    aboutAct->setShortcut(QKeySequence::HelpContents);
    aboutAct->setStatusTip("Help using this part of the program");

    //adds the actions and calls the appropriate functions
    fretB1 = new QAction(tr("&Style 1"), this);
    fretB1->isCheckable();
    connect(fretB1, &QAction::triggered, this, &ShowFretBoard::sFB1);
    fretB2 = new QAction(tr("&Style 2"), this);
    fretB2->isCheckable();
    connect(fretB2, &QAction::triggered, this, &ShowFretBoard::sFB2);
    fretB3 = new QAction(tr("&Style 3"), this);
    fretB3->isCheckable();
    connect(fretB3, &QAction::triggered, this, &ShowFretBoard::sFB3);

}

void ShowFretBoard::sFB1() {
    setupFretBoard("1");
    fretB1->setChecked(true);
    fretB2->setChecked(false);
    fretB3->setChecked(false);
}

void ShowFretBoard::sFB2() {
    setupFretBoard("2");
    fretB1->setChecked(false);
    fretB2->setChecked(true);
    fretB3->setChecked(false);

}

void ShowFretBoard::sFB3() {
    setupFretBoard("3");
    fretB1->setChecked(false);
    fretB2->setChecked(false);
    fretB3->setChecked(true);

}

void ShowFretBoard::setupFretBoard(QString fretNum){
    //get properties of the user screen and set geometry of label accordingly

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    ui->fretboardLabel->setMaximumWidth(screenGeometry.width());
    ui->fretboardLabel->setMaximumHeight(screenGeometry.width()/5);
    ui->centralwidget->setLayout(ui->verticalLayout);

    QPixmap fretboard(":/resources/Resources/fretboard" + fretNum + ".png");
    ui->fretboardLabel->setScaledContents(true);
    ui->fretboardLabel->setPixmap(fretboard);
    QObject::connect(ui->okButton, SIGNAL(clicked(bool)), SLOT(cancel()));

    getGuitarBoard(currKey);
}

void ShowFretBoard::addNoteToScale(int string, int pos, bool root, QString note){
    QSize size = ui->fretboardLabel->size();
    pos++;

    int offsetWidth = 0;
    int offsetHeight = 0;
    float boardHeight = size.rheight();
    boardHeight = boardHeight/1.17;
    float boardWidth = size.rwidth() + 10;
    offsetWidth -= boardWidth/25-10;

    offsetHeight =+ boardHeight/3;

    //creates a new label and sets where the label should be placed.
    QLabel *noteLabel = new QLabel(this);
    noteLabel->setGeometry(boardWidth/24.8 * pos + offsetWidth, boardHeight/6 * string + offsetHeight, size.rwidth()/53, size.rwidth()/53);

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
    currKey = key;
    QFile file(":/guitarboard.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox qbox;
        qbox.about(this, "Error", "Cannot open guitarboard.txt. Please redownload application");
        qbox.show();
    }

    QTextStream in(&file);
    int index = 0;
    //reads line by line then note by note to see if they belong in the selected mode
    qDebug()<< standardScale;
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
    int pos = scalesR.indexOf(key);
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
        standardScale[2] = scales[(scalePos[2] + 11) % 12];

        standardScale[5] = scales[(scalePos[5] + 11) % 12];
        standardScale[6] = scales[(scalePos[6] + 11) % 12];

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
    else if (mode == "Arabian") {
        standardScale[1] = scales[(scalePos[1] + 11) % 12];
        standardScale[5] = scales[(scalePos[5] + 11) % 12];
    }
    else if (mode == "Augmented") {
        standardScale[1] = scales[(scalePos[1] + 1) % 12];
        standardScale[4] = "" ;
        standardScale[5] = scales[(scalePos[5] + 11) % 12];
    }
    else if (mode == "Augmented Heptatonic") {
        standardScale[1] = scales[(scalePos[1] + 1) % 12];
        standardScale[5] = scales[(scalePos[5] + 11) % 12];
    }
    else if (mode == "Balinese") {
        standardScale[1] = scales[(scalePos[1] + 11) % 12];
        standardScale[2] = scales[(scalePos[2] + 11) % 12];
        standardScale[5] = scales[(scalePos[5] + 11) % 12];
    }
    else if (mode == "Bebop" || "Bebob Major") {
        standardScale.append(scales[scalePos[0] + 8]);
    }
    else if (mode == "Bebop Dominant") {
        standardScale.append(scales[scalePos[0] + 10]);
    }
    else if (mode == "Bebop Locrian") {
        standardScale[1] = scales[(scalePos[1] + 11) % 12];
        standardScale[2] = scales[(scalePos[2] + 11) % 12];
        standardScale[5] = scales[(scalePos[5] + 11) % 12];
        standardScale[6] = scales[(scalePos[6] + 11) % 12];
        standardScale.append(scales[scalePos[0] + 5]);
    }
    else if (mode == "Bebop Minor") {

        standardScale[6] = scales[(scalePos[6] + 11) % 12];
        standardScale.append(scales[scalePos[0] + 3]);
    }
    getGuitarBoard(key);
}

ShowFretBoard::~ShowFretBoard()
{
    delete ui;
}
