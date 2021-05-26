#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include <QList>
#include <QVector>
struct Item//物品
{
    QString Name;  //名字
    int Id;         //编号
    int Type;       //类型
    QString Info; //信息

};



struct Uitem//用户物品
{
    Item* item{};     //物品
    int number;      //数量
    bool equip;      //是否已经装备

};
struct Skill//技能
{
     QString Name;  //名字
//    int Id;         //编号
//    int Type;       //类型
//    QString  Info; //信息

    int Mpp;//内力消耗
    int Spp;//怒气
    int Act;//攻击
    int ActB;//翻倍攻击
    int CoolDown;//冷却时间
};
struct Uskill//用户技能
{
    Skill* skill{};
    int lv;
    int cooldown;
    int buse;
};

class Role : public QObject
{
    Q_OBJECT
public:
   explicit Role(QObject *parent = nullptr);
    Role(QString _Name,int _Hp[2],int _Mp[2],int _Sp[2], int _Act, QVector<Uskill>_skills, QVector<Uitem>_items);
    QString Name;  //名字
    int Hp[2];
    int Mp[2];
    int Sp[2];
    int Act;
//    int		Level;			//角色等级
//    int		Strength;		//角色力量值
//    int		Intelligence;   //角色智力值
//    int		Agility;		//角色敏捷值
    QVector<Uskill>skills;
    QVector<Uitem>items;
    //Uskill skills[5];
    //Uitem items[5];
    void ChSkill();//改变用户技能
    void addItem(Uitem _item);


};

#endif // ROLE_H
