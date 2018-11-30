#ifndef SHOWSCALE_H
#define SHOWSCALE_H
#include<vector>
#include<string>

#include <QMainWindow>
#include "showfretboard.h"

namespace Ui {
class ShowScale;
}

class ShowScale : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowScale(QWidget *parent = 0);
    ~ShowScale();

    void populateList(QVector<QString> &notes, QString rootNote);

private slots:
    void cancel();
    void openNoteWindow();

private:
    Ui::ShowScale *ui;

    ShowFretBoard *showFretBoard;
};

#endif // SHOWSCALE_H
