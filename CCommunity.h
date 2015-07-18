#ifndef CCOMMUNITY_H
#define CCOMMUNITY_H
#include "CPerson.h"
#include "CMyMenu.h"
#include "CMyMaps.h"
#include "CItem.h"
#include <windows.h>
#include <list>
#include <conio.h>

#define __CONSOLE	//在非控制台下请注释掉
#define _EVENT00	1000
#define _EVENT01	1001
#define _EVENT02	1002
#define _EVENT03	1003
#define _EVENT04	1004
#define _EVENTMAX	1005

class CCommunity
{
	class FindString
	{
	public:
		FindString(std::string a){str=a;}
		bool operator()(CItem &c){
			if(str==c.GetName()) return true;
			else	return false;}
	private:
		std::string str;
	};
	enum{_LEFT=0x61,_RIGHT=0x64,_UP=0x77,_DOWN=0x73,_MAXHP=100,
		 _LINES=6,_SELLGROUP=1,_BUYGROUP=2,_MENU=3,_MAPS=4,_ROW=4,_COL=22,
		_HOUSEMIN=10000,_HOUSEMAX=50000000};
	typedef std::vector<CItem> vecItems;
	typedef std::list<CItem> listItems;
	typedef std::list<CItem>::iterator listItemPos;
public:
	//constructor and destructor
	CCommunity(void);
	~CCommunity(void);
public:
	//message
	void	PrtMessage(char* str,int x=_ROW,int y=_COL){
			COORD cc={x,y};
			WriteConsoleOutputCharacter(m_hOut,str,strlen(str)+1,cc,0);
	}
	//m_nMaxNum
	void	SetMaxNum(int n){m_nMaxNum=n;}
	int		GetMaxNum(){return m_nMaxNum;}
	void	AddMaxNum(int n){m_nMaxNum+=n;}
	void	MaxNumPlus(){m_nMaxNum+=10;}

	inline int		CheckTotalItemNum(){return m_nMaxNum-m_nTotalItemNum;}	//返回剩余空间

	int		AddTotalItemNum(int n)	//添加拥有物品总数量
	{ m_nTotalItemNum+=n; if(m_nTotalItemNum>m_nMaxNum) m_nTotalItemNum=m_nMaxNum;
		else if(m_nTotalItemNum<0) m_nTotalItemNum=0; }
	int		SubTotalItemNum(int n)	//削减拥有物品总数量
	{ m_nTotalItemNum-=n; if(m_nTotalItemNum>m_nMaxNum) m_nTotalItemNum=m_nMaxNum;
		else if(m_nTotalItemNum<0) m_nTotalItemNum=0; }

	const char* GetBuf(){return m_strBuf.c_str();}
	//m_nKey
	void	SetKey(int k){m_nKey=k;}
	int		GetKey(){return m_nKey;}
	void	SetDay(int d){m_nToday=d;}
	int		GetDay(){return m_nToday;}
	void	DayPlus(){++m_nToday;}
public:
	//perform Items
	void	ReleaseItems(){m_vecItems.clear();}	//释放所有物品
	void	InitItems();
	void	UpdateItem();
	void	UpdateBuf();
	bool	MoveCursorBuy(bool);
	bool	MoveCursorSell(bool);
	bool	RandSetSellItems();

	void	RandMidPrice(){if(!m_listSellItem.empty())
	for_each(m_listSellItem.begin(),m_listSellItem.end(),
			std::mem_fun_ref(&CItem::GetRandPrice));	//随机市场价格,仅卖方
	}
	void	RandLowPrice(){if(!m_listSellItem.empty())
	for_each(m_listSellItem.begin(),m_listSellItem.end(),
			std::mem_fun_ref(&CItem::GetRandLowPrice));	//随机市场价格
	}
	void	RandHigPrice(){if(!m_listSellItem.empty())
	for_each(m_listSellItem.begin(),m_listSellItem.end(),
			std::mem_fun_ref(&CItem::GetRandHighPrice));	//随机市场价格
	}
public:
	void	UpdatePlace();
public:
	//method
	void 	Init();		//自定义初始化
	void	UnInit();	//自定义卸载
	void	Update();	//数据更新
	void	Draw();		//屏莫显示
public:
	//移植用函数
	//初始化操作 物品组定义
	void	PushItem(char* str,int Min,int Max){	//增加一个物品
	m_vecItems.push_back( CItem(str,0,0,Min,Max));
	}
	void	PushItem(CItem & c){
	m_vecItems.push_back(c);
	}
	void	PopItem(){		//去掉一个物品
		if(!m_vecItems.empty())m_vecItems.pop_back();
	}
	//Items
	bool	buyItem(int);
	bool	sellItem(int);
	//m_MyMenu m_MyMaps
	bool	SaveMoney(long &m){				//银行存钱
		if(m<=0)	return false;
		long tm=m_Person.GetMoney();
		if(m>tm) m=tm;
		m_Person.AddSaving(m);
		m_Person.SubMoney(m);
		return true;
	}
	bool	GetMoney(long &m=99999999){		//银行取钱
		if(m<=0) return false;
		long  tm=m_Person.GetSaving();
		if(m>tm) m=tm;
		m_Person.SubSaving(m);
		m_Person.AddMoney(m);
		return true;
	}
	bool	SubArrear(long &m=99999999){	//还债
		if(m<=0) return false;
		long  tm=m_Person.GetArrear();
		if(m>tm) m=tm;
		m_Person.SubArrear(m);
		m_Person.SubMoney(m);
		return true;
	}
	int		GetAllHPMoney(){return m_Person.RandHPMoney();}	//医疗费用总共需要多少
	bool	CureHealth(int &m=100){		//治疗健康
		if(m_Person.GetMoney()==0 || m<=0)	return false;
		int loseHp=m_Person.GetLoseHealth();
		if(loseHp>=_MAXHP) return false;
		int hpm=m_Person.GetHPMoney();
		int cancure=m_Person.GetMoney()/hpm;
		if(cancure<=0) return false;
		else if( loseHp<cancure) cancure=loseHp;
		if(m>cancure) m=cancure;
		m_Person.cure(m);}
	long	RetHouseMoney(){return m_nHouseMoney=rand()% (_HOUSEMAX-_HOUSEMIN)+_HOUSEMIN;}	//返回房子租金
	bool	leaseHouse(){			//租取房屋
		long tm=m_Person.GetMoney();
		if(tm<m_nHouseMoney)	return false;
		else	m_Person.SubMoney(m_nHouseMoney);
		MaxNumPlus();
		return true;
	}
	int 	RandAddMoney(){long r=rand()%50+2; m_Person.AddMoney(r); return r;}	//上网随机得到金钱
	int		RandSubHP(){int r=rand()%6+1; m_Person.SubHealth(r);return r;}
	int		RandAddHP(){if(m_Person.GetHealth()>=_MAXHP) return 0;int r=rand()%6+1; m_Person.AddHealth(r);return r;}
	int		RandEvent(){return m_nEvent=rand()%(_EVENT00-_EVENTMAX)+_EVENT00;}
	int		RandArrear(){int m=m_Person.GetMoney();int r=rand()%m/2+m/5;}
	bool	isEnd(){return m_nToday>=m_nMaxDay;}
	void	EventPerform();

public:
	//test print
	void	run();
	void	testprintf(int);
private:
	std::string		m_tmpBuf;	//排序买卖物品的字符串
	std::string 	m_strBuf;	//屏幕显示字符串
	std::string		m_strEvent;	//事件内容
private:
	CPerson m_Person;
	CMyMenu	m_MyMenu;
	CMyMaps m_MyMaps;

	vecItems	m_vecItems;
	listItems	m_listBuyItem;
	listItems	m_listSellItem;

	int		m_nToday;	//天数
	int		m_nMaxDay;	//期限
	int 	m_nGroup;	//光标在哪个区域(市场/仓库)
	int		m_nGroupMenu;	//光标区域(菜单/地图)
	int 	m_nBuyPos;	//买方物品光标位置
	int 	m_nSellPos;	//卖方物品光标位置
	int		m_nMaxNum;	//房间最大能装多少货物
	int		m_nTotalItemNum;	//以有货物数量
	int		m_nKey;		//按键值
	long	m_nHouseMoney;	//房屋租金
	int		m_nEvent;	//事件编号
	HANDLE	m_hOut;
};

#endif
