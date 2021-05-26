#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QToolButton>
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QSound>//多媒体模块下的音效头文件
//#define PARTICLE_NUMBER	80							//表示粒子数量的宏，以方便修改粒子数量
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/1.png"));
    setWindowTitle("科大历险记");
    setFixedSize(640,480);
    srand((unsigned)time(NULL));      //用系统时间初始化随机种子
    g_rect=this->geometry();
    //播放背景音乐
    QSound *startSound = new QSound(":/Audio/BGM/Field1.wav",this);
    startSound->setLoops(-1);//设置循环次数 -1代表循环无限次
    startSound->play();

    //用定时器播放动态精灵图片
    frame=0;
    QTimer* timer1 = new QTimer;
    connect(timer1,&QTimer::timeout,[=](){
        if(frame<14)
        {
            frame++;

        }
        else
        {
            frame=0;

        }
        update();
        QString str=QString("第%1张图片").arg(frame);
        //qDebug() <<str;
    });
    timer1->start(200);




    //设置透明开始按钮
    QPixmap pix;

    pix.load(":/Graphics/Titles1/Com_0.png");
    QToolButton* startbtn = new QToolButton(this);
    startbtn->setMinimumSize(pix.width(),pix.height());
    startbtn->setMaximumSize(pix.width(),pix.height());
    startbtn->setGeometry((this->width()-startbtn->width())/2,this->height()/2,startbtn->width(),startbtn->height());
    startbtn->setIcon(pix);
    startbtn->setIconSize(pix.size());
    startbtn->setStyleSheet("background-color:rgba(0,0,0,0)");
    startbtn->setFocusPolicy(Qt::NoFocus);

    pix.load(":/Graphics/Titles1/Com_1.png");
    QToolButton* continuebtn = new QToolButton(this);
    continuebtn->setMinimumSize(pix.width(),pix.height());
    continuebtn->setMaximumSize(pix.width(),pix.height());
    continuebtn->setGeometry((this->width()-continuebtn->width())/2,this->height()/2+startbtn->height(),continuebtn->width(),continuebtn->height());
    continuebtn->setIcon(pix);
    continuebtn->setIconSize(pix.size());
    continuebtn->setStyleSheet("background-color:rgba(0,0,0,0)");
    continuebtn->setFocusPolicy(Qt::NoFocus);

    pix.load(":/Graphics/Titles1/Com_2.png");
    QToolButton* shutdownbtn = new QToolButton(this);
    shutdownbtn->setMinimumSize(pix.width(),pix.height());
    shutdownbtn->setMaximumSize(pix.width(),pix.height());
    shutdownbtn->setGeometry((this->width()-shutdownbtn->width())/2,this->height()/2+startbtn->height()+continuebtn->height(),shutdownbtn->width(),shutdownbtn->height());
    shutdownbtn->setIcon(pix);
    shutdownbtn->setIconSize(pix.size());
    shutdownbtn->setStyleSheet("background-color:rgba(0,0,0,0)");
    shutdownbtn->setFocusPolicy(Qt::NoFocus);

    pix.load(":/Graphics/Titles1/Cursor.png");
    QLabel* cursorlab=new QLabel(this);
    cursorlab->setMinimumSize(pix.width(),pix.height());
    cursorlab->setMaximumSize(pix.width(),pix.height());
    cursorlab->setGeometry((this->width()-startbtn->width()-cursorlab->width())/2,this->height()/2-10,cursorlab->width(),cursorlab->height());
    cursorlab->setPixmap(pix);
    cursorlab->setBaseSize(pix.size());
    cursorlab->setStyleSheet("background-color:rgba(0,0,0,0)");
    cursorlab->setFocusPolicy(Qt::NoFocus);


    connect(startbtn,&QToolButton::clicked,[=](){
        timer1->stop();
        startSound->stop();
        map=new testmap001;
        map->show();
        this->close();
    });

    connect(continuebtn,&QToolButton::clicked,[=](){
        QMessageBox::information(this,"提示","此功能暂未开放，敬请期待！");
    });

    connect(shutdownbtn,&QToolButton::clicked,[=](){
        this->close();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}


//重写绘图事件
void MainWindow::paintEvent(QPaintEvent *)
{

     QPainter painter(this);
     //加载背景
     QPixmap pix;
     pix.load(":/Graphics/Titles1/Background_0.jpg");
     painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载选项
//    pix.load(":/Graphics/System/PNG/paper_panel_242_x_240b.png");
//    painter.drawPixmap((this->width()-pix.width())*0.5,250,pix.width(),pix.height(),pix);


     QImage Asprites1[15];
     for (int var = 0; var < 15; ++var) {
         QString path1=QString(":/Graphics/Titles1/Asprites_0_%1.png").arg(var);
         Asprites1[var].load(path1);
         if(Asprites1[var].isNull()){
             qDebug()<<"读取图片错误";
         }
         else{
             Asprites1[var].save(path1,"PNG");
             //qDebug()<<"适配成功";
         }
     }
    //加载绘制动态精灵图片
    QPixmap Asprites[15];
    for (int var = 0; var < 15; ++var) {
        QString path=QString(":/Graphics/Titles1/Asprites_0_%1.png").arg(var);
        Asprites[var].load(path);
    }
    painter.drawPixmap(0,54, Asprites[frame].width(), Asprites[frame].height(), Asprites[frame]);


    pix.load(":/Graphics/Titles1/Background_2.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //加载粒子图片
    pix.load(":/Graphics/Titles1/snow1.png");
    //创建粒子
        if(g_SnowNum< PARTICLE_NUMBER)  //当粒子数小于规定的粒子数时，便产生新的粒子，设定每个粒子的属性值
        {
            SnowFlowers[g_SnowNum].x = rand()%g_rect.right(); //将粒子的X坐标设为窗口中水平方向上的任意位置
            SnowFlowers[g_SnowNum].y = 0;    //将每个粒子的Y坐标都设为"0"，即从窗口上沿往下落
            SnowFlowers[g_SnowNum].exist = true; //设定粒子存在
            g_SnowNum++;   //每产生一个粒子后进行累加计数
        }


        //首先判断粒子是否存在，若存在，进行贴图操作
        for(int i=0;i<PARTICLE_NUMBER;i++)
        {
            if(SnowFlowers[i].exist)  //粒子还存在
            {
                //贴上粒子图
                painter.drawPixmap(SnowFlowers[i].x,SnowFlowers[i].y,30,30,pix,0,0,pix.width(),pix.height());
//                SelectObject(g_bufdc,g_hSnow);
//                TransparentBlt(g_mdc,SnowFlowers[i].x,SnowFlowers[i].y,30,30,g_bufdc,0,0,30,30,RGB(0,0,0));

                //随机决定横向的移动方向和偏移量
                if(rand()%2==0)
                    SnowFlowers[i].x+=rand()%6;  //x坐标加上0~5之间的一个随机值
                else
                    SnowFlowers[i].x-=rand()%6;	 //y坐标加上0~5之间的一个随机值
                //纵方向上做匀速运动
                SnowFlowers[i].y+=10;  //纵坐标加上10
                //如果粒子坐标超出了窗口长度，就让它以随机的x坐标出现在窗口顶部
                if(SnowFlowers[i].y > g_rect.bottom())
                {
                    SnowFlowers[i].x = rand()%g_rect.right();
                    SnowFlowers[i].y = 0;
                }
            }

        }

}

//重写键盘事件
void MainWindow::keyPressEvent(QKeyEvent *e)
{

    switch(e->key())
    {
    case Qt::Key_Enter:
        qDebug() << "按下回车键";
        break;
    case Qt::Key_Up:
        qDebug() << "按下向上键";
        break;
    case Qt::Key_Down:
        qDebug() << "按下向下键";
        break;
    default:
        break;


    }
}
