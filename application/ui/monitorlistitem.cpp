#include "monitorlistitem.h"
#include "ui_monitorlistitem.h"

MonitorListItem::MonitorListItem(int id,
                                 int uid,
                                 std::string username,
                                 int reports,
                                 QWidget *parent) :
                                                    QWidget(parent),
                                                    ui(new Ui::MonitorListItem),
                                                    id(id)
{
    ui->setupUi(this);

    ui->userId->setText(QString::number(uid));
    ui->username->setText(QString::fromStdString(username));
    ui->reportCount->setText(QString::number(reports));

    this->setPalette(Theme::Current);
}

MonitorListItem::~MonitorListItem()
{
    delete ui;
}

void MonitorListItem::make_selected(int enable) {
    ui->selectButton->setChecked(enable);
}

void MonitorListItem::on_viewButton_clicked()
{
    emit view_item(id);
}

int MonitorListItem::is_checked() { return ui->selectButton->isChecked(); }
int MonitorListItem::get_id() { return id; }
