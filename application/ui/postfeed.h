#ifndef POSTFEED_H
#define POSTFEED_H

#include "../content/post.h"
#include "../content/postio.h"
#include "../monitor/reporter.h"
#include "createpost.h"
#include "postcard.h"
#include <QWidget>

namespace Ui {
class PostFeed;
}

class PostFeed : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief refresh_list emits when user refreshes post list button
     */
    void refresh_list();

    /**
     * @brief open_profile emits when user clicks a post poster to visit them
     * @param u account to open
     */
    void open_profile(user::Account* u);

    /**
     * @brief open_shoal emits when user clicks a posts shoal to visit
     * @param s shoal to open
     */
    void open_shoal(content::Shoal* s);

    /**
     * @brief create_shoal emits when user clicks create shoal button
     */
    void create_shoal();

    /**
     * @brief update_shoallist emits when user joins/leaves a shoal
     */
    void update_shoallist();

public:
    explicit PostFeed(user::Account* user, db::Database* db, QWidget *parent = nullptr);
    ~PostFeed();

protected slots:
    void on_createPostButton_clicked();
    void close_creator();
    void creator_post(content::Post* p);

    void on_report(content::Post* p);
    void on_shoal(content::Shoal s);
    void on_profile(user::Account* u);

    void on_refresh_clicked();

protected:
    Ui::PostFeed* ui;
    std::vector<content::Post *> posts;
    content::PostIO pio;
    monitor::Reporter r;
    user::Account* user;

    virtual void refresh() {}
private slots:
    void on_loadMoreButton_clicked();
    void on_createShoalButton_clicked();
};

#endif // POSTFEED_H
