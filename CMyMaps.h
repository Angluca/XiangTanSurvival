#ifndef CMYMAPS_H
#define CMYMAPS_H
#include "CMymenu.h"


class CMyMaps : public CMyMenu
{
	enum{_LEFT=0x4B,_RIGHT=0x4D,_UP=0x48,_DOWN=0x50,_MAXSIZE=200,_LINES=5};

public:
	//constructor and destructor
	CMyMaps(void);
	virtual ~CMyMaps(void);
public:
	//method
	virtual void	Init();	//�Զ����ʼ��
	virtual void	UnInit();	//�Զ���ж��
	virtual int 	MoveCursor(int);	//����ƶ�
	virtual void	Update();	//���ݸ���
	virtual bool	Updatebuf();	//��ʾ�������
	virtual void	Draw();		//��Ļ��ʾ
	virtual char*	GetBuf(){return m_szBuf;}	//������Ļ����

protected:
/*	�̳г�Ա
	typedef std::vector<char *> VecMenu;
	VecMenu	m_vecMenu;	//�˵��ַ�������
	int		m_nSize;	//m_vecMenu�д���Ԫ�صĸ���
	int		m_nPosition; //���λ��
	bool	m_bGroup;	//�Ƿ��ڵ�ǰ����
	int		m_nKey;		//��������
*/
private:
	char	m_szBuf[_MAXSIZE];
};



#endif
