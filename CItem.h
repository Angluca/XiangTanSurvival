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
		m_nMlwPrice=m_nMidPrice/2+m_nLowPrice;} //������Ʒ���/��߼�
	unsigned int GetLowPrice(){return m_nLowPrice;}
	unsigned int GetHigPrice(){return m_nHigPrice;}
	unsigned int GetMidPrice(){return m_nMidPrice;}
	unsigned int GetMlwPrice(){return m_nMlwPrice;}
	//method
	unsigned int GetRandPrice();	//���������Ʒ��ͨ��
	unsigned int GetRandHighPrice();//���������Ʒ�߷��
	unsigned int GetRandLowPrice();//���������Ʒ�ͷ��

protected:
	std::string	m_strName;	//��Ʒ��
	unsigned int m_nPrice;	//��Ʒ����
	unsigned int m_nNum;	//����
	long	m_lTotalPrice;	//�ϼƼ�ֵ=����*����
	unsigned int m_nHigPrice;	//��Ʒ��߼�
	unsigned int m_nMidPrice;	//��Ʒƽ��
	unsigned int m_nMlwPrice;	//��Ʒ�ͷ��
	unsigned int m_nLowPrice;	//��Ʒ��ͼ�
};

#endif
