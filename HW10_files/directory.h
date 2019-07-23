#pragma once
#include <vector>
#include <iostream>
using namespace std;
#ifndef DIRECTORY_H
#define DIRECTORY_H
struct Data {
	char* firm_name;
	char* owner;
	char* phone_number;
	char* firm_adress;
	char* kind_of_activity;
	Data();
	Data(const Data&);
	~Data();
	void freeData();
	friend ostream& operator<<(ostream&, const Data&);
};
class Directory {
	
public:
	//interface
	vector<Data> data;
	void f_firm_name();
	void f_owner();
	void f_phone_number();
	void f_kind_of_activity();
	void show_all();
	void add();
};

#endif // !DIRECTORY_H

