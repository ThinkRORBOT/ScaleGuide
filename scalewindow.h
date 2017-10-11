#ifndef SCALEWINDOW_H
#define SCALEWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
    void findKeyButtonPressed();
    void backButtonPressed();

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

};

#endif // SCALEWINDOW_H
