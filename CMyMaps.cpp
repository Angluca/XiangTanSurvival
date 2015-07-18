#include <windows.h>
#include "CMyMaps.h"



//constructor
CMyMaps::CMyMaps(void)
{
	m_bGroup=false;
	m_vecMenu.clear();
	memset(m_szBuf,0,_MAXSIZE);
}

//destructor
CMyMaps::~CMyMaps(void)
{
}
void	CMyMaps::Init()	//�Զ����ʼ��
{
	m_vecMenu.push_back("��վ");
	m_vecMenu.push_back("����Ӫ");
	m_vecMenu.push_back("�����");
	m_vecMenu.push_back("��ɽ·");
	m_vecMenu.push_back("����·��");
	m_vecMenu.push_back("������");
	m_vecMenu.push_back("��ʯ��԰");
	m_vecMenu.push_back("������");
	m_vecMenu.push_back("��ɽ·");
	m_nSize = m_vecMenu.size();
}
void	CMyMaps::UnInit()	//�Զ���ж��
{
	m_vecMenu.clear();
	m_nSize=0;
}
int 	CMyMaps::MoveCursor(int d)	//����ƶ�
{
	if(m_vecMenu.empty())
	{
		::MessageBox(NULL,"Maps string is NULL\n",0,0);
		return 0;
	}
	int num=m_vecMenu.size()-1;
	if(d)
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
void	CMyMaps::Update()	//���ݸ���
{
	//ȷ���ڸ�����
	if(_UP==m_nKey)	m_bGroup=false;
	else if(_DOWN==m_nKey) m_bGroup=true;
	if(m_bGroup)
	{
		//������ƶ���� left0 right1
		if(_LEFT == m_nKey)	MoveCursor(0);
		else if(_RIGHT==m_nKey) MoveCursor(1);
	}
	m_nKey=0;	//�ͷŰ���
}
bool	CMyMaps::Updatebuf()	//��ʾ�������
{
	int head=m_nPosition-_LINES,end=_LINES;
	if(head<=0)	head=0;
	else	end+=head;
	char* tbuf= "\n=====================================================\n" ;
	char buf[_MAXSIZE]="=[maps]===========================================/\n";
	for(int i=head;i<=end;++i)
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
void	CMyMaps::Draw()		//��Ļ��ʾ
{
	Updatebuf();
	printf(m_szBuf);
}

