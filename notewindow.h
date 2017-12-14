#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QMainWindow>

namespace Ui {
class NoteWindow;
}

class NoteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NoteWindow(QWidget *parent = 0);
    ~NoteWindow();

private:
    Ui::NoteWindow *ui;
    QMenu *helpMenu;
    QAction *aboutAction;
    QAction *helpAction;

    void createMenu();
    void createActions();
    void openAbout();
    void openHelp();
};

#endif // NOTEWINDOW_H
