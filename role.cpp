#include "role.h"

Role::Role(QObject *parent) : QObject(parent)
{

}

Role::Role(QString _Name,int _Hp[2],int _Mp[2],int _Sp[2], int _Act, QVector<Uskill>_skills, QVector<Uitem>_items)
{
    Name=_Name;

    Hp[0]=_Hp[0];
    Hp[1]=_Hp[1];

    Mp[0]=_Mp[0];
    Mp[1]=_Mp[1];

    Sp[0]=_Sp[0];
    Sp[1]=_Sp[1];

    Act=_Act;
    skills.swap(_skills);
    items.swap(_items);


}
void Role::ChSkill()
{

}
void Role::addItem(Uitem _item)
{
    items.push_back(_item);
}
