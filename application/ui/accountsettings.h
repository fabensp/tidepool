#ifndef ACCOUNTSETTINGS_H
#define ACCOUNTSETTINGS_H

#include "../database/userdb.h"
#include "../user/account.h"
#include "../user/accountio.h"
#include <QWidget>

namespace Ui {
class AccountSettings;
}

class AccountSettings : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief validated sends signal when user has saved changes
     */
    void validated();

public:
    explicit AccountSettings(user::Account *a, db::Database *db,
                             QWidget *parent = nullptr);
    AccountSettings(user::Account *a, user::AccountIO aio,
                    user::Account *admin = nullptr, QWidget *parent = nullptr);
    ~AccountSettings();

private slots:
    void on_saveButton_clicked();

    void on_selectAccess_currentIndexChanged(int index);

private:
    Ui::AccountSettings *ui;
    user::Account *a;
    user::AccountIO aio;
};

#endif // ACCOUNTSETTINGS_H
