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
//코드수정
int meal = 0;
int ballett = 0;
int Car_No = 0;

struct date		// 날짜를 저장하는 구조체
{
	int da_day;
	int da_mon;
	int da_year;
};


void delay(int x)		//delay 함수 생성
{
	Sleep (x);
};


void gotoxy(int x, int y)		//커서를 원하는 곳으로 옮기기
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);


};

void textcolor(int color_number)		//콘솔창 글자에 색 넣는 함수 생성
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}



void getdate(date *d)		//호텔을 예약하는 날짜를 받음
{
	scanf_s("%d %d %d", d->da_day, d->da_mon, d->da_year);
}

void basic()		//콘솔 창 생성
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


void graph()		//콘솔 창 생성2
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

class ROOMS		//객실 정보
{
public:
	int roomNo;		//객실 번호	
	int roomType;		//객실 유형		
	int roomStatus;		//객실상태
	int roomCharges;		//객실 가격	
	//소스코드수정
	int grade;							//객실평가에 대한 변수
	void Database();		//객실의 정보를 가지는 DB함수
	void status();		//객실의 상태 정보를 가지는 DB함수
	int findRoomNo(int TYPE);		//사용가능한 객실을 알 수 있는 함수
	void bookRoom(int roomNo);		//객실 예약하는 함수
	unsigned long retRoomCharges(int roomNo);	//객실의 가격을 저장하는 DB 함수
	void releaseRoom(int roomNo);		//해당 객실을 해제
}r;										//ROOMS r

class CUSTOMER		//사용자 정보 
{
public:
	int Roomn;		//사용자가 예약하는 객실의 호수	
	char name[30];		//사용자의 이름
	char add[30];		//주소 선언하는 배열
	char phone[20];		//연락처 선언하는 배열
	int daysStayed;		//숙박 기간	
	int DAY, MONTH, YEAR;		//숙박 날짜
	long amount;		//객실의 가격
	void searchRoomNo();		//사용자가 찾고자 하는 객실을 번호로 찾는함수 
	void searchCust();		//사용자를 검색하는 함수
	void check_in();		//객실 예약에 대한 함수
	void check_out();		//사용자의 퇴실 정보 함수
	void reports();		//방을 사용한 가격에 대한 함수
	void previous_Customer();		//호텔 이용 중인 고객 정보 함수
};
int DAY, MONTH, YEAR;



void ROOMS::Database()		//객실의 DB 저장하는 함수
{
	fstream fin("rooms", ios::binary | ios::in);		//이진 파일 입력
	fin.close();
	for (int i = 1;i <= 200;i++)
	{
		if (i<100)		//객실 1~100호정보 
		{
			r.roomNo = i;
			r.roomStatus = 0;
			r.roomCharges = 300;
			r.roomType = 0;
			fstream fout("rooms", ios::binary | ios::app);		//
			fout.write((char*)&r, sizeof(r));
			fout.close();
		}
		else if (i >= 101 && i <= 150)		//객실 101~150호 정보
		{
			r.roomNo = i;
			r.roomStatus = 0;
			r.roomCharges = 500;
			r.roomType = 1;
			fstream fout("rooms", ios::binary | ios::app);
			fout.write((char*)&r, sizeof(r));
			fout.close();
		}
		else if (i>150 && i <= 200)		//객실 150~200호 정보
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
void CUSTOMER::searchCust()		//사용자를 검색하는 함수
{
	system("cls");
	basic();
	struct date d;
	getdate(&d);		//날짜를 입력 받음	
	DAY = d.da_day;
	MONTH = d.da_mon;
	YEAR = d.da_year;
	int flag = 0;
	char NAME[20];
	gotoxy(32, 3); cout << "H I L L   V I E W";
	gotoxy(26, 5); cout << "C U S T O M E R    D E T A I L";
	gotoxy(5, 15);cout << "Enter Customer's Name : ";
	gets_s(NAME);		//사용자의 이름을 입력 받음
	CUSTOMER c;
	fstream fin("cust", ios::binary | ios::in);		//이진 입력으로 cust파일을 입력 받음
	while (fin.read((char*)&c, sizeof(c)))		//파일의 끝까지 모든 레코드를 읽겠다
	{
		if (strcmp(NAME, c.name) == 0)		//파일의 내용과 같으면 정보출력
		{
			flag = 1;
			gotoxy(40, 15);cout << "Room Number: " << c.Roomn;		//객실 번호 출력
			gotoxy(40, 16);cout << "Customer Name : " << c.name;		//사용자 이름 출력
			gotoxy(40, 17);cout << "Address: " << c.add;		//사용자 주소 출력
			gotoxy(40, 18);cout << "Phone No. : " << c.phone;		//사용자 연락처 출력
			gotoxy(40, 19);cout << "Check-in : " << c.DAY << "/" << c.MONTH << "/" << c.YEAR;		//체크인 날짜 출력
			break;
		}
	}
	fin.close();
	if (flag == 0)
	{
		gotoxy(40, 15);	cout << "No such Name Found !!!";
	}
	_getch();		//출력뒤에 화면이 바로 넘어가면 안되게 때문에 값을 입력받을때까지 기다리도록 함
	closegraph();	//그래픽모드를 닫고 텍스트모드로 집입
	restorecrtmode();	//graph에서 설정했던 값들로 화면 모드를 복구
}

int ROOMS::findRoomNo(int TYPE)
{
	ROOMS r;
	int RNO, flag = 0;
	fstream fin("rooms", ios::binary | ios::in);		//
	while (fin.read((char*)&r, sizeof(r)))		//파일의 끝까지 모든 레코드를 읽음
	{
		if (TYPE == r.roomType)		//파일의 정보와 비교
		{
			if (r.roomStatus == 0)		//객실 사용 가능
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
		return 0;				//findRoomNo가 0을 반환한다면 방을 찾을 수 없다.
	else if (flag == 1)
		return RNO;				//findRoomNo가 룸넘버를 반환한다면 방을 사용할 수 있다.
	else if (flag == 2)
		return -1;				//findRoomNo가 -1이라면 누군가 방을 예약중이다
	return 0;
}


void CUSTOMER::searchRoomNo()															//방번호로 방을 검색해주는 함수
{
	system("cls");																		//화면 지우기
	basic();																			//기본사각형을그린다
	struct date d;																		//날짜에대한 구조체
	getdate(&d);							
	DAY=	d.da_day;
	MONTH=	d.da_mon;
	YEAR=	d.da_year;																	//날짜,달,연도를 받아온다
	int roomno, flag=0;																	//방번호에 대한 roomno변수, 방을 예약했는지 안했는지를 확인할 flag변수를 선언
	gotoxy(32,3); cout<<"H I L L  V I E W ";
	gotoxy(26,5);cout<<"C U S T O M E R   D E T A I L ";
	gotoxy(5,15);cout<<"Enter Room Number : ";
	cin>>roomno;																		//찾고자하는 방번호를 입력받아 roomno변수에 입력해준다.
	CUSTOMER c;
	fstream fin("cust", ios::binary | ios::in);											//fin파일을 이진 입력형태로 열겠다.(읽어오겠다.)
	while(fin.read((char *) &c, sizeof(c)))												//파일의 끝까지 모든 레코드를 읽겠다.
	{
		if(roomno==c.Roomn)																//만약 찾고자 하는 방이 파일안에 있다면
		{
			flag=1;																		//방이 있다면 flag = 1로 바꿔준다.
			gotoxy (40,15);cout<<"Room Number: "<<c.Roomn;
			gotoxy (40,16);cout<<"Customer Name : "<<c.name;
			gotoxy (40,17);cout<<"Address: "<<c.add;
			gotoxy (40,18);cout<<"Phone No. : "<<c.phone;
			gotoxy (40,19);cout<<"Check-in : "<<c.DAY<<"."<<c.MONTH<<"."<<c.YEAR;		//기타 방에 대한 정보를 출력해준다.(예약한 고객의 이름, 주소, 전화번호, 체크인날짜)
			break;
		}
	}
	fin.close();																		//fin파일 실행 종료
	if(flag==0)																			//flag = 0이라는것은 찾는 방이 없다는 얘기
	{
		gotoxy(40, 15);
		cout<<"No such Room No. Found !!!";												//방을 찾을 수 없다고 출력
	}
	_getch();																			//출력뒤에 화면이 바로 넘어가면 안되게 때문에 값을 입력받을때까지 기다리도록 한다.
	closegraph();																		//그래픽모드를 닫고 텍스트모드로 집입하겠다.
	restorecrtmode();																	//graph에서 설정했던 값들로 화면 모드를 복구한다.
}


void CUSTOMER::reports()																//방을 사용한 가격에 대한 함수
{
	system("cls");																		//화면을 지운다.
	basic();																			//기본 화면의값
	CUSTOMER c;																			//고객에 대한 구조체 c
	gotoxy(32,3); cout<<"H I L L   V I E W";	
	gotoxy(21, 5);	cout<<"C U S T O M E R  S T A Y    S U M M A R Y";
	int i=11;																			
	unsigned  long AMOUNT=0;															//가격
	fstream fin("detail", ios::binary | ios::in);										//fin
	gotoxy(7,9);																		
	cout<<"R.No NAME\t ADDRESS\t AMOUNT\t DT OF CHECK-IN\tDAYS STAYED";					
	while(fin.read((char*)&c, sizeof(c)))												//파일의 끝까지 읽겠다.
	{
		gotoxy(7, i);	cout<<c.Roomn;													
		gotoxy(12, i);	cout<<c.name;													
		gotoxy(23, i);	cout<<c.add;													//고객의 방번호와 이름 주소 출력
		gotoxy(37, i);																
		if(c.amount==-1)
			cout<<"N/A";																//해당사항없다.	
		else
		{
			cout<<c.amount<<"/=";														
			AMOUNT=AMOUNT+c.amount;														//호텔의 총소득
		}
		gotoxy(50, i);	cout<<c.DAY<<"/"<<c.MONTH<<"/"<<c.YEAR;
		gotoxy(68, i);
		if(c.daysStayed==-1)	
			cout<<"N/A";																//해당사항없다.
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
	gotoxy(27, 25);	cout<<"< Net Amount Rs.: "<<AMOUNT<<"/= >";						//호텔의 총소득 출력
	fin.close();
	_getch();																		//출력뒤에 화면이 바로 넘어가면 안되게 때문에 값을 입력받을때까지 기다리도록 한다.
	closegraph();																	//그래픽모드를 닫고 텍스트모드로 집입하겠다.
	restorecrtmode();																//graph에서 설정했던 값들로 화면 모드를 복구한다.
}
void ROOMS::status()																//방 상태를 보여주는 함수
{
	system("cls");																	
	ROOMS r;																		//방에 대한 구조체 r
	gotoxy(8, 9);	cout<<"\tR O O M  S T A T U S";									
	fstream fin("rooms", ios::binary | ios::in);									
	gotoxy(5,19);cout<<"  R.No    Room Type  Room Charges   Status    Grade"<<"\n\n";
	int maxPageSize = 25;															//최대 페이지 사이즈는 25
	int initPageSize = 4;															//페이지 초기값은 4
	for (int i=1;i<200;i++)															//방이 200개 이므로 int i=1부터 200
	{
		fin.read((char*)&r, sizeof(r));												
		cout<<"\t"<<r.roomNo<<"\t";													

		if(r.roomType==2)															//Deluxe 방의 룸타입은 2번이므로
		{
			cout<<"Deluxe  "<<"\t";
		}
		else if(r.roomType==1)														//semi-deluxe 방의 룸타입은 1번이다
		{
			cout<<"semi-deluxe"<<"\t";
		}
		else                                                                        //둘다 아닌방은 Ordinary이다.
		{
			cout<<"Ordinary"<<"\t";										
		}
		cout<<r.roomCharges<<"\t";													//방의 가격을 화면에 출력해준다.
		cout<<r.grade<<"\t";														//방의 별점을 화면에 출력해준다.

		if(r.roomStatus==1)															//roomStatus가 1이라는 얘기는 누군가 예약or사용중인 방이라는 얘기다
			cout<<"Occupied"<<"\n";
		else                                                                        //아무도 예약하지 않은 방이므로 --------를 출력
			cout<<"--------"<<endl;

		initPageSize++;																//한 화면에 다 못담을시 초기 페이지를 ++시킨다
		if(initPageSize == maxPageSize) {                                           //만약 초기 페이지 사이즈와 최대 페이지의 수가 같아진다면 
			initPageSize = 1;														//초기 페이지를 1로 다시 초기화 시킨다

			_getch();																//입력을 기다린다.
		}
	}
	fin.close();
	_getch();																		//출력뒤에 화면이 바로 넘어가면 안되게 때문에 값을 입력받을때까지 기다리도록 한다.
}

void CUSTOMER::check_in()															//객실 예약에 대한 함수
{
	system("cls");
	int TYPE, roomno, flag;															//TYPE은 방의 타입, roomno는 방의 넘버, flag는 방을 예약했는가 안했는가에 대한 함수이다.
	char c;
	struct date d;																	//날짜를 저장하는 구조체 d
	getdate(&d); 
	DAY=d.da_day;
	MONTH=d.da_mon;
	YEAR=d.da_year;																	//날짜, 달, 연도를 d에 받아준다.
	ROOMS r;																		//방에 대한 정보를 저장하는 구조체 r
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
	}																				//앞의 c가 입력받은 값은 방의 타입이므로!
			
	gotoxy(20, 24);
	roomno=r.findRoomNo(TYPE);														//findRoomNo 함수 
	gotoxy(20, 24);																	
	if(roomno==-1)																	//roomno가 -1이라면 방을 예약할 수 없다는 뜻이다.			
	{
		cout<<"This Room Type is not available !!!";
		_getch();
		return;
	}
	else if(roomno==0)																//roomno가 0이라면 방을 찾을 수 없다는것
	{
		cout<<"Invalid room number !!!";
		_getch();
		return;
	}
	else                                                                           //방을 찾을 수 있고 예약할 수있다
	{
		CUSTOMER c;
		static char NAME[30], ADD[30], PHONE[20];	
		fstream fout("cust", ios::binary | ios::app);								// 출력하는 데이터가 파일의 제일 끝에 기록된다.
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
		strcpy(c.phone, PHONE);													//이름, 주소, 번호, 차번호를 입력받는다
		c.DAY=DAY;
		c.MONTH=MONTH;
		c.YEAR=YEAR;
		fout.write((char*)&c, sizeof(c));										//
		fout.close();															//파일을 닫는다
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
      if(roomno==c.Roomn)   //입력받은 룸넘버와, 파일에서 읽은 고객의 룸넘버를 비교했을 때 같다면
      {
         flag=1;    // flag를 1로 만들어준다.
         break;
      }
   }
   fin.close();
   if(flag==0)         // flag가 0이라면
   {
      gotoxy(28, 17);
      cout<<"The Room is Unoccupied !!!"; //입력받은 룸넘버와 파일에서 읽은 룸넘버가 다르기 때문에 이 방은 비어있다.
      _getch();
      return;
   }
   if(flag==1)         //flag가 1이라면
   {
      ROOMS r;      
      r.releaseRoom(roomno);      //room이 예약이 되어있다는 처리를 해준다.
      AMOUNT=r.retRoomCharges(roomno);
   }
   fstream fin1("cust", ios::binary | ios::in);
   fstream fout1("temp", ios::binary | ios::out);
   while(fin1.read((char*)&c, sizeof(c)))
   {
      if(roomno==c.Roomn && c.daysStayed==-1)   //룸넘버와 파일에서 읽어들인 (고객의)룸넘버와 같고 호텔 투박수가 -1일때 (-1일때 지정되지 않음을 뜻한다)
      {
         int D;
         gotoxy(23,16);   cout<<"Enter No. of Days stayed : ";      //몇일 숙박할 것인지 입력하시오
         cin>>D;
         c.daysStayed=D; 
        
        c.amount=D*AMOUNT+meal;																				//총지불금액 = 머문날*객실금액+밥값
			gotoxy(23,18);	cout<<"Total Charges are Rupees : "<<c.amount;										
			gotoxy(18,20);  cout<<"발렛 서비스를 원하시나요? (예 : 1, 아니오 : 2) : ";
			cin>>ballett;																						//발렛서비스에 대한 변수 ballett
			system("cls");
			if(ballett == 1) {gotoxy(18, 10); cout<<"차 번호 "<<Car_No<<"발렛 서비스 신청 완료. 대기중입니다.";
							  gotoxy(22, 12); cout<<"만족하셨나요? 별점을 주세요 (1~10점) : "; cin>>r.grade;
							  gotoxy(26, 14); cout<<"감사합니다 :) 안녕히가세요!" ;}
			else if(ballett == 2) {gotoxy(26, 11); cout<<"감사합니다 :) 안녕히가세요!";}
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
      if(RNO==r.roomNo)   //인자로 받은 RNO와 rooms파일에서 읽어들인 roomNo와 같을 때
      {
         gotoxy(22,25);
         cout<<"Room No '"<<RNO<<"' has been booked";   // 이 방은 예약되어 있다.
         r.roomStatus=1;               //roomStatus를 1로 바꾸어줌
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
void ROOMS::releaseRoom(int RNO)   //예약해지
{
   ROOMS r;
   int NO_DAYS;
   fstream fin("rooms", ios::binary | ios::in);
   fstream fout("temp", ios::binary | ios::out);
   while(fin.read((char*)&r, sizeof(r)))
   {
      if(RNO==r.roomNo)      //RNO와 rooms 파일에서 읽은 룸넘버가 같을 때
      {
         r.roomStatus=0;      // roomStatus를 0으로 바꾸어줌
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
unsigned long ROOMS::retRoomCharges(int RNO)   //요금 반환 메소드
{
   ROOMS r;
   long double AMOUNT;
   fstream fin("rooms", ios::binary | ios::in);
   while(fin.read((char*)&r, sizeof(r)))
   {
      if(RNO==r.roomNo)   //인자로 받은 방 번호와 rooms파일에 있는 roomNo가 같을 때
      {
         AMOUNT=r.roomCharges;   //AMOUNT에 파일에 써놓은 roomCharges를 대입한다.
         break;
      }
   }
   fin.close();
   return AMOUNT;   //AMOUNT를 반환한다.
}
void CUSTOMER::previous_Customer(void)		//예약 함수 수정해야함
{
	system("cls");
	basic();
	CUSTOMER c;
	char NAME[30];					//예약할 고객의 이름
	gotoxy(32,3); cout<<"H I L L   V I E W";
	gotoxy(5,6);cout<<"Enter customer name: ";
	gets(NAME);						//예약할 고객의 이름을 받음
	fstream fin("detail", ios::binary | ios::in);
	while(fin.read((char*)&c, sizeof(c)))
	{
		if(strcmp(c.name,NAME)==0)				//c,name이랑 NAME을 비교하여 같으면 실행
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
void enter_password()				//처음메인화면 들어갈때 비밀번호 함수
{
	system("cls");
	char pass[10],c;
	int i =0;
	gotoxy(25,18);cout <<"Enter the password : " ;
	do{
		c = _getch();			//비밀번호를 받음
		if(c==8) {cout<<'\b'<<' '<<'\b';i--;}		// back space일 경우 받는 문자를지음
		else if(c!=13) {cout<<'*';pass[i]=c;i++;}	// Enter칠때까지 받는 문자열을 *로 표시
	}
	while(c!=13);			// Enter 치지않으면 계속 실행(Enter 치면 종료)
	pass[i]='\0';			//나머지 쓰레기값방지용

	if (strcmp(pass,"1234")==0)			//입력받은 비밀번호랑 설정한 비밀번호 확인후 같으면 종료
		return ;
	gotoxy(28,20);cout <<"   WRONG PASSWORD    " ;	//입력받은 값이랑 다를때
	_getch() ;
	exit(0) ;
}


void main()
{
	basic();

	
	char c;
	
	textcolor(GREEN);	
	void graph(void);

	
	void enter_password();		//메인페이지 들어가기전 비밀번호확인 함수 호출

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
		gotoxy (5,12);cout<<"1. Search";			//메인화면에 나오는 문자들
		gotoxy (5,13);cout<<"2. Check in";
		gotoxy (5,14);cout<<"3. Check out";
		gotoxy (5,15);cout<<"4. Room status";
		gotoxy (5,16);cout<<"5. Earnings";
		gotoxy (5,17);cout<<"6. Previous Customers";
		gotoxy (5,18);cout<<"0. Exit";
		gotoxy(30,21);	cout<<"Enter choice : ";
		do{c=_getch();				//받는 값을 c값에 넣어줌
		if(c>=48 &&c<=54) {cout<<c; delay(500);}		//받은 c 값이 0이상 6이하면 if문실행
		}while(c<48 || c>54);					//받은 c 값이 0이상 6이하가 아니면 계속실행
		switch(c)						//위에서 받은c값으로 switch문 실행
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
		case 1:	{					//메인 페인지에서 1. Search 들어갈때
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
					if(ch>=48 &&ch<=50) {cout<<ch;delay(500);}		//0이상 2이하일때 값을 받음
				}
				while(ch<48 || ch>50);			//0이상 2이하가 아닐경우 계속실행
				switch(ch)				//메인 페인지에서 1. Search 들어가서 다음 Room 또는 이름으로 찾기
				{ 
				case '0':choice =0;break;
				case '1' : choice =1;break;
				case '2':choice=2;break;
				}

				closegraph();
				restorecrtmode();
				switch(choice)
				{
				case 1:	{				//이름으로 찾기
					CUSTOMER c;
					c.searchCust();
					break;
						}
				case 2:	{				//룸번호로 찾기
					CUSTOMER c;
					c.searchRoomNo();
					break;
						}
				}
			}while(choice!=0);				//0입력아닐때까지 계속 입력
			break;
				}
		case 2:	{						//메인 페인지에서 2.check in 들어갈때 check _in()실행
			CUSTOMER c;
			c.check_in();
			break;
				}

		case 3:	{						//메인 페인지에서 3.check out 들어갈때 check_out()실행
			CUSTOMER c;
			c.check_out();
			break;
				}
		case 4:	{						//메인 페인지에서 4.Room status 들어갈때 r.status()실행
			ROOMS r;
			r.status();
			break;
				}
		case 5:	{						//메인 페이지에서 5.repots 들어갈때 c.reports();실행
			CUSTOMER c;
			c.reports();
			break;
				}
		case 6: {						//메인 페이지에서 6.previous_Customer 들어갈때 c.previous_Customer();실행
			CUSTOMER c;
			c.previous_Customer();
			break;
				}

		}
	}while(choice!=0);						//0입력아닐때까지 계속 입력
	
}