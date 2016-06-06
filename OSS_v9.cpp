#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<fstream>
#include<string.h>
#include<process.h>
#include<ctype.h>
#include<dos.h>
#include "graphics.h"
#include <windows.h>

using namespace std;

int choice;
void graph(void);
//�ڵ����
int meal = 0;
int ballett = 0;
int Car_No = 0;

struct date		// ��¥�� �����ϴ� ����ü
{
	int da_day;
	int da_mon;
	int da_year;
};


void delay(int x)		//delay �Լ� ����
{
	Sleep (x);
};


void gotoxy(int x, int y)		//Ŀ���� ���ϴ� ������ �ű��
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);


};

void textcolor(int color_number)		//�ܼ�â ���ڿ� �� �ִ� �Լ� ����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}



void getdate(date *d)		//ȣ���� �����ϴ� ��¥�� ����
{
	scanf_s("%d %d %d", d->da_day, d->da_mon, d->da_year);
}

void basic()		//�ܼ� â ����
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");
	setcolor(4);
	rectangle(0, 0, 636, 476);
	rectangle(2, 2, 634, 474);
	line(247, 52, 384, 52);
	line(247, 50, 384, 50);
	setbkcolor(1);

}


void graph()		//�ܼ� â ����2
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");
	setcolor(4);
	rectangle(0, 0, 636, 476);
	rectangle(2, 2, 634, 474);
	line(247, 52, 384, 52);
	line(247, 50, 384, 50);
	setbkcolor(0);
	setcolor(10);
	line(172, 345, 400, 345);

}

class ROOMS		//���� ����
{
public:
	int roomNo;		//���� ��ȣ	
	int roomType;		//���� ����		
	int roomStatus;		//���ǻ���
	int roomCharges;		//���� ����	
	//�ҽ��ڵ����
	int grade;							//�����򰡿� ���� ����
	void Database();		//������ ������ ������ DB�Լ�
	void status();		//������ ���� ������ ������ DB�Լ�
	int findRoomNo(int TYPE);		//��밡���� ������ �� �� �ִ� �Լ�
	void bookRoom(int roomNo);		//���� �����ϴ� �Լ�
	unsigned long retRoomCharges(int roomNo);	//������ ������ �����ϴ� DB �Լ�
	void releaseRoom(int roomNo);		//�ش� ������ ����
}r;										//ROOMS r

class CUSTOMER		//����� ���� 
{
public:
	int Roomn;		//����ڰ� �����ϴ� ������ ȣ��	
	char name[30];		//������� �̸�
	char add[30];		//�ּ� �����ϴ� �迭
	char phone[20];		//����ó �����ϴ� �迭
	int daysStayed;		//���� �Ⱓ	
	int DAY, MONTH, YEAR;		//���� ��¥
	long amount;		//������ ����
	void searchRoomNo();		//����ڰ� ã���� �ϴ� ������ ��ȣ�� ã���Լ� 
	void searchCust();		//����ڸ� �˻��ϴ� �Լ�
	void check_in();		//���� ���࿡ ���� �Լ�
	void check_out();		//������� ��� ���� �Լ�
	void reports();		//���� ����� ���ݿ� ���� �Լ�
	void previous_Customer();		//ȣ�� �̿� ���� �� ���� �Լ�
};
int DAY, MONTH, YEAR;



void ROOMS::Database()		//������ DB �����ϴ� �Լ�
{
	fstream fin("rooms", ios::binary | ios::in);		//���� ���� �Է�
	fin.close();
	for (int i = 1;i <= 200;i++)
	{
		if (i<100)		//���� 1~100ȣ���� 
		{
			r.roomNo = i;
			r.roomStatus = 0;
			r.roomCharges = 300;
			r.roomType = 0;
			fstream fout("rooms", ios::binary | ios::app);		//
			fout.write((char*)&r, sizeof(r));
			fout.close();
		}
		else if (i >= 101 && i <= 150)		//���� 101~150ȣ ����
		{
			r.roomNo = i;
			r.roomStatus = 0;
			r.roomCharges = 500;
			r.roomType = 1;
			fstream fout("rooms", ios::binary | ios::app);
			fout.write((char*)&r, sizeof(r));
			fout.close();
		}
		else if (i>150 && i <= 200)		//���� 150~200ȣ ����
		{
			r.roomNo = i;
			r.roomStatus = 0;
			r.roomCharges = 1000;
			r.roomType = 2;
			fstream fout("rooms", ios::binary | ios::app);
			fout.write((char*)&r, sizeof(r));
			fout.close();
		}
	}
}
void CUSTOMER::searchCust()		//����ڸ� �˻��ϴ� �Լ�
{
	system("cls");
	basic();
	struct date d;
	getdate(&d);		//��¥�� �Է� ����	
	DAY = d.da_day;
	MONTH = d.da_mon;
	YEAR = d.da_year;
	int flag = 0;
	char NAME[20];
	gotoxy(32, 3); cout << "H I L L   V I E W";
	gotoxy(26, 5); cout << "C U S T O M E R    D E T A I L";
	gotoxy(5, 15);cout << "Enter Customer's Name : ";
	gets_s(NAME);		//������� �̸��� �Է� ����
	CUSTOMER c;
	fstream fin("cust", ios::binary | ios::in);		//���� �Է����� cust������ �Է� ����
	while (fin.read((char*)&c, sizeof(c)))		//������ ������ ��� ���ڵ带 �аڴ�
	{
		if (strcmp(NAME, c.name) == 0)		//������ ����� ������ �������
		{
			flag = 1;
			gotoxy(40, 15);cout << "Room Number: " << c.Roomn;		//���� ��ȣ ���
			gotoxy(40, 16);cout << "Customer Name : " << c.name;		//����� �̸� ���
			gotoxy(40, 17);cout << "Address: " << c.add;		//����� �ּ� ���
			gotoxy(40, 18);cout << "Phone No. : " << c.phone;		//����� ����ó ���
			gotoxy(40, 19);cout << "Check-in : " << c.DAY << "/" << c.MONTH << "/" << c.YEAR;		//üũ�� ��¥ ���
			break;
		}
	}
	fin.close();
	if (flag == 0)
	{
		gotoxy(40, 15);	cout << "No such Name Found !!!";
	}
	_getch();		//��µڿ� ȭ���� �ٷ� �Ѿ�� �ȵǰ� ������ ���� �Է¹��������� ��ٸ����� ��
	closegraph();	//�׷��ȸ�带 �ݰ� �ؽ�Ʈ���� ����
	restorecrtmode();	//graph���� �����ߴ� ����� ȭ�� ��带 ����
}

int ROOMS::findRoomNo(int TYPE)
{
	ROOMS r;
	int RNO, flag = 0;
	fstream fin("rooms", ios::binary | ios::in);		//
	while (fin.read((char*)&r, sizeof(r)))		//������ ������ ��� ���ڵ带 ����
	{
		if (TYPE == r.roomType)		//������ ������ ��
		{
			if (r.roomStatus == 0)		//���� ��� ����
			{
				RNO = r.roomNo;
				flag = 1;
				break;
			}
			else
				flag = 2;
		}
	}
	fin.close();
	if (flag == 0)
		return 0;				//findRoomNo�� 0�� ��ȯ�Ѵٸ� ���� ã�� �� ����.
	else if (flag == 1)
		return RNO;				//findRoomNo�� ��ѹ��� ��ȯ�Ѵٸ� ���� ����� �� �ִ�.
	else if (flag == 2)
		return -1;				//findRoomNo�� -1�̶�� ������ ���� �������̴�
	return 0;
}


void CUSTOMER::searchRoomNo()															//���ȣ�� ���� �˻����ִ� �Լ�
{
	system("cls");																		//ȭ�� �����
	basic();																			//�⺻�簢�����׸���
	struct date d;																		//��¥������ ����ü
	getdate(&d);							
	DAY=	d.da_day;
	MONTH=	d.da_mon;
	YEAR=	d.da_year;																	//��¥,��,������ �޾ƿ´�
	int roomno, flag=0;																	//���ȣ�� ���� roomno����, ���� �����ߴ��� ���ߴ����� Ȯ���� flag������ ����
	gotoxy(32,3); cout<<"H I L L  V I E W ";
	gotoxy(26,5);cout<<"C U S T O M E R   D E T A I L ";
	gotoxy(5,15);cout<<"Enter Room Number : ";
	cin>>roomno;																		//ã�����ϴ� ���ȣ�� �Է¹޾� roomno������ �Է����ش�.
	CUSTOMER c;
	fstream fin("cust", ios::binary | ios::in);											//fin������ ���� �Է����·� ���ڴ�.(�о���ڴ�.)
	while(fin.read((char *) &c, sizeof(c)))												//������ ������ ��� ���ڵ带 �аڴ�.
	{
		if(roomno==c.Roomn)																//���� ã���� �ϴ� ���� ���Ͼȿ� �ִٸ�
		{
			flag=1;																		//���� �ִٸ� flag = 1�� �ٲ��ش�.
			gotoxy (40,15);cout<<"Room Number: "<<c.Roomn;
			gotoxy (40,16);cout<<"Customer Name : "<<c.name;
			gotoxy (40,17);cout<<"Address: "<<c.add;
			gotoxy (40,18);cout<<"Phone No. : "<<c.phone;
			gotoxy (40,19);cout<<"Check-in : "<<c.DAY<<"."<<c.MONTH<<"."<<c.YEAR;		//��Ÿ �濡 ���� ������ ������ش�.(������ ���� �̸�, �ּ�, ��ȭ��ȣ, üũ�γ�¥)
			break;
		}
	}
	fin.close();																		//fin���� ���� ����
	if(flag==0)																			//flag = 0�̶�°��� ã�� ���� ���ٴ� ���
	{
		gotoxy(40, 15);
		cout<<"No such Room No. Found !!!";												//���� ã�� �� ���ٰ� ���
	}
	_getch();																			//��µڿ� ȭ���� �ٷ� �Ѿ�� �ȵǰ� ������ ���� �Է¹��������� ��ٸ����� �Ѵ�.
	closegraph();																		//�׷��ȸ�带 �ݰ� �ؽ�Ʈ���� �����ϰڴ�.
	restorecrtmode();																	//graph���� �����ߴ� ����� ȭ�� ��带 �����Ѵ�.
}


void CUSTOMER::reports()																//���� ����� ���ݿ� ���� �Լ�
{
	system("cls");																		//ȭ���� �����.
	basic();																			//�⺻ ȭ���ǰ�
	CUSTOMER c;																			//���� ���� ����ü c
	gotoxy(32,3); cout<<"H I L L   V I E W";	
	gotoxy(21, 5);	cout<<"C U S T O M E R  S T A Y    S U M M A R Y";
	int i=11;																			
	unsigned  long AMOUNT=0;															//����
	fstream fin("detail", ios::binary | ios::in);										//fin
	gotoxy(7,9);																		
	cout<<"R.No NAME\t ADDRESS\t AMOUNT\t DT OF CHECK-IN\tDAYS STAYED";					
	while(fin.read((char*)&c, sizeof(c)))												//������ ������ �аڴ�.
	{
		gotoxy(7, i);	cout<<c.Roomn;													
		gotoxy(12, i);	cout<<c.name;													
		gotoxy(23, i);	cout<<c.add;													//���� ���ȣ�� �̸� �ּ� ���
		gotoxy(37, i);																
		if(c.amount==-1)
			cout<<"N/A";																//�ش���׾���.	
		else
		{
			cout<<c.amount<<"/=";														
			AMOUNT=AMOUNT+c.amount;														//ȣ���� �Ѽҵ�
		}
		gotoxy(50, i);	cout<<c.DAY<<"/"<<c.MONTH<<"/"<<c.YEAR;
		gotoxy(68, i);
		if(c.daysStayed==-1)	
			cout<<"N/A";																//�ش���׾���.
		else
			cout<<c.daysStayed;
		i++;
		if(i==22)
		{
			i=11;
			gotoxy(21, 5);	cout<<"C U S T O M E R   S T A Y    S U M M A R Y";
			gotoxy(7,9);
			cout<<"R.No NAMEADDRESS AMOUNT";
			cout<<"DT/OF CHECK-INDAYS STAYED";
			gotoxy(28,23);
			cout<<"<Press any key to continue>";
			_getch();
		}
	}
	gotoxy(27, 25);
	gotoxy(27, 25);	cout<<"< Net Amount Rs.: "<<AMOUNT<<"/= >";						//ȣ���� �Ѽҵ� ���
	fin.close();
	_getch();																		//��µڿ� ȭ���� �ٷ� �Ѿ�� �ȵǰ� ������ ���� �Է¹��������� ��ٸ����� �Ѵ�.
	closegraph();																	//�׷��ȸ�带 �ݰ� �ؽ�Ʈ���� �����ϰڴ�.
	restorecrtmode();																//graph���� �����ߴ� ����� ȭ�� ��带 �����Ѵ�.
}
void ROOMS::status()																//�� ���¸� �����ִ� �Լ�
{
	system("cls");																	
	ROOMS r;																		//�濡 ���� ����ü r
	gotoxy(8, 9);	cout<<"\tR O O M  S T A T U S";									
	fstream fin("rooms", ios::binary | ios::in);									
	gotoxy(5,19);cout<<"  R.No    Room Type  Room Charges   Status    Grade"<<"\n\n";
	int maxPageSize = 25;															//�ִ� ������ ������� 25
	int initPageSize = 4;															//������ �ʱⰪ�� 4
	for (int i=1;i<200;i++)															//���� 200�� �̹Ƿ� int i=1���� 200
	{
		fin.read((char*)&r, sizeof(r));												
		cout<<"\t"<<r.roomNo<<"\t";													

		if(r.roomType==2)															//Deluxe ���� ��Ÿ���� 2���̹Ƿ�
		{
			cout<<"Deluxe  "<<"\t";
		}
		else if(r.roomType==1)														//semi-deluxe ���� ��Ÿ���� 1���̴�
		{
			cout<<"semi-deluxe"<<"\t";
		}
		else                                                                        //�Ѵ� �ƴѹ��� Ordinary�̴�.
		{
			cout<<"Ordinary"<<"\t";										
		}
		cout<<r.roomCharges<<"\t";													//���� ������ ȭ�鿡 ������ش�.
		cout<<r.grade<<"\t";														//���� ������ ȭ�鿡 ������ش�.

		if(r.roomStatus==1)															//roomStatus�� 1�̶�� ���� ������ ����or������� ���̶�� ����
			cout<<"Occupied"<<"\n";
		else                                                                        //�ƹ��� �������� ���� ���̹Ƿ� --------�� ���
			cout<<"--------"<<endl;

		initPageSize++;																//�� ȭ�鿡 �� �������� �ʱ� �������� ++��Ų��
		if(initPageSize == maxPageSize) {                                           //���� �ʱ� ������ ������� �ִ� �������� ���� �������ٸ� 
			initPageSize = 1;														//�ʱ� �������� 1�� �ٽ� �ʱ�ȭ ��Ų��

			_getch();																//�Է��� ��ٸ���.
		}
	}
	fin.close();
	_getch();																		//��µڿ� ȭ���� �ٷ� �Ѿ�� �ȵǰ� ������ ���� �Է¹��������� ��ٸ����� �Ѵ�.
}

void CUSTOMER::check_in()															//���� ���࿡ ���� �Լ�
{
	system("cls");
	int TYPE, roomno, flag;															//TYPE�� ���� Ÿ��, roomno�� ���� �ѹ�, flag�� ���� �����ߴ°� ���ߴ°��� ���� �Լ��̴�.
	char c;
	struct date d;																	//��¥�� �����ϴ� ����ü d
	getdate(&d); 
	DAY=d.da_day;
	MONTH=d.da_mon;
	YEAR=d.da_year;																	//��¥, ��, ������ d�� �޾��ش�.
	ROOMS r;																		//�濡 ���� ������ �����ϴ� ����ü r
	basic();
	r.Database();																	
	gotoxy(32,3); cout<<"H I L L  V I E W";
	gotoxy(28,5);cout<<"C H E C K    I N";
	gotoxy(10, 10);cout<<"<Enter:: '2' for Deluxe, '1' for Semi Deluxe and '0' for Ordinary>";
	gotoxy(5,15);cout<<"Enter Room Type : ";
	
	do{
		c=_getch();																	//
		if(c>=48 && c<=50) {cout<<c;delay(2000);}									//
	}while(c<48 || c>50);															//
	
	switch(c)
	{  
	case '0' : TYPE =0;break;
	case '1' : TYPE =1;break;
	case '2' : TYPE =2;break;
	}																				//���� c�� �Է¹��� ���� ���� Ÿ���̹Ƿ�!
			
	gotoxy(20, 24);
	roomno=r.findRoomNo(TYPE);														//findRoomNo �Լ� 
	gotoxy(20, 24);																	
	if(roomno==-1)																	//roomno�� -1�̶�� ���� ������ �� ���ٴ� ���̴�.			
	{
		cout<<"This Room Type is not available !!!";
		_getch();
		return;
	}
	else if(roomno==0)																//roomno�� 0�̶�� ���� ã�� �� ���ٴ°�
	{
		cout<<"Invalid room number !!!";
		_getch();
		return;
	}
	else                                                                           //���� ã�� �� �ְ� ������ ���ִ�
	{
		CUSTOMER c;
		static char NAME[30], ADD[30], PHONE[20];	
		fstream fout("cust", ios::binary | ios::app);								// ����ϴ� �����Ͱ� ������ ���� ���� ��ϵȴ�.
		gotoxy(5,16);	cout<<"Enter the Name : ";
		gets(NAME);
		gotoxy(5, 17); cout<<"Enter Address: ";
		gets(ADD);
		gotoxy(5, 18);	cout<<"Enter Phone No. : ";
		gets(PHONE);
		gotoxy(5, 19); cout<<"Enter th Car No. : "; cin>>Car_No;

		c.Roomn=roomno;
		c.daysStayed=-1;
		c.amount=-1;
		strcpy(c.name, NAME);
		strcpy(c.add, ADD);
		strcpy(c.phone, PHONE);													//�̸�, �ּ�, ��ȣ, ����ȣ�� �Է¹޴´�
		c.DAY=DAY;
		c.MONTH=MONTH;
		c.YEAR=YEAR;
		fout.write((char*)&c, sizeof(c));										//
		fout.close();															//������ �ݴ´�
	}
	r.bookRoom(roomno);															//
	closegraph();
	restorecrtmode();
}

void CUSTOMER::check_out()
{
   system("cls");
   basic();
   int roomno, flag=0;
   long double AMOUNT;
   gotoxy(32,3); cout<<"H I L L   V I E W";
   gotoxy(32,5);   cout<<"C H E C K  O U T";
   gotoxy(23,14);   cout<<"Enter Room No. to Vacate : ";
   cin>>roomno;
   CUSTOMER c;
   fstream fin("cust", ios::binary | ios::in);

   while(fin.read((char*)&c, sizeof(c)))
   {
      if(roomno==c.Roomn)   //�Է¹��� ��ѹ���, ���Ͽ��� ���� ���� ��ѹ��� ������ �� ���ٸ�
      {
         flag=1;    // flag�� 1�� ������ش�.
         break;
      }
   }
   fin.close();
   if(flag==0)         // flag�� 0�̶��
   {
      gotoxy(28, 17);
      cout<<"The Room is Unoccupied !!!"; //�Է¹��� ��ѹ��� ���Ͽ��� ���� ��ѹ��� �ٸ��� ������ �� ���� ����ִ�.
      _getch();
      return;
   }
   if(flag==1)         //flag�� 1�̶��
   {
      ROOMS r;      
      r.releaseRoom(roomno);      //room�� ������ �Ǿ��ִٴ� ó���� ���ش�.
      AMOUNT=r.retRoomCharges(roomno);
   }
   fstream fin1("cust", ios::binary | ios::in);
   fstream fout1("temp", ios::binary | ios::out);
   while(fin1.read((char*)&c, sizeof(c)))
   {
      if(roomno==c.Roomn && c.daysStayed==-1)   //��ѹ��� ���Ͽ��� �о���� (����)��ѹ��� ���� ȣ�� ���ڼ��� -1�϶� (-1�϶� �������� ������ ���Ѵ�)
      {
         int D;
         gotoxy(23,16);   cout<<"Enter No. of Days stayed : ";      //���� ������ ������ �Է��Ͻÿ�
         cin>>D;
         c.daysStayed=D; 
        
        c.amount=D*AMOUNT+meal;																				//�����ұݾ� = �ӹ���*���Ǳݾ�+�䰪
			gotoxy(23,18);	cout<<"Total Charges are Rupees : "<<c.amount;										
			gotoxy(18,20);  cout<<"�߷� ���񽺸� ���Ͻó���? (�� : 1, �ƴϿ� : 2) : ";
			cin>>ballett;																						//�߷����񽺿� ���� ���� ballett
			system("cls");
			if(ballett == 1) {gotoxy(18, 10); cout<<"�� ��ȣ "<<Car_No<<"�߷� ���� ��û �Ϸ�. ������Դϴ�.";
							  gotoxy(22, 12); cout<<"�����ϼ̳���? ������ �ּ��� (1~10��) : "; cin>>r.grade;
							  gotoxy(26, 14); cout<<"�����մϴ� :) �ȳ���������!" ;}
			else if(ballett == 2) {gotoxy(26, 11); cout<<"�����մϴ� :) �ȳ���������!";}
			fout1.write((char*)&c, sizeof(c));
			_getch();
			return;
      }
      else
         fout1.write((char*)&c, sizeof(c));
   }
   fin1.close();
   fout1.close();
   remove("cust");
   rename("temp","cust");

   ofstream f1,f2;
   f1.open("temp", ios::binary | ios::out | ios::app);
   f2.open("detail",ios::binary | ios::out | ios::app);
   fstream fin2("cust", ios::binary | ios::in | ios::app);
   while(!fin2.eof())
   {
      fin2.read((char*)&c, sizeof(c));
      if(!fin2.eof())
      {
         if(roomno!=c.Roomn)
         {
            f1.write((char*)&c ,sizeof(c));
         }
         else
         {
            f2.write((char*)&c ,sizeof(c));
         }
      }
   }
   fin2.close();
   f1.close();
   f2.close();
   remove("cust");
   rename("temp","cust");

   _getch();
   closegraph();
   restorecrtmode();
}

void ROOMS::bookRoom(int RNO
{
   ROOMS r;
   fstream fin("rooms", ios::binary | ios::in);
   fstream fout("temp", ios::binary | ios::out);
   while(fin.read((char*)&r, sizeof(r)))
   {
      if(RNO==r.roomNo)   //���ڷ� ���� RNO�� rooms���Ͽ��� �о���� roomNo�� ���� ��
      {
         gotoxy(22,25);
         cout<<"Room No '"<<RNO<<"' has been booked";   // �� ���� ����Ǿ� �ִ�.
         r.roomStatus=1;               //roomStatus�� 1�� �ٲپ���
         fout.write((char*)&r, sizeof(r));
      }
      else
         fout.write((char*)&r, sizeof(r));
   }
   fout.close();
   fin.close();
   remove("rooms");
   rename("temp","rooms");
   _getch();
}
void ROOMS::releaseRoom(int RNO)   //��������
{
   ROOMS r;
   int NO_DAYS;
   fstream fin("rooms", ios::binary | ios::in);
   fstream fout("temp", ios::binary | ios::out);
   while(fin.read((char*)&r, sizeof(r)))
   {
      if(RNO==r.roomNo)      //RNO�� rooms ���Ͽ��� ���� ��ѹ��� ���� ��
      {
         r.roomStatus=0;      // roomStatus�� 0���� �ٲپ���
         fout.write((char*)&r, sizeof(r));
      }
      else
         fout.write((char*)&r, sizeof(r));
   }
   fin.close();
   fout.close();
   remove("rooms");
   rename("temp","rooms");
}
unsigned long ROOMS::retRoomCharges(int RNO)   //��� ��ȯ �޼ҵ�
{
   ROOMS r;
   long double AMOUNT;
   fstream fin("rooms", ios::binary | ios::in);
   while(fin.read((char*)&r, sizeof(r)))
   {
      if(RNO==r.roomNo)   //���ڷ� ���� �� ��ȣ�� rooms���Ͽ� �ִ� roomNo�� ���� ��
      {
         AMOUNT=r.roomCharges;   //AMOUNT�� ���Ͽ� ����� roomCharges�� �����Ѵ�.
         break;
      }
   }
   fin.close();
   return AMOUNT;   //AMOUNT�� ��ȯ�Ѵ�.
}
void CUSTOMER::previous_Customer(void)		//���� �Լ� �����ؾ���
{
	system("cls");
	basic();
	CUSTOMER c;
	char NAME[30];					//������ ���� �̸�
	gotoxy(32,3); cout<<"H I L L   V I E W";
	gotoxy(5,6);cout<<"Enter customer name: ";
	gets(NAME);						//������ ���� �̸��� ����
	fstream fin("detail", ios::binary | ios::in);
	while(fin.read((char*)&c, sizeof(c)))
	{
		if(strcmp(c.name,NAME)==0)				//c,name�̶� NAME�� ���Ͽ� ������ ����
		{
			gotoxy (26,8);cout<<"Room Number: "<<c.Roomn;
			gotoxy (26,9);cout<<"Customer Name : "<<c.name;
			gotoxy (26,10);cout<<"Address: "<<c.add;
			gotoxy (26,11);cout<<"Phone No. : "<<c.phone;
		}
	}
	_getch();
	closegraph();
	restorecrtmode();
}
void enter_password()				//ó������ȭ�� ���� ��й�ȣ �Լ�
{
	system("cls");
	char pass[10],c;
	int i =0;
	gotoxy(25,18);cout <<"Enter the password : " ;
	do{
		c = _getch();			//��й�ȣ�� ����
		if(c==8) {cout<<'\b'<<' '<<'\b';i--;}		// back space�� ��� �޴� ���ڸ�����
		else if(c!=13) {cout<<'*';pass[i]=c;i++;}	// Enterĥ������ �޴� ���ڿ��� *�� ǥ��
	}
	while(c!=13);			// Enter ġ�������� ��� ����(Enter ġ�� ����)
	pass[i]='\0';			//������ �����Ⱚ������

	if (strcmp(pass,"1234")==0)			//�Է¹��� ��й�ȣ�� ������ ��й�ȣ Ȯ���� ������ ����
		return ;
	gotoxy(28,20);cout <<"   WRONG PASSWORD    " ;	//�Է¹��� ���̶� �ٸ���
	_getch() ;
	exit(0) ;
}


void main()
{
	basic();

	
	char c;
	
	textcolor(GREEN);	
	void graph(void);

	
	void enter_password();		//���������� ������ ��й�ȣȮ�� �Լ� ȣ��

	enter_password();
	system("cls");
	struct date d;
	
	do
	{
		system("cls");	
		graph();
		gotoxy(32,3); cout<<"H I L L   V I E W";
		gotoxy(5,23); cout<<"Designed and Created by";
		gotoxy(30,24); cout <<"ARUN VENKATESH";
		gotoxy(30,25); cout <<"ANANDA VALLIAPPAN";
		gotoxy(30,26); cout <<"ATEETH KUMAR";
		gotoxy (5,12);cout<<"1. Search";			//����ȭ�鿡 ������ ���ڵ�
		gotoxy (5,13);cout<<"2. Check in";
		gotoxy (5,14);cout<<"3. Check out";
		gotoxy (5,15);cout<<"4. Room status";
		gotoxy (5,16);cout<<"5. Earnings";
		gotoxy (5,17);cout<<"6. Previous Customers";
		gotoxy (5,18);cout<<"0. Exit";
		gotoxy(30,21);	cout<<"Enter choice : ";
		do{c=_getch();				//�޴� ���� c���� �־���
		if(c>=48 &&c<=54) {cout<<c; delay(500);}		//���� c ���� 0�̻� 6���ϸ� if������
		}while(c<48 || c>54);					//���� c ���� 0�̻� 6���ϰ� �ƴϸ� ��ӽ���
		switch(c)						//������ ����c������ switch�� ����
		{ case '0':choice =0;break;
		case '1' : choice =1;break;
		case '2':choice=2;break;
		case '3':choice =3;break;
		case '4':choice=4;break;
		case '5':choice=5;break;
		case '6':choice=6;break;
		case '7':choice=7;break;
		}
		closegraph();
		restorecrtmode();
		switch(choice)
		{
		case 1:	{					//���� ���������� 1. Search ����
			int choice;
			char ch;
			do
			{
				system("cls");
				graph();
				gotoxy(32,3);cout<<"H I L L   V I E W";
				gotoxy(32, 5);cout<<"S E A R C H\n\n";
				gotoxy (5,12);cout<<"1. To search by NAME";
				gotoxy (5,13);cout<<"2. To search by ROOM NO.";
				gotoxy (5,14);cout<<"0. Exit";
				gotoxy(30,21);cout<<"Enter choice : ";
				do{
					ch=_getch();
					if(ch>=48 &&ch<=50) {cout<<ch;delay(500);}		//0�̻� 2�����϶� ���� ����
				}
				while(ch<48 || ch>50);			//0�̻� 2���ϰ� �ƴҰ�� ��ӽ���
				switch(ch)				//���� ���������� 1. Search ���� ���� Room �Ǵ� �̸����� ã��
				{ 
				case '0':choice =0;break;
				case '1' : choice =1;break;
				case '2':choice=2;break;
				}

				closegraph();
				restorecrtmode();
				switch(choice)
				{
				case 1:	{				//�̸����� ã��
					CUSTOMER c;
					c.searchCust();
					break;
						}
				case 2:	{				//���ȣ�� ã��
					CUSTOMER c;
					c.searchRoomNo();
					break;
						}
				}
			}while(choice!=0);				//0�Է¾ƴҶ����� ��� �Է�
			break;
				}
		case 2:	{						//���� ���������� 2.check in ���� check _in()����
			CUSTOMER c;
			c.check_in();
			break;
				}

		case 3:	{						//���� ���������� 3.check out ���� check_out()����
			CUSTOMER c;
			c.check_out();
			break;
				}
		case 4:	{						//���� ���������� 4.Room status ���� r.status()����
			ROOMS r;
			r.status();
			break;
				}
		case 5:	{						//���� ���������� 5.repots ���� c.reports();����
			CUSTOMER c;
			c.reports();
			break;
				}
		case 6: {						//���� ���������� 6.previous_Customer ���� c.previous_Customer();����
			CUSTOMER c;
			c.previous_Customer();
			break;
				}

		}
	}while(choice!=0);						//0�Է¾ƴҶ����� ��� �Է�
	
}