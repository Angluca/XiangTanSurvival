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
	virtual void	Init();	//自定义初始化
	virtual void	UnInit();	//自定义卸载
	virtual int 	MoveCursor(int);	//光标移动
	virtual void	Update();	//数据更新
	virtual bool	Updatebuf();	//显示缓存更新
	virtual void	Draw();		//屏幕显示
	virtual char*	GetBuf(){return m_szBuf;}	//返回屏幕缓存

protected:
/*	继承成员
	typedef std::vector<char *> VecMenu;
	VecMenu	m_vecMenu;	//菜单字符串向量
	int		m_nSize;	//m_vecMenu中储存元素的个数
	int		m_nPosition; //光标位置
	bool	m_bGroup;	//是否在当前区域
	int		m_nKey;		//按键设置
*/
private:
	char	m_szBuf[_MAXSIZE];
};



#endif
