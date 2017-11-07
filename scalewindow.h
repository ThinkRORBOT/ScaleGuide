#ifndef SCALEWINDOW_H
#define SCALEWINDOW_H

#include "showscale.h"

#include <QMainWindow>
#include <QLabel>
#include <string>
#include <vector>
#include <QVector>
#include <QString>
class MainWindow;

namespace Ui {
class ScaleWindow;
}

class ScaleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScaleWindow(QWidget *parent = 0);
    ~ScaleWindow();

private slots:
    void buttonPressed();

    void openAbout();
    void openHelp();

private:
    Ui::ScaleWindow *ui;

    void createMenu();
    void createActions();
    void figureKey();
    void figureMode();
    void openNoteWindowOption(QVector<QString> &finalresult);
    QVector<QString> returnKey(QVector<QString> &note_arr);

    QMenu *helpMenu;
    QAction *aboutAction;
    QAction *helpAction;

    MainWindow* mainWindow;
    ShowScale* showScale;
    std::string initial_char = " ";
    QString noteReference[14] = {};

    int i = 0;

};

#endif // SCALEWINDOW_H
