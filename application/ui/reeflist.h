#ifndef REEFLIST_H
#define REEFLIST_H

#include "../profile/profileio.h"
#include "profilepage.h"
#include "indexbutton.h"
#include <QPushButton>
#include <QWidget>

namespace Ui {
class ReefList;
}

class ReefList : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief open_profile emits when user clicks to open profile in reef list
     * @param u user to open
     */
    void open_profile(user::Account* u);

public:
    explicit ReefList(user::Account* user, db::Database* db,
                       QWidget* parent = nullptr);
    ~ReefList();
private slots:
    void get_click(int i);

private:
    Ui::ReefList *ui;
    user::Account* user;
    profile::ProfileIO pio;
    db::Database* db;
    std::vector<user::Account> reef;
};

#endif // REEFLIST_H
