#ifndef PALSHOWCASE_H
#define PALSHOWCASE_H

#include "../profile/pal.h"
#include <QWidget>

namespace Ui {
class PalShowcase;
}

class PalShowcase : public QWidget
{
    Q_OBJECT

public:
    explicit PalShowcase(profile::Pal *pal, QWidget *parent = nullptr);
    ~PalShowcase();

private:
    Ui::PalShowcase *ui;
    profile::Pal *pal;
};

#endif // PALSHOWCASE_H
