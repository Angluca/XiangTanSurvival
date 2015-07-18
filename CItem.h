#ifndef CITEM_H
#define CITEM_H
#include <string>


class CItem
{
public:
	//constructor and destructor
	CItem(void);
	CItem(char*,int,int,int,int);	//buyItem
	~CItem(void);
public:
	//m_szName
	void 	SetName(char* buf){ m_strName=buf; }
	const char*	GetName(){return m_strName.c_str();}
	//m_nPrice
	void 	SetPrice(unsigned int n){m_nPrice=n;}
	unsigned int GetPrice(){return m_nPrice;}
	//m_nNum
	void	SetNum(unsigned int n){m_nNum=n;}
	unsigned int GetNum(){return m_nNum;}
	void	AddNum(int n){m_nNum+=n;}
	void	SubNum(int n){n<m_nNum?m_nNum-=n:m_nNum=0;}
	//m_lTotalPrice
	long	GetTotalPrice(){return m_lTotalPrice=m_nPrice*m_nNum;}
	//m_nLow/HigPrice
	void	SetRandPrice(unsigned int low,unsigned int hig){
		m_nLowPrice=low,m_nHigPrice=hig;
		m_nMidPrice=m_nHigPrice/2+m_nLowPrice;
		m_nMlwPrice=m_nMidPrice/2+m_nLowPrice;} //设置物品最低/最高价
	unsigned int GetLowPrice(){return m_nLowPrice;}
	unsigned int GetHigPrice(){return m_nHigPrice;}
	unsigned int GetMidPrice(){return m_nMidPrice;}
	unsigned int GetMlwPrice(){return m_nMlwPrice;}
	//method
	unsigned int GetRandPrice();	//随机生成物品普通价
	unsigned int GetRandHighPrice();//随机生成物品高峰价
	unsigned int GetRandLowPrice();//随机生成物品低峰价

protected:
	std::string	m_strName;	//物品名
	unsigned int m_nPrice;	//物品单价
	unsigned int m_nNum;	//数量
	long	m_lTotalPrice;	//合计价值=单价*数量
	unsigned int m_nHigPrice;	//产品最高价
	unsigned int m_nMidPrice;	//产品平价
	unsigned int m_nMlwPrice;	//产品低峰价
	unsigned int m_nLowPrice;	//产品最低价
};

#endif
