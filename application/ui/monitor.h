#ifndef MONITOR_H
#define MONITOR_H

#include "../chat/chatio.h"
#include "../chat/message.h"
#include "../content/post.h"
#include "../content/postio.h"
#include "../database/database.h"
#include "../database/monitordb.h"
#include "../monitor/monitoritem.h"
#include "../monitor/reportaggregator.h"
#include "../profile/profile.h"
#include "../profile/profileio.h"
#include "../user/accountio.h"
#include "accountsettings.h"
#include "chatmessageitem.h"
#include "monitoraccountitem.h"
#include "monitorlistitem.h"
#include "profilepage.h"
#include <QWidget>

namespace Ui {
class Monitor;
}

class Monitor : public QWidget {
    Q_OBJECT

signals:
    /**
     * @brief select_all emits when the user clicks the select all button
     * @param enable bool value whether to select or deselect
     */
    void select_all(int enable);

public:
    explicit Monitor(user::Account* user, db::Database* db,
                     QWidget* parent = nullptr);
    ~Monitor();

private slots:
    void on_selectAllButton_clicked(bool checked);
    void open_profile_view(int id);
    void open_post_view(int id);
    void open_message_view(int id);
    void open_account_modify(user::Account* a);

    void on_submitButton_clicked();

    void on_selectDataType_currentIndexChanged(int index);

    void on_excuseButton_clicked();

    void on_removeButton_clicked();

    void on_banButton_clicked();

    void on_selectScope_currentIndexChanged(int index);

    void on_closeViewButton_clicked();

    void on_exitAccountView_clicked();

private:
    Ui::Monitor* ui;
    monitor::ReportAggregator* aggregator;
    std::vector<monitor::MonitorItem*> items;
    user::Account* user;
    user::AccountIO* aio;
    chat::ChatIO* cio;
    content::PostIO* psio;
    profile::ProfileIO* prio;

    template <char T>
    void list_monitor_items(std::vector<monitor::MonitorItem*>);

    void list_accounts();
};

#endif // MONITOR_H
