#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include<stdio.h>
#include<string>
#include <fstream>
#include <iostream>
using namespace std;
struct date
{
	int day=0, month=0, year=0;
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
	string p_name, renter_id;;
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
	string id;
	string f_name;
	string l_name, p_num, email, password;
	
};

struct landlord
{
	traveler info;
	bank_account transfer;
	property** prop=NULL;//check
	
};
#endif
