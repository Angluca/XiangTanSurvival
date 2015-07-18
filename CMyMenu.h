#ifndef CMYMENU_H
#define CMYMENU_H
#include <vector>


class CMyMenu
{
	enum{_LEFT=0x4b,_UP=0x48,_RIGHT=0x4D,_DOWN=0x50,_MAXSIZE=200};
public:
	//constructor and destructor
	CMyMenu(void);
	virtual ~CMyMenu(void);
public:
	typedef std::vector<char *> VecMenu;
	//m_bGroup
	void 	SetGroup(bool b){m_bGroup=b;}
	bool 	GetGroup(){return m_bGroup;}
	//m_nPosition
	int 	SetPosition(int &pos){return m_nPosition=pos;}
	int 	GetPosition(){return m_nPosition;}
	//m_nKey
	void 	SetKey(int k){m_nKey=k;}
	int 	GetKey(){return m_nKey;}
	void	ReleaseKey(){m_nKey=0;}
	//m_nSize
	int		GetSize(){return m_vecMenu.size();}
	//m_vecMenu
	void 	PushString(char * str){m_vecMenu.push_back(str),m_nSize=m_vecMenu.size();}
	void 	PopString(){m_vecMenu.pop_back(),m_nSize=m_vecMenu.size();}
	char*	GetVecString(int num){return m_vecMenu.at(num);}
	VecMenu	RetVec(){return m_vecMenu;}
public:
	//method
	virtual void	Init();	//�Զ����ʼ��
	virtual void	UnInit();	//�Զ���ж��
	virtual int 	MoveCursor(int);	//����ƶ�
	virtual void	Update();	//���ݸ���
	virtual bool	Updatebuf();	//��ʾ�������
	virtual void	Draw();		//��Ļ��ʾ
	virtual char*	GetBuf(){return m_szBuf;}	//������Ļ����
public:
	//test func
	void 	testprint(int);
protected:
	VecMenu	m_vecMenu;	//�洢�˵��ַ���
	int		m_nSize;	//m_vecMenu�д���Ԫ�صĸ���
	int		m_nPosition; //���λ��
	bool	m_bGroup;	//�Ƿ��ڵ�ǰ����
	int		m_nKey;		//��������
private:
	char	m_szBuf[_MAXSIZE];
};

#endif

