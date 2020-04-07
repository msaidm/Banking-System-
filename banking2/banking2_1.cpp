#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
using namespace std;
class Accounts
{
private:
	string name, email, username, mobile, password;
	Accounts* next;
	Accounts* prev;
	double balance;     //ynf3 -ve???
	int ID;
	int counter = 0;
public:
	Accounts(string u, string p, string e, string m, string n, double b)
	{
		username = u;
		password = p;
		email = e;
		mobile = m;
		name = n;
		balance = b;
		ID = counter;
		counter++;
	}

	string getname()
	{
		return name;
	}
	void setname(string n)
	{
		name = n;
	}

	string getmob()
	{
		return mobile;
	}
	void setmob(string n)
	{
		mobile = n;
	}

	string getmail()
	{
		return email;
	}
	void setmail(string n)
	{
		email = n;
	}

	string getusername()
	{
		return username;
	}
	void setusername(string n)
	{
		username = n;
	}

	string getpassword()
	{
		return password;
	}
	void setpassword(string n)
	{
		password = n;
	}

	double getbal()
	{
		return balance;
	}
	int getID()
	{
		return ID;
	}

	void withdraw(double n)
	{
		if (n > 0)
			balance -= n;
		else
			cout << "This is called making a deposit\n";
	}
	void deposit(double n)
	{
		if (n > 0)
			balance += n;
		else
			cout << "This is called making a withdrawal\n";
	}

	Accounts* getnext()
	{
		return next;
	}
	void setnext(Accounts* p)
	{
		next = p;
	}

	Accounts* getprev()
	{
		return prev;
	}
	void setprev(Accounts* p)
	{
		prev = p;
	}

	friend class list;
};

class list
{
private:
	Accounts* tail = NULL;
	Accounts* chain = NULL;
	vector <Accounts*> nodes;
public:
	void transfer(string a, string b, double d)
	{
		if (find(b) != NULL)
			if (d > 0)
				if (find(a)->balance > d)
				{
					find(a)->withdraw(d);
					find(b)->deposit(d);
				}
				else
					cout << "Insufficient funds\n";
			else
				cout << "Negative currency is not accepted\n";
		else
			cout << "This account doesn't exist\n";
	}
	void transfer(int a, int b, double d)
	{
		if (nodes[b])
			if (d > 0)
				if (nodes[a]->balance > d)
				{
					nodes[a]->withdraw(d);
					nodes[b]->deposit(d);
				}
				else
					cout << "Insufficient funds\n";
			else
				cout << "Negative currency is not accepted\n";
		else
			cout << "This account doesn't exist\n";
	}
	void transfer(Accounts* a, Accounts*b, double d)
	{
		if (a != NULL)
			if (b != NULL)
				if (d > 0)
					if (a->balance > d)
					{
						a->withdraw(d);
						b->deposit(d);
					}
					else
						cout << "Insufficient funds\n";
				else
					cout << "Negative currency is not accepted\n";
			else
				cout << "This account doesn't exist\n";
	}

	void add(string u, string p, string e, string m, string n, double b)
	{
		if (chain == NULL)
		{
			Accounts* temp = new Accounts(u, p, e, m, n, b); //memory?
			chain = temp;
			tail = chain;
			nodes.push_back(temp);
		}
		else
		{
			Accounts* temp = new Accounts(u, p, e, m, n, b);
			tail->setnext(temp);
			temp->setprev(tail);
			temp = tail;
			nodes.push_back(temp);
		}
	}
	Accounts* find(Accounts* p)
	{
		while (p != NULL)
		{
			for (int i = 0; i < nodes.size(); i++)
				if (p == nodes[i])
					return nodes[i];
		}
		return NULL;
	}
	Accounts* find(string use, string pass)
	{
		for (int i = 0; i < nodes.size(); i++)
			if (nodes[i]->username == use && nodes[i]->password == pass)
				return nodes[i];
		return NULL;
	}
	Accounts* find(string use)
	{
		for (int i = 0; i < nodes.size(); i++)
			if (nodes[i]->username == use)
				return nodes[i];
		return NULL;
	}
	Accounts* find(int IDD)
	{
		return nodes[IDD];
	}
	void del(Accounts* p)
	{
		for (int i = 0; i < nodes.size(); i++)
			if (p == nodes[i])
			{
				nodes[i]->username = "";
				nodes[i]->name = "";
				nodes[i]->password = "";
				nodes[i]->email = "";
				nodes[i]->balance = 0;
				nodes[i]->ID = -1;
				nodes[i]->mobile = "";
			}
	}
	void del(string use)
	{
		for (int i = 0; i < nodes.size(); i++)
			if (find(use) == nodes[i])
			{
				nodes[i]->username = "";
				nodes[i]->name = "";
				nodes[i]->password = "";
				nodes[i]->email = "";
				nodes[i]->balance = 0;
				nodes[i]->ID = -1;
				nodes[i]->mobile = "";
			}
	}
	void print_all()
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			cout << "Client Name: " << nodes[i]->name;
			cout << "\t\tClient ID: " << fixed << nodes[i]->ID;
			cout << "\nCrruent Balance: " << fixed << nodes[i]->balance;
		}
	}
	void print(Accounts* a)
	{
			cout << "Client Name: " << find(a)->name;
			cout << "\t\tClient ID: " << fixed << find(a)->ID;
			cout << "\nCrruent Balance: " << fixed << find(a)->balance;
			cout << "\nClient E-Mail: " << find(a)->email;
			cout << "\nClient Mobile Number: " << find(a)->mobile;
	}
	void print(int a)
	{
		cout << "Client Name: " << find(a)->name;
		cout << "\t\tClient ID: " << fixed << find(a)->ID;
		cout << "\nCrruent Balance: " << fixed << find(a)->balance;
		cout << "\nClient E-Mail: " << find(a)->email;
		cout << "\nClient Mobile Number: " << find(a)->mobile;
	}
};
int main()
{
	int choice, choice2, ch, ch2, ch3, ban;
	string n, u, p, e, m, chh;
	double b, money;
	time_t t = time(0);
	queue<int> Que;
	list Bank;
	struct tm * now = localtime(&t);
	//ifstream input("Median.txt");
	//ofstream output("results.txt");
ban1:
	cout << "Choose current simulation\n";
	cout << "_________________________\n";
	cout << "1) Bank branch simulation\t\t2) online banking simulation\n";
	cout << "_________________________________________________________\n";
	cout << "Choice: ";
	cin >> ban;
	if (ban == 1)
	{
		int qq = 5;
		cout << "Date:" << (now->tm_mday) << '/' << (now->tm_mon + 1) << '/' << now->tm_year + 1900 << endl;
		cout << "Time:" << (now->tm_hour) << ':' << (now->tm_mday) << ':' << now->tm_sec << endl;
		cout << "You are client number: " << qq + 416 << endl;
		for (int i = 1; i <= qq; i++)
			Que.push(i + 415);
		for (int i = 1; i <= qq; i++) {
			cout << "Now serving customer number:" << Que.front() << endl;
			Que.pop();
			//_sleep(1502);
		}
		goto bank;
	}
	else if (ban != 1 && ban != 2) {
		cout << "Invalid input";
		goto ban1;
	}
bank:
	cout << "ASU National Bank (ANB)\n";
	cout << "_________________________________\n";
	cout << "Choose an operation\n";
	cout << "___________________\n";
	cout << "1) Create an Account\t\t2) Login to your account\n";
	cout << "________________________________________________\n";
cho:
	cout << "Choice: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
	cho2:
		cout << "Enter 1 to continue or 0 to return to previous menu: ";
		cin >> choice2;
		if (choice2 == 0)
			goto bank;
		else if (choice2 == 1)
		{
		nuse:
			cout << "Enter a unique username: ";
			cin >> u;
			if (Bank.find(u))
			{
				cout << "Username already taken\n";
				goto nuse;
			}
			cout << "Enter a password: ";
			cin >> p;
			cout << "Enter your full name: ";
			cin >> n;
			cout << "Enter your E-Mail: ";
			cin >> e;
			cout << "Enter your Mobile number: ";
			cin >> m;
			cout << "Enter your starting balance (Preferably over 1000): ";
			cin >> b;
			Bank.add(u, p, e, m, n, b);
			cout << "Account creation successful\n";
			cout << "__________________________________________________\n";
		}
		else
		{
			cout << "Invalid input";
			goto cho2;
		}
		goto op1;
		break;
	case 2:
	cho3:
		cout << "Enter 1 to continue or 0 to return to previous menu: ";
		cin >> choice2;
		if (choice2 == 0)
			goto bank;
		else if (choice2 == 1)
		{
		use:
			cout << "Enter your username: ";
			cin >> u;
			if (Bank.find(u))
			{
			pass:
				cout << "Enter your password or enter 0 to re-enter your username: ";
				cin >> p;
				if (p == "0")
					goto use;
				if (Bank.find(u, p))
				{
				op1:
					cout << "Greetings " << Bank.find(u)->getname();
					cout << "\t\t\t\tCurrent Balance: " << fixed << Bank.find(u, p)->getbal() << endl;
				op:
					cout << "Choose an operation\n";
					cout << "___________________\n";
					cout << "1) Withdraw\t\t\t2) Deposit\n";
					cout << "3) Transfer funds\t\t4) Change accout details\n";
					cout << "____________________________________________________________\n";
					cout << "Choice: ";
					cin >> ch;
					switch (ch)
					{
					case 1:
						cout << "Enter desired amount or enter 0 to return to previous menu: ";
						cin >> money;
						if (money == 0)
							goto op;
						Bank.find(u)->withdraw(money);
						goto op1;
						break;
					case 2:
						cout << "Enter desired amount or enter 0 to return to previous menu: ";
						cin >> money;
						if (money == 0)
							goto op;
						Bank.find(u)->deposit(money);
						goto op1;
						break;
					case 3:
						cout << "Enter desired amount or enter 0 to return to previous menu: ";
						cin >> money;
						if (money == 0)
							goto op;
						cout << "Enter an ID to transfer to: ";
						cout << "__________________________\n";
						int ii;
						cin >> ii;
						Bank.transfer((Bank.find(u)->getID()), ii, money);
						goto op1;
						break;
					case 4:
						Bank.print(Bank.find(u));
					profile:
						cout << "\n_______________________________________________\n";
						cout << "\nChoose an operation\n";
						cout << "___________________\n";
						cout << "1) Change username\t\t2) Change password\n";
						cout << "3) Change E-Mail\t\t4) Change mobile number\n";
						cout << "\t\t\t0) Terminate current account\n";
						cout << "choice: ";
						cin >> ch3;
						switch (ch3)
						{
						case 0:
							cout << "Are you sure?(Y/N): ";
							cin >> chh;
							if (chh == "Y" || chh == "y")
							{
								Bank.del(u);
								cout << "Account terminated successfully\n";
								cout << "_______________________________\n";
								goto bank;
							}
							else if (chh == "N" || chh == "n")
								goto profile;
							break;
						case 1:
							cout << "Enter a new username or enter 0 to return to previous menu: ";
							cin >> chh;
							if (chh == "0")
								goto bank;
							else {
								Bank.find(u)->setusername(chh);
								u = chh;
								goto op1;
							}
							break;
						case 2:
							cout << "Enter a new password or enter 0 to return to previous menu: ";
							cin >> chh;
							if (chh == "0")
								goto bank;
							else {
								Bank.find(u)->setpassword(chh);
								p = chh;
								goto op1;
							}
							break;
						case 3:
							cout << "Enter a new E-Mail or enter 0 to return to previous menu: ";
							cin >> chh;
							if (chh == "0")
								goto bank;
							else {
								Bank.find(u)->setmail(chh);
								e = chh;
								goto op1;
							}
							break;
						case 4:
							cout << "Enter a new Mobile number or enter 0 to return to previous menu: ";
							cin >> chh;
							if (chh == "0")
								goto bank;
							else {
								Bank.find(u)->setmob(chh);
								m = chh;
								goto op1;
							}
							break;
						default:
							cout << "Invalid input";
							break;
						}
						break;
					default:
						cout << "invalid choice\n";
						goto op;
						break;
					}
				}
				else
				{
					cout << "Wrong password\n";
					goto pass;
				}
			}
			else
			{
				cout << "Username doesn't exis\n";
				goto use;
			}
		}
		else
		{
			cout << "Invalid input\n";
			goto cho3;
		}
		break;
	default:
		cout << "Invalid input\n";
		goto cho;
		break;
	}
	return 0;
}