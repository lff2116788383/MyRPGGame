#include "battlescene.h"
#include "ui_battlescene.h"
#include <tchar.h>//使用swprintf_s函数所需的头文件
#include  <time.h> //使用获取系统时间time()函数需要包含的头文件
#include "ui_mainwindow.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QToolButton>
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QSound>//多媒体模块下的音效头文件
#include "map.h"
extern Role* User;
BattleScene::BattleScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BattleScene)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/1.png"));
    setWindowTitle("战斗场景");
    //载入一系列游戏资源图到位图句柄中
    g_hGameOver.load(":/GameMedia/gameover.png"); //游戏结束位图
    g_hVictory.load(":/GameMedia/victory.png");  //游戏胜利位图
    g_hBackGround.load(":/GameMedia/bg.png"); //背景位图
    g_hMonsterBitmap.load(":/GameMedia/monster.png");  //怪物角色位图
    g_hHeroBitmap .load(":/GameMedia/hero.png"); //英雄角色位图
    g_hHeroSkill1.load(":/GameMedia/heroslash.png"); //英雄1技能位图
    g_hHeroSkill2.load(":/GameMedia/heromagic.png"); //英雄2技能位图
    g_hHeroSkill3.load(":/GameMedia/herocritical.png"); //英雄3技能位图
    g_hSkillButton1 .load(":/GameMedia/skillbutton1.png");  //技能1图标位图
    g_hSkillButton2.load(":/GameMedia/skillbutton2.png");   //技能2图标位图
    g_hSkillButton3.load(":/GameMedia/skillbutton3.png");  //技能3图标位图
    g_hSkillButton4.load(":/GameMedia/skillbutton4.png");   //技能4图标位图
    g_hBossSkill1.load(":/GameMedia/monsterslash.png");  //怪物1技能位图
    g_hBossSkill2.load(":/GameMedia/monstermagic.png");  //怪物2技能位图
    g_hBossSkill3.load(":/GameMedia/monstercritical.png"); //怪物3技能位图
    g_hSnow .load(":/GameMedia/snow.png");  //雪花位图
    g_hRecoverSkill.load(":/GameMedia/recover.png");



    QSound* battleSound =new QSound(":/GameMedia/battle.wav",this);
    battleSound->setLoops(-1);//设置循环次数 -1代表循环无限次
    battleSound->play();

    srand((unsigned)time(NULL));      //用系统时间初始化随机种子
    g_rect=this->geometry();//取得内部窗口区域的大小

    //设定玩家圣殿骑士的各项属性值
    Hero.NowHp = Hero.MaxHp = 1000;	//设定玩家生命值的当前值及上限
    Hero.Level = 6;					//设定玩家角色等级
    Hero.NowMp=Hero.MaxMp=60;    //玩家魔法值的当前值及上限
    Hero.Strength  = 10;			//设定英雄的力量值
    Hero.Agility=20;				//设定英雄的敏捷值
    Hero.Intelligence=10;		//设定英雄的智力值

    //设定BOSS黄金魔龙君的各项属性值
    Boss.NowHp = Boss.MaxHp = 2000;	//设定BOSS生命值的当前值及上限
    Boss.Level = 10;						//设定BOSS的等级
    Boss.Strength = 10;				//设定BOSS的力量值
    Boss.Agility=10;                   //设定BOSS的敏捷值
    Boss.Intelligence=10;			//设定BOSS的智力值

    g_iTxtNum = 0;		//初始化显示消息数目
    //update();//Game_Main(hwnd);  //调用一次游戏Main函数

    qDebug()<<User->Hp[0];


    skillbutton[0] = new QToolButton(this);
    skillbutton[0]->setMinimumSize(50,50);
    skillbutton[0]->setMaximumSize(50,50);
    skillbutton[0]->setGeometry(530,420,50,50);
    skillbutton[0]->setIcon(g_hSkillButton1);
    skillbutton[0]->setIconSize(g_hSkillButton1.size());
    skillbutton[0]->setStyleSheet("background-color:rgba(0,0,0,0)");
    skillbutton[0]->setFocusPolicy(Qt::NoFocus);

    skillbutton[1] = new QToolButton(this);
    skillbutton[1]->setMinimumSize(50,50);
    skillbutton[1]->setMaximumSize(50,50);
    skillbutton[1]->setGeometry(590,420,50,50);
    skillbutton[1]->setIcon(g_hSkillButton2);
    skillbutton[1]->setIconSize(g_hSkillButton2.size());
    skillbutton[1]->setStyleSheet("background-color:rgba(0,0,0,0)");
    skillbutton[1]->setFocusPolicy(Qt::NoFocus);

    skillbutton[2] = new QToolButton(this);
    skillbutton[2]->setMinimumSize(50,50);
    skillbutton[2]->setMaximumSize(50,50);
    skillbutton[2]->setGeometry(650,420,50,50);
    skillbutton[2]->setIcon(g_hSkillButton3);
    skillbutton[2]->setIconSize(g_hSkillButton3.size());
    skillbutton[2]->setStyleSheet("background-color:rgba(0,0,0,0)");
    skillbutton[2]->setFocusPolicy(Qt::NoFocus);

    skillbutton[3] = new QToolButton(this);
    skillbutton[3]->setMinimumSize(50,50);
    skillbutton[3]->setMaximumSize(50,50);
    skillbutton[3]->setGeometry(710,420,50,50);
    skillbutton[3]->setIcon(g_hSkillButton4);
    skillbutton[3]->setIconSize(g_hSkillButton4.size());
    skillbutton[3]->setStyleSheet("background-color:rgba(0,0,0,0)");
    skillbutton[3]->setFocusPolicy(Qt::NoFocus);

    connect(skillbutton[0],&QToolButton::clicked,[=](){
        g_bCanAttack = true;
        HeroActionType=ACTION_TYPE_NORMAL;

    });

    connect(skillbutton[1],&QToolButton::clicked,[=](){
        g_bCanAttack = true;
        HeroActionType=ACTION_TYPE_MAGIC;
    });

    connect(skillbutton[2],&QToolButton::clicked,[=](){
        g_bCanAttack = true;
        HeroActionType=ACTION_TYPE_MAGIC;
    });

    connect(skillbutton[3],&QToolButton::clicked,[=](){
        g_bCanAttack = true;
        HeroActionType=ACTION_TYPE_RECOVER;
    });

    QTimer* timer1 = new QTimer;
    connect(timer1,&QTimer::timeout,[=](){
        update();
        //qDebug() <<"更新绘图";


    });
    timer1->start(200);

}

BattleScene::~BattleScene()
{
    delete ui;
}

//-----------------------------------【paintEvent(QPaintEvent *)函数】--------------------------------------
//	描述：游戏paintEvent(QPaintEvent *)函数，游戏的心脏，处理游戏大大小小函数的合理调用与运作
//--------------------------------------------------------------------------------------------------
void BattleScene::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    painter.setFont(QFont("微软雅黑",10,0));

    wchar_t str[100];

    //先在mdc中贴上背景图
    painter.drawPixmap(0,0,g_hBackGround);
    //SelectObject(g_bufdc,g_hBackGround);
    //BitBlt(g_mdc,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,g_bufdc,0,0,SRCCOPY);

    //贴上怪物图以及显示怪物血量
    if(Boss.NowHp>0)
    {

        painter.drawPixmap(0,50,360,360,g_hMonsterBitmap,0,0,360,360);
        //显示怪物血量
        swprintf_s(str,L"%d / %d",Boss.NowHp,Boss.MaxHp);
        painter.setPen(QColor(255,10,10));
        painter.drawText(100,370,QString::fromWCharArray(str));

    }
    //贴上玩家图以及玩家生命值，魔法值的显示
    if(Hero.NowHp>0)
    {
        //贴上人物图
        painter.drawPixmap(400,50,360,360,g_hHeroBitmap,0,0,360,360);
        //显示血量
        swprintf_s(str,L"%d / %d",Hero.NowHp,Hero.MaxHp);

        painter.setPen(QColor(255,10,10));

        painter.drawText(600,350,QString::fromWCharArray(str));
        //显示魔法值
        swprintf_s(str,L"%d / %d",Hero.NowMp,Hero.MaxMp);

        painter.setPen(QColor(10,10,255));

        painter.drawText(600,370,QString::fromWCharArray(str));
    }

    if (!g_bGameOver)//如果游戏未结束
    {
        //Snow_Paint(); //调用封装了雪花飞舞粒子效果的函数，模拟下雪场景

        //下雪效果的绘制
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
                painter.drawPixmap(SnowFlowers[i].x,SnowFlowers[i].y,30,30,g_hSnow ,0,0,g_hSnow.width(),g_hSnow.height());

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

        //显示对战消息

        painter.setPen(QColor(255,255,255));
        for(int i=0;i<g_iTxtNum;i++)
            painter.drawText(20,410+i*18,QString::fromWCharArray(text[i]));




        //贴上玩家图以及玩家生命值，魔法值的显示
        if(Hero.NowHp>0)
        {

            //如果游戏没结束，且为玩家可攻击状态，便依次贴上技能图标
            if(!g_bCanAttack)		//贴上技能按钮
            {
                qDebug() << "玩家处于攻击状态";
                for (int var = 0; var < 4; ++var) {
                    skillbutton[var]->show();
                }
            }
            //游戏没结束，且为玩家不可攻击状态，便开始接下来的绘图
            else
            {
                qDebug() << "玩家处于不可攻击状态";
                for (int var = 0; var < 4; ++var) {
                    skillbutton[var]->hide();
                }

                g_iFrameNum++;

                //第5~10个画面时显示玩家攻击效果图
                if(g_iFrameNum>=5 && g_iFrameNum<=10)
                {
                    //第5个画面时根据之前的输入计算出游戏逻辑并进行消息显示
                    if(g_iFrameNum == 5)
                    {
                        HeroAction_Logic( );
                        Die_Check(Boss.NowHp,false);
                    }
                    //根据人物的动作类型进行相应贴图
                    //HeroAction_Paint();
                    switch (HeroActionType)
                    {
                    case ACTION_TYPE_NORMAL:   //普通攻击，无敌斩

                        painter.drawPixmap(50,170,364,140,g_hHeroSkill1,0,0,364,140);
                        break;

                    case ACTION_TYPE_CRITICAL:  //暴击，恩赐解脱
                     painter.drawPixmap(20,60,574,306,g_hHeroSkill3,0,0,574,306);
                        break;

                    case ACTION_TYPE_MAGIC:  //魔法攻击，烈火剑法
                       painter.drawPixmap(50,100,374,288,g_hHeroSkill2,0,0,374,288);
                        break;

                    case ACTION_TYPE_RECOVER:   //恢复，气疗术
                        painter.drawPixmap(560,170,150,150,g_hRecoverSkill,0,0,150,150);
                        break;
                    default:
                        break;
                    }
                }

                //第15个画面时判断怪物进行哪项动作
                if(g_iFrameNum == 15)
                {
                    BossAction_Logic();
                }

                //第26~30个画面时显示怪物攻击图标
                if(g_iFrameNum>=26  && g_iFrameNum<=30)
                {
                    //BossAction_Paint();
                    int damage=0,recover=0;
                    wchar_t str[100];

                    switch(BossActionType)
                    {
                    case ACTION_TYPE_NORMAL:							//释放普通攻击“幽冥鬼火”
                       painter.drawPixmap(500,150,234,188,g_hBossSkill1,0,0,234,188);
                        //第30个画面时计算玩家受伤害程度并加入显示消息
                        if(g_iFrameNum == 30)
                        {
                            damage = rand()%Boss.Agility+ Boss.Level*Boss.Strength;
                            Hero.NowHp -= (int)damage;

                            swprintf_s(str,L"黄金魔龙君释放幽冥鬼火...对玩家照成【 %d】 点伤害",damage);
                            Message_Insert(str);

                            Die_Check(Hero.NowHp,true);
                        }
                        break;

                    case ACTION_TYPE_MAGIC:							//释放嗜血咒
                        painter.drawPixmap(450,150,387,254,g_hBossSkill2,0,0,387,254);
                        //第30个画面时计算玩家受伤害程度并加入显示消息
                        if(g_iFrameNum == 30)
                        {
                            damage = 2*(2*(rand()%Boss.Agility) + Boss.Strength*Boss.Intelligence);  //嗜血咒的伤害值计算
                            Hero.NowHp -= damage;	   //让英雄血量减掉一个计算出来的伤害值
                            recover	=(int)((float)damage*0.2f);   //吸血量20%
                            Boss.NowHp+=recover;   //怪物恢复吸到的血量
                            swprintf_s(str,L"黄金魔龙君释放嗜血咒...对玩家照成【 %d 】点伤害,自身恢复【%d】点生命值",damage,recover);   //将数字格式化到文字中
                            Message_Insert(str);   //插入文字消息

                            Die_Check(Hero.NowHp,true);
                        }
                        break;

                    case ACTION_TYPE_CRITICAL:							//释放致命一击
                       painter.drawPixmap(280,100,574,306,g_hBossSkill3,0,0,574,306);
                        //第30个画面时计算玩家受伤害程度并加入显示消息
                        if(g_iFrameNum == 30)
                        {
                            damage = 2*(rand()%Boss.Agility+ Boss.Level*Boss.Strength);
                            Hero.NowHp -= (int)damage;

                            swprintf_s(str,L"黄金魔龙君致命一击...对玩家照成【%d】点伤害.",damage);
                            Message_Insert(str);

                            Die_Check(Hero.NowHp,true);
                        }
                        break;

                    case ACTION_TYPE_RECOVER:							//使用梅肯斯姆补血
                       painter.drawPixmap(150,150,150,150,g_hRecoverSkill,0,0,150,150);
                        //第30个画面时怪物回复生命值并加入显示消息
                        if(g_iFrameNum == 30)
                        {
                                recover= 2*Boss.Intelligence*Boss.Intelligence;
                                Boss.NowHp +=recover;
                            swprintf_s(str,L"黄金魔龙君使用梅肯斯姆...恢复了【%d】点生命值",recover);
                            Message_Insert(str);
                        }
                        break;
                    default:
                        break;
                    }
                }

                if(g_iFrameNum == 30)			//回合结束
                {
                    g_bCanAttack = false;
                    g_iFrameNum = 0;

                    //每回合的魔法自然恢复，6点固定值加上0到智力值之间的一个随机值的三倍
                    if(!g_bGameOver)
                    {
                        int MpRecover=2*(rand()%Hero.Intelligence)+6;
                        Hero.NowMp+=MpRecover;

                        if (Hero.NowMp>=Hero.MaxMp)
                        {
                            Hero.NowMp=Hero.MaxMp;
                        }

                        swprintf_s(str,L"回合结束，自动恢复了【%d】点魔法值",MpRecover);
                        Message_Insert(str);
                    }
                }
            }


        }
     }
    else
    {
        if(Hero.NowHp <= 0)  //玩家阵亡，就贴出“GameOver”图片
        {
            painter.drawPixmap(120,50,543,396,g_hGameOver,543,0,g_hGameOver.width()/2,g_hGameOver.height());
            qDebug() << "玩家阵亡";
        }

        else  //怪物阵亡，就贴出“胜利”图片
        {
            painter.drawPixmap(0,0,800,600,g_hVictory,0,0,800,600);
            qDebug() << "Boss阵亡";
        }
    }





}
//-----------------------------------【Message_Insert( )函数】----------------------------------
//	描述：对战消息函数，用于插入文字消息
//---------------------------------------------------------------------------------------------------
void BattleScene::Message_Insert(wchar_t* str)
{
    //如果未满8行消息，直接新开一条消息
    if(g_iTxtNum < 8)
    {
        swprintf_s(text[g_iTxtNum],str);
        g_iTxtNum++;
    }
    //如果满了8行消息，只有挤走最上面的一条消息
    else
    {
        for(int i=0;i<g_iTxtNum;i++)
        {
            swprintf_s(text[i],text[i+1]);
        }
            swprintf_s(text[7],str);
    }
}


//-----------------------------------【Die_Check( )函数】----------------------------------------
//	描述：生命值判断函数，检查角色是否死亡，第一个参数填某角色当前生命值
//--------------------------------------------------------------------------------------------------
void BattleScene::Die_Check(int NowHp,bool isHero)
{
    wchar_t str[100];

    if(NowHp <= 0)//生命值小于等于0了
    {
        g_bGameOver = true;
        if(isHero)  //如果是英雄的生命值小于零，表示游戏失败
        {

            QSound* failureSound=new QSound(":/GameMedia/failure.wav",this);
            failureSound->setLoops(1);
            failureSound->play();
            swprintf_s(str,L": ( 胜败乃兵家常事，大侠请重新来过......");  //输出失败提示语
            Message_Insert(str);  //插入到文字消息中
        }
        else
        {

            QSound* victorySound=new QSound(":/GameMedia/victory.wav",this);
            victorySound->setLoops(1);
            victorySound->play();
            swprintf_s(str,L"少年，你赢了，有两下子啊~~~~~！！！！");  //输出胜利提示语
            Message_Insert(str);  //插入到文字消息中
        }
    }
}

//-----------------------------------【HeroAction_Logic( )函数】------------------------------
//	描述：玩家动作逻辑判断函数
//--------------------------------------------------------------------------------------------------
void		BattleScene::HeroAction_Logic( )
{
        int damage=0;
        wchar_t str[100];

        switch(HeroActionType)
        {
        case ACTION_TYPE_NORMAL:

            if (1==rand()%4)                   // 20%几率触发幻影刺客的大招，恩赐解脱，4倍暴击伤害
            {
                HeroActionType=ACTION_TYPE_CRITICAL;
                damage = (int)(4.5f*(float)(3*(rand()%Hero.Agility) + Hero.Level*Hero.Strength+20));
                Boss.NowHp -= (int)damage;

                swprintf_s(str,L"恩赐解脱触发，这下牛逼了，4.5倍暴击...对怪物照成了【%d】点伤害",damage);
            }
            else       //没有触发”恩赐解脱“，还是用普通攻击”无敌斩“
            {
                damage = 3*(rand()%Hero.Agility) + Hero.Level*Hero.Strength+20;
                Boss.NowHp -= (int)damage;

                swprintf_s(str,L"玩家%d级圣殿骑士使用了普通攻击“无敌斩”，伤害一般般...对怪物照成了【%d】点伤害",Hero.Level,damage);
            }

            Message_Insert(str);
            break;

        case ACTION_TYPE_MAGIC:  //释放烈火剑法
            if(Hero.NowMp>=30)
            {
                damage = 5*(2*(rand()%Hero.Agility) + Hero.Level*Hero.Intelligence);
                Boss.NowHp -= (int)damage;
                Hero.NowMp-=30;
                swprintf_s(str,L"玩家圣殿骑士释放烈火剑法...对怪物照成了【%d】点伤害",damage);
            }
            else
            {
                HeroActionType=ACTION_TYPE_MISS;
                swprintf_s(str,L"你傻啊~!，魔法值不足30点，施法失败，这回合白费了~！");
            }
            Message_Insert(str);
            break;

        case ACTION_TYPE_RECOVER:  //使用气疗术

            if(Hero.NowMp>=40)
            {
                Hero.NowMp-=40;
                int HpRecover=5*(5*(rand()%Hero.Intelligence)+40);
                Hero.NowHp+=HpRecover;
                if (Hero.NowHp>=Hero.MaxHp)
                {
                    Hero.NowHp=Hero.MaxHp;
                }
                swprintf_s(str,L"玩家圣殿骑士使用了气疗术，恢复了【%d】点生命值，感觉好多了。",HpRecover);
            }
            else
            {
                HeroActionType=ACTION_TYPE_MISS;
                swprintf_s(str,L"你傻啊~!，魔法值不足40点，施法失败，这回合白费了~！");
            }
            Message_Insert(str);
            break;
        default:
            break;
        }

}


//-----------------------------------【HeroAction_Paint( )函数】-------------------------------
//	描述：玩家动作贴图函数
//--------------------------------------------------------------------------------------------------
void BattleScene::HeroAction_Paint()
{

    switch (HeroActionType)
    {
    case ACTION_TYPE_NORMAL:   //普通攻击，无敌斩
//        SelectObject(g_bufdc,g_hHeroSkill1);
//        TransparentBlt(g_mdc,50,170,364,140,g_bufdc,0,0,364,140,RGB(0,0,0));//TransparentBlt函数的透明颜色设为RGB(0,0,0)
        //painter.drawPixmap(50,170,364,140,g_hHeroSkill1,0,0,364,140);
        break;

    case ACTION_TYPE_CRITICAL:  //暴击，恩赐解脱
//        SelectObject(g_bufdc,g_hHeroSkill3);
//        TransparentBlt(g_mdc,20,60,574,306,g_bufdc,0,0,574,306,RGB(0,0,0));//TransparentBlt函数的透明颜色设为RGB(0,0,0)
        //painter.drawPixmap(20,60,574,306,g_hHeroSkill3,0,0,574,306);
        break;

    case ACTION_TYPE_MAGIC:  //魔法攻击，烈火剑法
//        SelectObject(g_bufdc,g_hHeroSkill2);
//        TransparentBlt(g_mdc,50,100,374,288,g_bufdc,0,0,374,288,RGB(0,0,0));//TransparentBlt函数的透明颜色设为RGB(0,0,0)
        //painter.drawPixmap(50,100,374,288,g_hHeroSkill2,0,0,374,288);
        break;

    case ACTION_TYPE_RECOVER:   //恢复，气疗术
//        SelectObject(g_bufdc,g_hRecoverSkill);
//        TransparentBlt(g_mdc,560,170,150,150,g_bufdc,0,0,150,150,RGB(0,0,0));//TransparentBlt函数的透明颜色设为RGB(0,0,0)
        //painter.drawPixmap(560,170,150,150,g_hRecoverSkill,0,0,150,150);
        break;
    default:
        break;
    }
}

//-----------------------------------【BossAction_Logic( )函数】-------------------------------
//	描述：Boss动作逻辑判断函数
//--------------------------------------------------------------------------------------------------
void BattleScene::BossAction_Logic()
{
    srand((unsigned)time(NULL));      //用系统时间初始化随机种子
    if(Boss.NowHp > (Boss.MaxHp/2))				//生命值大于1/2时
    {
        switch(rand()%3)
        {
        case 0:						//释放普通攻击“幽冥鬼火”
            BossActionType = ACTION_TYPE_NORMAL;
            break;
        case 1:						//释放致命一击
            BossActionType = ACTION_TYPE_CRITICAL;
            break;
        case 2:						//使用嗜血咒
            BossActionType = ACTION_TYPE_MAGIC;
            break;
        }
    }
    else								//生命值小于1/2时
    {
        switch(rand()%3)
        {
        case 0:						//释放嗜血咒
            BossActionType = ACTION_TYPE_MAGIC;
            break;
        case 1:						//释放致命一击
            BossActionType = ACTION_TYPE_CRITICAL;
            break;
        case 2:						//使用梅肯斯姆回复
            BossActionType = ACTION_TYPE_RECOVER;
            break;
        }
    }
}

//-----------------------------------【BossAction_Paint( )函数】-------------------------------
//	描述：Boss动作贴图函数
//--------------------------------------------------------------------------------------------------
void		BattleScene::BossAction_Paint()
{

    int damage=0,recover=0;
    wchar_t str[100];

    switch(BossActionType)
    {
    case ACTION_TYPE_NORMAL:							//释放普通攻击“幽冥鬼火”
//        SelectObject(g_bufdc,g_hBossSkill1);
//        TransparentBlt(g_mdc,500,150,234,188,g_bufdc,0,0,234,188,RGB(0,0,0));//TransparentBlt函数的透明颜色设为RGB(0,0,0)
        //painter.drawPixmap(500,150,234,188,g_hBossSkill1,0,0,234,188);
        //第30个画面时计算玩家受伤害程度并加入显示消息
        if(g_iFrameNum == 30)
        {
            damage = rand()%Boss.Agility+ Boss.Level*Boss.Strength;
            Hero.NowHp -= (int)damage;

            swprintf_s(str,L"黄金魔龙君释放幽冥鬼火...对玩家照成【 %d】 点伤害",damage);
            Message_Insert(str);

            Die_Check(Hero.NowHp,true);
        }
        break;

    case ACTION_TYPE_MAGIC:							//释放嗜血咒
//        SelectObject(g_bufdc,g_hBossSkill2);
//        TransparentBlt(g_mdc,450,150,387,254,g_bufdc,0,0,387,254,RGB(0,0,0));//TransparentBlt函数的透明颜色设为RGB(0,0,0)
        //painter.drawPixmap(450,150,387,254,g_hBossSkill2,0,0,387,254);
        //第30个画面时计算玩家受伤害程度并加入显示消息
        if(g_iFrameNum == 30)
        {
            damage = 2*(2*(rand()%Boss.Agility) + Boss.Strength*Boss.Intelligence);  //嗜血咒的伤害值计算
            Hero.NowHp -= damage;	   //让英雄血量减掉一个计算出来的伤害值
            recover	=(int)((float)damage*0.2f);   //吸血量20%
            Boss.NowHp+=recover;   //怪物恢复吸到的血量
            swprintf_s(str,L"黄金魔龙君释放嗜血咒...对玩家照成【 %d 】点伤害,自身恢复【%d】点生命值",damage,recover);   //将数字格式化到文字中
            Message_Insert(str);   //插入文字消息

            Die_Check(Hero.NowHp,true);
        }
        break;

    case ACTION_TYPE_CRITICAL:							//释放致命一击
//        SelectObject(g_bufdc,g_hBossSkill3);
//        TransparentBlt(g_mdc,280,100,574,306,g_bufdc,0,0,574,306,RGB(0,0,0));//TransparentBlt函数的透明颜色设为RGB(0,0,0)
        //painter.drawPixmap(280,100,574,306,g_hBossSkill3,0,0,574,306);
        //第30个画面时计算玩家受伤害程度并加入显示消息
        if(g_iFrameNum == 30)
        {
            damage = 2*(rand()%Boss.Agility+ Boss.Level*Boss.Strength);
            Hero.NowHp -= (int)damage;

            swprintf_s(str,L"黄金魔龙君致命一击...对玩家照成【%d】点伤害.",damage);
            Message_Insert(str);

            Die_Check(Hero.NowHp,true);
        }
        break;

    case ACTION_TYPE_RECOVER:							//使用梅肯斯姆补血
//        SelectObject(g_bufdc,g_hRecoverSkill);
//        TransparentBlt(g_mdc,150,150,150,150,g_bufdc,0,0,150,150,RGB(0,0,0));//TransparentBlt函数的透明颜色设为RGB(0,0,0)
        //painter.drawPixmap(150,150,150,150,g_hRecoverSkill,0,0,150,150);
        //第30个画面时怪物回复生命值并加入显示消息
        if(g_iFrameNum == 30)
        {
                recover= 2*Boss.Intelligence*Boss.Intelligence;
                Boss.NowHp +=recover;
            swprintf_s(str,L"黄金魔龙君使用梅肯斯姆...恢复了【%d】点生命值",recover);
            Message_Insert(str);
        }
        break;
    default:
        break;
    }
}
/*
//-----------------------------------【Snow_Paint( )函数】--------------------------------------
//	描述：封装了雪花飞舞粒子效果的函数，模拟下雪场景
//--------------------------------------------------------------------------------------------------
void BattleScene::Snow_Paint()
{

    //创建粒子
    if(g_SnowNum< PARTICLE_NUMBER)  //当粒子数小于规定的粒子数时，便产生新的粒子，设定每个粒子的属性值
    {
        SnowFlowers[g_SnowNum].x = rand()%g_rect.right(); //将粒子的X坐标设为窗口中水平方向上的任意位置
        SnowFlowers[g_SnowNum].y = 0;    //将每个粒子的Y坐标都设为"0"，即从窗口上沿往下落
        SnowFlowers[g_SnowNum].exist = true; //设定粒子存在
        g_SnowNum++;   //每产生一个粒子后进行累加计数
    }

    //首先判断粒子是否存在，若存在，进行透明贴图操作
    for(int i=0;i<PARTICLE_NUMBER;i++)
    {
        if(SnowFlowers[i].exist)  //粒子还存在
        {
            //贴上粒子图
//            SelectObject(g_bufdc,g_hSnow);
//            TransparentBlt(g_mdc,SnowFlowers[i].x,SnowFlowers[i].y,30,30,g_bufdc,0,0,30,30,RGB(0,0,0));
            //painter.drawPixmap(SnowFlowers[i].x,SnowFlowers[i].y,30,30,g_hSnow,0,0,30,30);
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
*/

void BattleScene::on_pushButton_clicked()
{
    Map* map=new Map;
    map->show();
    this->close();
}
