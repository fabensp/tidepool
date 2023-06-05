#ifndef INDEXBUTTON_H
#define INDEXBUTTON_H

#include <QWidget>

namespace Ui {
class IndexButton;
}

/**
 * @brief The IndexButton class is just a normal QPushButton but it holds an int
 */
class IndexButton : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief on_click emits when button is clicked
     * @param i index held by button
     */
    void on_click(int i);

public:
    explicit IndexButton(int i, QString s, int f = 0,
                         QWidget *parent = nullptr);
    ~IndexButton();

private slots:
    void on_button_clicked();

private:
    Ui::IndexButton *ui;
    int i;
};

#endif // INDEXBUTTON_H
