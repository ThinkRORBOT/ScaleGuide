#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "notewindow.h"
#include "scalewindow.h"
#include "chordwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:
    void handleButton();
    void openAbout();


private:
    Ui::MainWindow *ui;

    void createMenu();
    void createActions();
    void setButtons();

    QMenu *helpMenu;
    QAction *aboutAction;

    NoteWindow *newNoteWindow;
    ScaleWindow *newScaleWindow;
    ChordWindow *newChordWindow;

};

#endif // MAINWINDOW_H
