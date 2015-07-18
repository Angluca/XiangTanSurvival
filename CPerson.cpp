#include <windows.h>
#include "CPerson.h"
#include <iostream>

//constructor
CPerson::CPerson(void)
{
	//m_nHealth=_MAXHP;
	m_nHealth=100;
	m_nHonor=100;
	m_lMoney=2000;
	m_lSaving=0;
	m_lArrear=5500;
	m_lTotalMoney=m_lMoney+m_lSaving-m_lArrear;
	m_nHPMoney=3000;
	memset(m_szBuf,0,_MAXSIZE);
}

//destructor
CPerson::~CPerson(void)
{
}

void	CPerson::Init()
{
	m_vecMenu.clear();
	m_vecMenu.push_back("½¡¿µ");
	m_vecMenu.push_back("ÉùÍû");
	m_vecMenu.push_back("½ðÇ®");
	m_vecMenu.push_back("´æ¿î");
	m_vecMenu.push_back("Ç·Õ®");
	m_nSize = m_vecMenu.size();
}

void	CPerson::UnInit()
{
	m_vecMenu.clear();
	m_nSize=0;
}

bool	CPerson::Updatebuf()
{
	char* tbuf= "\n=====================================================\n" ;
	char buf[_MAXSIZE]="=[status]============================================\n";
	char tbuf2[100]={0};
	sprintf(tbuf2,"  %s:%d  %s:%d\n  %s:%d  %s:%d  %s:%d",
			m_vecMenu.at(0),m_nHealth,m_vecMenu.at(1),m_nHonor,
			m_vecMenu.at(2),m_lMoney,m_vecMenu.at(3),m_lSaving,m_vecMenu.at(4),m_lArrear);
	strcat(buf,tbuf2);
	strcat(buf,tbuf);
	strcpy(m_szBuf,buf);
	return true;
}

void	CPerson::Draw()
{
	Updatebuf();
	printf(m_szBuf);
}

