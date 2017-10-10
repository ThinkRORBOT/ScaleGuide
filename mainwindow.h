#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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

    void on_scaleButton_pressed();
    void on_noteButton_clicked();

private:
    Ui::MainWindow *ui;

    void createMenu();
    void createActions();
    void setButtons();

    QMenu *helpMenu;
    QAction *aboutAction;

};

#endif // MAINWINDOW_H
