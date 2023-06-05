#include "postsurvey.h"
#include "ui_postsurvey.h"

PostSurvey::PostSurvey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PostSurvey)
{
    ui->setupUi(this);
}

PostSurvey::~PostSurvey()
{
    delete ui;
}
