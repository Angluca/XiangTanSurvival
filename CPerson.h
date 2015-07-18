#ifndef CPERSON_H
#define CPERSON_H
#include <vector>


class CPerson
{
	enum{_MAXSIZE=200,_MAXHP=100,_HPMMIN=3000,_HPMMAX=10000};
public:
	//constructor and destructor
	CPerson(void);
	~CPerson(void);
public:
	typedef std::vector<char *> VecMenu;
	//====属性方法====
	//m_nHealth
	void	SetHealth(int &h){m_nHealth=h;}
	int		GetHealth(){return m_nHealth;}
	void	AddHealth(int &h){m_nHealth+=h;}
	void	SubHealth(int &h){m_nHealth-=h;}
	int		GetLoseHealth(){return _MAXHP-m_nHealth;}
	int 	RandHPMoney(){m_nHPMoney=rand()%(_HPMMAX-_HPMMIN)+_HPMMIN;
	return m_nHPMoney*GetLoseHealth();}	//返回需要治疗的金额
	int		GetHPMoney(){return m_nHPMoney;}
	bool	cure(int &m){	//需要治疗几点健康
			long t=m*m_nHPMoney;
			m_lMoney-=t;
			AddHealth(m);
	}
	//m_nHonor
	void 	SetHonor(int &h){m_nHonor=h;}
	int 	GetHonor(){return m_nHonor;}
	//m_lMoney
	void	SetMoney(long &m){m_lMoney=m;}
	long	GetMoney(){return m_lMoney;}
	void	AddMoney(long &m){m_lMoney+=m;}
	void	SubMoney(long &m)
			{
				if((m_lMoney-=m)<0){
					m_lArrear-=m_lMoney;
					m_lMoney=0;
				}
			}
	//m_lSaving
	void 	SetSaving(long &m){m_lSaving=m;}
	long	GetSaving(){return m_lSaving;}
	void	AddSaving(long &m){m_lSaving+=m;}
	void	SubSaving(long &m){m_lSaving-=m;}
	//m_lArrear
	void	SetArrear(long &m){m_lArrear=m;}
	long	GetArrear(){return m_lArrear;}
	void	AddArrear(long &m){m_lArrear+=m;}
	void	SubArrear(long &m){m_lArrear-=m;}
	void	ArrearPlus(){m_lArrear+=m_lArrear/10;}	//10%高利带 简化所以没有用浮点
	//m_lTotalMoney
	long	GetTotalMoney(){return m_lTotalMoney=m_lMoney+m_lSaving-m_lArrear;}
	//m_vecMenu
	void 	PushString(char * str){m_vecMenu.push_back(str),m_nSize=m_vecMenu.size();}
	void 	PopString(){m_vecMenu.pop_back(),m_nSize=m_vecMenu.size();}
	char*	GetVecString(int num){return m_vecMenu.at(num);}
	VecMenu	RetVec(){return m_vecMenu;}
	char*	GetBuf(){return m_szBuf;}	//返回屏幕缓存
	int		GetSize(){return m_nSize;}
public:
	//method
	void	Init();
	void	UnInit();
	bool	Updatebuf();	//显示缓存更新
	void	Draw();

private:
	//状态属性
	VecMenu	m_vecMenu;	//存储属性字符串
	int		m_nHealth;	//健康
	int		m_nHPMoney; //1点健康需要的金钱
	int		m_nHonor;	//声望
	int		m_nSize;
	long	m_lMoney;	//随身金钱
	long	m_lSaving;	//存款
	long	m_lArrear;	//欠债
	long	m_lTotalMoney;	//金钱总值
private:
	char	m_szBuf[_MAXSIZE];
};

#endif

