#include "monitor.h"
#include "ui_monitor.h"

Monitor::Monitor(user::Account* user, db::Database* db, QWidget* parent) :
    QWidget(parent), ui(new Ui::Monitor),
    aggregator(new monitor::ReportAggregator(user, db)), user(user),
    aio(new user::AccountIO((db::UserDB*)db)),
    cio(new chat::ChatIO((db::ChatDB*)db)),
    psio(new content::PostIO((db::ContentDB*)db)),
    prio(new profile::ProfileIO((db::ProfileDB*)db)) {
    ui->setupUi(this);

    ui->profileBox->hide();
    ui->postBox->hide();
    ui->messageBox->hide();
    ui->accounts->hide();
    ui->reportHeader->hide();
    ui->divider->hide();

    // only admins can search among all site data
    if (user->get_access() >= 64) ui->selectScope->addItem("All");
}

Monitor::~Monitor() {
    delete ui;
    delete aggregator;
    delete aio;
    delete cio;
    delete psio;
    delete prio;
}

void Monitor::on_selectAllButton_clicked(bool checked) {
    emit select_all(checked);
}

void Monitor::open_profile_view(int id) {
    profile::Profile* p = new profile::Profile();
    prio->pull_profile_id(*p, id);
    QLayoutItem* child;
    while ((child = ui->viewLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }
    ui->viewLayout->addWidget(new ProfilePage(user, p));
}

void Monitor::open_post_view(int id) {
    content::Post* p = new content::Post();
    psio->pull_post(*p, id);
    QLayoutItem* child;
    while ((child = ui->viewLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }
    ui->viewLayout->addWidget(new PostCard(p));
}

void Monitor::open_message_view(int id) {
    chat::Message* m = new chat::Message();
    cio->pull_message(*m, id);
    QLayoutItem* child;
    while ((child = ui->viewLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }
    ui->viewLayout->addWidget(new ChatMessageItem(0, m, Theme::Current));
}

void Monitor::on_submitButton_clicked() {

    // hide sections in case they are empty
    ui->profileBox->hide();
    ui->postBox->hide();
    ui->messageBox->hide();
    ui->accounts->hide();
    ui->reportHeader->hide();

    // if searching reported
    if (ui->selectScope->currentIndex() == 0) {
        switch (ui->selectDataType->currentIndex()) {
        case 0: // All
            // list profiles
            list_monitor_items<'r'>(aggregator->fetch_among_profiles(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 1));

            // list posts
            list_monitor_items<'s'>(aggregator->fetch_among_posts(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 1));

            // list messages
            list_monitor_items<'m'>(aggregator->fetch_among_messages(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 1));

            break;
        case 1: // Profiles
            list_monitor_items<'r'>(aggregator->fetch_among_profiles(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 1));
            break;
        case 2: // Posts
            list_monitor_items<'s'>(aggregator->fetch_among_posts(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 1));
            break;
        case 3: // Messages
            list_monitor_items<'m'>(aggregator->fetch_among_messages(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 1));
            break;
        }
    } else { // if searching all
        switch (ui->selectDataType->currentIndex()) {
        case 0: // All
            // list profiles
            list_monitor_items<'r'>(aggregator->fetch_among_profiles(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 0));

            // list posts
            list_monitor_items<'s'>(aggregator->fetch_among_posts(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 0));

            // list messages
            list_monitor_items<'m'>(aggregator->fetch_among_messages(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 0));

            list_accounts();

            break;
        case 1: // Profiles
            list_monitor_items<'r'>(aggregator->fetch_among_profiles(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 0));
            break;
        case 2: // Posts
            list_monitor_items<'s'>(aggregator->fetch_among_posts(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 0));
            break;
        case 3: // Messages
            list_monitor_items<'m'>(aggregator->fetch_among_messages(
                ui->selectSearchType->currentIndex(),
                ui->searchField->text().toStdString(), 0));
            break;
        case 4: // Accounts
            list_accounts();
            break;
        }
    }

    // if there are both accounts and posts/messages/profiles, put a divider
    if (ui->accounts->isVisible() && ui->reportHeader->isVisible())
        ui->divider->show();

    // close any open views
    on_closeViewButton_clicked();
}

void Monitor::list_accounts() {

    // empty ui list
    QLayoutItem* child;
    while ((child = ui->accountsList->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }
    std::vector<user::Account*> avec;
    int idx = ui->selectSearchType->currentIndex();
    if (idx < 3) {
        if (ui->searchField->text().toStdString() == "") {
            return;
        } else avec.push_back(new user::Account());
    }

    // depending on search type, change how to interpret search field
    // only case 3 has the potential to result in more than 1 user
    switch (idx) {
    case 0:
        aio->pull_username(*(avec[0]), ui->searchField->text().toStdString());
        break;
    case 1:
        aio->pull_email(*(avec[0]), ui->searchField->text().toStdString());
        break;
    case 2: aio->pull(*(avec[0]), ui->searchField->text().toInt()); break;
    case 3:
        if (ui->selectDataType->currentIndex() == 4)
            avec = aio->pull_unapproved();
        break;
    default: return;
    }

    // populate ui list
    for (user::Account* a : avec) {
        ui->accounts->show();
        MonitorAccountItem* mai = new MonitorAccountItem(a);
        ui->accountsList->addWidget(mai);
        connect(mai, &MonitorAccountItem::modifyAccount, this,
                &Monitor::open_account_modify);
    }
}

void Monitor::open_account_modify(user::Account* a) {
    // close any open views
    on_closeViewButton_clicked();

    // open account settings page as admin
    AccountSettings* w = new AccountSettings(a, *aio, user);
    ui->viewLayout->addWidget(w);
    connect(w, &AccountSettings::validated, this,
            &Monitor::on_submitButton_clicked);
}

template <char T>
void Monitor::list_monitor_items(std::vector<monitor::MonitorItem*> list) {

    // depending on usage, clear appropriate section of ui
    QLayoutItem* child;
    if (T == 'r') {
        while ((child = ui->profileLayout->takeAt(0)) != 0) {
            child->widget()->hide();
            delete child;
        }
    } else if (T == 's') {
        while ((child = ui->postLayout->takeAt(0)) != 0) {
            child->widget()->hide();
            delete child;
        }
    } else if (T == 'm') {
        while ((child = ui->messageLayout->takeAt(0)) != 0) {
            child->widget()->hide();
            delete child;
        }
    }

    // for each item in list, get it from the database and list in the ui
    for (monitor::MonitorItem* item : list) {
        ui->reportHeader->show();
        MonitorListItem* mli =
            new MonitorListItem(item->get_item_id(), item->get_user_id(),
                                item->get_username(), item->get_report_cnt());
        connect(this, &Monitor::select_all, mli,
                &MonitorListItem::make_selected);
        if (T == 'r') {
            ui->profileBox->show();
            ui->profileLayout->addWidget(mli);
            connect(mli, &MonitorListItem::view_item, this,
                    &Monitor::open_profile_view);
        } else if (T == 's') {
            ui->postBox->show();
            ui->postLayout->addWidget(mli);
            connect(mli, &MonitorListItem::view_item, this,
                    &Monitor::open_post_view);
        } else if (T == 'm') {
            ui->messageBox->show();
            ui->messageLayout->addWidget(mli);
            connect(mli, &MonitorListItem::view_item, this,
                    &Monitor::open_message_view);
        }
    }
}

void Monitor::on_selectDataType_currentIndexChanged(int index) {
    // clear options from search type box
    ui->selectSearchType->clear();

    // show base options
    ui->selectSearchType->addItems(
        {"Username", "Email", "User ID", "Display Name", "Phrase"});

    // add extra options depending on search data type
    switch (index) {
    // Posts
    case 2: ui->selectSearchType->addItems({"Shoal Tag", "MM/DD/YYYY"}); break;
    // Messages
    case 3:
        ui->selectSearchType->addItems({"Chat ID", "Chat Title", "MM/DD/YYY"});
        break;
    case 4:
        ui->selectSearchType->removeItem(4);
        ui->selectSearchType->removeItem(3);
        ui->selectSearchType->addItem("Unapproved");
        break;
    }
}

void Monitor::on_excuseButton_clicked() {
    MonitorListItem* item = nullptr;

    // for each profile in list
    for (int i = 0; i < ui->profileLayout->count(); i++) {
        item = (MonitorListItem*)ui->profileLayout->itemAt(i)->widget();

        // if selected, unreport
        if (item->is_checked()) {
            user::Account a;
            aio->pull(a, item->get_id());
            if (a.get_access() >= user->get_access()) continue;
            aggregator->unreport_profile(a, *user);
        }
    }

    // for each post in list,
    for (int i = 0; i < ui->postLayout->count(); i++) {
        item = (MonitorListItem*)ui->postLayout->itemAt(i)->widget();

        // if selected, unreport
        if (item->is_checked()) {
            content::Post p;
            psio->pull_post(p, item->get_id());
            if (p.get_user()->get_access() >= user->get_access()) continue;
            aggregator->unreport_post(p, *user);
        }
    }

    // for each message in list,
    for (int i = 0; i < ui->messageLayout->count(); i++) {
        item = (MonitorListItem*)ui->messageLayout->itemAt(i)->widget();

        // if selected, unreport
        if (item->is_checked()) {
            chat::Message m;
            cio->pull_message(m, item->get_id());
            if (m.get_sender().get_access() >= user->get_access()) continue;
            aggregator->unreport_message(m, *user);
        }
    }

    // refresh list
    on_submitButton_clicked();
}

void Monitor::on_removeButton_clicked() {
    MonitorListItem* item = nullptr;

    // for each profile in list
    for (int i = 0; i < ui->profileLayout->count(); i++) {
        item = (MonitorListItem*)ui->profileLayout->itemAt(i)->widget();

        // if checked, remove
        if (item->is_checked()) {
            user::Account a;
            aio->pull(a, item->get_id());
            if (a.get_access() >= user->get_access()) continue;
            aio->ban(a.get_id(), *user);
            aggregator->unreport_profile(a, *user);
        }
    }

    // for each post in list
    for (int i = 0; i < ui->postLayout->count(); i++) {
        item = (MonitorListItem*)ui->postLayout->itemAt(i)->widget();

        // if checked, remove
        if (item->is_checked()) {
            content::Post p;
            psio->pull_post(p, item->get_id());
            if (p.get_user()->get_access() >= user->get_access()) continue;
            psio->remove_post(p, *user);
        }
    }

    // for each message in list
    for (int i = 0; i < ui->messageLayout->count(); i++) {
        item = (MonitorListItem*)ui->messageLayout->itemAt(i)->widget();

        // if checked, remove
        if (item->is_checked()) {
            chat::Message m;
            cio->pull_message(m, item->get_id());
            if (m.get_sender().get_access() >= user->get_access()) continue;
            cio->remove_message(m, *user);
        }
    }

    // refresh list
    on_submitButton_clicked();
}

void Monitor::on_banButton_clicked() {
    MonitorListItem* item = nullptr;

    // for each profile in list
    for (int i = 0; i < ui->profileLayout->count(); i++) {
        item = (MonitorListItem*)ui->profileLayout->itemAt(i)->widget();

        // if checked, ban owner
        if (item->is_checked()) {
            user::Account a;
            aio->pull(a, item->get_id());
            if (a.get_access() >= user->get_access()) continue;
            aio->ban(a.get_id(), *user);
        }
    }

    // for each post in list
    for (int i = 0; i < ui->postLayout->count(); i++) {
        item = (MonitorListItem*)ui->postLayout->itemAt(i)->widget();

        // if checked, ben poster
        if (item->is_checked()) {
            content::Post p;
            psio->pull_post(p, item->get_id());
            if (p.get_user()->get_access() >= user->get_access()) continue;
            aio->ban(p.get_user()->get_id(), *user);
        }
    }

    // for each message in list
    for (int i = 0; i < ui->messageLayout->count(); i++) {
        item = (MonitorListItem*)ui->postLayout->itemAt(i)->widget();

        // if checked, ban sender
        if (item->is_checked()) {
            chat::Message m;
            cio->pull_message(m, item->get_id());
            if (m.get_sender().get_access() >= user->get_access()) continue;
            aio->ban(m.get_sender().get_id(), *user);
        }
    }

    // refresh list
    on_submitButton_clicked();
}

void Monitor::on_selectScope_currentIndexChanged(int index) {
    if (index == 1) {
        ui->selectDataType->addItem("Accounts");
    } else {
        ui->selectDataType->removeItem(4);
    }
}

void Monitor::on_closeViewButton_clicked() {
    QLayoutItem* child;
    while ((child = ui->viewLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }
}

void Monitor::on_exitAccountView_clicked() { on_closeViewButton_clicked(); }
