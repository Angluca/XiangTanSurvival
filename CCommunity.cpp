#include "CCommunity.h"
#include <windows.h>
#include <iostream>
#include <iterator>
#include <new>


//constructor
CCommunity::CCommunity(void)
{
	m_strBuf="";
	m_nBuyPos=0;
	m_nSellPos=0;
	m_nGroup=1;
	m_nGroupMenu=3;
	m_nMaxNum=100;
	m_nTotalItemNum=0;
	m_nKey=0;
	m_listBuyItem.clear();
	m_listSellItem.clear();
	m_tmpBuf="";
	m_nToday=0;
	m_nMaxDay=40;
	m_nHouseMoney=10000;
	m_nEvent=0;
	m_strEvent="";
	m_hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));
}

//destructor
CCommunity::~CCommunity(void)
{
	//TODO:Add your code here
}

void	CCommunity::InitItems()
{
	//物品名,单价(仅买方用),数量(仅买方),最低单价(卖方),最高单价(卖方)
	m_vecItems.clear();
	m_vecItems.push_back( CItem("进口香烟",0,0,30,800));
	m_vecItems.push_back( CItem("盗版VCD",0,0,1,200));
	m_vecItems.push_back( CItem("进口玩具",0,0,90,800));
	m_vecItems.push_back( CItem("水货手机",0,0,100,5000));
	m_vecItems.push_back( CItem("上床小宝贝",0,0,3000,120000));
	m_vecItems.push_back( CItem("走私汽车",0,0,5000,150000));
	m_vecItems.push_back( CItem("伪劣化妆品",0,0,30,600));
	m_vecItems.push_back( CItem("假白酒(工业酒精)",0,0,200,5000));
	m_vecItems.push_back( CItem("游戏点卡",0,0,10,500));
	m_vecItems.push_back( CItem("数码照像机",0,0,200,6000));
	m_vecItems.push_back( CItem("水货笔记本",0,0,1000,50000));
	m_vecItems.push_back( CItem("PSP掌上游戏机",0,0,1000,6000));
	m_vecItems.push_back( CItem("PSPUMD游戏光盘",0,0,50,900));
	m_vecItems.push_back( CItem("xbox360游戏机",0,0,200,5000));
	m_vecItems.push_back( CItem("Av光碟",0,0,5,1000));
	m_vecItems.push_back( CItem("槟榔",0,0,5,100));
	m_vecItems.push_back( CItem("软白烟",0,0,5,100));
	RandSetSellItems();
}
bool	CCommunity::MoveCursorBuy(bool b)
{
	if(m_listBuyItem.empty())	return false;
	int num=m_listBuyItem.size()-1;
	if(b) m_nBuyPos>=num?m_nBuyPos=num:++m_nBuyPos;
	else	m_nBuyPos<=0?m_nBuyPos=0:--m_nBuyPos;
	return true;
}
bool	CCommunity::MoveCursorSell(bool b)
{
	if(m_listSellItem.empty())	
	{
		MessageBox(NULL,"SellItems is null",0,0);
		return false;
	}
	int num=m_listSellItem.size()-1;
	if(b) m_nSellPos>=num?m_nSellPos=num:++m_nSellPos;
	else	m_nSellPos<=0?m_nSellPos=0:--m_nSellPos;
	return true;
}
bool	CCommunity::RandSetSellItems()
{
	if(m_vecItems.empty())
	{
		MessageBox(NULL,"Items is null!",0,0);
		return false;
	}
	m_listSellItem.clear();
	int	vecsize=m_vecItems.size();
	int midsize=vecsize/2;
	int rnd;		//显示多少商品
	if(m_nToday<(m_nMaxDay-1)) rnd=rand()%3-1+midsize;
	else rnd=vecsize;	//回家的最后一天市场显示全部商品
	rnd>vecsize?rnd=vecsize:0;
	int	tmpRnd=0;
	bool*	isChoose=new(std::nothrow) bool[vecsize];	//确认随机没物品不重复
	if(!isChoose) return false;
	memset(isChoose,0,vecsize);
	while(m_listSellItem.size()<rnd)	//随机装入市场需要显示的物品
	{
		tmpRnd=rand()%vecsize;
		if(isChoose[tmpRnd])	continue;
		m_listSellItem.push_back(m_vecItems.at(tmpRnd));
		isChoose[tmpRnd]=true;
	}
	delete isChoose;
	m_nSellPos=m_nBuyPos=0;
	for_each(m_listSellItem.begin(),m_listSellItem.end(),
			std::mem_fun_ref(&CItem::GetRandPrice));	//随机市场价格

	return true;
}
void	CCommunity::EventPerform()
{
	RandEvent();
	m_strEvent="";
	char tbuf[100]={0};
	switch(m_nEvent)
	{
		case	_EVENT00:
			sprintf(tbuf,"今天运气真好拣到%d块大洋!! 幸福ing.",RandAddMoney());
			m_strEvent=tbuf;
			break;
		case	_EVENT01:
			sprintf(tbuf,"我KAO,运气不好掉到臭水沟,一身晦气,掉了%d点健康.",RandSubHP());
			m_strEvent=tbuf;
			break;
		case	_EVENT02:
			sprintf(tbuf,"-.-,很和谐的一天~~");
			m_strEvent=tbuf;
			break;
		case	_EVENT03:
			sprintf(tbuf,"今天看到美吕MINI+黑丝,一下子精神焕发,健康增加了%d点^_^v.",RandAddHP());
			m_strEvent=tbuf;
			break;
		case	_EVENT04:
			sprintf(tbuf,"-.-,相当平常的一天~~");
			m_strEvent=tbuf;
			break;
		case	_EVENTMAX:
			long n=RandArrear();
			sprintf(tbuf,"一不小心打破别人古董了,我曰!欠了别人%d块大洋",n);
			m_Person.AddArrear(n);
			m_strEvent=tbuf;
			break;
		default:
			break;
	}
#ifdef	__CONSOLE
	PrtMessage(tbuf);
	getch();
#endif
}
void	CCommunity::UpdatePlace()
{

	switch(m_nKey)
	{
		case 0x48:
			m_nGroupMenu=_MENU;
			break;
		case 0x50:
			m_nGroupMenu=_MAPS;
			break;
		case 0x0d:
			Draw();
			switch(m_nGroupMenu)
			{
				case	_MENU:
					switch(m_MyMenu.GetPosition())
					{
						case 0:		//存取款
						{
							long n=0;
							char bf[50]={0};
							PrtMessage("XX银行: 请问您要取钱还是存钱? 1:存钱,2:取钱");
							std::cin.getline(bf,50);
							if(strcmp(bf,"")==0)	n=-1;
							else n=atoi(bf);
							memset(bf,0,50);
							if(n==1)
							{
								PrtMessage("XX银行: 请您输入存入金额?");
								PrtMessage("回车:MAX,取消:空格_回车",_ROW,_COL+1);
								std::cin.getline(bf,50);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0) n=m_Person.GetMoney();
								SaveMoney(n);
							}
							else if(n==2)
							{
								PrtMessage("XX银行: 请您输入取出金额!");
								PrtMessage("回车:MAX,取消:空格_回车",_ROW,_COL+1);
								std::cin.getline(bf,50);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0)	n=m_Person.GetSaving();
								GetMoney(n);
							}
						}
							break;
						case 1:		//医院治疗
							{
								if(m_Person.GetLoseHealth()<=0)
								{
									PrtMessage("您现在很贱康,不需要治疗.");
									getch();
									break;
								}
								int n=0;
								char bf[100]={0};
								sprintf(bf,"中心医院: 您需要%d元进行全套服务,你也可以自己输入治疗点数? ",GetAllHPMoney());
								PrtMessage(bf);
								PrtMessage("回车:MAX,取消:空格_回车",_ROW,_COL+1);
								memset(bf,0,100);
								std::cin.getline(bf,100);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0) n=100;
								CureHealth(n);
							}
							break;
						case 2:		//还债
							{
								if(m_Person.GetArrear()<=0)
								{
									PrtMessage("-.-我已经没有欠款了!");
									getch();
									break;
								}
								long n=0;
								char bf[50]={0};
								PrtMessage("嘿,小子啊,这么多钱看你怎么还^___^ 你打算还多少?");
								PrtMessage("回车:MAX,取消:空格_回车",_ROW,_COL+1);
								std::cin.getline(bf,100);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0) n=99999999;
								SubArrear(n);
							}
							break;
						case 3:		//租房
							{
								if(m_Person.GetMoney()<=3000)
								{
									PrtMessage("-____-!没钱还想租房,一边凉快去~~!.");
									getch();
									break;
								}
								int n=0;
								char bf[100]={0};
								sprintf(bf,"租房大爷: 这套房子要%d这个价,租不租! ",RetHouseMoney());
								PrtMessage(bf);
								PrtMessage("回车:确定,取消:空格_回车",_ROW,_COL+1);
								memset(bf,0,100);
								std::cin.getline(bf,100);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0)	
								{
									if(leaseHouse())	PrtMessage("^^哈哈,赚了赚了,再见小伙!");
									else	PrtMessage(">_<!我曰,没钱也来租,有无有搞错~~!");
									getch();
								}
							}

							break;
						case 4:		//上网
							{
								int n=0;
								char bf[100]={0};
								sprintf(bf,"^_^v上网作人肉鸡,赚得%d块大洋!",RandAddMoney());
								PrtMessage(bf);
								PrtMessage("关于 作者:言浩(Angluca) QQ:7333979 Email:Angluca@qq.com ",_ROW,_COL+1);
								PrtMessage("回车:确定,取消:空格_回车",_ROW,_COL+2);
								getch();
							}
							break;
						default:
							break;
					}
					break;
				case	_MAPS:
					{
						DayPlus();
						m_Person.ArrearPlus();
						RandSetSellItems();
						EventPerform();
					}
					break;
				default:
					break;
			}
			system("cls");
			break;
		default:
			break;
	}
}
void	CCommunity::UpdateItem()
{

	switch(m_nKey)
	{
		case _LEFT:
			m_nGroup=_SELLGROUP;
			break;
		case _RIGHT:
			m_nGroup=_BUYGROUP;
			break;
		case _UP:
			switch(m_nGroup)
			{
				case _SELLGROUP:
					MoveCursorSell(0);
					break;
				case _BUYGROUP:
					MoveCursorBuy(0);
					break;
			}
			break;
		case _DOWN:
			switch(m_nGroup)
			{
				case _SELLGROUP:
					MoveCursorSell(1);
					break;
				case _BUYGROUP:
					MoveCursorBuy(1);
					break;
			}
			break;
		case 0x20:	//空格
			switch(m_nGroup)
			{
				case _SELLGROUP:
					{
						int n=0;
						char bf[50]={0};
						PrtMessage("-0-请输入你要买的数量?");
						PrtMessage("回车:MAX,取消:空格_回车",_ROW,_COL+1);
						Draw();
						std::cin.getline(bf,50);
						if(strcmp(bf,"")==0)	n=-1;
						else n=atoi(bf);
						system("cls");
						if(n<0) n=m_nMaxNum;
						buyItem(n);
					}
					break;
				case _BUYGROUP:
					{
						int num=0;
						char bf2[50]={0};
						PrtMessage("请输入你要卖的数量?");
						PrtMessage("回车:MAX,取消:空格_回车",_ROW,_COL+1);
						Draw();
						std::cin.getline(bf2,50);
						if(strcmp(bf2,"")==0)	num=-1;
						else num=atoi(bf2);
						system("cls");
						if(num<0) num=m_nMaxNum;
						sellItem(num);
					}
					break;
			}
			break;
		default:
			break;
	}

}

void	CCommunity::UpdateBuf()
{
	int buyHead=0,buyEnd=_LINES,sellHead=0,sellEnd=_LINES;
	int tmpbuy=m_nBuyPos-buyEnd;
	int tmpsell=m_nSellPos-sellEnd;
	bool buybreak=false,sellbreak=false;
	if(tmpbuy>0)	buyHead=tmpbuy,buyEnd+=tmpbuy;
	if(tmpsell>0)	sellHead=tmpsell,sellEnd+=tmpsell;

	listItemPos		buyPos=m_listBuyItem.begin();
	listItemPos 	sellPos=m_listSellItem.begin();
	int buyloop=0,sellloop=0;
	while(!buybreak || !sellbreak)
	{
		if(buyloop<buyHead && buyPos!=m_listBuyItem.end()) ++buyPos,++buyloop;
		else	buybreak=true;
		if(sellloop<sellHead && sellPos!=m_listSellItem.end()) ++sellPos,++sellloop;
		else	sellbreak=true;
	}
	buybreak=sellbreak=false;
	char tmpb[30]={0};
	sprintf(tmpb,"%d/%d/%d天\n",m_nTotalItemNum,m_nMaxNum,m_nToday);
	m_tmpBuf="============[黑市]===========+==============[房间]====== ";
	m_tmpBuf+=tmpb;
	m_tmpBuf+="=[商品名]==============[价格]+[商品名]===============[购价][数量]\n";
	while(!buybreak || !sellbreak)
	{
		char tbuf[50]={0},tbuf2[50]={0};
		if(sellloop<=sellEnd && sellPos!=m_listSellItem.end())
		{
			if(sellloop==m_nSellPos && m_nGroup==_SELLGROUP)
			sprintf(tbuf,"*%-20s%7d |",(*sellPos).GetName(),(*sellPos).GetPrice());
			else
			sprintf(tbuf," %-20s%7d |",(*sellPos).GetName(),(*sellPos).GetPrice());
			++sellPos;
			++sellloop;
		}
		else{
			sprintf(tbuf,"                             |");
			sellbreak=true;
		}
		if(buyloop<=buyEnd && buyPos!=m_listBuyItem.end())
		{
			if(buyloop==m_nBuyPos && m_nGroup==_BUYGROUP)
			sprintf(tbuf2,"*%-20s%7d%5d\n",(*buyPos).GetName(),(*buyPos).GetPrice(),(*buyPos).GetNum());
			else
			sprintf(tbuf2," %-20s%7d%5d\n",(*buyPos).GetName(),(*buyPos).GetPrice(),(*buyPos).GetNum());
			++buyPos;
			++buyloop;
		}
		else{
			sprintf(tbuf2,"\n");
			buybreak=true;
		}
		if(!buybreak || !sellbreak)
			m_tmpBuf+=tbuf,m_tmpBuf+=tbuf2;
	}
	m_tmpBuf+="=============================+===================================\\\n";

	//test
	//static int a=0;
	//if(a<200)
	//m_listBuyItem.push_back(CItem("测试",a,a++,0,0));
}
bool	CCommunity::buyItem(int n=999)
{
	if(n<=0 || m_listSellItem.empty()) return false;
	int size=CheckTotalItemNum();		//确认房间空间还能放多少
	if(size<=0)
	{
#ifdef __CONSOLE
		PrtMessage("- -!!!满了还要撑呀!");
#endif
		return false;
	}
	listItemPos sellPos=m_listSellItem.begin();
	listItemPos buyPos;
	int sellloop=0;
	while(sellPos!=m_listSellItem.end() && sellloop!=m_nSellPos)
	{
		++sellPos;
		++sellloop;
	}
	if(sellPos==m_listSellItem.end()) return false;

	FindString fd(sellPos->GetName());
	buyPos=std::find_if(m_listBuyItem.begin(),m_listBuyItem.end(),fd);
	int money=m_Person.GetMoney();
	int price=sellPos->GetPrice();
	if(price<=0) price=1;
	int tNum=money/price;	//最多能买多少物品 单位:数量
	if(tNum<=0)	{
#ifdef __CONSOLE
		PrtMessage("-___-!小子啊,钱不够呢!");
#endif
		return false;}
	else if(tNum>size) tNum=size;
	if(n>tNum) n=tNum;
	long t=n*price;			//实际数量总额 =n:实际数量 * price:单个数量
	m_Person.SubMoney(t);
	sellPos->SetNum(n);
	if(buyPos==m_listBuyItem.end())	m_listBuyItem.push_back(*sellPos);
	else	buyPos->AddNum(n);
	AddTotalItemNum(n);		//增加房间物品数量

	return true;
}

bool	CCommunity::sellItem(int n=999)
{
	if(n<=0 || m_listBuyItem.empty()) return false;
	listItemPos sellPos;
	listItemPos buyPos=m_listBuyItem.begin();
	int buyloop=0;
	while(buyPos!=m_listBuyItem.end() && buyloop!=m_nBuyPos)
	{
		++buyPos;
		++buyloop;
	}
	if(buyPos==m_listBuyItem.end()) return false;

	FindString fd(buyPos->GetName());
	sellPos=std::find_if(m_listSellItem.begin(),m_listSellItem.end(),fd);
	if(sellPos == m_listSellItem.end())
	{
#ifdef		__CONSOLE
		PrtMessage("T^T现在没人收这个东西,去其它地方看看吧!");
#endif
			return false;
	}
	int Num=buyPos->GetNum();
	if(n>Num) n=Num;
	long totalMoney=n*sellPos->GetPrice();
	m_Person.AddMoney(totalMoney);
	buyPos->SubNum(n);
	if(buyPos->GetNum()==0) m_listBuyItem.erase(buyPos);
	SubTotalItemNum(n);

	return true;
}

void 	CCommunity::Init()
{
	m_Person.Init();
	m_MyMenu.Init();
	m_MyMaps.Init();
	InitItems();
}
void 	CCommunity::UnInit()
{
	m_Person.UnInit();
	m_MyMenu.UnInit();
	m_MyMaps.UnInit();
	m_vecItems.clear();
	m_listBuyItem.clear();
	m_listSellItem.clear();
}
void 	CCommunity::Update()
{
#ifdef __CONSOLE
	//m_MyMenu
	m_MyMenu.SetKey(m_nKey);
	m_MyMenu.Update();
	//m_MyMaps
	m_MyMaps.SetKey(m_nKey);
	m_MyMaps.Update();
	UpdateItem();
#endif
	UpdatePlace();

	m_nKey=0;		//release m_nkey;
}
void 	CCommunity::Draw()
{
	m_strBuf="";
	m_MyMenu.Updatebuf();
	m_strBuf+=m_MyMenu.GetBuf();
	m_MyMaps.Updatebuf();
	m_strBuf+=m_MyMaps.GetBuf();
	m_Person.Updatebuf();
	m_strBuf+=m_Person.GetBuf();

	UpdateBuf();
	m_strBuf+=m_tmpBuf;
	//m_MyMenu.Draw();
	//m_MyMaps.Draw();
#ifdef	__CONSOLE
	printf(m_strBuf.c_str());
#endif

	//FillConsoleOutputCharacter(m_hOut,' ',m_strBuf.size(),tmpDrawPos,0);
	
	//CONSOLE_SCREEN_BUFFER_INFO bInfo; // 窗口信息
	//GetConsoleScreenBufferInfo(m_hOut, &bInfo ); 
	//unsigned long size = bInfo.dwSize.X * bInfo.dwSize.Y;
	//FillConsoleOutputAttribute(m_hOut, bInfo.wAttributes, size, tmpDrawPos, NULL);

	//FillConsoleOutputCharacter(m_hOut,' ', size, tmpDrawPos, NULL);
	//SetConsoleCursorPosition(m_hOut,tmpDrawPos);
}

void	CCommunity::testprintf(int key)
{
	SetKey(key);
	Update();
	Draw();
}
void	CCommunity::run()
{
	unsigned int ch=0;
	int row=6,col=5;
	PrtMessage("湘潭浮生记 console:",row,col-2);
	PrtMessage("游戏说明:",row,col);
	PrtMessage("方向键盘为菜单/地图的光标移动,回车:确定:",row,col+2);
	PrtMessage("ASDW为黑市/房间的光标移动,空格:确定",row,col+4);
	PrtMessage("作者:Angluca QQ:7333979 Email:Angluca@qq.com ",row,col+6);
	PrtMessage("have a good time ^-^v! ",row,col+8);
	getch();
	Init();
	while(ch!=0x86)
	{
		system("cls");
		testprintf(ch);
		if(isEnd())
			ch=0x86;
		else
			ch=getch();
	}
	PrtMessage("-.-!你被大婶遣送回家了!");
	getch();
	MessageBox(NULL,"Game over ,thx for u play! ^-^v",0,0);
	UnInit();
}
