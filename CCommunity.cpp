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
	//��Ʒ��,����(������),����(����),��͵���(����),��ߵ���(����)
	m_vecItems.clear();
	m_vecItems.push_back( CItem("��������",0,0,30,800));
	m_vecItems.push_back( CItem("����VCD",0,0,1,200));
	m_vecItems.push_back( CItem("�������",0,0,90,800));
	m_vecItems.push_back( CItem("ˮ���ֻ�",0,0,100,5000));
	m_vecItems.push_back( CItem("�ϴ�С����",0,0,3000,120000));
	m_vecItems.push_back( CItem("��˽����",0,0,5000,150000));
	m_vecItems.push_back( CItem("α�ӻ�ױƷ",0,0,30,600));
	m_vecItems.push_back( CItem("�ٰ׾�(��ҵ�ƾ�)",0,0,200,5000));
	m_vecItems.push_back( CItem("��Ϸ�㿨",0,0,10,500));
	m_vecItems.push_back( CItem("���������",0,0,200,6000));
	m_vecItems.push_back( CItem("ˮ���ʼǱ�",0,0,1000,50000));
	m_vecItems.push_back( CItem("PSP������Ϸ��",0,0,1000,6000));
	m_vecItems.push_back( CItem("PSPUMD��Ϸ����",0,0,50,900));
	m_vecItems.push_back( CItem("xbox360��Ϸ��",0,0,200,5000));
	m_vecItems.push_back( CItem("Av���",0,0,5,1000));
	m_vecItems.push_back( CItem("����",0,0,5,100));
	m_vecItems.push_back( CItem("�����",0,0,5,100));
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
	int rnd;		//��ʾ������Ʒ
	if(m_nToday<(m_nMaxDay-1)) rnd=rand()%3-1+midsize;
	else rnd=vecsize;	//�ؼҵ����һ���г���ʾȫ����Ʒ
	rnd>vecsize?rnd=vecsize:0;
	int	tmpRnd=0;
	bool*	isChoose=new(std::nothrow) bool[vecsize];	//ȷ�����û��Ʒ���ظ�
	if(!isChoose) return false;
	memset(isChoose,0,vecsize);
	while(m_listSellItem.size()<rnd)	//���װ���г���Ҫ��ʾ����Ʒ
	{
		tmpRnd=rand()%vecsize;
		if(isChoose[tmpRnd])	continue;
		m_listSellItem.push_back(m_vecItems.at(tmpRnd));
		isChoose[tmpRnd]=true;
	}
	delete isChoose;
	m_nSellPos=m_nBuyPos=0;
	for_each(m_listSellItem.begin(),m_listSellItem.end(),
			std::mem_fun_ref(&CItem::GetRandPrice));	//����г��۸�

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
			sprintf(tbuf,"����������ü�%d�����!! �Ҹ�ing.",RandAddMoney());
			m_strEvent=tbuf;
			break;
		case	_EVENT01:
			sprintf(tbuf,"��KAO,�������õ�����ˮ��,һ�����,����%d�㽡��.",RandSubHP());
			m_strEvent=tbuf;
			break;
		case	_EVENT02:
			sprintf(tbuf,"-.-,�ܺ�г��һ��~~");
			m_strEvent=tbuf;
			break;
		case	_EVENT03:
			sprintf(tbuf,"���쿴������MINI+��˿,һ���Ӿ������,����������%d��^_^v.",RandAddHP());
			m_strEvent=tbuf;
			break;
		case	_EVENT04:
			sprintf(tbuf,"-.-,�൱ƽ����һ��~~");
			m_strEvent=tbuf;
			break;
		case	_EVENTMAX:
			long n=RandArrear();
			sprintf(tbuf,"һ��С�Ĵ��Ʊ��˹Ŷ���,��Ի!Ƿ�˱���%d�����",n);
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
						case 0:		//��ȡ��
						{
							long n=0;
							char bf[50]={0};
							PrtMessage("XX����: ������ҪȡǮ���Ǵ�Ǯ? 1:��Ǯ,2:ȡǮ");
							std::cin.getline(bf,50);
							if(strcmp(bf,"")==0)	n=-1;
							else n=atoi(bf);
							memset(bf,0,50);
							if(n==1)
							{
								PrtMessage("XX����: �������������?");
								PrtMessage("�س�:MAX,ȡ��:�ո�_�س�",_ROW,_COL+1);
								std::cin.getline(bf,50);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0) n=m_Person.GetMoney();
								SaveMoney(n);
							}
							else if(n==2)
							{
								PrtMessage("XX����: ��������ȡ�����!");
								PrtMessage("�س�:MAX,ȡ��:�ո�_�س�",_ROW,_COL+1);
								std::cin.getline(bf,50);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0)	n=m_Person.GetSaving();
								GetMoney(n);
							}
						}
							break;
						case 1:		//ҽԺ����
							{
								if(m_Person.GetLoseHealth()<=0)
								{
									PrtMessage("�����ںܼ���,����Ҫ����.");
									getch();
									break;
								}
								int n=0;
								char bf[100]={0};
								sprintf(bf,"����ҽԺ: ����Ҫ%dԪ����ȫ�׷���,��Ҳ�����Լ��������Ƶ���? ",GetAllHPMoney());
								PrtMessage(bf);
								PrtMessage("�س�:MAX,ȡ��:�ո�_�س�",_ROW,_COL+1);
								memset(bf,0,100);
								std::cin.getline(bf,100);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0) n=100;
								CureHealth(n);
							}
							break;
						case 2:		//��ծ
							{
								if(m_Person.GetArrear()<=0)
								{
									PrtMessage("-.-���Ѿ�û��Ƿ����!");
									getch();
									break;
								}
								long n=0;
								char bf[50]={0};
								PrtMessage("��,С�Ӱ�,��ô��Ǯ������ô��^___^ ����㻹����?");
								PrtMessage("�س�:MAX,ȡ��:�ո�_�س�",_ROW,_COL+1);
								std::cin.getline(bf,100);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0) n=99999999;
								SubArrear(n);
							}
							break;
						case 3:		//�ⷿ
							{
								if(m_Person.GetMoney()<=3000)
								{
									PrtMessage("-____-!ûǮ�����ⷿ,һ������ȥ~~!.");
									getch();
									break;
								}
								int n=0;
								char bf[100]={0};
								sprintf(bf,"�ⷿ��ү: ���׷���Ҫ%d�����,�ⲻ��! ",RetHouseMoney());
								PrtMessage(bf);
								PrtMessage("�س�:ȷ��,ȡ��:�ո�_�س�",_ROW,_COL+1);
								memset(bf,0,100);
								std::cin.getline(bf,100);
								if(strcmp(bf,"")==0)	n=-1;
								else n=atoi(bf);
								if(n<0)	
								{
									if(leaseHouse())	PrtMessage("^^����,׬��׬��,�ټ�С��!");
									else	PrtMessage(">_<!��Ի,ûǮҲ����,�����и��~~!");
									getch();
								}
							}

							break;
						case 4:		//����
							{
								int n=0;
								char bf[100]={0};
								sprintf(bf,"^_^v���������⼦,׬��%d�����!",RandAddMoney());
								PrtMessage(bf);
								PrtMessage("���� ����:�Ժ�(Angluca) QQ:7333979 Email:Angluca@qq.com ",_ROW,_COL+1);
								PrtMessage("�س�:ȷ��,ȡ��:�ո�_�س�",_ROW,_COL+2);
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
		case 0x20:	//�ո�
			switch(m_nGroup)
			{
				case _SELLGROUP:
					{
						int n=0;
						char bf[50]={0};
						PrtMessage("-0-��������Ҫ�������?");
						PrtMessage("�س�:MAX,ȡ��:�ո�_�س�",_ROW,_COL+1);
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
						PrtMessage("��������Ҫ��������?");
						PrtMessage("�س�:MAX,ȡ��:�ո�_�س�",_ROW,_COL+1);
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
	sprintf(tmpb,"%d/%d/%d��\n",m_nTotalItemNum,m_nMaxNum,m_nToday);
	m_tmpBuf="============[����]===========+==============[����]====== ";
	m_tmpBuf+=tmpb;
	m_tmpBuf+="=[��Ʒ��]==============[�۸�]+[��Ʒ��]===============[����][����]\n";
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
	//m_listBuyItem.push_back(CItem("����",a,a++,0,0));
}
bool	CCommunity::buyItem(int n=999)
{
	if(n<=0 || m_listSellItem.empty()) return false;
	int size=CheckTotalItemNum();		//ȷ�Ϸ���ռ仹�ܷŶ���
	if(size<=0)
	{
#ifdef __CONSOLE
		PrtMessage("- -!!!���˻�Ҫ��ѽ!");
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
	int tNum=money/price;	//������������Ʒ ��λ:����
	if(tNum<=0)	{
#ifdef __CONSOLE
		PrtMessage("-___-!С�Ӱ�,Ǯ������!");
#endif
		return false;}
	else if(tNum>size) tNum=size;
	if(n>tNum) n=tNum;
	long t=n*price;			//ʵ�������ܶ� =n:ʵ������ * price:��������
	m_Person.SubMoney(t);
	sellPos->SetNum(n);
	if(buyPos==m_listBuyItem.end())	m_listBuyItem.push_back(*sellPos);
	else	buyPos->AddNum(n);
	AddTotalItemNum(n);		//���ӷ�����Ʒ����

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
		PrtMessage("T^T����û�����������,ȥ�����ط�������!");
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
	
	//CONSOLE_SCREEN_BUFFER_INFO bInfo; // ������Ϣ
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
	PrtMessage("��̶������ console:",row,col-2);
	PrtMessage("��Ϸ˵��:",row,col);
	PrtMessage("�������Ϊ�˵�/��ͼ�Ĺ���ƶ�,�س�:ȷ��:",row,col+2);
	PrtMessage("ASDWΪ����/����Ĺ���ƶ�,�ո�:ȷ��",row,col+4);
	PrtMessage("����:Angluca QQ:7333979 Email:Angluca@qq.com ",row,col+6);
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
	PrtMessage("-.-!�㱻����ǲ�ͻؼ���!");
	getch();
	MessageBox(NULL,"Game over ,thx for u play! ^-^v",0,0);
	UnInit();
}
