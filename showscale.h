#ifndef SHOWSCALE_H
#define SHOWSCALE_H
#include<vector>
#include<string>

#include <QMainWindow>

namespace Ui {
class ShowScale;
}

class ShowScale : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowScale(QWidget *parent = 0);
    ~ShowScale();

    void populateList(QVector<QString> &notes);

private slots:
    void cancel();
    void openNoteWindow(QString scale);

private:
    Ui::ShowScale *ui;

};

#endif // SHOWSCALE_H
