#include <windows.h>
#include "CMyMenu.h"


CMyMenu::CMyMenu(void)
{
	m_nPosition=0;
	m_vecMenu.clear();
	m_nKey=0;
	m_bGroup=true;
	memset(m_szBuf,0,_MAXSIZE);
}
CMyMenu::~CMyMenu(void)
{
}

void CMyMenu::Init()	//�Զ����ʼ��
{
	m_vecMenu.push_back("����");
	m_vecMenu.push_back("ҽԺ");
	m_vecMenu.push_back("�ʾ�");
	m_vecMenu.push_back("�����н�");
	m_vecMenu.push_back("����");
	m_nSize = m_vecMenu.size();
}
void CMyMenu::UnInit()	//�Զ���ж��
{
	m_vecMenu.clear();
	m_nSize=0;
}

int CMyMenu::MoveCursor(int b)	//�ƶ��˵����λ��
{
	if(m_vecMenu.empty())
	{
		::MessageBox(NULL,"Menu string is NULL\n",0,0);
		return 0;
	}
	int num=m_vecMenu.size()-1;
	if(b)
	{
		if(m_nPosition >= num) m_nPosition=num;
		else	++m_nPosition;
	}
	else
	{
		if(m_nPosition <= 0) m_nPosition=0;
		else	--m_nPosition;
	}
	return m_nPosition;
}
void	CMyMenu::Update()	//���ݸ��º���
{
	//ȷ���ڸ�����
	if(_UP==m_nKey)	m_bGroup=true;
	else if(_DOWN==m_nKey) m_bGroup=false;
	if(m_bGroup)
	{
		//������ƶ���� left0 right1
		if(_LEFT == m_nKey)	MoveCursor(0);
		else if(_RIGHT==m_nKey) MoveCursor(1);
	}
	m_nKey=0;	//�ͷŰ���
}

bool	CMyMenu::Updatebuf()
{
	char* tbuf= "\n==================================================\\\n" ;
	char buf[_MAXSIZE]="=[menu]==========================================================/\n";
	for(int i=0;i<m_nSize;++i)
	{
		char tbuf2[50]={0};
		if(m_nPosition==i && m_bGroup)
			sprintf(tbuf2," *%s",m_vecMenu.at(i));
		else	sprintf(tbuf2,"  %s",m_vecMenu.at(i));
		strcat(buf,tbuf2);
	}
	strcat(buf,tbuf);
	strcpy(m_szBuf,buf);
	return true;
}

void	CMyMenu::Draw()		//��Ļ��ʾ
{
	//printf("==============================================\n");
	//for(int i=0;i<m_nSize;++i)
	//{
		//if(m_nPosition==i && m_bGroup)
			//printf(" *%s",m_vecMenu.at(i));
		//else	printf("  %s",m_vecMenu.at(i));
	//}
	//printf("\n==============================================\n");
	Updatebuf();
	printf(m_szBuf);
}

void CMyMenu::testprint(int key)	//���������ú���,��ʵ��
{
	SetKey(key);
	Update();
	Draw();
}
