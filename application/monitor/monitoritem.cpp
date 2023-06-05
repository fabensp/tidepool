
#include "monitoritem.h"

monitor::MonitorItem::MonitorItem(int item_id, int user_id, int report_cnt,
                                  std::string username) :
    item_id(item_id),
    user_id(user_id), report_cnt(report_cnt), username(username) {}
