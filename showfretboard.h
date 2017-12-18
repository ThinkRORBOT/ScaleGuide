#ifndef SHOWFRETBOARD_H
#define SHOWFRETBOARD_H

#include <QMainWindow>
#include <QString>
#include <QVector>

namespace Ui {
class ShowFretBoard;
}

class ShowFretBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowFretBoard(QWidget *parent = 0);
    void getInfo(QString key, QString mode);
    ~ShowFretBoard();

private slots:
    void cancel();

private:
    Ui::ShowFretBoard *ui;
    const QVector<QString> scales= {"C", "C#", "D", "D#", "E", "F", "G", "G#", "A", "A#", "B", "B#"};
};

#endif // SHOWFRETBOARD_H
