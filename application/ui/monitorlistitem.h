#ifndef MONITORLISTITEM_H
#define MONITORLISTITEM_H

#include "tidepoolbase.h"
#include <QWidget>

namespace Ui {
class MonitorListItem;
}

class MonitorListItem : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief view_item emits when view button is clicked
     * @param id id of item
     */
    void view_item(int id);

public:
    /**
     * @brief MonitorListItem construct and populate a monitor list item
     * @param type item type
     * @param cid item content id
     * @param uid poster id
     * @param username poster username
     * @param reports report #
     * @param parent
     */
    explicit MonitorListItem(int id,
                             int uid,
                             std::string username,
                             int reports,
                             QWidget *parent = nullptr);
    ~MonitorListItem();

    /**
     * @brief is_checked returns if the checkmark on the item is checked
     * @return int boolean
     */
    int is_checked();

    /**
     * @brief get_id
     * @return int id of item
     */
    int get_id();

public slots:
    /**
     * @brief make_selected sets state of the checkbox on the item
     * @param enable int boolean
     */
    void make_selected(int enable);

private slots:
    void on_viewButton_clicked();

private:
    Ui::MonitorListItem *ui;
    int id;
};

#endif // MONITORLISTITEM_H
