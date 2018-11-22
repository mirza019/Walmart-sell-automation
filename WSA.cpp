#include<iostream>
#include<windows.h>
#include<conio.h>u
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;
int k=7,r=0,flag=0;
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{int mm,dd,yy;};
ofstream fout;
ifstream fin;
class CalculateGross
{
public:
    float price,tax,gross;
    CalculateGross operator ++ () //operator overloading
    {
        CalculateGross temp;
        temp.gross=price+(price*(tax/100));
        return temp;
    }
};
class CalculateNet
{
public:
    float qty,gross,dis,netamt;
    CalculateNet operator -- ()
    {
      CalculateNet temp;
      temp.netamt=qty*(gross-(gross*(dis/100)));
      return temp;
    }
};
class item
{
public:
int itemno;
char name[25];
date d;
void add()
{
 cout<<"\n\n\tNumber: ";
 cin>>itemno;
 cout<<"\n\n\tName of the Product: ";
 cin>>name;
 cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
 cin>>d.mm>>d.dd>>d.yy;
}
void show()
{
 cout<<"\n\tProduct No: ";
 cout<<itemno;
 cout<<"\n\n\tName of the Product: ";
 cout<<name;
 cout<<"\n\n\tDate : ";
 cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
}
void report()
{
gotoxy(3,k);
cout<<itemno;
gotoxy(13,k);
puts(name);
}
int retno()
{
    return(itemno);
}
};
class amount: public item
{
public:
float price,qty,tax,gross,dis,netamt;
void add(); //overriding
void show();
void report();
void calculate();
void pay();
float retnetamt()
{
    return(netamt);
}

}amt;
void amount::add()
{
 item::add();//function overriding from base class
 cout<<"\n\n\tPrice: ";
 cin>>price;
 cout<<"\n\n\tQuantity: ";
 cin>>qty;
 cout<<"\n\n\tTax percent: ";
 cin>>tax;
 cout<<"\n\n\tDiscount percent: ";
 cin>>dis;
 calculate(); //operator overloading
 fout.write((char *)&amt,sizeof(amt));//writing info to file
 fout.close();
}
void amount::calculate()
{
 CalculateGross A,C;
 A.price=price;
 A.tax=tax;
 C = ++A;
 gross=C.gross;//handling operator overloading in one variable
 CalculateNet B,D;
 B.qty=qty;
 B.gross=gross;
 B.dis=dis;
 D = --B;
 netamt=D.netamt;
}
void amount::show()
{
 fin.open("itemstore.dat",ios::binary);
 fin.read((char*)&amt,sizeof(amt));
 item::show();
 cout<<"\n\n\tNet amount: ";
 cout<<netamt;
 fin.close();
}
void amount::report()
{
 item::report();
 gotoxy(23,k);
 cout<<price;
 gotoxy(33,k);
 cout<<qty;
 gotoxy(44,k);
 cout<<tax;
 gotoxy(52,k);
 cout<<dis;
 gotoxy(64,k);
 cout<<netamt;
 k=k+1;
 if(k==50)
 {
  gotoxy(25,50);
  cout<<"PRESS ANY KEY TO CONTINUE...";
  getch(); // oi function er prothom e jabe
  k=7;
  system("cls"); //new screen nia asbe
  gotoxy(30,3);
  cout<<" PRODUCT INFORMATIONS ";
  gotoxy(3,5);
  cout<<"NUMBER";
  gotoxy(13,5);
  cout<<"NAME";
  gotoxy(23,5);
  cout<<"PRICE";
  gotoxy(33,5);
  cout<<"QUANTITY";
  gotoxy(44,5);
  cout<<"TAX";
  gotoxy(52,5);
  cout<<"DISCOUNT";
  gotoxy(64,5);
  cout<<"NET AMOUNT";
}

}
void amount::pay()
{
 show();
 cout<<"\n\n\n\t\t*********************************************";
 cout<<"\n\t\t                 DETAILS                  ";
 cout<<"\n\t\t*********************************************";
 cout<<"\n\n\t\tPRICE                     :"<<price;
 cout<<"\n\n\t\tQUANTITY                  :"<<qty;
 cout<<"\n\t\tTAX PERCENTAGE              :"<<tax;
 cout<<"\n\t\tDISCOUNT PERCENTAGE         :"<<dis;
 cout<<"\n\n\n\t\tNET AMOUNT              :TK."<<netamt;
 cout<<"\n\t\t*********************************************";
}
void coverPage();
void coverPage()
{
system("cls");
gotoxy(20,2);
cout<<"My project is about Walmart Stock Automation. ";
gotoxy(12,3);
cout<<"It represents the current stock information of Walmart Warehouse ";
gotoxy(28,6);
cout<<"Student's Name =>    Mirza Shaheen Iqubal";
gotoxy(28,7);
cout<<"Student's ID =>    2015-1-60-019";
gotoxy(28,8);
cout<<"Course=>    Object Oriented Program ";
gotoxy(28,9);
cout<<"Section        =>         07";
gotoxy(28,10);
getch();
system("cls");

}
int main()

{
coverPage();
cout.setf(ios::fixed);
cout.setf(ios::showpoint);
cout<<setprecision(2);
fstream tmp("temp.dat",ios::binary|ios::out);
menu:
system("cls");
gotoxy(25,2);
cout<<"Walmart Stock Automation";
gotoxy(25,3);
cout<<"************************\n\n";
cout<<"\n\t\t1.Stock Informations\n\n";
cout<<"\t\t2.Add Data or Modify Data or Erase Data\n\n";
cout<<"\t\t3.Display Item's Informations\n\n";
cout<<"\t\t4.Quit\n\n";
cout<<"\t\tEnter To Choose Option: ";
int ch,ff;
float gtotal;
cin>>ch;
switch(ch)
{
 case 1:
 ss:
 system("cls");
 gotoxy(25,2);
 cout<<"  Stock Informations";
 gotoxy(25,3);
 cout<<"****************\n\n";
 cout<<"\n\t\t1.Available Products\n\n";
 cout<<"\t\t2.Jump on Main Menu\n\n";
 cout<<"\t\tEnter To Choose Option: ";
 int cho;
 cin>>cho;
 if(cho==1)
 {
  system("cls");
  gotoxy(30,3);
  cout<<" STOCK Informations ";
  gotoxy(3,5);
  cout<<"Product NO";
  gotoxy(13,5);
  cout<<"Name";
  gotoxy(23,5);
  cout<<"Price(TK)";
  gotoxy(33,5);
  cout<<"Quantity";
  gotoxy(44,5);
  cout<<"Tax(%)";
  gotoxy(52,5);
  cout<<"Discount(%)";
  gotoxy(64,5);
  cout<<"Net Amount";
  fin.open("itemstore.dat",ios::binary);
  if(!fin)
  {
   cout<<"\n\nFile Not Found...";
   goto menu;
  }
  fin.seekg(0);
  gtotal=0;
  while(!fin.eof())
  {
   fin.read((char*)&amt,sizeof(amt));
   if(!fin.eof())
   {
    amt.report();
    gtotal+=amt.retnetamt();
    ff=0;
   }
   if(ff!=0) gtotal=0;
  }
  gotoxy(17,k);
  cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
  getch();
  fin.close();
 }
if(cho==2)
{
    goto menu;
}
goto ss;
case 2:
db:
system("cls");
gotoxy(25,2);
cout<<"Stock Editor";
gotoxy(25,3);
cout<<"=================\n\n";
cout<<"\n\t\t1.Add Product Informations\n\n";
cout<<"\t\t2.Modify Product Informations\n\n";
cout<<"\t\t3.Erase Product Informations\n";
cout<<"\t\t4.Jump to Main Menu ";
int apc;
cin>>apc;
switch(apc)
{
case 1:fout.open("itemstore.dat",ios::binary|ios::app);
amt.add();
cout<<"\n\t\tProduct Added Successfully!";
getch();
goto db;
case 2:
int ino;
flag=0;
cout<<"\n\n\tEnter Product Number to be Modified :";
cin>>ino;
fin.open("itemstore.dat",ios::binary);
fout.open("itemstore.dat",ios::binary|ios::app);
if(!fin)
{cout<<"\n\nFile Not Found...";
goto menu;
}
fin.seekg(0);
r=0;
while(!fin.eof())
{fin.read((char*)&amt,sizeof(amt));
if(!fin.eof())
{int x=amt.item::retno();
if(x==ino)
{flag=1;
fout.seekp(r*sizeof(amt));
system("cls");
cout<<"\n\t\tCurrent Informations are\n";
amt.show();
cout<<"\n\n\t\tEnter New Informations\n";
amt.add();
cout<<"\n\t\tProduct Informations Modified";
}
}r++;
}
if(flag==0)
{cout<<"\n\t\tProduct No does not exist...Try again later!!!";
getch();
goto db;
}
fin.close();
getch();
goto db;
case 3:flag=0;
cout<<"\n\n\tEnter Product Number to be erased :";
cin>>ino;
fin.open("itemstore.dat",ios::binary);
if(!fin)
{cout<<"\n\nFile Not Found...";
goto menu;
}
fin.seekg(0);
while(fin.read((char*)&amt, sizeof(amt)))
{int x=amt.item::retno();
if(x!=ino)
tmp.write((char*)&amt,sizeof(amt));
else
{flag=1;}
}
fin.close();
tmp.close();
fout.open("itemstore.dat",ios::trunc|ios::binary);
fout.seekp(0);
tmp.open("temp.dat",ios::binary|ios::in);
if(!tmp)
{cout<<"Error in File";
goto db;
}
while(tmp.read((char*)&amt,sizeof(amt)))
fout.write((char*)&amt,sizeof(amt));
tmp.close();
fout.close();
if(flag==1)
cout<<"\n\t\tProduct Successfully Erased";
else if (flag==0)
cout<<"\n\t\tProduct does not Exist! Please try again later!!!";
getch();
goto db;
case 4:
goto menu;
default: cout<<"\n\n\t\tWrong Choice!!! Retry";
getch();
goto db;
}
case 3:system("cls");
flag=0;
int ino;
cout<<"\n\n\t\tEnter Item Number :";
cin>>ino;
fin.open("itemstore.dat",ios::binary);
if(!fin)
{cout<<"\n\nFile Not Found...\nProgram Terminated!";
goto menu;
}
fin.seekg(0); //set cursor position initial
while(fin.read((char*)&amt,sizeof(amt)))
{int x=amt.item::retno();
if(x==ino)
{amt.pay();
flag=1;
break;
}
}
if(flag==0)
cout<<"\n\t\tProduct does not exist....Please Try again later!";
getch();
fin.close();
goto menu;

case 4:system("cls");
gotoxy(10,19);
cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
char yn;
cin>>yn;
if((yn=='Y')||(yn=='y'))
{
 gotoxy(12,20);
 system("cls");
 cout<<"************************** THANKS **************************************";
 getch();
 exit(0);
}
else if((yn=='N')||(yn=='n'))
goto menu;
else{goto menu;}
default:cout<<"\n\n\t\tWrong Choice....Please Retry!";
getch();
goto menu;
}
return 0;
}