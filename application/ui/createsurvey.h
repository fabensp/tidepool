#ifndef CREATESURVEY_H
#define CREATESURVEY_H

#include <QWidget>

namespace Ui {
class CreateSurvey;
}

class CreateSurvey : public QWidget
{
    Q_OBJECT

public:
    explicit CreateSurvey(QWidget *parent = nullptr);
    ~CreateSurvey();

private slots:
    void on_addOptionButton_clicked();

    void on_removeOptionButton_clicked();

private:
    Ui::CreateSurvey *ui;
};

#endif // CREATESURVEY_H
