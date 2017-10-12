#include "scalewindow.h"
#include "ui_scalewindow.h"
#include "mainwindow.h"
#include <QTCore>
#include <QTGui>
#include <QWidget>
#include <QMessageBox>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <QString>

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

    QObject::connect(ui->okButton, SIGNAL(clicked(bool)), SLOT(buttonPressed()));
    QObject::connect(ui->closeButton, SIGNAL(clicked(bool)), SLOT(buttonPressed()));

}

void ScaleWindow::openAbout() {
    QMessageBox::about(this, tr("About Menu"), tr("Scale Guide helps you to find the right notes for the right scales. 2017"));
}

void ScaleWindow::openHelp() {

}


void ScaleWindow::buttonPressed(){
    QPushButton *button = (QPushButton*) sender();
    if (button->objectName() == "okButton") {
        figureScale();
    } else if (button->objectName() == "closeButton") {
        mainWindow = new MainWindow;
        mainWindow->show();
        this->close();
    }
}

void ScaleWindow::figureScale(){
    QString note_input = ui->inputLine->text();
    string input = note_input.toLocal8Bit().constData();
    istringstream iss(input);
    vector <string> notes{istream_iterator<string>{iss}, istream_iterator<string>{}};



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
