#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QMainWindow>
#include "showfretboard.h"
class MainWindow;

namespace Ui {
class NoteWindow;
}

class NoteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NoteWindow(QWidget *parent = 0);
    ~NoteWindow();

private slots:
    void buttonPressed();

    void openAbout();
    void openHelp();

    void on_addButton_clicked();

private:
    Ui::NoteWindow *ui;
    QMenu *helpMenu;
    QAction *aboutAction;
    QAction *helpAction;
    MainWindow *mainWindow;
    ShowFretBoard *showFretBoard;

    void createMenu();
    void createActions();
};

#endif // NOTEWINDOW_H
