#include "scalewindow.h"
#include "ui_scalewindow.h"
#include <QTCore>
#include <QTGui>
#include <QWidget>
#include <QMessageBox>

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

}

void ScaleWindow::openAbout() {
    QMessageBox::about(this, tr("About Menu"), tr("Scale Guide helps you to find the right notes for the right scales. 2017"));
}

void ScaleWindow::openHelp() {

}

void ScaleWindow::backButtonPressed(){

}

void ScaleWindow::findKeyButtonPressed(){

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
