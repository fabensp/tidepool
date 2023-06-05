#ifndef PROFILEEDITORPAL_H
#define PROFILEEDITORPAL_H

#include "../profile/pal.h"
#include <QWidget>

namespace Ui {
class ProfileEditorPal;
}

class ProfileEditorPal : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief remove_pal emits when user clicks button to remove a pal
     * @param w widget to remove (self)
     * @param pal pal to remove
     */
    void remove_pal(QWidget *w, profile::Pal *pal);

public:
    explicit ProfileEditorPal(profile::Pal *pal, QWidget *parent = nullptr);
    ~ProfileEditorPal();

private slots:
    void on_toolButton_clicked();

private:
    Ui::ProfileEditorPal *ui;
    profile::Pal *pal;
};

#endif // PROFILEEDITORPAL_H
