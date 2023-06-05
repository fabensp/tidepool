#ifndef CREATEPOST_H
#define CREATEPOST_H

#include "../content/postio.h"
#include "createsurvey.h"
#include <QWidget>

namespace Ui {
class CreatePost;
}

class CreatePost : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief close emits when the cancel post button is clicked
     */
    void close();

    /**
     * @brief post emits when the confirm button is clicked
     * @param p post object to send to db
     */
    void post(content::Post* p);

    /**
     * @brief grab_addons gets data from addon ui objects
     * @param p post to populate with addons
     */
    void grab_addons(content::Post* p);

public:
    explicit CreatePost(user::Account *user, content::PostIO *pio,
                        QWidget *parent = nullptr);
    ~CreatePost();

private slots:
    void on_selectAddon_currentTextChanged(const QString &arg1);

    void on_cancelButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::CreatePost *ui;
    user::Account *user;
    content::PostIO *pio;
};

#endif // CREATEPOST_H
