#include "notewindow.h"
#include "ui_notewindow.h"
#include "mainwindow.h"

#include <QTCore>
#include <QTGui>
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

    QStringList list=(QStringList()<<"C"<<"C#/Db"<<"D"<<"D#/Eb"<<"E"<<"F"<<"F#/Gb"<<"G"<<"G#/Ab"<<"A"<<"A#/Bb" << "B");
    ui->keyComboBox->addItems(list);

    list = (QStringList()<< "Aeolian"<<"Altered"<<"Arabian" << "Augmented"
            << "Augmented Heptatonic" << "Balinese" << "Bepop" << "Bepop Dominant" << "Bepop Locrian" << "Bepop Major" << "Bepop Minor" << "Blues" << "Chinese" << "Chromatic" << "Composite Blues"
            << "Diminished Whole Tone" << "Dominant" << "Dorian" << "Dorian #4" << "Dorian b2" << "Dorian Harmonic Lydian" << "Dorian Harmonic Major" << "Egyption" << "Enigmatic"
            << "Flamenco" << "Flat 6 Pentatonic" << "Flat 3 Pentatonic" << "Gypsy" << "Harmonic Major" << "Harmonic Minor" << "Hindu" << "Hirajoshi" << "Hungarian Major"
            << "Hungarian Minor" << "Ichikosucho" << "Insen" << "Indian" << "Ionian"<< "Ionian Augmented" << "Ionic Pentatonic" << "Iwato" << "Kafi raga" << "Kumoi"
            << "Kumoi Joshi" << "Locrian" << "Locrian #2" << "Locrian Major" << "Locrian Pentatonic" << "Lydian" << "Lydian #5P pentatonic" << "Lydian #9 Pentatonic" << "Lydian Augmented"
            << "Lydian b7" << "Lydian Diminished" << "Lydian Dominant" << "Lydian Dominant Pentatonic" << "Lydian Minor" << "Lydian Pentatonic" << "Major" <<"Major Blues" << "Major b2 pentatonic"
            << "Malkos Raga" << "Melodic Minor" << "Melodic Minor Fifth mode" << "Melodic Minor Second mode" << "Minor" << "Minor #7M Pentatonic" << "Minor Bebop" << "Minor Blues"
            << "Minor Hexatonic" << "Minor Seven Flat Five Pentatonic" << "Minor Six Diminished" << "Minor Six Pentatonic" << "Mixolydian" << "Mixolydian b6M" << "Mixolydian pentatonic" << "Neopolitan"
            << "Neopolitan Major Pentatonic" << "Neopolitan Minor" << "Oriental" << "Pelog" << "Persian" << "Phrygian" << "Phrygian Major" << "Prometheus" << "Prometheus Neoplitan"
            << "Purvi Raga" << "Ritusen" << "Romanian Minor" << "Scriabin" << "Six Tone Symmetric" << "Spanish" << "Spanish Heptatonic" << "Super Locrian" << "Super Locrian Pentatonic" << "Todi Raga" << "Vietnamese" << "Whole Tone"
            << "Whole Tone Pentatonic");
    ui->modeComboBox->addItems(list);
}

void NoteWindow::openAbout() {
    QMessageBox::about(this, tr("About Menu"), tr("Scale Guide helps you to find the right notes for the right scales. 2017"));
}

void NoteWindow::openHelp() {
    QMessageBox::about(this ,tr("Error"), tr("Help Menu \n Enter find the key and scale type in the combo boxes below."));

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
