#ifndef MONITORACCOUNTITEM_H
#define MONITORACCOUNTITEM_H

#include "../user/account.h"
#include <QWidget>

namespace Ui {
class MonitorAccountItem;
}

class MonitorAccountItem : public QWidget {
    Q_OBJECT

signals:
    /**
     * @brief modifyAccount emits when the modify button is clicked
     * @param a account to modify
     */
    void modifyAccount(user::Account *a);

public:
    explicit MonitorAccountItem(user::Account *a, QWidget *parent = nullptr);
    ~MonitorAccountItem();

private slots:
    void on_modifyButton_clicked();

private:
    Ui::MonitorAccountItem *ui;
    user::Account *a;
};

#endif // MONITORACCOUNTITEM_H
