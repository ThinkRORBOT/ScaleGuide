#ifndef CHORDWINDOW_H
#define CHORDWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChordWindow;
}

class ChordWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChordWindow(QWidget *parent = 0);
    ~ChordWindow();

private:
    Ui::ChordWindow *ui;
};

#endif // CHORDWINDOW_H
