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
	virtual void	Init();	//自定义初始化
	virtual void	UnInit();	//自定义卸载
	virtual int 	MoveCursor(int);	//光标移动
	virtual void	Update();	//数据更新
	virtual bool	Updatebuf();	//显示缓存更新
	virtual void	Draw();		//屏幕显示
	virtual char*	GetBuf(){return m_szBuf;}	//返回屏幕缓存
public:
	//test func
	void 	testprint(int);
protected:
	VecMenu	m_vecMenu;	//存储菜单字符串
	int		m_nSize;	//m_vecMenu中储存元素的个数
	int		m_nPosition; //光标位置
	bool	m_bGroup;	//是否在当前区域
	int		m_nKey;		//按键设置
private:
	char	m_szBuf[_MAXSIZE];
};

#endif

