#ifndef BANK_H
#define BANK_H
#include<iostream>
#include "console.h"
using namespace std;
class bank
{
	unsigned long long T_amount;
	int id, r5000, r1000, r500, r100, r50, r10;   //to store quantity of specific currency
public:
	bank()              //constructor of bank
	{
		T_amount = 6660000;
		id = 999;
		r5000 = 1000;
		r1000 = 1000;
		r500 = 1000;
		r100 = 1000;
		r50 = 1000;
		r10 = 1000;
	}
	void setcurrency(unsigned long long m, int a, int b, int c, int d, int e, int f, int t) //perameter contains quantity of each currency
	{
		if (t == 1)     //if t is 1 then add the quantity ofnotes else subtract that quantity of notes
		{
			r5000 = r5000 + a;
			r1000 = r1000 + b;
			r500 = r500 + c;
			r100 = r100 + d;
			r50 = r50 + e;
			r10 = r10 + f;
			T_amount = T_amount + m;
		}
		else
		{
			r5000 = r5000 - a;
			r1000 = r1000 - b;
			r500 = r500 - c;
			r100 = r100 - d;
			r50 = r50 - e;
			r10 = r10 - f;
			T_amount = T_amount - m;
		}
	}

	void bank_budget()
	{
		HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
		int d;

		cout << "\nenter id of bank to see this info :";
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin >> d;
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		if (id == d)
		{
			cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
			cout << "\ntotal amount bank have : " << T_amount;
			cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
			cout << "total 5000 rupee notes : " << r5000;
			cout << "\n\ntotal 1000 rupee notes : " << r1000;
			cout << "\n\ntotal  500 rupee notes : " << r500;
			cout << "\n\ntotal  100 rupee notes : " << r100;
			cout << "\n\ntotal   50 rupee notes : " << r50;
			cout << "\n\ntotal   10 rupee notes : " << r10;
		}
		else
			cout << "\n\n\tincorrect id !!!";
	}
	void bank_info()
	{
		cout << "\n\t$ $ $ $ $   welcome to HABIB BANK LIMITED !!!   $ $ $ $ $\n\n\n-> our bank will provide both interest and loan";
		cout << " facility.\n\n-> The interest you can get per month is 5% of your current balance in bank. ";
		cout << "\n\n-> you will get a loan with the returning limit of 5 years.";
	}


};
#endif
