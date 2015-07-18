#include "CItem.h"


//constructor
CItem::CItem(void)
{
	m_nPrice=1;
	m_nNum=0;
	m_lTotalPrice=0;
	m_nHigPrice=50;
	m_nMidPrice=30;
	m_nMlwPrice=20;
	m_nLowPrice=5;
	m_strName="";
	srand(time(0));
}
CItem::CItem(char* str,int price,int num,int lowprice=0,int higprice=0)	//物品名,单价,数量,最低价,最高价
{
	m_strName=str;
	m_nPrice=price;
	m_nNum=num;
	m_nLowPrice=lowprice;
	m_nHigPrice=higprice;
	SetRandPrice(lowprice,higprice);
	srand(time(0));
}

//destructor
CItem::~CItem(void)
{
}

unsigned int CItem::GetRandPrice()
{
	 m_nPrice=(rand()%(m_nMidPrice-m_nLowPrice))+m_nMlwPrice;
	 return m_nPrice;
}
unsigned int CItem::GetRandHighPrice()
{
	 m_nPrice=(rand()%(m_nHigPrice-m_nMidPrice))+m_nMidPrice;
	 return m_nPrice;
}
unsigned int CItem::GetRandLowPrice()
{
	 m_nPrice=(rand()%(m_nMlwPrice-m_nLowPrice))+m_nLowPrice;
	 return m_nPrice;
}
