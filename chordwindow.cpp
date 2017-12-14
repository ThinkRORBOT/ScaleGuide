#include "chordwindow.h"
#include "ui_chordwindow.h"

ChordWindow::ChordWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChordWindow)
{
    ui->setupUi(this);
}

ChordWindow::~ChordWindow()
{
    delete ui;
}
