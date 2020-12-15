#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include "Structs.h"

//--- READ FROM FILES---//
void read_users(landlord** landlords_array, int& landi, traveler** travelers_array, int& travi);//reads from users data base and inserting into arrays the data from file
reservation** read_reservation(int &r_size);//reads from reservations data base and returns array with data from file
property** read_properties(int& p_size);//reads from properties data base and returns array with data from file

//--- SUB-FUNCTIONS FOR FILES---//
string* readLine(ifstream& fp);//returns line from file separated by delimeter into array
traveler* strtotraveler(string* line);//returns traveler containing all data from line
landlord* strtolandlord(string* line);//returns landlord containing all data from line
reservation* strtores(string* line);//returns reservation containing all data from line
property* strtopro(string* line);//returns property containing all data from line

//---USEFUL AND CASTING FUNCTIONS---//
template <typename T>
T** install_new_data(T** array, int size, T* new_data)
{//manual reallocation template and inserting new data from file in last cell on array
	T** newArr = new T*[size];
	if (!newArr)//if allocation fails
	{
		cout << " Memory allocation failed!" << endl;//error message
		return NULL;
	}
	for (int i = 0; i < size - 1; i++)
	{//loop for copying old array
		newArr[i] = array[i];
	}
	newArr[size - 1] = new_data;
	//delete allocation
	delete[] array;
	array = newArr;
	return array;
}
date stringtodate(string str);// casting from string to date
string datetostring(date d);//casting from date to string

//--- WRITE INTO FILES---//
void write_users(landlord** landlords, int land_len, traveler** travelers, int trav_len);//write to file all users details
string travelertostr(traveler* t, int size);//traveler cast to string
void write_reservations(reservation** reservations, int res_len);//write to file all reservations details details
void write_properties(property** properties, int p_len);//write to file all properties details

//---------------------------------------------------------------------------------------

traveler* traveler_login(traveler* travelers);
traveler* traveler_signup(traveler** travelers, landlord* landlords, int* size_of_travelers);
landlord* landlord_login(landlord* landlords);
landlord** landlord_signup(landlord** landlords, traveler** travelers, int* size_of_landlords, int size_of_travelers);

bool check_id(string id);//checks if id is valid

void print_properties(property** properties, int size_of_properties);
void print_property(property* prop);\
void print_confirmation(property* booked, date from, date to, int nights);
void print_reservations(reservation** reservations, int size_res, property** properties, int size_pro, traveler* user);

property* search(property** prop_list, reservation** res_list, int sizeof_properties, int sizeof_res, traveler trav);
property** filter(string* filters, property** properties, int& sizeof_properties);
property** sort(property** ads, int sizeof_ads, int sort_op);

void yes_no(string am[10], int index);


reservation** payment(property* chosen, traveler renter, reservation** reservations, int* size_of_reservations, date chek_in, date chek_out);

property** add_property(landlord* host, property** properties, int* size_of_properties);

property** editMenu(landlord* host, property** properties, int& size_of_properties);

property* edit(property* old_prop);

property** deletep(property* p_chosen, property** properties, int& size_of_properties);



void rate(reservation* res, property** properties, int size_pro);

int compDates(date a, date b);

void mainMenu();

bool loginMenu();

void LandlordMenu(landlord* user, traveler** travelers, int size_travel, landlord** landlords, int size_land, reservation** reservations, int size_res, property** properties, int size_pro);

void travelerdMenu(traveler* user, traveler** travelers, int size_travel, landlord** landlords, int size_land, reservation** reservations, int size_res, property** properties, int size_pro);

void freeMemory(traveler** travelers, landlord** landlords, reservation** reservations, property** properties);//frees all allocations

#endif