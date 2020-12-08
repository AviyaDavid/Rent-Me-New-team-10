#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string>
#include <fstream>
#include <iostream>
#include "Structs.h"
#include"functions.h"
using namespace std;

void read_users(landlord* landlords, traveler* travelers)
{
	ifstream users("usersDB.csv");// file pointer Open an existing file 
	if (!users.is_open())//if open failed
	{
		cout << "ERROR USERS FILE DOES NOT EXIST" << endl;
		return;
	}
	string flag ;//if landlord it will be 0
	int landi = 0,travi=0;//index for traveler array and landlord array
	landlord templ;//temporary landlord
	traveler tempt;//temporary traveler

	while (!users.eof())
	{
		getline(users, flag, ',');
		if (flag.compare("1") == 0)//if landlord
		{
			getline(users, templ.info.id, ',');
			getline(users, templ.info.f_name, ',');
			getline(users, templ.info.l_name, ',');
			getline(users, templ.info.p_num, ',');
			getline(users, templ.info.email, ',');
			getline(users, templ.info.password, ',');
			getline(users, templ.transfer.card_num, ',');
			//getline(users, templ.transfer.due.month, ',');
			//getline(users, templ.transfer.due.year, ',');int to str
			//לקלוט את התאריך לסטרינג דייט ואז ליצור דייט ולהכניס ללנדלורד
			getline(users, templ.transfer.cvv, '\n');
			
			landlords[landi] = templ;
			landi++;
		}
		else
		{
			getline(users, tempt.id, ',');
			getline(users, tempt.f_name, ',');
			getline(users, tempt.l_name, ',');
			getline(users, tempt.p_num, ',');
			getline(users, tempt.email, ',');
			getline(users, tempt.password, '\n');
			travelers[travi] = tempt;
			travi++;
		}
	}

}
reservation* read_reservation(){}
property* read_properties(){}
void write_users(landlord* landlords, traveler* travelers){}
void write_reservations(reservation* reservations){}
void write_properties(property* properties){}