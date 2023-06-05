#ifndef SHOALLIST_H
#define SHOALLIST_H

#include "../content/postio.h"
#include "shoalhome.h"
#include "indexbutton.h"
#include <QPushButton>
#include <QWidget>

namespace Ui {
class ShoalList;
}

class ShoalList : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief open_shoal emits when user clicks to open a shoal in the list
     * @param s shoal to open
     */
    void open_shoal(content::Shoal* s);

public:
    explicit ShoalList(user::Account* user, db::Database* db,
                       QWidget* parent = nullptr);
    ~ShoalList();

private slots:
    void get_click(int i);

private:
    Ui::ShoalList *ui;
    user::Account* user;
    content::PostIO pio;
    db::Database* db;
    std::vector<content::Shoal*> shoals;
};

#endif // SHOALLIST_H
