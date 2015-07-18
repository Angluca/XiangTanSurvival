#ifndef CCOMMUNITY_H
#define CCOMMUNITY_H
#include "CPerson.h"
#include "CMyMenu.h"
#include "CMyMaps.h"
#include "CItem.h"
#include <windows.h>
#include <list>
#include <conio.h>

#define __CONSOLE	//�ڷǿ���̨����ע�͵�
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

	inline int		CheckTotalItemNum(){return m_nMaxNum-m_nTotalItemNum;}	//����ʣ��ռ�

	int		AddTotalItemNum(int n)	//���ӵ����Ʒ������
	{ m_nTotalItemNum+=n; if(m_nTotalItemNum>m_nMaxNum) m_nTotalItemNum=m_nMaxNum;
		else if(m_nTotalItemNum<0) m_nTotalItemNum=0; }
	int		SubTotalItemNum(int n)	//����ӵ����Ʒ������
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
	void	ReleaseItems(){m_vecItems.clear();}	//�ͷ�������Ʒ
	void	InitItems();
	void	UpdateItem();
	void	UpdateBuf();
	bool	MoveCursorBuy(bool);
	bool	MoveCursorSell(bool);
	bool	RandSetSellItems();

	void	RandMidPrice(){if(!m_listSellItem.empty())
	for_each(m_listSellItem.begin(),m_listSellItem.end(),
			std::mem_fun_ref(&CItem::GetRandPrice));	//����г��۸�,������
	}
	void	RandLowPrice(){if(!m_listSellItem.empty())
	for_each(m_listSellItem.begin(),m_listSellItem.end(),
			std::mem_fun_ref(&CItem::GetRandLowPrice));	//����г��۸�
	}
	void	RandHigPrice(){if(!m_listSellItem.empty())
	for_each(m_listSellItem.begin(),m_listSellItem.end(),
			std::mem_fun_ref(&CItem::GetRandHighPrice));	//����г��۸�
	}
public:
	void	UpdatePlace();
public:
	//method
	void 	Init();		//�Զ����ʼ��
	void	UnInit();	//�Զ���ж��
	void	Update();	//���ݸ���
	void	Draw();		//��Ī��ʾ
public:
	//��ֲ�ú���
	//��ʼ������ ��Ʒ�鶨��
	void	PushItem(char* str,int Min,int Max){	//����һ����Ʒ
	m_vecItems.push_back( CItem(str,0,0,Min,Max));
	}
	void	PushItem(CItem & c){
	m_vecItems.push_back(c);
	}
	void	PopItem(){		//ȥ��һ����Ʒ
		if(!m_vecItems.empty())m_vecItems.pop_back();
	}
	//Items
	bool	buyItem(int);
	bool	sellItem(int);
	//m_MyMenu m_MyMaps
	bool	SaveMoney(long &m){				//���д�Ǯ
		if(m<=0)	return false;
		long tm=m_Person.GetMoney();
		if(m>tm) m=tm;
		m_Person.AddSaving(m);
		m_Person.SubMoney(m);
		return true;
	}
	bool	GetMoney(long &m=99999999){		//����ȡǮ
		if(m<=0) return false;
		long  tm=m_Person.GetSaving();
		if(m>tm) m=tm;
		m_Person.SubSaving(m);
		m_Person.AddMoney(m);
		return true;
	}
	bool	SubArrear(long &m=99999999){	//��ծ
		if(m<=0) return false;
		long  tm=m_Person.GetArrear();
		if(m>tm) m=tm;
		m_Person.SubArrear(m);
		m_Person.SubMoney(m);
		return true;
	}
	int		GetAllHPMoney(){return m_Person.RandHPMoney();}	//ҽ�Ʒ����ܹ���Ҫ����
	bool	CureHealth(int &m=100){		//���ƽ���
		if(m_Person.GetMoney()==0 || m<=0)	return false;
		int loseHp=m_Person.GetLoseHealth();
		if(loseHp>=_MAXHP) return false;
		int hpm=m_Person.GetHPMoney();
		int cancure=m_Person.GetMoney()/hpm;
		if(cancure<=0) return false;
		else if( loseHp<cancure) cancure=loseHp;
		if(m>cancure) m=cancure;
		m_Person.cure(m);}
	long	RetHouseMoney(){return m_nHouseMoney=rand()% (_HOUSEMAX-_HOUSEMIN)+_HOUSEMIN;}	//���ط������
	bool	leaseHouse(){			//��ȡ����
		long tm=m_Person.GetMoney();
		if(tm<m_nHouseMoney)	return false;
		else	m_Person.SubMoney(m_nHouseMoney);
		MaxNumPlus();
		return true;
	}
	int 	RandAddMoney(){long r=rand()%50+2; m_Person.AddMoney(r); return r;}	//��������õ���Ǯ
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
	std::string		m_tmpBuf;	//����������Ʒ���ַ���
	std::string 	m_strBuf;	//��Ļ��ʾ�ַ���
	std::string		m_strEvent;	//�¼�����
private:
	CPerson m_Person;
	CMyMenu	m_MyMenu;
	CMyMaps m_MyMaps;

	vecItems	m_vecItems;
	listItems	m_listBuyItem;
	listItems	m_listSellItem;

	int		m_nToday;	//����
	int		m_nMaxDay;	//����
	int 	m_nGroup;	//������ĸ�����(�г�/�ֿ�)
	int		m_nGroupMenu;	//�������(�˵�/��ͼ)
	int 	m_nBuyPos;	//����Ʒ���λ��
	int 	m_nSellPos;	//������Ʒ���λ��
	int		m_nMaxNum;	//���������װ���ٻ���
	int		m_nTotalItemNum;	//���л�������
	int		m_nKey;		//����ֵ
	long	m_nHouseMoney;	//�������
	int		m_nEvent;	//�¼����
	HANDLE	m_hOut;
};

#endif
