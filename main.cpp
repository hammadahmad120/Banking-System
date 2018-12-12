#include<iostream>
#include <fstream>         //header for file handling
#include<cctype>       //header for function like to_upper or to_lower
#include<string>   //header for string objects
#include "bank.h"
#include "account.h"
#include "console.h"
using namespace std;
void create_account();    //to add new account
void deposit(int, int);     //to deposit or withdraw amount
void loan(int);            //to get loan facility
void display_all();            //to see all account holders list
void bank_budget();            //to see bank amount details
void display_your(int);  //to see specific amount 
void transfer(int);   //to transfer amount to another account
void html();         //to write all accounts list in html file
void main()
{
	html();
	bank b;
	int no;
	SetEntireConsoleColor(AQUA, LIGHT_GREEN);
	ButtonInfo buttons[10] = { { "** Create New Account **", { 25, 6 } }, //to handle location of menu
	{ "** Deposit Amount **", { 25, 8 } },
	{ "** Withdraw Amount **", { 25, 10 } },
	{ "** Loan Facility **", { 25, 12 } },
	{ "** Account Holders List **", { 25, 14 } },
	{ "** Bank Balance **", { 25, 16 } },
	{ "** Bank Info **", { 25, 18 } },
	{ "** Account Info **", { 25, 20 } },
	{ "** Transfer Amount **", { 25, 22 } },
	{ "( Exit )", { 55, 24 } }
	};
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);  //for mouse handling,,wrtie this in every function
	int choice = 0;

	while (choice != 10)
	{
		system("CLS");
		choice = ProceedMenuButtonsKAM(buttons, 10, AQUA, LIGHT_GREEN, RED); //to select background,foreground and text color
		switch (choice + 1)
		{
		case 1:
			system("CLS");
			create_account();
			cin.ignore();
			cin.get();
			break;
		case 2:
			system("CLS");
			cout << "\n\n\tEnter The account No. to deposit : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> no;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			deposit(no, 1);
			cin.ignore();
			cin.get();
			break;
		case 3:
			system("CLS");
			cout << "\n\n\tEnter The account No. : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> no;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			deposit(no, 2);
			cin.ignore();
			cin.get();
			break;
		case 4:
			system("CLS");
			cout << "\n\n\tEnter The account No. : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> no;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			loan(no);
			cin.ignore();
			cin.get();
			break;
		case 5:
			system("CLS");
			display_all();
			cin.ignore();
			cin.get();
			break;
		case 6:
			system("CLS");
			bank_budget();
			cin.ignore();
			cin.get();
			break;
		case 7:
			system("CLS");
			b.bank_info();
			cin.ignore();
			cin.get();
			break;
		case 8:
			system("CLS");
			cout << "enter your account number : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> no;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			display_your(no);
			cin.ignore();
			cin.get();
			break;
		case 9:
			system("CLS");

			cout << "enter your account number : ";
			cin >> no;
			transfer(no);
			cin.ignore();
			cin.get();
			break;
		case 10:
			system("CLS");
			cout << "\n\n\tTHANKS FOR BEING PART OF OUR BANK....\n\n\n\t\t\tTAKE CARE...ALLAH HAFIZ !!!";
			cin.ignore();
			cin.get();
			exit(-1);
			break;
		default:cout << "\a";
		}
	}
}
void create_account()
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	account p;
	int temp = 0;
	int acno;
	ifstream in;
	ofstream out;
	out.open("accountdetail.dat", ios::binary | ios::app);

	do
	{
		cout << "enter account number : ";
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);   //to enable mouse
		cin >> acno;
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);   //to disable mouse
		temp = 0;
		in.open("accountdetail.dat", ios::binary);
		while (!in.eof())
		{
			in.read(reinterpret_cast<char*>(&p), sizeof(p));

			if (p.getacno() == acno)       //condition to check whether id already exist or not
			{
				temp = 1;
				cout << "already exist!!!again ";

			}

		}
		in.close();
	} while (temp == 1);

	p.set_act(acno);
	out.write(reinterpret_cast<char *>(&p), sizeof(account));   //to write whole objects members in file
	out.close();
}
void transfer(int n)
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	double amt;
	int t = 0;
	account p;
	fstream File;
	File.open("accountdetail.dat", ios::binary | ios::in | ios::out);
	while (!File.eof() && t == 0)
	{
		File.read(reinterpret_cast<char*>(&p), sizeof(p));

		if (p.getacno() == n)
		{
			t = 1;
			p.show();
			cout << "\nEnter amount you wanna transfer : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> amt;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			if (amt > p.getamount())
			{
				cout << "\n\tyou donot have sufficient amount\n\nyour balance is : " << p.getamount() << " \n\nenter again : ";
				SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
				cin >> amt;
				SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);

			}
			p.withdraw(amt);
		}
	}
	int pos = (-1)*int(sizeof(p));
	File.seekp(pos, ios::cur);
	File.write(reinterpret_cast<char *> (&p), sizeof(p));
	cout << "\n\n\t Record Updated ,ur new balance is :";
	p.show();
	File.close();
	account p1;
	int x;
	cout << "\n\nEnter account number in which you want to transfer : ";
	SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
	cin >> x;
	SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
	int t1 = 0;
	fstream file;
	file.open("accountdetail.dat", ios::binary | ios::in | ios::out);
	while (!file.eof() && t1 == 0)
	{
		file.read(reinterpret_cast<char*>(&p1), sizeof(p1));

		if (p1.getacno() == x)
		{
			t1 = 1;
			p1.deposit(amt);
			cout << "\n\n\tAMOUNT DEPOSITED .... ";
		}
	}
	if (t == 0)
		cout << "\n\n\taccount doesnot exist....";
	int po = (-1)*int(sizeof(p1));
	file.seekp(po, ios::cur);
	file.write(reinterpret_cast<char *> (&p1), sizeof(p1));
	cout << "\n\n\t amount in his account is now : " << p1.getamount() << endl;
	file.close();
}
void deposit(int n, int c)
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	double amt;
	int t = 0, temp = 0;
	account p;
	fstream File;
	File.open("accountdetail.dat", ios::binary | ios::in | ios::out);
	while (!File.eof() && t == 0)
	{
		int  r5000, r1000, r500, r100, r50, r10;
		File.read(reinterpret_cast<char*>(&p), sizeof(p));   //to read single object in RAM from file 

		if (p.getacno() == n)
		{
			p.show();
			if (c == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter The amount to be deposited";
				cout << "\n5000 rupee notes : ";
				SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT); //wrtie these 2 functions before and after every input
				cin >> r5000;;
				SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				cout << "1000 rupee notes : ";
				SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
				cin >> r1000;;
				SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				cout << "500 rupee notes : ";
				SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
				cin >> r500;;
				SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				cout << "100 rupee notes : ";
				SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
				cin >> r100;;
				SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				cout << "50 rupee notes : ";
				SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
				cin >> r50;;
				SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				cout << "10 rupee notes : ";
				SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
				cin >> r10;;
				SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				amt = (r5000 * 5000 + r1000 * 1000 + r500 * 500 + r100 * 100 + r50 * 50 + r10 * 10); //total amount calculation
				cout << "total amount you entered is : " << amt << endl;
				p.forbank(amt, r5000, r1000, r500, r100, r50, r10, 1);      //funtion to handle currency notes quantity 
				p.deposit(amt);
			}
			if (c == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT \n\n";
				do{
					temp = 0;
					cout << "\n5000 rupee notes : ";


					SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
					cin >> r5000;;
					SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
					cout << "1000 rupee notes : ";
					SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
					cin >> r1000;;
					SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
					cout << "500 rupee notes : ";
					SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
					cin >> r500;;
					SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
					cout << "100 rupee notes : ";
					SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
					cin >> r100;;
					SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
					cout << "50 rupee notes : ";
					SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
					cin >> r50;;
					SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
					cout << "10 rupee notes : ";
					SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
					cin >> r10;;
					SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);

					amt = (r5000 * 5000 + r1000 * 1000 + r500 * 500 + r100 * 100 + r50 * 50 + r10 * 10);
					if (amt > p.getamount())    //condition to check whether account has sufficient amount to withdraw or not.
					{
						cout << "\nyou donot have sufficient amount,,again ";
						temp = 1;
					}
				} while (temp == 1);
				cout << "total amount you entered is : " << amt << endl;
				p.forbank(amt, r5000, r1000, r500, r100, r50, r10, 2);
				p.withdraw(amt);
			}

			int pos = (-1)*int(sizeof(p));    //to calculate location of pointer
			File.seekp(pos, ios::cur);  //to put write pointer on that location
			File.write(reinterpret_cast<char *> (&p), sizeof(p));
			cout << "\n\n\t Record Updated ,ur new balance is :";
			p.show();
			t = 1;
		}
	}
	File.close();
}
void display_your(int n)
{
	int t = 0;
	account p;
	fstream File;
	File.open("accountdetail.dat", ios::binary | ios::in | ios::out);
	while (!File.eof())
	{
		File.read(reinterpret_cast<char*>(&p), sizeof(p));

		if (p.getacno() == n&&t == 0)
		{
			cout << "===========================================================\n\n";
			cout << "AC.NO\t  NAME\t TYPE\t AMOUNT\t LOAN\tLOAN_RETURN_TIME(years)\n\n";
			cout << "===========================================================\n\n";
			p.detail();
			t = 1;
		}
	}
}
void loan(int n)
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	account p;
	double amt;
	int t;
	int temp = 0;
	fstream File;
	File.open("accountdetail.dat", ios::binary | ios::in | ios::out);
	while (!File.eof() && temp == 0)
	{
		File.read(reinterpret_cast<char *> (&p), sizeof(account));
		if (p.getacno() == n)
		{
			temp = 1;
			int r5000, r1000, r500, r100, r50, r10;
			cout << "\nenter amount you want to take for loan : ";
			cout << "\n5000 rupee notes : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> r5000;;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			cout << "1000 rupee notes : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> r1000;;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			cout << "500 rupee notes : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> r500;;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			cout << "100 rupee notes : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> r100;;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			cout << "50 rupee notes : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> r50;;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			cout << "10 rupee notes : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> r10;;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			amt = (r5000 * 5000 + r1000 * 1000 + r500 * 500 + r100 * 100 + r50 * 50 + r10 * 10);
			cout << "total amount you entered is : " << amt << endl;
			do
			{
				cout << "\nenter time duration in which you return this amount : ";
				SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
				cin >> t;
				SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				if (t > 5 || t < 0)
					cout << "maximum duration is 5 years!!! again input in range...";
			} while (t > 5 || t < 0);
			//p.forbank(0, r5000, r1000, r500, r100, r50, r10, 2);
			p.setloan(amt, t);
			int pos = (-1)*int(sizeof(p));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&p), sizeof(account));
			cout << "\n\nyour new balance and loan is : ";
			p.show();
		}
	}
	File.close();

}
void display_all()
{
	int t = 0;
	account p;
	ifstream in;
	in.open("accountdetail.dat", ios::binary);
	cout << "===========================================================\n\n";
	cout << "AC.NO\t  NAME\t TYPE\t AMOUNT\t  LOAN\tLOAN_RETURN_TIME(years)\n\n";
	cout << "===========================================================\n\n";
	cout << "___________________________________________________________\n";
	while (in.read(reinterpret_cast<char *> (&p), sizeof(account)))
	{
		t = 1;
		p.detail();
		cout << "\n___________________________________________________________\n";
	}
	if (t == 0)
		cout << "\n \t\tno account exist\n ";
	ofstream outhtml;
	outhtml.open("www.html", ios::app);
	outhtml << "</table>\n</font></p></body>\n</html>";
	outhtml.close();
	in.close();
}
void bank_budget()
{
	bank ob;
	ifstream in;
	in.open("bankdetails.dat", ios::binary);
	in.read(reinterpret_cast<char *> (&ob), sizeof(bank));
	ob.bank_budget();
	in.close();

}
void html()
{
	ofstream outhtml;
	outhtml.open("www.html");
	outhtml << "<html>\n<body bgcolor=aqua>\n";
	outhtml << "<p align=center><font size=62 face=arial color=blue>BANKING SYSTEM</font></p>\n<br><br>\n<p align=center>\n";
	outhtml << "<font size=24 type=italic color=brown><table border=1 bgcolor=pink>\n<tr>\n<th bgcolor=red>Ac.No</th>\n<th bgcolor=red>NAME</th>\n<th bgcolor=red>TYPE</th>\n";
	outhtml << "<th bgcolor=red>AMOUNT</th>\n<th bgcolor=red>LOAN</th>\n";
	outhtml << "<th bgcolor=red>LOAN_RETURN_TIME(year)</th>\n</tr>\n";
	outhtml.close();
}