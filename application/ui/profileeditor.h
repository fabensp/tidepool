#ifndef PROFILEEDITOR_H
#define PROFILEEDITOR_H

#include "../profile/profileio.h"
#include "../user/account.h"
#include "profileeditorlink.h"
#include "profileeditorpal.h"
#include <QLineEdit>
#include <QWidget>
#include <QFileDialog>

namespace Ui {
class ProfileEditor;
}

class ProfileEditor : public QWidget {
    Q_OBJECT

signals:
    /**
     * @brief update_profile emits when user clicks save, to update sidebar
     */
    void update_profile();

    /**
     * @brief exit emits when user exits page
     */
    void exit();

public:
    explicit ProfileEditor(user::Account *user, db::Database *db,
                           QWidget *parent = nullptr);
    ~ProfileEditor();

private slots:
    void remove_link(QWidget *w, std::string la, std::string li);

    void remove_pal(QWidget *w, profile::Pal *pal);

    void on_saveButton_clicked();

    void on_palAddButton_clicked();

    void on_linkAddButton_clicked();

    void on_pfpSelect_currentIndexChanged(int index);

private:
    Ui::ProfileEditor *ui;
    profile::Profile p;
    user::Account *user;
    profile::ProfileIO *pio;
};

#endif // PROFILEEDITOR_H
