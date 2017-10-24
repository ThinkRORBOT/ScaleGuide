#include "scalewindow.h"
#include "ui_scalewindow.h"
#include "mainwindow.h"
#include "dbmanager.h"
#include <QTCore>
#include <QTGui>
#include <QWidget>
#include <QMessageBox>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <QString>
#include <QMessageBox>
#include <QRegularExpression>

//remove later on, bad practise
using namespace std;

ScaleWindow::ScaleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScaleWindow)
{

    ui->setupUi(this);
    //sets up the rest of the ui
    createActions();
    createMenu();
    setWindowTitle(tr("ScaleGuide: Scale Window"));

    ui->instructLabel->setText("Enter notes in order played (each note separated by a space): ");

    QObject::connect(ui->okButtonK, SIGNAL(clicked(bool)), SLOT(buttonPressed()));
    QObject::connect(ui->closeButton, SIGNAL(clicked(bool)), SLOT(buttonPressed()));
    QObject::connect(ui->okButtonM, SIGNAL(clicked(bool)), SLOT(buttonPressed()));

    QStringList list=(QStringList()<<"C"<<"C#/Db"<<"D"<<"D#/Eb"<<"E"<<"F"<<"F#/Gb"<<"G"<<"G#/Ab"<<"A"<<"A#/Bb" << "B");
    ui->keyComboBox->addItems(list);

}

void ScaleWindow::openAbout() {
    QMessageBox::about(this, tr("About Menu"), tr("Scale Guide helps you to find the right notes for the right scales. 2017"));
}

void ScaleWindow::openHelp() {
    QMessageBox::about(this ,tr("Error"), tr("Help Menu \n Enter the notes in the scale to find out what scale they belong to. \n Try to enter the notes in order. \n Use characters \'A, B, C, D, E, F, G\' for notes and \'#, b\' for symbols \n"));

}


void ScaleWindow::buttonPressed(){
    //handles different windows oppening from buttons pressed
    QPushButton *button = (QPushButton*) sender();
    if (button->objectName() == "okButtonK") {
        figureKey();
    } else if (button->objectName() == "closeButton") {
        mainWindow = new MainWindow;
        mainWindow->show();
        this->close();
    } else if (button->objectName() == "okButtonM") {
        figureMode();
    }
}

void ScaleWindow::returnKey(string *note_arr){
    DbManager = new DbManager();

}

//converts notes entered into a key
void ScaleWindow::figureKey(){
    //convets qt string to c++ string
    QString note_input = ui->inputLine->text();
    string input = note_input.toLocal8Bit().constData();
    istringstream iss(input);
    //converts string to a vector
    vector <string> notes{istream_iterator<string>{iss}, istream_iterator<string>{}};

    //makes sure the notes entered are valid in terms of syntax
    QRegularExpression valid_notes("^[ABCDEFG]#?$");

    string notes_arr[notes.size()] = {};
    initial_char = " ";

    i = 0;
    bool valid = true;
    //iterates through vector making sure the notes are valid
    for(vector<string>::iterator it = notes.begin(); it != notes.end(); ++it)
    {
        string temp = *it;
        QString tempQ = QString::fromStdString(temp);
        if(valid_notes.match(tempQ).hasMatch()) {
            qDebug("Valid");
            if (i == 0) {
                initial_char = temp;
            }

            notes_arr[i] = temp;

        } else {
            QMessageBox::about(this, tr("Error"), tr("Notes entered are not valid"));
            valid = false;
            break;
        }

        i++;
    }

    if (valid) {
        returnKey(note_arr);
    }

    if (notes.size() < 3) {
        QMessageBox msgBox;
        msgBox.setText("There needs to be more than two notes entered");
        msgBox.exec();
    }

}

void ScaleWindow::figureMode(){

}

//sets up what the actions in the menu do
void ScaleWindow::createActions() {
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About this program"));
    connect(aboutAction, &QAction::triggered, this, &ScaleWindow::openAbout);

    helpAction = new QAction(tr("&Help"), this);
    helpAction->setStatusTip(tr("Help with this mode"));
    connect(helpAction, &QAction::triggered, this, &ScaleWindow::openHelp);

}

void ScaleWindow::createMenu() {
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(helpAction);
}

ScaleWindow::~ScaleWindow()
{
    delete ui;
}
