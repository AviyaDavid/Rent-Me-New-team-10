#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include"Structs.h"
#include"functions.h"
using namespace std;
<<<<<<< HEAD
=======
struct date 
{
	int day, month, year;

};
struct property
{
	string owner_id, description, p_name, location;
	int price, capacity;
	string near;
	string amenities[10];//accessability,smoke,pet,balcony,wash,wifi,pool,bed_num room_num,rate
	bool status;
	int num_of_rates;
};

struct reservation
{
	string p_name,renter_id;;
	date check_in, check_out;
	string loc;
	int rate;
	bool israted; 
};

struct bank_account
{
	string card_num;
	date due;
	string cvv;
};

struct traveler
{
	string id, f_name, l_name, p_num, email, password;
	reservation* history;
};

struct landlord
{
	traveler info;
	bank_account transfer;
	property* prop;
};
traveler* traveler_login(traveler* travelers)
{
	string id, password;
	int i, size = sizeof(travelers + 1);
	int index = 0, flag=0;
	cout << "Enter I.D. : ";
	cin >> id;
	for (i = 0; i < sizeof(travelers); i++)
	{
		if (id == travelers[i].id)
			index= i;//true
	}
	if (index == 0)
		return NULL;
	do
	{
		cout << "Enter Password: ";
		cin >> password;
		flag++;
		cout << "["<<flag<<":3]" << endl;
	} while (password != travelers[index].password||flag==3);
	if (flag == 3)
	{
		cout << "Incorrect password, user blocked!!" << endl;
		return NULL;
	}
	return &travelers[index];
}
traveler* traveler_signup(traveler** travelers, landlord* landlords)
{
	string id, f_name, l_name, p_num, email, password;
	int i=0,size = sizeof(travelers);
	bool flag1 = 0;//false	
	cout << "Enter your first name please:" << endl;
	cin >> f_name;
	cout << "Enter your last name please:" << endl;
	cin >> l_name;
	cout << "Enter your phone nunber please:" << endl;
	cin >> p_num;
	cout << "Enter your password please:" << endl;
	cin >> password;
	cout << "Enter your email please:" << endl;
	cin >> email;
	do
	{
		cout << "Enter I.D. : ";
		cin >> id;
	} while (id == (*travelers[i]).id || id == landlords[i].info.id);
	size++;
	traveler** temp = new traveler * [size];//יצירת מערך זמני למאגר
	for (int i = 0; i < size-1; i++)
	{
		temp[i]->email = travelers[i]->email;//העתקת המערך הקיים לזמני
		temp[i]->f_name = travelers[i]->f_name;
		temp[i]->history = travelers[i]->history;
		temp[i]->id = travelers[i]->id;
		temp[i]->l_name = travelers[i]->l_name;
		temp[i]->password = travelers[i]->password;
		temp[i]->p_num = travelers[i]->p_num;
	}
	temp[size]->id = id;//הןספה של האדם החדש למערך
	temp[size]->f_name = f_name;
	temp[size]->l_name = l_name;
	temp[size]->password = password;
	temp[size]->p_num = p_num;
	temp[size]->email = email;
	delete[] *travelers;//שחרור המערך
	travelers= new traveler*[size];//יצירת מערך זמני למאגר
	for (int i = 0; i < size; i++)
	{
		travelers[i]->email = temp[i]->email;//העתקת המערך הקיים לזמני
		travelers[i]->f_name = temp[i]->f_name;
		travelers[i]->history = temp[i]->history;
		travelers[i]->id = temp[i]->id;
		travelers[i]->l_name = temp[i]->l_name;
		travelers[i]->password = temp[i]->password;
		travelers[i]->p_num = temp[i]->p_num;;//העתקת המערך הקיים לזמני
	}
	return *travelers;
}
landlord* landlord_login(landlord* landlords)
{
	string id, password;
	int i, size = sizeof(landlords + 1);
	int index = 0, flag = 0;
	cout << "Enter I.D. : ";
	cin >> id;
	for (i = 0; i < size; i++)
	{
		if (id == landlords[i].info.id)
			index = i;//true
	}
	if (index == 0)
		return NULL;
	do
	{
		cout << "Enter Password: ";
		cin >> password;
		flag++;
		cout << "[" << flag << ":3]" << endl;
	} while (password != landlords[index].info.password || flag == 3);
	if (flag == 3)
	{
		cout << "Incorrect password, user blocked!!" << endl;
		return NULL;
	}
	return &landlords[index];
}
landlord* landlord_signup(landlord** landlords, traveler* travelers)
{
	string id, f_name, l_name, p_num, email, password;
	int i = 0, size = sizeof(landlords);
	bool flag1 = 0;//false	
	cout << "Enter your first name please:" << endl;
	cin >> f_name;
	cout << "Enter your last name please:" << endl;
	cin >> l_name;
	cout << "Enter your phone nunber please:" << endl;
	cin >> p_num;
	cout << "Enter your password please:" << endl;
	cin >> password;
	cout << "Enter your email please:" << endl;
	cin >> email;
	do
	{
		cout << "Enter I.D. : ";
		cin >> id;
	} while (id == (*landlords[i]).info.id || id == travelers[i].id);
	size++;
	landlord** temp = new landlord * [size];//יצירת מערך זמני למאגר
	for (int i = 0; i < size - 1; i++)
	{
		temp[i]->info.email = landlords[i]->info.email;//העתקת המערך הקיים לזמני
		temp[i]->info.f_name = landlords[i]->info.f_name;
		temp[i]->info.history = landlords[i]->info.history;
		temp[i]->info.id = landlords[i]->info.id;
		temp[i]->info.l_name = landlords[i]->info.l_name;
		temp[i]->info.password = landlords[i]->info.password;
		temp[i]->info.p_num = landlords[i]->info.p_num;
	}
	temp[size]->info.id = id;//הןספה של האדם החדש למערך
	temp[size]->info.f_name = f_name;
	temp[size]->info.l_name = l_name;
	temp[size]->info.password = password;
	temp[size]->info.p_num = p_num;
	temp[size]->info.email = email;
	delete[] landlords;//שחרור המערך
	landlords = new landlord * [size];//יצירת מערך זמני למאגר
	for (int i = 0; i < size; i++)
	{
		landlords[i]->info.email = temp[i]->info.email;//העתקת המערך הקיים לזמני
		landlords[i]->info.f_name = temp[i]->info.f_name;
		landlords[i]->info.history = temp[i]->info.history;
		landlords[i]->info.id = temp[i]->info.id;
		landlords[i]->info.l_name = temp[i]->info.l_name;
		landlords[i]->info.password = temp[i]->info.password;
		landlords[i]->info.p_num = temp[i]->info.p_num;;//העתקת המערך הקיים לזמני
	}
	return *landlords;
}
>>>>>>> main
