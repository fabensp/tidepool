#ifndef PROFILECARD_H
#define PROFILECARD_H

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
#include "userfeed.h"
#include <QDesktopServices>
#include <QListWidgetItem>
#include <QUrl>
#include <QWidget>

namespace Ui {
class ProfileCard;
}

class ProfileCard : public QWidget {
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

public:
    explicit ProfileCard(profile::Profile* p, QWidget* parent = nullptr);
    ~ProfileCard();

private slots:
    void on_linkList_itemClicked(QListWidgetItem* item);

private:
    Ui::ProfileCard* ui;
    user::Account* user;
    profile::Profile* profile;

    void fill_info();
};

#endif // PROFILECARD_H
