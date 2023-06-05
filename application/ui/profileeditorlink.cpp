#include "profileeditorlink.h"
#include "ui_profileeditorlink.h"

ProfileEditorLink::ProfileEditorLink(std::string label, std::string link,
                                     QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileEditorLink), label(label), link(link) {
    ui->setupUi(this);

    ui->label->setText(QString::fromStdString(label));
    ui->url->setText(QString::fromStdString(link));
}

ProfileEditorLink::~ProfileEditorLink()
{
    delete ui;
}

void ProfileEditorLink::on_deleteButton_clicked() {
    emit remove_link(this, label, link);
}
