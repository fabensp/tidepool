#ifndef LOGIN_H
#define LOGIN_H

#include "../database/database.h"
#include "../database/userdb.h"
#include "../profile/profileio.h"
#include "../user/account.h"
#include "../user/accountio.h"
#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(user::Account* a, db::Database* db, QWidget *parent = nullptr);
    ~Login();

signals:
    /**
     * @brief validated emits when the user has logged in or signed up
     */
    void validated();

private slots:
    void on_loginSelect_clicked();

    void on_signupSelect_clicked();

    void on_submitL_clicked();

    void on_submitS_clicked();

    void on_enthusiastButton_clicked();

    void on_organizationButton_clicked();

    void on_underageButton_toggled(bool checked);

private:
    Ui::Login *ui;
    user::Account* a;
    user::AccountIO aio;
    profile::ProfileIO pio;
};

#endif // LOGIN_H
