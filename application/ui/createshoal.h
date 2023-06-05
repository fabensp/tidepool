#ifndef CREATESHOAL_H
#define CREATESHOAL_H

#include "../content/postio.h"
#include "../profile/profileio.h"
#include <QWidget>

namespace Ui {
class CreateShoal;
}

class CreateShoal : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief exit emits when user confirms shoal creation
     */
    void exit();

public:
    explicit CreateShoal(user::Account* user, db::Database* db,
                         QWidget* parent = nullptr);
    ~CreateShoal();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateShoal *ui;
    user::Account* user;
    content::PostIO pio;
    profile::ProfileIO prio;
};

#endif // CREATESHOAL_H
