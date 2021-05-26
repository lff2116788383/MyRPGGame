#include "testmap001.h"
#include "ui_testmap001.h"
#include <QPainter>
#include <QDebug>
#include "battlescene.h"
#include "map.h"
testmap001::testmap001(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::testmap001)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/1.png"));
    setWindowTitle("科大历险记");

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        BattleScene* battlescene=new BattleScene;
        battlescene->show();
        this->close();
    });
    connect(ui->pushButton_Map,&QPushButton::clicked,[=](){
        Map* map=new Map;
        map->show();
        this->close();
    });

//    QImage Asprites[15];
//    for (int var = 0; var < 15; ++var) {
//        QString path=QString(":/Graphics/Titles1/Asprites_0_%1.png").arg(var);
//        Asprites[var].load(path);
//        if(Asprites[var].isNull()){
//            qDebug()<<"读取图片错误";
//        }
//        else{
//            Asprites[var].save(path,"PNG");
//        }
//    }
//    QString pixmap_url = ":/image/bg_mainjpt .png";
//    QImage image(pixmap_url);//定义QImage对象，读取图片
//    if(image.isNull()){
//        qdebug()<<"读取图片错误";
//    }
//    else{
//        image.save(pixmap_url,"PNG");
//    }

}

testmap001::~testmap001()
{
    delete ui;
}


//重写绘图事件
void testmap001::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //加载背景
    QPixmap pix;
    pix.load(":/SampleMap/Map010.png");
    //painter.drawPixmap(0,0,this->width(),this->height(),pix,0,0,pix.width(),pix.height());
}
