#ifndef POSTSURVEY_H
#define POSTSURVEY_H

#include <QWidget>

namespace Ui {
class PostSurvey;
}

class PostSurvey : public QWidget
{
    Q_OBJECT

public:
    explicit PostSurvey(QWidget *parent = nullptr);
    ~PostSurvey();

private:
    Ui::PostSurvey *ui;
};

#endif // POSTSURVEY_H
