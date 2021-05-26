#ifndef TESTMAP001_H
#define TESTMAP001_H

#include <QWidget>

namespace Ui {
class testmap001;
}

class testmap001 : public QWidget
{
    Q_OBJECT

public:
    explicit testmap001(QWidget *parent = nullptr);
    ~testmap001();


    //重写绘图事件
    void paintEvent(QPaintEvent *);
private:
    Ui::testmap001 *ui;
};

#endif // TESTMAP001_H
