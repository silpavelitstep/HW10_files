#include "directory.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#pragma warning(disable:4996)
using namespace std;
//#define ADD_AUTO "ON"
//help functions
void genword(char *tmp, int size, char first, char last) {
	for (int i = 0; i < size; i++) {
		tmp[i] = (char)(rand() % (last - first) + first);
	}
	tmp[0]=towupper(tmp[0]);
	tmp[size - 1] = 0;
	
}
char* trueinput(const char *name) {
	char tmp[256];
	while (true) {
		cout << name<<": ";
		cin.getline(tmp, 255);
		if (strstr(tmp, "#") || strstr(tmp, "&")) cout << "Incorrect input!\n";
		else break;
	}
	char *value = new char[strlen(tmp) + 1];
	strcpy(value, tmp);
	return value;

}
//class Data
Data::Data() {
	firm_name = owner = phone_number = 0;
	firm_adress = kind_of_activity = 0;
	//cout << "new Data: " << (int)this << endl;
}
Data::Data(const Data &dt) {
	if (dt.firm_name) {
		firm_name = new char[strlen(dt.firm_name) + 1];
		strcpy(firm_name, dt.firm_name);
	}
	else
		firm_name = 0;
	if (dt.owner) {
		owner = new char[strlen(dt.owner) + 1];
		strcpy(owner, dt.owner);
	}
	else
		owner = 0;
	if (dt.phone_number) {
		phone_number = new char[strlen(dt.phone_number) + 1];
		strcpy(phone_number, dt.phone_number);
	}
	else
		phone_number = 0;
	if (dt.firm_adress) {
		firm_adress = new char[strlen(dt.firm_adress) + 1];
		strcpy(firm_adress, dt.firm_adress);
	}
	else
		firm_adress = 0;
	if (dt.kind_of_activity) {
		kind_of_activity = new char[strlen(dt.kind_of_activity) + 1];
		strcpy(kind_of_activity, dt.kind_of_activity);
	}
	else
		kind_of_activity = 0;
	//cout << "new copy Data: " << (int)this << endl;
}
Data::~Data() {
	//cout << "free Data: " << (int)this << endl;
	freeData();
}
void Data::freeData() {
	if (firm_name) delete[] firm_name;
	if (owner) delete[] owner;
	if (phone_number) delete[] phone_number;
	if (firm_adress) delete[] firm_adress;
	if (kind_of_activity) delete[] kind_of_activity;
}
ostream& operator<<(ostream& out, const Data& dt) {
	if (&dt==0)
		return out;
	out << "\n--------------------------\n"
		<<"firm_name: "<< dt.firm_name << '\n'
		<<"firm_adress: "<< dt.firm_adress << '\n'
		<<"owner: "<< dt.owner << '\n'
		<<"phone_number: "<< dt.phone_number << '\n'
		<<"kind_of_activity: "<< dt.kind_of_activity
		<< "\n==========================\n";
	return out;
}
//class Directory
void Directory::add() {
	Data dt;
#ifdef ADD_AUTO //auto fill
	srand(time(0));
	int size;
	size = rand() % (5) + 5;
	dt.firm_name = new char[size];
	genword(dt.firm_name, size, 'a', 'z');

	size = rand() % (10) + 3;
	dt.owner = new char[size];
	genword(dt.owner, size, 'a', 'z');

	size = rand() % (5) + 10;
	dt.phone_number = new char[size];
	genword(dt.phone_number, size, '0', '9');
	dt.phone_number[0] = '+';

	size = rand() % (30) + 10;
	dt.firm_adress = new char[size];
	genword(dt.firm_adress, size, 'a', 'z');
	dt.firm_adress[7] = ' ';

	size = rand() % (5) + 10;
	dt.kind_of_activity = new char[size];
	genword(dt.kind_of_activity, size, 'a', 'z');
	dt.kind_of_activity[7] = ' ';
#else //user input 
	cout << "\n-------put value (ecept # and & simbols)-----------\n";
	dt.firm_name=trueinput("firm_name");
	dt.firm_adress=trueinput("firm_adress");
	dt.owner=trueinput("owner");
	dt.phone_number=trueinput("phone_number");
	dt.kind_of_activity=trueinput("kind_of_activity");
	cout<<"\n==========================\n";
#endif // !ADD_AUTO
	data.push_back(dt);
	
	//save to file dir.txt
	ofstream out;
	out.open("dir.txt", ios::app);
	if (!out)
		return;
	out << '#';
	out << dt.firm_name << '&';
	out << dt.owner << '&';
	out << dt.phone_number << '&';
	out << dt.firm_adress << '&';
	out << dt.kind_of_activity << endl;
	out.close();

}
void Directory::show_all() {
	for (Data dt : data)
		cout << dt;
	
}
Directory::Directory() {
	ifstream in;
	in.open("dir.txt");
	if (!in)//error open file
		return;
	char c;//for #,&,\n
	char buf[256];
	Data dt;
	while (in) {
		in >> c;//out << '#';
		if (!in)
			break;
		//dt.firm_name << '&';
		in.getline(buf, 255, '&');//with space
		dt.firm_name = new char[strlen(buf)+1];
		strcpy(dt.firm_name, buf);
		//out << dt.owner << '&';
		in.getline(buf, 255, '&');//with space
		dt.owner = new char[strlen(buf) + 1];
		strcpy(dt.owner, buf);
		//out << dt.phone_number << '&';
		in.getline(buf, 255, '&');//with space
		dt.phone_number = new char[strlen(buf) + 1];
		strcpy(dt.phone_number, buf);
		//out << dt.firm_adress << '&';
		in.getline(buf, 255, '&');//with space
		dt.firm_adress = new char[strlen(buf) + 1];
		strcpy(dt.firm_adress, buf);
		//out << dt.kind_of_activity << endl;
		in.getline(buf, 255);//with space		\n !!! end line
		dt.kind_of_activity = new char[strlen(buf) + 1];
		strcpy(dt.kind_of_activity, buf);
		//add to vector
		data.push_back(dt);
		
	}

	in.close();

}

