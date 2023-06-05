#ifndef MONITORITEM_H
#define MONITORITEM_H

#include <string>

namespace monitor {

class MonitorItem {
public:
    /**
     * @brief MonitorItem just holds the essential info on some reported item
     */
    MonitorItem(int item_id, int user_id, int report_cnt, std::string username);

    int get_item_id() { return item_id; }
    int get_user_id() { return user_id; }
    int get_report_cnt() { return report_cnt; }
    std::string get_username() { return username; }

private:
    int item_id;
    int user_id;
    int report_cnt;
    std::string username;
};

} // namespace monitor

#endif // MONITORITEM_H
