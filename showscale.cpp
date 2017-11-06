#include "showscale.h"
#include "ui_showscale.h"
#include<vector>
#include<string>

ShowScale::ShowScale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowScale)
{
    ui->setupUi(this);

}

void ShowScale::populateList(std::vector<std::string> &notes){

}

ShowScale::~ShowScale()
{
    delete ui;
}
