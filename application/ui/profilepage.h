#ifndef UIPROFILE_H
#define UIPROFILE_H

#include "../content/postio.h"
#include "../database/contentdb.h"
#include "../database/profiledb.h"
#include "../monitor/reporter.h"
#include "../profile/profileio.h"
#include "../user/account.h"
#include "palcard.h"
#include "palshowcase.h"
#include "postcard.h"
#include "profileeditor.h"
#include "tidepoolbase.h"
#include "userfeed.h"
#include <QDesktopServices>
#include <QListWidgetItem>
#include <QUrl>
#include <QWidget>

namespace Ui {
class ProfilePage;
}

class ProfilePage : public QWidget {
    Q_OBJECT

    /**
     * @brief The LinkItem class holds a url to open when clicked
     */
    class LinkItem : public QListWidgetItem {

    public:
        LinkItem(QString label, QString url) :
            QListWidgetItem(label), url(url) {}
        void open() { QDesktopServices::openUrl(QUrl(url)); }

    private:
        QString url;
    };

signals:
    /**
     * @brief enter_editor emits when user clicks edit profile button
     */
    void enter_editor();

    /**
     * @brief reef_view emits when user clicks to view a user's reef
     * @param u user to open page for
     */
    void reef_view(user::Account* u);

    /**
     * @brief shoal_view emits when user clicks to see a users shoals
     * @param u user to open page for
     */
    void shoal_view(user::Account* u);

    /**
     * @brief update_reef emits when user adds/removes person from reef
     */
    void update_reef();

public:
    explicit ProfilePage(user::Account* user, user::Account profile_owner,
                         db::Database* db, QWidget* parent = nullptr);
    ProfilePage(user::Account* user, profile::Profile* p,
                QWidget* parent = nullptr);
    ~ProfilePage();

private slots:
    void open_pal(profile::Pal* p);

    void on_contextButton_clicked();

    void on_linkList_itemClicked(QListWidgetItem* item);

    void on_addToReefButton_clicked();

    void on_viewReef_clicked();

    void on_viewShoals_clicked();

private:
    Ui::ProfilePage* ui;
    user::Account* user;
    profile::Profile* profile;
    profile::ProfileIO* prio;
    content::PostIO psio;
    monitor::Reporter r;

    void fill_info();
};

#endif // UIPROFILE_H
