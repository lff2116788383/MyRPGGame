#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include "role.h"
namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

    Role hero;




private slots:
    //void on_pushButton_addItem_clicked();

private:
    Ui::Map *ui;
};

#endif // MAP_H
