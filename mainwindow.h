#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "testmap001.h"
#include <QMainWindow>
#define PARTICLE_NUMBER	50
struct SNOW
{
    int x; //雪花的 X坐标
    int y; //雪花的Y坐标
    bool exist;  //雪花是否存在
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //重写键盘事件
    void keyPressEvent(QKeyEvent *e);

    //void particle(QString path,int particle_number);
    int frame;
    QRect				g_rect;				//定义一个RECT结构体，用于储存内部窗口区域的坐标
    SNOW			SnowFlowers[PARTICLE_NUMBER];   //雪花粒子数组
    int					g_SnowNum=0; //定义g_SnowNum用于计数


    testmap001* map;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
