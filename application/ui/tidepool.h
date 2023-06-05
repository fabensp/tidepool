#ifndef TIDEPOOL_H
#define TIDEPOOL_H

#include "../database/database.h"
#include "../profile/profile.h"
#include "../user/account.h"
#include "../user/userconfig.h"
#include "accountsettings.h"
#include "chatpage.h"
#include "createshoal.h"
#include "inbox.h"
#include "login.h"
#include "monitor.h"
#include "postfeed.h"
#include "profilecard.h"
#include "profilepage.h"
#include "qboxlayout.h"
#include "qgroupbox.h"
#include "reeffeed.h"
#include "reeflist.h"
#include "shoalfeed.h"
#include "shoalhome.h"
#include "shoallist.h"
#include "tidepoolbase.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Tidepool;
}
QT_END_NAMESPACE

class Tidepool : public QMainWindow {
    Q_OBJECT

public:
    Tidepool(QWidget* parent = nullptr);
    ~Tidepool();

public slots:
    /**
     * @brief open_page opens a widget in the main view box
     * @param w widget to open
     * @param t title to give the box
     */
    void open_page(QWidget* w, QString t);

    /**
     * @brief check_user_valid either opens log in or homepage based on verified
     */
    void check_user_valid();

private slots:
    void on_actionMenuShoal_triggered();
    void on_actionMenuReef_triggered();
    void on_actionTopProfile_triggered();
    void on_actionTopShoals_triggered();
    void on_actionTopReef_triggered();
    void on_actionTopInbox_triggered();
    void on_actionTopInfo_triggered();
    void on_actionTopTank_triggered();
    void on_actionBottomProfile_triggered();
    void on_actionBottomShoals_triggered();
    void on_actionBottomReef_triggered();
    void on_actionBottomInbox_triggered();
    void on_actionBottomInfo_triggered();
    void on_actionBottomTank_triggered();
    void on_profileButton_clicked();
    void on_shoalFlowButton_clicked();
    void on_reefFlowButton_clicked();
    void on_inboxButton_clicked();
    void on_actionLog_Out_triggered();
    void on_modButton_clicked();
    void on_actionTopHidden_triggered();
    void on_actionBottomHidden_triggered();
    void moderation_triggered();
    void on_actionAccount_Settings_triggered();
    void on_actionFroth_triggered();
    void on_actionDeep_Sea_triggered();
    void on_actionOcean_triggered();
    void on_actionSeaweed_triggered();
    void on_actionBeach_triggered();
    void on_actionRiverbed_triggered();
    void on_actionJelly_triggered();
    void on_actionCoral_triggered();

    void open_reefList(user::Account* user);
    void open_shoalList(user::Account* user);
    void open_profile(user::Account* user);
    void open_shoal(content::Shoal* s);
    void open_postfeed(PostFeed* pf, QString s);
    void create_shoal();
    void update_profile();
    void update_reeflist();
    void update_shoallist();
    void create_chat();
    void open_chat(chat::Chat* ch);
    void edit_profile();
    void edit_chat(chat::Chat* ch);

    void on_actionExit_triggered();

private:
    Ui::Tidepool* ui;
    db::Database* db;
    user::Account user;
    user::UserConfig* cfg;

    void switch_custom_widget(QVBoxLayout* l, QWidget* w, QGroupBox* g,
                              QString t);
};
#endif // TIDEPOOL_H
