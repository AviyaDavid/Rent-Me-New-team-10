#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string>
using namespace std;
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