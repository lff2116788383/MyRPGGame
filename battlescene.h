#ifndef BATTLESCENE_H
#define BATTLESCENE_H
#include <QPainter>
#include <QWidget>
#include <QToolButton>
#define PARTICLE_NUMBER	50							//表示粒子数量的宏，以方便修改粒子数量

//定义一个角色结构体
struct CHARACTER
{
    int		NowHp;		//当前生命值
    int		MaxHp;			//最大生命值
    int		NowMp;		//当前魔法值
    int		MaxMp;		//最大魔法值
    int		Level;			//角色等级
    int		Strength;		//角色力量值
    int		Intelligence; //角色智力值
    int		Agility;			//角色敏捷值

};

//定义一个雪花结构体
struct SNOW
{
    int x; //雪花的 X坐标
    int y; //雪花的Y坐标
    bool exist;  //雪花是否存在
};

//定义一个动作枚举体
enum ActionTypes
{
    ACTION_TYPE_NORMAL=0,		//普通攻击
    ACTION_TYPE_CRITICAL=1,		//致命一击
    ACTION_TYPE_MAGIC=2,		//魔法攻击
    ACTION_TYPE_MISS=3,			//攻击落空
    ACTION_TYPE_RECOVER=4,	//释放恢复魔法
};
namespace Ui {
class BattleScene;
}

class BattleScene : public QWidget
{
    Q_OBJECT

public:
    explicit BattleScene(QWidget *parent = nullptr);			//在此函数中进行资源的初始化
    ~BattleScene();                                          	//在此函数中进行资源的清理

    //-----------------------------------【全局变量声明部分】-------------------------------------
    //	描述：全局变量的声明
    //------------------------------------------------------------------------------------------------
    QRect				g_rect;				//定义一个RECT结构体，用于储存内部窗口区域的坐标
    int					g_iFrameNum,g_iTxtNum;  //帧数和文字数量
    wchar_t			text[8][100];  //存储着输出文字的字符串数组
    bool			g_bCanAttack=false,g_bGameOver=false;   //两个游戏状态标识，角色是否可以攻击，游戏是否结束
    SNOW			SnowFlowers[PARTICLE_NUMBER];   //雪花粒子数组
    int					g_SnowNum=0; //定义g_SnowNum用于雪花的计数
    CHARACTER	Hero,Boss;  //两个角色结构体实例，分别表示英雄和BOSS
    ActionTypes	HeroActionType,BossActionType;  //两个动作类型枚举实例，分别表示英雄和BOSS的动作类型
    //一系列位图句柄的定义
    QPixmap		g_hBackGround,g_hGameOver,g_hVictory,g_hSnow;  //背景，游戏结束，游戏胜利的位图句柄
    QPixmap		g_hMonsterBitmap,g_hHeroBitmap,g_hRecoverSkill;  //BOSS角色图，英雄角色图，恢复技能图的位图句柄
    QPixmap		g_hSkillButton1,g_hSkillButton2,g_hSkillButton3,g_hSkillButton4;  //4个技能按钮的位图句柄
    QPixmap 	g_hHeroSkill1,g_hHeroSkill2,g_hHeroSkill3;  //3个英雄技能效果的位图句柄
    QPixmap		g_hBossSkill1,g_hBossSkill2,g_hBossSkill3;  //3个BOSS技能效果的位图句柄

    QToolButton* skillbutton[4];

    //-----------------------------------【全局函数声明部分】-------------------------------------
    //	描述：全局函数声明，防止“未声明的标识”系列错误
    //------------------------------------------------------------------------------------------------

    void paintEvent(QPaintEvent *);               		        //在此函数中进行绘图代码的书写

    void							Die_Check(int NowHp,bool isHero);   //死亡检查函数
    void							Message_Insert(wchar_t* str);  //文字消息处理函数
    void							HeroAction_Logic();  //英雄动作逻辑判断函数
    void							HeroAction_Paint();  //英雄动作绘图函数
    void							BossAction_Logic(); //怪物动作逻辑判断函数
    void							BossAction_Paint(); //怪物动作绘图函数
    void							Snow_Paint();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BattleScene *ui;
};

#endif // BATTLESCENE_H
