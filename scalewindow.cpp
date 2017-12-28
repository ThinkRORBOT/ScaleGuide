#include "scalewindow.h"
#include "ui_scalewindow.h"
#include "mainwindow.h"
#include "dbmanager.h"
#include "showscale.h"
#include <QTCore>
#include <QTGui>
#include <QWidget>
#include <QMessageBox>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <QString>
#include <QVector>
#include <QMessageBox>
#include <QRegularExpression>
#include <algorithm>

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

    ui->centralwidget->setLayout(ui->gridLayout);

    QObject::connect(ui->okButtonK, SIGNAL(clicked(bool)), SLOT(buttonPressed()));
    QObject::connect(ui->closeButton, SIGNAL(clicked(bool)), SLOT(buttonPressed()));
    QObject::connect(ui->okButtonM, SIGNAL(clicked(bool)), SLOT(buttonPressed()));

    QStringList list=(QStringList()<<"C"<<"D"<<"E"<<"F"<<"G"<<"A"<< "B" << "C#/Db"<<"D#/Eb"<<"F#/Gb"<<"G#/Ab"<<"A#/Bb");
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

//gets the data from the database and appends scales to a vector
QVector<QString> ScaleWindow::returnKey(QVector<QString> &note_arr){
    DbManager dbmanager;
    QVector<QString> scales = {};
    //converts integer returned from calculations to scale
    QString noteReference[12] = {"C Major", "D Major", "E Major", "F Major", "G Major", "A Major", "B Major", "C# Major", "D# Major", "F# Major", "G# Major", "A# Major"};
    QString noteReferenceM[12] = {"A Minor", "B Minor", "C# Minor", "D Minor", "E Minor", "F# Minor", "G# Minor", "A# Minor", "C Minor", "D# Minor", "F Minor", "G Minor"};

    //goes through each possible scale
    for (int m = 1; m < 12; m++) {

        QVector<QString> scalesReturn = {};
        scalesReturn = dbmanager.returnScales(m);
        //sorts the vectors and check that cone vector contails the other
        sort(note_arr.begin(), note_arr.end());
        sort(scalesReturn.begin(), scalesReturn.end());

        if(includes(scalesReturn.begin(), scalesReturn.end(), note_arr.begin(), note_arr.end())) {
            qDebug("Success");
            scales.push_back(noteReference[m - 1] + "/" + noteReferenceM[m - 1]);
        }

        if (scalesReturn[0] == "NDB") {
            QMessageBox::critical(this, "Error", "Unable to open database, please install application");
            break;
        }
    }
    return scales;

}

//opens window showscale
void ScaleWindow::openNoteWindowOption(QVector<QString> &finalresult){
    showScale = new ShowScale();
    showScale->show();
    //populated the listview
    showScale->populateList(finalresult, initial_char);
}


//get the writing inside of the text box and returns it as a qvector
QVector<QString> ScaleWindow::getTextBox(int textbox) {
    //convets qt string to c++ string
    QString note_input;
    if (textbox == 0) {
        note_input = ui->inputLine->text();
    }
    else if (textbox == 1) {
        note_input = ui->modeTextInput->text();
    }
    string input = note_input.toLocal8Bit().constData();
    istringstream iss(input);

    QVector<QString> notesEntered;

    //converts string to a vector separated by a space
    vector <string> notes{istream_iterator<string>{iss}, istream_iterator<string>{}};
    //makes sure the user has entered more than 3 notes
    if(notes.size() > 7){
        QMessageBox msgBox;
        msgBox.setText("There needs to be less than 8 notes entered");
        QVector<QString> error = {" "};
        msgBox.exec();
        return error;
    }
    if (notes.size() < 3 && textbox == 0) {
        QMessageBox msgBox;
        msgBox.setText("There needs to be more than two notes entered");
        QVector<QString> error = {" "};
        msgBox.exec();
        return error;
    }
    else if(notes.size() < 4 && textbox == 1) {
        QMessageBox msgBox;
        msgBox.setText("There needs to be more than 3 notes entered");
        QVector<QString> error = {" "};
        msgBox.exec();
        return error;
    }

    //makes sure the notes entered are valid in terms of syntax
    QRegularExpression valid_notes("^[ABCDEFG][#b]?$");

    //string notes_arr[notes.size()] = {};

    i = 0;
    bool valid = true;
    //iterates through vector making sure the notes are valid
    for(vector<string>::iterator it = notes.begin(); it != notes.end(); ++it)
    {

        string temp = *it;

        if (*it == "Cb") {*it = "B";}
        if (*it == "Db") {*it = "C#";}
        if (*it == "Eb") {*it = "D#";}
        if (*it == "E#") {*it = "F";}
        if (*it == "Fb") {*it = "E";}
        if (*it == "Gb") {*it = "F#";}
        if (*it == "Ab") {*it = "G#";}
        if (*it == "Bb") {*it = "A#";}
        if (*it == "B#") {*it = "C";}

        notesEntered.push_back(QString::fromStdString(*it));

        QString tempQ = QString::fromStdString(temp);
        if(valid_notes.match(tempQ).hasMatch()) {
            qDebug("Valid");

            //notes_arr[i] = temp;

        } else {
            QMessageBox::about(this, tr("Error"), tr("Notes entered are not valid"));
            valid = false;
            break;
        }

        i++;
    }
    if (valid){
        return notesEntered;
    } else {
        QVector<QString> error = {" "};
        return error;
    }

}

//converts notes entered into a key
void ScaleWindow::figureKey(){

    //want to convert from vector to qvector to make things easier later on
    QVector <QString> qnotes;

    qnotes = getTextBox(0);
    initial_char = " ";
    initial_char = qnotes[0];

    QVector<QString> outputString{};

    //variable to check whether the input text if valid
    bool valid = false;

    if (qnotes.size() > 1) {
        valid = true;
    }

    if (valid) {
        outputString = returnKey(qnotes);

        //calls the function to open another window
        openNoteWindowOption(outputString);

    }



}

//by tying in a bunch of notes, find out which mode the set of notes is in
void ScaleWindow::figureMode(){
    DbManager dbmanager;

    int key = ui->keyComboBox->currentIndex();
    QString curr_key = ui->keyComboBox->currentText();
    QVector<QString> modeScaleReturn = dbmanager.returnScales(key + 1);
    QVector<QString> textBoxScale = getTextBox(1);
    QVector<QString> scale = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    QVector<QString> mode;
    QVector<int> scalePos;

    //iterates through vector and populates int vector with position within scale
    for (auto &it: modeScaleReturn) {
        bool found = false;
        for(int i = 0; i < scale.length(); i++){
            if(it == scale[i]) {
                scalePos.push_back(i);
                found = true;
            }
        }
        if (!found) {
            QMessageBox msgBox;
            msgBox.setText(it + " is not valid");
            msgBox.exec();
            return;
            break;
        }

    }

    bool modeDiscovered = false;
    //checks the scale for each of the modes
    //find a way later on to find all suitable modes
    for (int i = 0; i < 7; i++){
        QVector<QString> tempScale = modeScaleReturn;
        if (i == 0){
            //checks if two vectors are equal
            sort(modeScaleReturn.begin(), modeScaleReturn.end());
            sort(textBoxScale.begin(), textBoxScale.end());

            if(modeScaleReturn == textBoxScale || includes(modeScaleReturn.begin(), modeScaleReturn.end(), textBoxScale.begin(), textBoxScale.end()))
                {
                mode.push_back(curr_key + " Ionian");
                modeDiscovered = true;
            }
        }
        if (i == 1){

            //makes sure the notes are changed to the right notes
            //convert to use modulo in future cases/if you have time
            modeScaleReturn[2] = scale[(scalePos[2] + 11) % 12];
            modeScaleReturn[6] = scale[(scalePos[6] + 11) % 12];

            sort(modeScaleReturn.begin(), modeScaleReturn.end());
            sort(textBoxScale.begin(), textBoxScale.end());

            if(modeScaleReturn == textBoxScale || includes(modeScaleReturn.begin(), modeScaleReturn.end(), textBoxScale.begin(), textBoxScale.end())){
                mode.push_back(curr_key + " Dorian");
                modeDiscovered = true;
            }
        }

        if (i == 2){

            //makes sure the notes are changed to the right notes
            modeScaleReturn[1] = scale[(scalePos[1] + 11) % 12];
            modeScaleReturn[2] = scale[(scalePos[2] + 11) % 12];
            modeScaleReturn[5] = scale[(scalePos[5] + 11) % 12];
            modeScaleReturn[6] = scale[(scalePos[6] + 11) % 12];


            sort(modeScaleReturn.begin(), modeScaleReturn.end());
            sort(textBoxScale.begin(), textBoxScale.end());

            if(modeScaleReturn == textBoxScale || includes(modeScaleReturn.begin(), modeScaleReturn.end(), textBoxScale.begin(), textBoxScale.end())){
                mode.push_back(curr_key + " Phrygian");
                modeDiscovered = true;

            }
        }

        if (i == 3){


            modeScaleReturn[3] = scale[(scalePos[3] + 1) % 12];
            qDebug() << modeScaleReturn;

            sort(modeScaleReturn.begin(), modeScaleReturn.end());
            sort(textBoxScale.begin(), textBoxScale.end());

            if(modeScaleReturn == textBoxScale || includes(modeScaleReturn.begin(), modeScaleReturn.end(), textBoxScale.begin(), textBoxScale.end())){
                mode.push_back(curr_key + "  Lydian");
                modeDiscovered = true;
            }
        }

        if (i == 4){

            //makes sure the notes are changed to the right notes

            modeScaleReturn[6] = scale[(scalePos[6] + 11) % 12];

            sort(modeScaleReturn.begin(), modeScaleReturn.end());
            sort(textBoxScale.begin(), textBoxScale.end());

            if(modeScaleReturn == textBoxScale || includes(modeScaleReturn.begin(), modeScaleReturn.end(), textBoxScale.begin(), textBoxScale.end())){
                mode.push_back(curr_key + " Mixolydian");
                modeDiscovered = true;
            }
        }

        if (i == 5){

            //makes sure the notes are changed to the right notes
            modeScaleReturn[1] = scale[(scalePos[1] + 11) % 12];
            modeScaleReturn[5] = scale[(scalePos[5] + 11) % 12];
            modeScaleReturn[6] = scale[(scalePos[6] + 11) % 12];


            sort(modeScaleReturn.begin(), modeScaleReturn.end());
            sort(textBoxScale.begin(), textBoxScale.end());

            if(modeScaleReturn == textBoxScale || includes(modeScaleReturn.begin(), modeScaleReturn.end(), textBoxScale.begin(), textBoxScale.end())){
                mode.push_back(curr_key + " Aeolian");
                modeDiscovered = true;
            }
        }
        if (i == 6){
            modeScaleReturn[1] = scale[(scalePos[1] + 11) % 12];
            modeScaleReturn[5] = scale[(scalePos[5] + 11) % 12];
            modeScaleReturn[6] = scale[(scalePos[6] + 11) % 12];
            modeScaleReturn[2] = scale[(scalePos[2] + 11) % 12];
            modeScaleReturn[4] = scale[(scalePos[4] + 11) % 12];


            sort(modeScaleReturn.begin(), modeScaleReturn.end());
            sort(textBoxScale.begin(), textBoxScale.end());

            if(modeScaleReturn == textBoxScale || includes(modeScaleReturn.begin(), modeScaleReturn.end(), textBoxScale.begin(), textBoxScale.end())){
                mode.push_back(curr_key + " Aeolian");
                modeDiscovered = true;
            }
        }
        modeScaleReturn = tempScale;
        if(!modeDiscovered && i == 6){
            QMessageBox msgBox;
            msgBox.setText("No Suitable mode found");
            msgBox.exec();
            return;
        }
        else if (i == 6){
            qDebug("here");
            openNoteWindowOption(mode);
        }
    }
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
