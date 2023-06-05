#include "tidepool.h"
#include "ui_tidepool.h"

Tidepool::Tidepool(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::Tidepool),
    db(new db::Database("../../database.sqlite")), user(),
    cfg(new user::UserConfig((db::UserDB*)db)) {
    ui->setupUi(this);

    check_user_valid();
    this->setPalette(Theme::Current);
}

Tidepool::~Tidepool() { delete ui; }

/**
 * @brief switch_custom_widget for very limited use in switching sub-windows
 * @param l destination layout
 * @param w widget to switch to
 * @param g groupbox holding layout
 * @param t title to give groupbox
 */
void Tidepool::switch_custom_widget(QVBoxLayout* l, QWidget* w, QGroupBox* g,
                                    QString t) {
    // erase target location's current contents
    QLayoutItem* child;
    while ((child = l->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }

    // add new contents
    l->addWidget(w);
    g->setTitle(t);
    g->show();

    // if sidebar titles match, meld them in to one
    if (ui->rightTopCustom->title() == ui->rightBottomCustom->title())
        ui->rightBottomCustom->hide();
    else ui->rightBottomCustom->show();
}

void Tidepool::check_user_valid() {
    // if user has not been logged in
    if (!user.get_verified()) {
        // show login page
        ui->menuBar->setVisible(false);
        Login* lg = new Login(&user, db);
        ui->navList->hide();
        ui->infoPanels->hide();
        open_page(lg, "Welcome!");
        connect(lg, &Login::validated, this, &Tidepool::check_user_valid);
    } else { // if logged in,
        // show landing page with widgets as specified by config
        ui->menuBar->setVisible(true);
        QLayoutItem* child;
        while ((child = ui->MVLayout->takeAt(0)) != 0) {
            child->widget()->hide();
            delete child;
        }

        ui->navList->show();
        ui->infoPanels->show();

        cfg->touch_cfg(user);

        // get settings from cfg
        int th, mc, tc, bc, lc;
        th = cfg->get_entry(user, "theme");
        mc = cfg->get_entry(user, "menu");
        tc = cfg->get_entry(user, "top");
        bc = cfg->get_entry(user, "bottom");
        lc = cfg->get_entry(user, "landing");

        if (th > 7 || th < 0) th = 0; // constrain theme to 0-7
        QPalette palette = *Theme::get(th);
        palette.setColor(QPalette::ButtonText, QColor::fromRgb(0));
        this->setPalette(palette);
        Theme::Current = palette;

        // set menu widget
        switch (mc) {
        case 0: on_actionMenuShoal_triggered(); break;
        case 1: on_actionMenuReef_triggered(); break;
        }

        // set top sidebar widget
        switch (tc) {
        case 0: on_actionTopProfile_triggered(); break;
        case 1: on_actionTopShoals_triggered(); break;
        case 2: on_actionTopReef_triggered(); break;
        case 3: on_actionTopInbox_triggered(); break;
        case 4: on_actionTopInfo_triggered(); break;
        case 5: on_actionTopTank_triggered(); break;
        }

        // set bottom sidebar widget
        switch (bc) {
        case 0: on_actionBottomProfile_triggered(); break;
        case 1: on_actionBottomShoals_triggered(); break;
        case 2: on_actionBottomReef_triggered(); break;
        case 3: on_actionBottomInbox_triggered(); break;
        case 4: on_actionBottomInfo_triggered(); break;
        case 5: on_actionBottomTank_triggered(); break;
        }

        // set main view landing page widget
        switch (lc) {
        case 0: on_profileButton_clicked(); break;
        case 1: on_shoalFlowButton_clicked(); break;
        case 2: on_reefFlowButton_clicked(); break;
        case 3: on_inboxButton_clicked(); break;
        }

        // show username in top left
        ui->loggedInUserLabel->setText(
            QString::fromStdString(user.get_username()));

        // if privileged user, allow making moderation default main window
        if (user.get_access() < 32) {
            ui->modMenu->hide();
            QAction* action = new QAction("Moderation");
            connect(action, &QAction::triggered, this,
                    &Tidepool::moderation_triggered);
            ui->menuMain_View->addAction(action);
        } else ui->modMenu->show();
    }
}

void Tidepool::open_page(QWidget* w, QString t) {
    // switch main view page
    QLayoutItem* child;
    while ((child = ui->MVLayout->takeAt(0)) != 0) {
        child->widget()->hide();
        delete child;
    }
    ui->MVLayout->addWidget(w);
    ui->mainViewBox->setTitle(t);
}

// set menu to shoal list
void Tidepool::on_actionMenuShoal_triggered() {
    ShoalList* w = new ShoalList(&user, db);
    switch_custom_widget(ui->MCLayout, w, ui->menuCustom,
                         "My Shoals");
    connect(w, &ShoalList::open_shoal, this, &Tidepool::open_shoal);
    cfg->set_entry(user, "menu", 0);
}

// set menu to reef list
void Tidepool::on_actionMenuReef_triggered() {
    ReefList* w = new ReefList(&user, db);
    switch_custom_widget(ui->MCLayout, w, ui->menuCustom,
                         "My Reef");
    connect(w, &ReefList::open_profile, this, &Tidepool::open_profile);
    cfg->set_entry(user, "menu", 1);
}

// set top sidebar to profile
void Tidepool::on_actionTopProfile_triggered() {
    profile::ProfileIO pio((db::ProfileDB*)db);
    profile::Profile* p = new profile::Profile();
    pio.pull_profile_id(*p, user.get_id());
    switch_custom_widget(ui->RTCLayout, new ProfileCard(p), ui->rightTopCustom,
                         "My Profile");
    cfg->set_entry(user, "top", 0);
}

// set top sidebar to shoal list
void Tidepool::on_actionTopShoals_triggered() {
    ShoalList* w = new ShoalList(&user, db);
    switch_custom_widget(ui->RTCLayout, w,
                         ui->rightTopCustom, "My Shoals");
    connect(w, &ShoalList::open_shoal, this, &Tidepool::open_shoal);
    cfg->set_entry(user, "top", 1);
}

// set top sidebar to reef list
void Tidepool::on_actionTopReef_triggered() {
    ReefList* w = new ReefList(&user, db);
    switch_custom_widget(ui->RTCLayout, w, ui->rightTopCustom,
                         "My Reef");
    connect(w, &ReefList::open_profile, this, &Tidepool::open_profile);
    cfg->set_entry(user, "top", 2);
}

// set top sidebar to inbox
void Tidepool::on_actionTopInbox_triggered() {
    Inbox* i = new Inbox(&user, db);
    switch_custom_widget(ui->RTCLayout, i, ui->rightTopCustom, "Inbox");
    connect(i, &Inbox::open_page, this, &Tidepool::open_page);
    connect(i, &Inbox::open_chat, this, &Tidepool::open_chat);
    connect(i, &Inbox::create_chat, this, &Tidepool::create_chat);
    connect(i, &Inbox::edit_chat, this, &Tidepool::edit_chat);
    cfg->set_entry(user, "top", 3);
}

// set top sidebar to info
void Tidepool::on_actionTopInfo_triggered() {
    //    switch_custom_widget(
    //                ui->RTCLayout,
    //                new Info(),
    //                ui->rightTopCustom,
    //                "Info");
    cfg->set_entry(user, "top", 4);
}

// set top sidebar to tank
void Tidepool::on_actionTopTank_triggered() {
    //    switch_custom_widget(
    //                ui->RTCLayout,
    //                new Tank(),
    //                ui->rightTopCustom,
    //                "My Tank");
    cfg->set_entry(user, "top", 5);
}

// set bottom sidebar to profile
void Tidepool::on_actionBottomProfile_triggered() {
    profile::ProfileIO pio((db::ProfileDB*)db);
    profile::Profile* p = new profile::Profile();
    pio.pull_profile_id(*p, user.get_id());
    switch_custom_widget(ui->RBCLayout, new ProfileCard(p),
                         ui->rightBottomCustom, "My Profile");
    cfg->set_entry(user, "bottom", 0);
}

// set bottom sidebar to shoal list
void Tidepool::on_actionBottomShoals_triggered() {
    ShoalList* w = new ShoalList(&user, db);
    switch_custom_widget(ui->RBCLayout, w,
                         ui->rightBottomCustom, "My Shoals");
    connect(w, &ShoalList::open_shoal, this, &Tidepool::open_shoal);
    cfg->set_entry(user, "bottom", 1);
}

// set bottom sidebar to reef list
void Tidepool::on_actionBottomReef_triggered() {
    ReefList* w = new ReefList(&user, db);
    switch_custom_widget(ui->RBCLayout, w, ui->rightBottomCustom,
                         "My Reef");
    connect(w, &ReefList::open_profile, this, &Tidepool::open_profile);
    cfg->set_entry(user, "bottom", 2);
}

// set bottom sidebar to inbox
void Tidepool::on_actionBottomInbox_triggered() {
    Inbox* i = new Inbox(&user, db);
    switch_custom_widget(ui->RBCLayout, i, ui->rightBottomCustom, "Inbox");
    connect(i, &Inbox::open_page, this, &Tidepool::open_page);
    connect(i, &Inbox::open_chat, this, &Tidepool::open_chat);
    connect(i, &Inbox::create_chat, this, &Tidepool::create_chat);
    connect(i, &Inbox::edit_chat, this, &Tidepool::edit_chat);
    cfg->set_entry(user, "bottom", 3);
}

// set bottom sidebar to info
void Tidepool::on_actionBottomInfo_triggered() {
    //    switch_custom_widget(
    //                ui->RBCLayout,
    //                new Info(),
    //                ui->rightBottomCustom,
    //                "Info");
    cfg->set_entry(user, "bottom", 4);
}

// set bottom sidebar to tank
void Tidepool::on_actionBottomTank_triggered() {
    //    switch_custom_widget(
    //                ui->RBCLayout,
    //                new Tank(),
    //                ui->rightBottomCustom,
    //                "My Tank");
    cfg->set_entry(user, "bottom", 5);
}

// open current user profile
void Tidepool::on_profileButton_clicked() { open_profile(&user); }

// open current user shoal flow
void Tidepool::on_shoalFlowButton_clicked() {
    open_postfeed(new ShoalFeed(&user, db), "My Shoal Flow");
}

// open current user reef flow
void Tidepool::on_reefFlowButton_clicked() {
    open_postfeed(new ReefFeed(&user, db), "My Reef Flow");
}

// open current user inbox
void Tidepool::on_inboxButton_clicked() {
    Inbox* i = new Inbox(&user, db);
    open_page(i, "Inbox");
    connect(i, &Inbox::open_page, this, &Tidepool::open_page);
    connect(i, &Inbox::open_chat, this, &Tidepool::open_chat);
    connect(i, &Inbox::create_chat, this, &Tidepool::create_chat);
    connect(i, &Inbox::edit_chat, this, &Tidepool::edit_chat);
}

// log out
void Tidepool::on_actionLog_Out_triggered() {
    user.set_username("");
    user.set_email("");
    user.set_access(0);
    check_user_valid();
}

// open mod page
void Tidepool::on_modButton_clicked() {
    open_page(new Monitor(&user, db), "Moderation Tools");
}

// hide top sidebar
void Tidepool::on_actionTopHidden_triggered() {
    ui->rightTopCustom->hide();
    ui->rightTopCustom->setTitle("Hidden");
    cfg->set_entry(user, "top", 6);
}

// hide bottom sidebar
void Tidepool::on_actionBottomHidden_triggered() {
    ui->rightBottomCustom->hide();
    ui->rightBottomCustom->setTitle("Hidden");
    cfg->set_entry(user, "bottom", 6);
}

// set moderation as default landing page
void Tidepool::moderation_triggered() {
    if (user.get_access() >= 32) cfg->set_entry(user, "landing", 4);
}

// open user account settings
void Tidepool::on_actionAccount_Settings_triggered() {
    AccountSettings* lg = new AccountSettings(&user, db);
    open_page(lg, "Account Settings");
    connect(lg, &AccountSettings::validated, this, &Tidepool::check_user_valid);
}

// set application theme to froth
void Tidepool::on_actionFroth_triggered() {
    cfg->set_entry(user, "theme", 0);
    Theme::Current = Theme::Froth;
    this->setPalette(Theme::Current);
}

// set application theme to deep sea
void Tidepool::on_actionDeep_Sea_triggered() {
    cfg->set_entry(user, "theme", 1);
    Theme::Current = Theme::DeepSea;
    this->setPalette(Theme::Current);
}

// set application theme to ocean
void Tidepool::on_actionOcean_triggered() {
    cfg->set_entry(user, "theme", 2);
    Theme::Current = Theme::Ocean;
    this->setPalette(Theme::Current);
}

// set application theme to seaweed
void Tidepool::on_actionSeaweed_triggered() {
    cfg->set_entry(user, "theme", 3);
    Theme::Current = Theme::Seaweed;
    this->setPalette(Theme::Current);
}

// set application theme to beach
void Tidepool::on_actionBeach_triggered() {
    cfg->set_entry(user, "theme", 4);
    Theme::Current = Theme::Beach;
    this->setPalette(Theme::Current);
}

// set application theme to riverbed
void Tidepool::on_actionRiverbed_triggered() {
    cfg->set_entry(user, "theme", 5);
    Theme::Current = Theme::Riverbed;
    this->setPalette(Theme::Current);
}

// set application theme to jelly
void Tidepool::on_actionJelly_triggered() {
    cfg->set_entry(user, "theme", 6);
    Theme::Current = Theme::Jelly;
    this->setPalette(Theme::Current);
}

// set application theme to coral
void Tidepool::on_actionCoral_triggered() {
    cfg->set_entry(user, "theme", 7);
    Theme::Current = Theme::Coral;
    this->setPalette(Theme::Current);
}

// open reef list in main view
void Tidepool::open_reefList(user::Account* u) {
    ReefList* w = new ReefList(u, db);
    open_page(w, QString::fromStdString(u->get_username() + "'s Reef"));
    connect(w, &ReefList::open_profile, this, &Tidepool::open_profile);
}

// open shoal list in main view
void Tidepool::open_shoalList(user::Account* u) {
    ShoalList* w = new ShoalList(u, db);
    open_page(w, QString::fromStdString(u->get_username() + "'s Shoals"));
    connect(w, &ShoalList::open_shoal, this, &Tidepool::open_shoal);
}

// open profile page
void Tidepool::open_profile(user::Account* u) {
    ProfilePage* pp = new ProfilePage(&user, *u, db);
    open_page(pp, QString::fromStdString(u->get_username() + "'s Profile"));
    connect(pp, &ProfilePage::enter_editor, this, &Tidepool::edit_profile);
    connect(pp, &ProfilePage::reef_view, this, &Tidepool::open_reefList);
    connect(pp, &ProfilePage::shoal_view, this, &Tidepool::open_shoalList);
    connect(pp, &ProfilePage::update_reef, this, &Tidepool::update_reeflist);
}

// open shoal home page
void Tidepool::open_shoal(content::Shoal* s) {
    ShoalHome* sh = new ShoalHome(*s, &user, db);
    open_postfeed(sh, QString::fromStdString(s->get_tag()));
    connect(sh, &ShoalHome::update_shoallist, this,
            &Tidepool::update_shoallist);
}

// open post feed
void Tidepool::open_postfeed(PostFeed* pf, QString s) {
    open_page(pf, s);
    connect(pf, &PostFeed::open_shoal, this, &Tidepool::open_shoal);
    connect(pf, &PostFeed::open_profile, this, &Tidepool::open_profile);
    connect(pf, &PostFeed::create_shoal, this, &Tidepool::create_shoal);
}

// open shoal creator
void Tidepool::create_shoal() {
    CreateShoal* cs = new CreateShoal(&user, db);
    open_page(cs, "New Shoal");
    connect(cs, &CreateShoal::exit, this, &Tidepool::update_shoallist);
    connect(cs, &CreateShoal::exit, this,
            &Tidepool::on_shoalFlowButton_clicked);
}

// refresh sidebar profile
void Tidepool::update_profile() {
    if (ui->rightTopCustom->title() == "My Profile")
        on_actionTopProfile_triggered();
    if (ui->rightBottomCustom->title() == "My Profile")
        on_actionBottomProfile_triggered();
}

// refresh sidebar/menu reef list
void Tidepool::update_reeflist() {
    if (ui->rightTopCustom->title() == "My Reef") on_actionTopReef_triggered();
    if (ui->rightBottomCustom->title() == "My Reef")
        on_actionBottomReef_triggered();
    if (ui->menuCustom->title() == "My Reef") on_actionMenuReef_triggered();
}

// refresh sidebar/menu shoal list
void Tidepool::update_shoallist() {
    if (ui->rightTopCustom->title() == "My Shoals")
        on_actionTopShoals_triggered();
    if (ui->rightBottomCustom->title() == "My Shoals")
        on_actionBottomShoals_triggered();
    if (ui->menuCustom->title() == "My Shoals") on_actionMenuShoal_triggered();
}

// open chat creator
void Tidepool::create_chat() {
    CreateChat* cc = new CreateChat(&user, db);
    open_page(cc, "New Chat");
    connect(cc, &CreateChat::exit, this, &Tidepool::on_inboxButton_clicked);
}

// open chat page
void Tidepool::open_chat(chat::Chat* ch) {
    ChatPage* cc = new ChatPage(&user, db, ch);
    open_page(cc, QString::fromStdString(ch->get_title()));
    connect(cc, &ChatPage::exit, this, &Tidepool::on_inboxButton_clicked);
}

// open profile editor
void Tidepool::edit_profile() {
    ProfileEditor* pe = new ProfileEditor(&user, db);
    open_page(pe, "Edit Profile");
    connect(pe, &ProfileEditor::update_profile, this,
            &Tidepool::update_profile);
    connect(pe, &ProfileEditor::exit, this,
            &Tidepool::on_profileButton_clicked);
}

// open chat settings editor
void Tidepool::edit_chat(chat::Chat* ch) {
    ChatSettings* cc = new ChatSettings(&user, db, ch);
    open_page(cc, "Chat Settings");
    connect(cc, &ChatSettings::open_profile, this, &Tidepool::open_profile);
    connect(cc, &ChatSettings::close, this, &Tidepool::on_inboxButton_clicked);
}

void Tidepool::on_actionExit_triggered() { QApplication::quit(); }
