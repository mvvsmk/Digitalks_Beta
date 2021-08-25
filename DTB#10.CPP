#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>

class data                              //CLASS DATA
{
 char id[35],pwd[20],name[35];
 int s_no;

 public:

 static int count;
 void input()
 {
  cout<<"Enter name\n";
  gets(name);
  cout<<"Enter User ID\n";
  cin>>id;
  cout<<"Enter Password\n";
  cin>>pwd;
  s_no=++count;
 }
 void display()
 {
  cout<<"User#"<<s_no
      <<"\nName - "<<name
      <<"\nID - "<<id
      <<"\nPassword - "<<pwd<<endl;
 }

 void getid(char org[])
 {
  strcpy(org,id);
 }
 void getpwd(char pass[])
 {
  strcpy(pass,pwd);
 }
} ;

int data::count=0;

void u_interface(data d);
void main();
void inbox(data d);
void compose(data d);
void sent(data d);
void add_book(data d);
void checkid(data d);
void checkrid(data d,char ID[35]);


class message                                       //CLASS MESSAGE
{
 char s_id[35],r_id[35],sub[40],msg[80];

 public:
 void getS_ID(char s[])
 {
  strcpy(s,s_id);
 }
 void getR_ID(char s[])
 {
  strcpy(s,r_id);
 }
 void get_sub(char s[])
 {
  strcpy(s,sub);
 }

 void send_message (data d)
 {
  d.getid(s_id);
  cout<<"TO - ";
  cin>>r_id;
  cout<<"\nSubject:- ";
  gets(sub);
  cout<<"\nMessage-\n";
  gets(msg);
 }
 void read_message()
 {
  clrscr();
  cout<<"TO -"<<r_id;
  cout<<"\nFrom - "<<s_id;
  cout<<"\nSubject:- "<<sub;
  cout<<"\n\nMessage\n"<<msg<<endl;
 }
};

class relation                             //CLASS RELATION(ADDRESS BOOK)
{
 char s_id[35],r_id[20];

 public:

 void relationN(char a[],char b[])
 {
 strcpy(s_id,a);
 strcpy(r_id,b);
 }
 void S_id(char a[])
 {
  strcpy(a,s_id);
 }
 void R_id(char a[])
 {
  strcpy(a,r_id);
 }
};

void checkid(data d)                                //Check Id
{
 data d1;
 char id[35],n_id[35];
 d.getid(n_id);
 fstream f("USER_DETIALS.DAT", ios::binary| ios::in);
 while(f.read((char*)&d1,sizeof(d1)))
 {
  d1.getid(id);
  if(strcmp(id,n_id)==0)
  {
   cout<<" USER ID not available \n";
   cout<<"PRESS ANY KEY TO GOTO MAIN PAGE\n";
   getch();
   main();
  }
 }
}

void checkrid(data d,char n_ID[35])                           //CHECK Rid
{
 data d1;
 char id[35];
 int flag=0;
 fstream f("USER_DETIALS.DAT", ios::binary| ios::in);
 while(f.read((char*)&d1,sizeof(d1)))
 {
  d1.getid(id);
  if(strcmp(id,n_ID)==0)
   flag=1;
 }
 if(flag==0)
 {
  cout<<"\4 USER ID DOSEN'T EXIST \4\n";
  cout<<"PRESS ANY KEY TO GOTO USER INTERFACE\n";
  getch();
  u_interface(d);
 }
}

void u_interface(data d)                                 //UI
{
  clrscr();
  int i;
  cout<<"USER INTERFACE\n\n1:Inbox\n2:Sent\n3:Compose\n4:View adddress book \n5:Log Out\n\nEnter choice : ";
  cin>>i;
  switch (i)
  {
   case 1 :inbox(d);
   break;
   case 2 :sent(d);
   break;
   case 3 :compose(d);
   break;
   case 4 :add_book(d);
   break;
   case 5 :clrscr();
   cout<<"\t\t\t\t   LOGGED OUT";
   getch();
   main();
   break;
   default :cout<<"Wrong Input\n";u_interface(d);
   break;
  }
  getch();
}

void add_book(data d)                                        //ADDBOOK
{
 clrscr();
 cout<<"\t\t\t\t  ADDRESS BOOK\n";
 int i=0,c=1;
 relation r,r1;
 char id[35];
 d.getid(id);
 char s_id[35],r_id[35];
 fstream f("BOOK.DAT" , ios::binary | ios::in);
 while(f.read((char*)&r,sizeof(r)))
 {
  r.S_id(s_id);
  r.R_id(r_id);

  if (strcmp(id,s_id)==0)
  {
   cout<<"\n"<<c<<"\t"<<r_id;
   i++;
   c++;
  }
  else if(strcmp(id,r_id)==0)
  {
   cout<<"\n"<<c<<"\t"<<s_id;
   i++;
   c++;
  }
 }
 if(i==0)
 {
  cout<<"NO RECORDS PRESENT";
 }
cout<<"\n\nPRESS ANY KEY TO RETURN TO USER INTERFACE\n";
getch();
u_interface(d);
}


void inbox(data d)                                        //INBOX
{
 d.display();
 message m;
 clrscr();
 int i=1;
 cout<<"INBOX\n\n";
 fstream f("Mailbox.dat",ios::binary|ios::in);
 while(f.read((char*)&m,sizeof(m)))
 {
  char r[35],id[35];
  m.getR_ID(r);
  d.getid(id);
  if(strcmp(r,id)==0)
  {
    char p[35];
    cout<<i<<"\t";
    m.getS_ID(p);
    cout<<p<<"\t";
    m.get_sub(p);
    cout<<p;
    cout<<endl;
    i++;
  }
 }
 f.close();

 if(i==1)
  cout<<"EMPTY INBOX\n";
 else
 {
  f.open("Mailbox.dat", ios::binary|ios::in);
  int j;
  cout<<"\nEnter message number you want to view\n";
  cin>>j;
  i=1;
  char r[35],id[35];
  while(f.read((char*)&m,sizeof(m))&&i<=j)
  {
   m.getR_ID(r);
   d.getid(id);
   if(strcmp(r,id)==0)
   {
    if (i==j)
      m.read_message();
    i++;
   }
  }
 }
 cout<<"\nEnter Choice\n1)Inbox\n2)User Interface\n";
 cin>>i;
 switch(i)
 {
  case 1:inbox(d);
  break;
  case 2:u_interface(d);
  break;
  default :cout<<"Wrong input\n";
 }
getch();
}

void compose(data d)                                        //COMPOSE
{
 clrscr();
 int i;
 char r_id[35];
 message m;
 cout<<"\t\t\t\t   COMPOSE\n\n\n";
 m.send_message(d);
 m.getR_ID(r_id);
 cout<<"\n1)Send\t2)Cancel\n";
 cin>>i;
 if(i==1)
 {
  checkrid(d,r_id);
  fstream obj;
  obj.open("Mailbox.dat",ios::binary|ios::app);
  obj.write((char*)&m,sizeof(m));
  obj.close();
  cout<<"\nMail Sent\nPress any key to return to home screen\n";
  getch();

  int ch=0;
  relation r;
  char id[35];
  d.getid(id);
  fstream f2("BOOK.DAT" , ios::binary | ios::in);
  char s[35],re[35];
  while(f2.read((char*)&r,sizeof(r)))
  {
   r.S_id(s);
   r.R_id(re);
   if(strcmp(id,s)==0 || strcmp(id,re)==0)
   {
    ch++;
    break;
   }
  }
  f2.close();
  if(ch==0)
  {
  char s_id[35];
  d.getid(s_id);
  fstream f1("BOOK.DAT" , ios::binary|ios::app);
  r.relationN(s_id,r_id);
  f1.write((char*)&r,sizeof(r));
  f1.close();
  }
 }
 u_interface(d);
}

void sent(data d)                                         //SENT
{
 int i=1;
 message m;
 clrscr();
 cout<<"SENT\n\n";
 fstream f("Mailbox.DAT",ios::binary | ios::in);
 char s[35],id[35];
 while(f.read((char*)&m,sizeof(m)))
 {
  m.getS_ID(s);
  d.getid(id);
  if(strcmp(s,id)==0)
  {
    char p[35];
    cout<<i<<"\t";
    m.getR_ID(p);
    cout<<p<<"\t";
    m.get_sub(p);
    cout<<p;
    cout<<endl;
    i++;
  }
 }
 f.close();
 if(i==1)
  cout<<"No Message Sent\n";
 else
 {
  f.open("Mailbox.DAT", ios::binary|ios::in);
  int j;
  cout<<"\nEnter message number you want to view\n";
  cin>>j;
  i=1;
  char s[35],id[35];
  while(f.read((char*)&m,sizeof(m))&&i<=j)
  {
    m.getS_ID(s);
    d.getid(id);
    if(strcmp(s,id)==0)
    {
     if (i==j)
      m.read_message();
     i++;
    }
  }
 }
 cout<<"\nEnter Choice\n1)SENT\n2)User Interface\n";
 int ch;
 cin>>ch;
 switch(ch)
 {
   case 1:sent(d);
   break;
   case 2:u_interface(d);
   break;
   default :cout<<"Wrong input\n";
 }
 f.close();
 getch();
}

void log_in()                                         //LOG IN
{
 clrscr();
 data d ;
 int e=1;
 char ID[35],P[20];
 do
 {
  if(e!=1)
  {cout<<"\nWrong ID or Password\n";
   cout<<"\nTRY NO:- "<<e<<endl;
  }
  cout<<"Enter User ID\n";
  cin>>ID;
  cout<<"Enter Password \n";
  cin>>P;
  fstream f("User_Details.dat",ios::binary|ios::in);
  while(f.read((char*)&d,sizeof(d)))
  {
   char org[35],pass[20];
   d.getid(org);
   d.getpwd(pass);
   if(strcmp(ID,org)==0 && strcmp(pass,P)==0)
   {
    cout<<"\nLog In Successful\nPress any key to proceed";
    getch();
    u_interface(d);
   }
  }
 e++;
 }while(e<=3);

 cout<<"\nWrong ID or Password\nPress any key to return to main menu\n";
 getch();
 main();
}

void sign_up()                                             //SIGN IN
{
 clrscr();
 fstream obj;
 obj.open("User_Details.dat",ios::binary|ios::app);
 char ch;
 data d;
 cout<<"REGISTER\n\n";
 d.input();
 checkid(d);
 obj.write((char*)&d,sizeof(d));
 obj.close();
 cout<<"\nRegistration Successful\nPress any key to return to main menu\n";
 getch();
 main();
}


void main()                                                 //MAIN
{
 int i;
 clrscr();
 cout<<"Welcome to DIGITALKS\n\nEnter Choice\n";
 cout<<"1)Sign Up\n2)Log In\n3)Exit\n\n";
 cin>>i;
 switch(i)
 {
  case 1:sign_up();
  break;
  case 2:log_in();
  break;
  case 3:exit(0);
  break;
  default :cout<<"Wrong Input\n";
  break;
 }
getch();
}

