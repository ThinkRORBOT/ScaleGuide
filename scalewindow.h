#ifndef SCALEWINDOW_H
#define SCALEWINDOW_H

#include <QMainWindow>
#include <QLabel>
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
    void figureScale();

    QMenu *helpMenu;
    QAction *aboutAction;
    QAction *helpAction;

    MainWindow* mainWindow;

};

#endif // SCALEWINDOW_H
