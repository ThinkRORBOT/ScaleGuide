#include "notewindow.h"
#include "ui_notewindow.h"
#include "mainwindow.h"

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMessageBox>

NoteWindow::NoteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NoteWindow)
{
    ui->setupUi(this);
    setWindowTitle("ScaleGuide: NoteWindow");

    createActions();
    createMenu();

    QObject::connect(ui->cancelButton, SIGNAL(clicked(bool)), SLOT(buttonPressed()));
    QObject::connect(ui->okButton, SIGNAL(clicked(bool)), SLOT(buttonPressed()));

    //adds information to the combo boxes
    QStringList list=(QStringList()<<"C"<<"D"<<"E"<<"F"<<"G"<<"A"<< "B" << "C#/Db"<<"D#/Eb"<<"F#/Gb"<<"G#/Ab"<<"A#/Bb");
    ui->keyComboBox->addItems(list);


    list = (QStringList()<< "Aeolian"<<"Altered"<<"Arabian" << "Augmented"
            << "Augmented Heptatonic" << "Balinese" << "Bebop" << "Bebop Dominant" << "Bebop Locrian" << "Bebop Major" << "Bebop Minor" << "Blues" << "Chinese" << "Chromatic" << "Composite Blues" << "Diminished"
            << "Diminished Whole Tone" << "Dominant" << "Dorian" << "Dorian #4" << "Dorian b2" << "Double Harmonic Lydian" << "Double Harmonic Major" << "Egyption" << "Enigmatic"
            << "Flamenco" << "Flat 6 Pentatonic" << "Flat 3 Pentatonic" << "Gypsy" << "Harmonic Major" << "Harmonic Minor" << "Hindu" << "Hirajoshi" << "Hungarian Major"
            << "Hungarian Minor" << "Ichikosucho" << "Insen" << "Indian" << "Ionian"<< "Ionian Augmented" << "Ionic Pentatonic" << "Iwato" << "Kafi raga" << "Kumoi"
            << "Kumoi Joshi" << "Locrian" << "Locrian #2" << "Locrian Major" << "Locrian Pentatonic" << "Lydian" << "Lydian #5p Pentatonic" << "Lydian #9" << "Lydian Augmented"
            << "Lydian b7" << "Lydian Diminished" << "Lydian Dominant" << "Lydian Minor" << "Lydian Pentatonic" << "Major" <<"Major Blues" << "Major b2 pentatonic"
            << "Malkos Raga" << "Melodic Minor" << "Melodic Minor Fifth Mode" << "Minor" << "Minor #7M Pentatonic" << "Minor Bebop" << "Minor Blues"
            << "Minor Hexatonic" << "Minor Seven Flat Five Pentatonic" << "Minor Six Diminished" << "Minor Six Pentatonic" << "Mixolydian" << "Mixolydian b6M" << "Mixolydian pentatonic" << "Neopolitan"
            << "Neopolitan Major Pentatonic" << "Neopolitan Minor" << "Oriental" << "Pelog" << "Persian" << "Phrygian" << "Phrygian Major" << "Prometheus" << "Prometheus Neoplitan"
            << "Purvi Raga" << "Ritusen" << "Romanian Minor" << "Scriabin" << "Six Tone Symmetric" << "Spanish" << "Spanish Heptatonic" << "Super Locrian" << "Super Locrian Pentatonic" << "Todi Raga" << "Vietnamese" << "Whole Tone"
            << "Whole Tone Pentatonic");
    ui->modeComboBox->addItems(list);
}

void NoteWindow::buttonPressed(){
    //handles the buttons
    QPushButton *button = (QPushButton*) sender();
    if (button->objectName() == "okButton") {
        showFretBoard = new ShowFretBoard();
        showFretBoard->show();
        //get information from combo boxes
        QString keyTemp = ui->keyComboBox->currentText();
        if (keyTemp.length() != 1){
            keyTemp.truncate(2);
        }
        int keyNum = ui->keyComboBox->currentIndex();
        QString modeTemp = ui->modeComboBox->currentText();
        showFretBoard->getInfo(keyTemp, modeTemp);
    } else if (button->objectName() == "cancelButton") {
        mainWindow = new MainWindow;
        mainWindow->show();
        this->close();
    }
}

void NoteWindow::openAbout() {
    QMessageBox::about(this, tr("About Menu"), tr("Scale Guide helps you to find the right notes for the right scales. 2017"));
}

void NoteWindow::openHelp() {
    QMessageBox::about(this ,tr("Error"), tr("Help Menu \n Enter find the key and scale type in the combo boxes below. \n Type quickly once clicked on combo box to search."));

}

void NoteWindow::createActions() {
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About this program"));
    connect(aboutAction, &QAction::triggered, this, &NoteWindow::openAbout);

    helpAction = new QAction(tr("&Help"), this);
    helpAction->setStatusTip(tr("Help with this mode"));
    connect(helpAction, &QAction::triggered, this, &NoteWindow::openHelp);

}

void NoteWindow::createMenu() {
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(helpAction);
}


NoteWindow::~NoteWindow()
{
    delete ui;
}

void NoteWindow::on_addButton_clicked()
{
    int keyNum = ui->keyComboBox->currentIndex();
    QString keyStr = ui->keyComboBox->currentText();
    QString modeStr = ui->modeComboBox->currentText();
    QString numSeconds = ui->secondsInput->text();
    ui->secondsInput->setText("");
}
