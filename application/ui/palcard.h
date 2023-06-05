#ifndef PALCARD_H
#define PALCARD_H

#include "../profile/pal.h"
#include <QWidget>

namespace Ui {
class PalCard;
}

class PalCard : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief open_pal emits when user clicks view button on a pal
     * @param p pal to open
     */
    void open_pal(profile::Pal *p);

public:
    explicit PalCard(profile::Pal *pal, QWidget *parent = nullptr);
    ~PalCard();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PalCard *ui;
    profile::Pal *pal;
};

#endif // PALCARD_H
