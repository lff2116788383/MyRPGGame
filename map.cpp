#include "map.h"
#include "ui_map.h"
#include "battlescene.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <qDebug>
#include <QTimer>
Role* User;
Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    Item ALLitems[5]{
        {"铁剑",1,1,"一把生锈的铁剑"},
        {"水果刀",1,1,"一把削铁如泥的水果刀"},
        {"大剑",1,1,"一把宽阔的铁剑"},
        {"魔剑",1,1,"一把附有魔力的剑"},
        {"神剑",1,1,"一把拥有神之祝福的剑"}
    };

    Skill Allskills[11] {
        {"普通攻击",0,0,10,1,0},
        {"大力金刚指",10,0,50,1,1},
        {"云龙三观",0,0,60,1,1},
        {"一阳指",30,0,0,2,3},
        {"迎风破浪",30,0,300,0,3},
        {"八卦掌",50,0,0,5,4},
        {"六合八荒",50,0,500,0,4},
        {"仙人指路",100,0,0,10,6},
        {"横扫千军",100,0,50,2,6},
        {"气吞山河",0,100,500,5,0},
        {"秋风刀法",0,100,200,10,0}
    };//技能列表



//    Uskill s1;
//    s1.skill=&Allskills[3];
//    s1.lv=1;
//    s1.cooldown=1;
//    s1.buse=1;

//    Role* User=new Role;
//    User->Name="郝英俊";
//    User->Hp[0]=1000;
//    User->Hp[1]=1000;
//    User->Mp[0]=200;
//    User->Mp[1]=500;
//    User->Sp[0]=50;
//    User->Sp[1]=100;
//    User->skills[0]=s1;

    int hp[2]={1000,1000};
    int mp[2]={1000,1000};
    int sp[2]={100,1000};
    Uskill _s[5];
    Uitem _i[5];

    for (int i = 0; i < 5; ++i) {
        _s[i].skill=&Allskills[i];
        _s[i].lv=1;
        _s[i].cooldown=1;
        _s[i].buse=1;

        _i[i].item=&ALLitems[i];
        _i[i].number=1;
        _i[i].equip=false;
    };

    QVector<Uskill>_skills;
    _skills.push_back(_s[0]);
    _skills.push_back(_s[1]);
    QVector<Uitem>_items;
    _items.push_back(_i[0]);
    _items.push_back(_i[1]);
    _items.push_back(_i[2]);

    User=new Role(QString("郝英军"),hp,mp,sp,0,_skills,_items);

    QString name=User->Name;
    ui->lineEdit_Name->setText(name);

    QString user_hp=QString("%1/%2").arg(QString::number(User->Hp[0])).arg(QString::number(User->Hp[1]));
    ui->lineEdit_Hp->setText(user_hp);

    QString user_mp=QString("%1/%2").arg(QString::number(User->Mp[0])).arg(QString::number(User->Mp[1]));
    ui->lineEdit_Mp->setText(user_mp);

    QString user_sp=QString("%1/%2").arg(QString::number(User->Sp[0])).arg(QString::number(User->Sp[1]));
    ui->lineEdit_Sp->setText(user_sp);

    QString user_act=QString::number(User->Act);
    ui->lineEdit_Act->setText(user_act);


    ui->textEdit_Skill->append(QString("技能列表："));
    for (int i = 0; i < User->skills.size(); ++i) {
        ui->textEdit_Skill->append(User->skills[i].skill->Name);
    }
    ui->textEdit_Item->append(QString("物品列表："));
    for (int i = 0; i < User->items.size(); ++i) {
        ui->textEdit_Item->append(User->items[i].item->Name);
    }



    connect(ui->pushButton,&QPushButton::clicked,[=](){
        BattleScene* b=new BattleScene;
        b->show();
        this->close();
    });

    connect(ui->pushButton_addItem,&QPushButton::clicked,[=](){
        User->addItem(_items.back());
        qDebug()<<User->items.size();
        //qDebug()<<User->items[1].item->Name;

    });



    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("MyDB.db"); // 数据库名与路径, 此时是放在同目录下

   // 连接数据库, 然后就可以使用了.
    if(db.open())
    {
        qDebug()<<"数据库QSQLITE已连接";
    }
    else
    {
        qDebug()<<"数据库QSQLITE连接失败";
    }

    QSqlQuery query;

        query.prepare("insert into user(id, name) values(:id, :name)");

        query.bindValue(":id", 2);

        query.bindValue(":name", "黄彪");

        bool ok = query.exec();



        query.prepare("insert into user(id, name) values(:id, :name)");

        query.bindValue(":id", 3);

        query.bindValue(":name", "阿跑");

        query.exec();



        if (!ok) {
            qDebug() << "Already exits.";

        }



        query.exec("create table hello(id int primary key)");


    query.exec("select * from user");

    while (query.next()) {
        int id = query.value(0).toInt();

        QString name = query.value(1).toString();


        qDebug() << "Id=" << id << ", Name=" << name;

    }
    //查询数据库中所有表的名称
    QStringList tables = db.tables();
    foreach(QString table, tables)
        qDebug()<<"表名"<<table;



}

Map::~Map()
{
    delete ui;
}


