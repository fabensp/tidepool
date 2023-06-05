#ifndef POSTCARD_H
#define POSTCARD_H

#include "../content/post.h"
#include "postsurvey.h"
#include "tidepoolbase.h"
#include <QWidget>

namespace Ui {
class PostCard;
}

class PostCard : public QWidget {
    Q_OBJECT

signals:
    /**
     * @brief report emits when user clicks report button on post
     * @param p post to report
     */
    void report(content::Post *p);

    /**
     * @brief shoal emits when user clicks shoal on post to go to shoal page
     * @param s shoal to visit
     */
    void shoal(content::Shoal s);

    /**
     * @brief profile emits when user clicks a posters name to visit them
     * @param u user account to open profile for
     */
    void profile(user::Account *u);

public:
    explicit PostCard(content::Post *p, QWidget *parent = nullptr);
    ~PostCard();

private slots:
    void on_reportButton_clicked();

    void on_shoal_clicked();

    void on_poster_clicked();

private:
    Ui::PostCard *ui;
    content::Post *post;
};

#endif // POSTCARD_H
