#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTCore>
#include <QTGui>
#include <QWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenu();
    setButtons();

    setWindowTitle(tr("Scale Guide Main Menu"));
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(aboutAction);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::setButtons(){

    QObject::connect(ui->scaleButton, SIGNAL(clicked(bool)), SLOT(handleButton()));
    QObject::connect(ui->noteButton, SIGNAL(clicked(bool)), SLOT(handleButton()));

}

void MainWindow::handleButton() {
    QPushButton *button = (QPushButton*) sender();
    if (button->objectName() == "noteButton") {

    } else if (button->objectName() == "scaleButton") {

    }

}

void MainWindow::openAbout() {
    QMessageBox::about(this, tr("About Menu"), tr("Scale Guide helps you to find the right notes for the right scales. 2017"));
}

void MainWindow::createActions() {
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About this program"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::openAbout);
}

void MainWindow::createMenu() {
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);

}

MainWindow::~MainWindow()
{
    delete ui;
}



