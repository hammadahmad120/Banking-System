#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "bank.h"
#include "console.h"
#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;
class account
{
	char name[51];
	int acno;
	char type;
	double amount;
	double loan;
	int time;
public:
	account()
	{
		acno = 0;
		amount = 0;
		loan = 0;
		time = 0;
	}
	void set_act(int ac)      //function to set all data members
	{
		HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
		int t = 0;
		int r5000, r1000, r500, r100, r50, r10;
		acno = ac;
		cout << "\nenter your name : ";
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin.ignore();
		cin.getline(name, 51);
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			cout << "\n enter C for current and S for saving : ";
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> type;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			type = toupper(type);
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
		amount = (r5000 * 5000 + r1000 * 1000 + r500 * 500 + r100 * 100 + r50 * 50 + r10 * 10);
		cout << "total amount you entered is : " << amount << endl;
		forbank(amount, r5000, r1000, r500, r100, r50, r10, 1);
		loan = 0;
		time = 0;
	}
	void forbank(unsigned long long m, int a, int b, int c, int d, int e, int f, int t)
	{
		bank obj;
		fstream outfile;
		outfile.open("bankdetails.dat", ios::binary | ios::in);
		outfile.read(reinterpret_cast<char*>(&obj), sizeof(obj));
		obj.setcurrency(m, a, b, c, d, e, f, t);                   //to calculate bank amount
		outfile.close();
		outfile.open("bankdetails.dat", ios::binary | ios::out);
		outfile.write(reinterpret_cast<char *>(&obj), sizeof(obj));
		outfile.close();
	}
	int getacno()
	{
		return acno;
	}
	double getamount()
	{
		return amount;
	}
	void deposit(int n)
	{
		amount = amount + n;
	}
	void withdraw(int n)
	{
		amount = amount - n;
	}
	void show()
	{
		cout << "\n your account  " << acno << " has " << amount << " rupees and loan is " << loan << " rupees\n";
	}
	void detail()
	{
		ofstream outhtml;
		outhtml.open("www.html", ios::app);
		if (type == 'S'&&loan == 0)
		{
			cout << acno << setw(13) << name << setw(5) << type << setw(10) << amount<< setw(8)<< "-" << setw(12) << "-" << endl;
			cout << "\nThe interest you will get per month is : " << amount*(5 / 100.0) << endl;
		}
		else
			cout << acno << setw(13) << name << setw(5) << type << setw(10) << amount << setw(10) << loan << setw(10) << time << endl;
		outhtml << "<tr>\n<td align=center bgcolor=yellow>" << acno << "</td>\n" << "<td align=center>" << name << "</td>\n" << "<td align=center>" << type << "</td>\n";
		outhtml << "<td align=center>" << amount << "</td>\n" << "<td align=center>" << loan << "</td>\n" << "<td align=center>" << time << "</td>\n</tr>\n";
		outhtml.close();
	}
	void setloan(double r, int t)
	{
		loan = r;
		time = t;
	}

};
#endif