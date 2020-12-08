#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;
struct date 
{
	int day, month, year;
	// operator<=
	// operator>=

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

void print_properties(property* properties)
{
	for (int i = 0; i < sizeof(properties); i++)
		print_property(properties[i]);
};

void print_property(property prop)
{
	cout << "Name: " << prop.p_name << "Description: " << prop.description << "Location: " << prop.location << "Capacity: " << prop.capacity << "Amenities: ";
	string myarr[10] = { "Accessibility: ", "Smoking: ", "Pets: ", "Balcony", "Washing machine", "Wifi", "Pool", "Number of beds: ", "Number of rooms: ", "Rate: " };
	for (int i = 0; i < 3; i++)
		cout << myarr[i] << prop.amenities[i] << " ";
	for (int i = 3; i < 7; i++)
		if (prop.amenities[i] == "Yes")
			cout << myarr[i] << " ";
	for (int i = 7; i < 10; i++)
		cout << myarr[i] << prop.amenities[i] << " ";
	cout << endl;
};

void print_confirmation(property booked, date from, date to, int nights)
{
	print_property(booked);
	cout << "Dates: " << from.day << '/' << from.month << '/' << from.year << " - " << to.day << '/' << to.month << '/' << to.year << endl;
	cout << "Number of nights: " << nights << endl;
	cout << "Final price: " << nights * booked.price << endl;
};

property* search(property* prop_list, reservation* res_list)
{
	string loc;
	date checkin;
	date checkout;
	int travelers;
	property* ads;
	bool available = true;
	int count = 0;
	cout << "Enter location: ";
	cin >> loc;
	cout << "Enter check in (dd/mm/yyyy): ";
	cin >> checkin.day >> checkin.month >> checkin.year;
	cout << "Enter check out (dd/mm/yyyy): ";
	cin >> checkout.day >> checkout.month >> checkout.year;
	cout << "Enter number of travelers: ";
	cin >> travelers;
	for (int i = 0; i < sizeof(prop_list); i++)
	{
		if (prop_list[i].location == loc && prop_list[i].capacity >= travelers)
			for (int j = 0; j < sizeof(res_list); j++)
				if (prop_list[i].p_name == res_list[j].p_name)
					if (!(checkin >= res_list[j].check_out || checkout <= res_list[j].check_in))
						available = false;
		if (available)
		{
			count++;
			ads = new property[count];
			ads[count - 1] = prop_list[i];
		}
	}
	return ads;
}

property* filter(string* filters, property* properties)
{
	property* ads;
	bool relevant;
	int count = 0;
	for (int i = 0; i < sizeof(properties); i++)
	{
		relevant = true;
		for (int j = 0; j < sizeof(filters); j++)
			if (!(properties[i].amenities[j] == filters[j]))
				relevant = false;
		if (relevant)
		{
			count++;
			ads = new property[count];
			ads[count - 1] = properties[i];
		}
	}
	return ads;
}

property* sort(property** ads, int sort_op)
{
	property* temp;
	if (sort_op == 1) // by price low to high
	{
		for (int i = 0; i < sizeof(ads) - 1; i++)
			for (int j = i + 1; j < sizeof(ads); j++)
			    if (ads[i]->price > ads[j]->price)
			    {
					temp = ads[i];
					ads[i] = ads[j];
					ads[j] = temp;
		        }
	}
	else if (sort_op == 2) // by price high to low
	{
		for (int i = 0; i < sizeof(ads) - 1; i++)
			for (int j = i + 1; j < sizeof(ads); j++)
				if (ads[i]->price < ads[j]->price)
				{
					temp = ads[i];
					ads[i] = ads[j];
					ads[j] = temp;
				}
	}
	else if (sort_op == 3) // by rank high to low
	{
		for (int i = 0; i < sizeof(ads) - 1; i++)
			for (int j = i + 1; j < sizeof(ads); j++)
				if (ads[i]->num_of_rates < ads[j]->num_of_rates)
				{
					temp = ads[i];
					ads[i] = ads[j];
					ads[j] = temp;
				}
	}
	return *ads;
}