#ifndef PROFILEEDITORLINK_H
#define PROFILEEDITORLINK_H

#include <QWidget>

namespace Ui {
class ProfileEditorLink;
}

class ProfileEditorLink : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief remove_link emits when user clicks button to remove a link
     * @param w widget to remove (self)
     * @param la link label
     * @param li link url
     */
    void remove_link(QWidget *w, std::string la, std::string li);

public:
    explicit ProfileEditorLink(std::string label, std::string link,
                               QWidget *parent = nullptr);
    ~ProfileEditorLink();

private slots:
    void on_deleteButton_clicked();

private:
    Ui::ProfileEditorLink *ui;
    std::string label;
    std::string link;
};

#endif // PROFILEEDITORLINK_H
