#include "createpost.h"
#include "ui_createpost.h"

CreatePost::CreatePost(user::Account *user, content::PostIO *pio,
                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreatePost), user(user), pio(pio) {
    ui->setupUi(this);
    ui->selectAddon->hide();
    ui->addonLabel->hide();
    ui->selectShoal->clear();
    for (content::Shoal* s : pio->pull_user_shoals(user)) {
        ui->selectShoal->addItem(QString::fromStdString(s->get_tag()));
    }
}

CreatePost::~CreatePost()
{
    delete ui;
}

void CreatePost::on_selectAddon_currentTextChanged(const QString &arg1)
{
    // remove current addon
    QLayoutItem *child;
    while ((child = ui->scrollContentsLayout->takeAt(1)) != 0) {
        child->widget()->hide();
        delete child;
    }

    // add new addon
    if (arg1 == "Survey") ui->scrollContentsLayout->addWidget(new CreateSurvey());
//    if (arg1 == "Event") ui->scrollContentsLayout->addWidget(new CreateEvent());
//    if (arg1 == "Image") ui->scrollContentsLayout->addWidget(new CreateImage());
//    if (arg1 == "Trade") ui->scrollContentsLayout->addWidget(new CreateTrade());
}

void CreatePost::on_cancelButton_clicked()
{
    emit close();
}


void CreatePost::on_confirmButton_clicked()
{
    // construct post object
    content::Post* p = new content::Post();
    content::Shoal s;
    s.set_tag(ui->selectShoal->currentText().toStdString());
    p->set_shoal(s);
    p->set_message(ui->bodyField->toPlainText().toStdString());
    p->set_image(nullptr);
    p->set_trade(nullptr);
    p->set_survey(nullptr);
    p->set_event(nullptr);
    emit grab_addons(p);
    emit post(p);
}
