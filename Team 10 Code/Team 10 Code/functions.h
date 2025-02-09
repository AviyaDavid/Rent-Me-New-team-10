#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include "Structs.h"

//--- READ FROM FILES---//
landlord** readLandlords(int& l_size);
traveler** readTravelers(int& t_size);
reservation** read_reservation(int &r_size);//reads from reservations data base and returns array with data from file
property** read_properties(int& p_size);//reads from properties data base and returns array with data from file

//--- SUB-FUNCTIONS FOR FILES---//
string* readLine(ifstream& fp,string line[18]);//returns line from file separated by delimeter into array
void strtotraveler(string* line, traveler*);//returns traveler containing all data from line
void strtolandlord(string* line,landlord*);//returns landlord containing all data from line
void strtores(string* line,reservation*);//returns reservation containing all data from line
void strtopro(string* line, property*);//returns property containing all data from line

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
void writeUsers( traveler** travelers, int& trav_len, landlord** landlords, int& land_len);//write to file all users details
string travelertostr(traveler* t, int size);//traveler cast to string
void write_reservations(reservation** reservations, int res_len);//write to file all reservations details details
void write_properties(property** properties, int p_len);//write to file all properties details

//---------------------------------------------------------------------------------------
traveler* traveler_login(traveler** travelers, int sizet);
traveler* traveler_signup(traveler** travelers, landlord** landlords, int* size_of_travelers, int size_of_landlord);
landlord* landlord_login(landlord** landlords, int size_of_landlords);
landlord* landlord_signup(landlord** landlords, traveler** travelers, int* size_of_landlords, int size_of_travelers);
void LandlordMenu(landlord* user, traveler** travelers, int& size_travel, landlord** landlords, int& size_land, reservation** reservations, int& size_res, property** properties, int& size_pro);
bool check_id(string id);//checks if id is valid

void print_properties(property** properties, int size_of_properties);
void print_property(property* prop);\
void print_confirmation(property* booked, date from, date to, int nights);
void print_reservations(reservation** reservations, int size_res, property** properties, int size_pro, traveler* user);

property* search(property** prop_list, reservation** res_list, int sizeof_properties, int sizeof_res, traveler trav);
property** filter(string* filters, property** properties, int& sizeof_properties);
property** sort(property** ads, int sizeof_ads, int sort_op);

void yes_no(string am[10], int index);

reservation** payment(property* chosen, traveler renter, reservation** reservations, int& size_of_reservations, date chek_in, date chek_out, landlord** landlords, int& size_of_landlords);

property** add_property(landlord* host, property** properties, int* size_of_properties);

property** editMenu(landlord* host, property** properties, int& size_of_properties);

property* edit(property* old_prop);

property** deletep(property* p_chosen, property** properties, int& size_of_properties);



void rate(reservation* res, property** properties, int size_pro);

int compDates(date a, date b);

void mainMenu();

int loginMenu();

void travelerMenu(traveler* user, traveler** travelers, int& size_travel, landlord** landlords, int& size_land, reservation** reservations, int& size_res, property** properties, int& size_pro);

void freeMemory(traveler** travelers, landlord** landlords, reservation** reservations, property** properties);//frees all allocations

#endif