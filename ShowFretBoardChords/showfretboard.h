#ifndef SHOWFRETBOARD_H
#define SHOWFRETBOARD_H

#include <QMainWindow>
#include <QString>
#include <QVector>

class QAction;
class QMenu;

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
    void setupFretBoard(QString fretNum);
    void sFB1();
    void sFB2();
    void sFB3();

private:
    Ui::ShowFretBoard *ui;
    const QVector<QString> scales= {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    const QVector<QString> scalesR= {"C", "D", "E", "F", "G", "A", "B", "C#", "D#", "G#", "A#", "B#"};
    void getGuitarBoard(QString key);
    void addNoteToScale(int string, int pos, bool root, QString note);
    void createActions();
    QVector<QString> standardScale;
    QString currKey;
    QMenu *viewMenu;
    QMenu *fretBoardMenu;
    QMenu *helpMenu;

    QAction *fretB1;
    QAction *fretB2;
    QAction *fretB3;
    QAction *aboutAct;

};

#endif // SHOWFRETBOARD_H
