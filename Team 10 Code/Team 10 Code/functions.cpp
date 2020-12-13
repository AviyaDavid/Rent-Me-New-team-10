#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <ctime>
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
	string flag;//if landlord it will be 0
	int landi = 0, travi = 0;//index for traveler array and landlord array
	landlord templ;//temporary landlord
	traveler tempt;//temporary traveler
	string tempd;//temp for date insert
	while (!users.eof())
	{
		getline(users, flag, ',');
		if (flag.compare("1") == 0)//if landlord
		{//recieve all landlord details from file
			getline(users, templ.info.id, ',');
			getline(users, templ.info.f_name, ',');
			getline(users, templ.info.l_name, ',');
			getline(users, templ.info.p_num, ',');
			getline(users, templ.info.email, ',');
			getline(users, templ.info.password, ',');
			getline(users, templ.transfer.card_num, ',');
			getline(users, tempd, ',');
			templ.transfer.due = stringtodate(tempd);
			tempd = '\0';
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
	users.close();
}

reservation* read_reservation()
{
	ifstream reservations("reservationDB.csv");// file pointer Open an existing file 
	if (!reservations.is_open())//if open failed
	{
		cout << "ERROR USERS FILE DOES NOT EXIST" << endl;
		return;
	}
	int r_len = 0;
	reservation* rList = NULL;
	reservation temp;
	string tempstr = '\0';
	while (!reservations.eof())
	{
		r_len++;
		getline(reservations, temp.p_name, ',');
		getline(reservations, temp.renter_id, ',');
		getline(reservations, tempstr, ',');
		temp.check_in = stringtodate(tempstr);
		tempstr = '\0';
		getline(reservations, tempstr, ',');
		temp.check_out = stringtodate(tempstr);
		tempstr = '\0';
		getline(reservations, temp.loc, ',');
		getline(reservations, tempstr, ',');
		temp.rate = stoi(tempstr);
		tempstr = '\0';
		getline(reservations, tempstr, '\n');
		if (stoi(tempstr) == 1)
			temp.israted = true;
		else
			temp.israted = false;
		rList = addarr(rList, r_len, temp);
	}
	reservations.close();
	return rList;
}
reservation* addarr(reservation* old, int r_len, reservation res)
{
	reservation* newArr = new reservation[r_len];
	if (!newArr)
	{
		cout << " Memory allocation failed!" << endl;
		return NULL;
	}
	for (int i = 0; i < r_len - 1; i++)
	{
		newArr[i] = old[i];
	}
	newArr[r_len - 1] = res;
	//delete allocation
	delete[] old;
	old = newArr;
	return old;
}
date stringtodate(string str)
{
	date d;
	d.day = stoi(str.substr(0, 2));
	d.month = stoi(str.substr(3, 2));
	d.year = stoi(str.substr(6, 2));
	return d;
}

property* read_properties()
{
	ifstream prop("propertiesDB.csv");// file pointer Open an existing file 
	if (!prop.is_open())//if open failed
	{
		cout << "ERROR USERS FILE DOES NOT EXIST" << endl;
		return;
	}
	int p_len = 0;
	property* pList = NULL;
	property temp;
	string tempstr = '\0';
	while (!prop.eof())
	{
		p_len++;
		getline(prop, temp.owner_id, ',');
		getline(prop, temp.description, ',');
		getline(prop, temp.p_name, ',');
		getline(prop, temp.location, ',');
		getline(prop, tempstr, ',');
		temp.price = stoi(tempstr);
		tempstr = '\0';
		getline(prop, tempstr, ',');
		temp.capacity = stoi(tempstr);
		tempstr = '\0';
		getline(prop, temp.near, ',');
		for (int i = 0; i < 10; i++)//ameneties
			getline(prop, temp.amenities[i], ',');
		getline(prop, tempstr, ',');
		if (stoi(tempstr) == 1)
			temp.status = true;
		else
			temp.status = false;
		tempstr = '\0';
		getline(prop, tempstr, '\0');
		temp.num_of_rates = stoi(tempstr);
		tempstr = '\0';
		pList = addprop(pList, p_len, temp);
	}
	prop.close();
	return pList;
}
property* addprop(property* old, int p_len, property pr)
{
	property* newArr = new property[p_len];
	if (!newArr)
	{
		cout << " Memory allocation failed!" << endl;
		return NULL;
	}
	for (int i = 0; i < p_len - 1; i++)
	{
		newArr[i] = old[i];
	}
	newArr[p_len - 1] = pr;
	//delete allocation
	delete[] old;
	old = newArr;
	return old;
}

string datetostring(date d)
{
	string date = "/0";
	string day = to_string(d.day);
	string month = to_string(d.month);
	string year = to_string(d.year);
	if (day.length() == 1)
		date = '0' + day;
	else
		date = day;
	date.append("/");
	if (month.length() == 1)
		date.append('0' + month);
	else
		date = month;
	date.append("/");
	if (year.length() == 2)
		date.append(year);
	else
		date.append(year.substr(3, 2));
	return date;
}
void write_users(landlord* landlords, int land_len, traveler* travelers, int trav_len)
{
	ofstream p_users;
	p_users.open("usersDB.csv", ios::out || ios::app); //pointer to write into file
	for (int i = 0; i < land_len; i++)
	{
		string duedate = datetostring(landlords[i].transfer.due);
		p_users << 1 << ", "
			<< landlords[i].info.id << ", "
			<< landlords[i].info.f_name << ", "
			<< landlords[i].info.l_name << ", "
			<< landlords[i].info.p_num << ", "
			<< landlords[i].info.email << ", "
			<< landlords[i].info.password << ", "
			<< landlords[i].transfer.card_num << ", "
			<< duedate << ", "
			<< landlords[i].transfer.cvv
			<< "\n";
	}
	for (int i = 0; i < trav_len; i++)
	{
		p_users << 0 << ", "
			<< travelers[i].id << ", "
			<< travelers[i].f_name << ", "
			<< travelers[i].l_name << ", "
			<< travelers[i].p_num << ", "
			<< travelers[i].email << ", "
			<< travelers[i].password
			<< "\n";
	}

	p_users.close();
}
void write_reservations(reservation* reservations, int res_len)
{
	ofstream p_reservation;
	p_reservation.open("reservationDB.csv", ios::out || ios::app); //pointer to write into file
	for (int i = 0; i < res_len; i++)
	{
		string checkin = datetostring(reservations[i].check_in);
		string checkout = datetostring(reservations[i].check_out);

		p_reservation << reservations[i].p_name << ", "
			<< reservations[i].renter_id << ", "
			<< checkin << ", "
			<< checkout << ", "
			<< reservations[i].loc << ", "
			<< reservations[i].rate << ", "
			<< reservations[i].israted
			<< "\n";
	}
	p_reservation.close();

}
void write_properties(property* properties, int p_len)
{
	ofstream p_prop;
	p_prop.open("reservationDB.csv", ios::out || ios::app); //pointer to write into file
	for (int i = 0; i < p_len; i++)
	{
		p_prop << properties[i].owner_id << ", "
			<< properties[i].description << ", "
			<< properties[i].p_name << ", "
			<< properties[i].location << ", "
			<< properties[i].price << ", "
			<< properties[i].capacity << ", "
			<< properties[i].near << ", ";
		for (int j = 0; j < 10; j++)
			p_prop << properties[i].amenities[j] << ", ";
		p_prop << properties[i].status << ", "
			<< properties[i].num_of_rates
			<< "\n";
	}
	p_prop.close();
}

traveler* traveler_login(traveler* travelers)
{
	string id, password;
	int i, size = sizeof(travelers + 1);
	int index = 0, flag = 0;
	cout << "Enter I.D. : ";
	cin >> id;
	for (i = 0; i < sizeof(travelers); i++)
	{
		if (id == travelers[i].id)
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
	} while (password != travelers[index].password || flag == 3);
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
	int i = 0, size = sizeof(travelers);
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
	for (int i = 0; i < size - 1; i++)
	{
		temp[i]->email = travelers[i]->email;//העתקת המערך הקיים לזמני
		temp[i]->f_name = travelers[i]->f_name;
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
	delete[] * travelers;//שחרור המערך
	travelers = new traveler * [size];//יצירת מערך זמני למאגר
	for (int i = 0; i < size; i++)
	{
		travelers[i]->email = temp[i]->email;//העתקת המערך הקיים לזמני
		travelers[i]->f_name = temp[i]->f_name;
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
		landlords[i]->info.id = temp[i]->info.id;
		landlords[i]->info.l_name = temp[i]->info.l_name;
		landlords[i]->info.password = temp[i]->info.password;
		landlords[i]->info.p_num = temp[i]->info.p_num;;//העתקת המערך הקיים לזמני
	}
	return *landlords;
}

void print_properties(property** properties)
{
	for (int i = 0; i < sizeof(properties); i++)
	{
		cout << i + 1;
		print_property(properties[i]);
	}
};

void print_property(property* prop)
{
	cout << ". Name: " << prop->p_name << "\n Description: " << prop->description << "\n Location: " << prop->location << "\n Capacity: " << prop->capacity << "\n Amenities: ";
	string myarr[10] = { "Accessibility: ", "Smoking: ", "Pets: ", "Balcony", "Washing machine", "Wifi", "Pool", "Number of beds: ", "Number of rooms: ", "Rate: " };
	for (int i = 0; i < 3; i++)
		cout << myarr[i] << prop->amenities[i] << " ";
	for (int i = 3; i < 7; i++)
		if (prop->amenities[i] == "Yes")
			cout << myarr[i] << " ";
	for (int i = 7; i < 10; i++)
		cout << myarr[i] << prop->amenities[i] << " ";
	cout << endl;
};

void print_confirmation(property* booked, date from, date to, int nights)
{
	print_property(booked);
	cout << "Dates: " << from.day << '/' << from.month << '/' << from.year << " - " << to.day << '/' << to.month << '/' << to.year << endl;
	cout << "Number of nights: " << nights << endl;
	cout << "Final price: " << nights * booked->price << endl;
};

property* search(property** prop_list, reservation** res_list)
{
	string loc;
	date checkin;
	date checkout;
	int travelers;
	property** ads;
	bool available = true;
	int count = 0;
	int choice, am;
	string amenities[10];
	time_t current = time(0);
	tm* ltm = localtime(&current);
	date current_date;
	current_date.day = ltm->tm_mday;
	current_date.month = ltm->tm_mon;
	current_date.year = ltm->tm_year;
	cout << "Enter location: ";
	cin >> loc;
	do {
		cout << "Enter check in (dd/mm/yyyy): ";
		cin >> checkin.day >> checkin.month >> checkin.year;
		cout << "Enter check out (dd/mm/yyyy): ";
		cin >> checkout.day >> checkout.month >> checkout.year;
		if (checkin < current_date)
			cout << "Error: this date is due. Please enter new dates." << endl;
		if (checkout <= checkin)
			cout << "Error: checkout must be after checkin. Please enter new dates." << endl;
	} while (checkout <= checkin || checkin < current_date);
	cout << "Enter number of travelers: ";
	cin >> travelers;
	for (int i = 0; i < sizeof(prop_list); i++)
	{
		if (prop_list[i]->location == loc && prop_list[i]->capacity >= travelers)
			for (int j = 0; j < sizeof(res_list); j++)
				if (prop_list[i]->p_name == res_list[j]->p_name)
					if (!(checkin >= res_list[j]->check_out || checkout <= res_list[j]->check_in))
						available = false;
		if (available)
		{
			count++;
			ads = new property * [count];
			ads[count - 1] = prop_list[i];
		}
	}
	do {
		print_properties(ads);
		cout << endl << count + 1 << ". Filters" << count + 2 << ". Sort" << endl;
		cout << "Choose an ad or option: ";
		cin >> choice;
		if (choice <= count)
			return ads[choice];
		if (choice == count + 1)
		{
			cout << "Accessibility ? 1.Yes 2.No" << endl;
			yes_no(amenities, 0);
			cout << "Smoking ? 1.Yes 2.No" << endl;
			yes_no(amenities, 1);
			cout << "Pets allowed ? 1.Yes 2.No" << endl;
			yes_no(amenities, 2);
			cout << "Balcony ? 1.Yes 2.No" << endl;
			yes_no(amenities, 3);
			cout << "Wahing machin ? 1.Yes 2.No" << endl;
			yes_no(amenities, 4);
			cout << "Wifi ? 1.Yes 2.No" << endl;
			yes_no(amenities, 5);
			cout << "Pool ? 1.Yes 2.No" << endl;
			yes_no(amenities, 6);
			cout << "Number of beds: ";
			cin >> am;
			amenities[7] = am;
			cout << "Number of rooms: ";
			cin >> am;
			amenities[8] = am;
			cout << "Rate: ";
			cin >> am;
			amenities[9] = am;
			ads = filter(amenities, ads);
		}
		if (choice == count + 2)
		{
			cout << "Choose sort option:\n1.Price low to high   2.Price high to low   3.Rank high to low" << endl;
			cin >> am;
			ads = sort(ads, am);
		}
	} while (choice > count);
}

void yes_no(string am[10], int index)
{
	int choice;
	cin >> choice;
	if (choice == 1)
		am[index] = "Yes";
	else am[index] = "No";
}

property** filter(string* filters, property** properties)
{
	property** ads;
	bool relevant;
	int count = 0;
	for (int i = 0; i < sizeof(properties); i++)
	{
		relevant = true;
		for (int j = 0; j < sizeof(filters); j++)
			if (!(properties[i]->amenities[j] == filters[j]))
				relevant = false;
		if (relevant)
		{
			count++;
			ads = new property*[count];
			ads[count - 1] = properties[i];
		}
	}
	return ads;
}

property** sort(property** ads, int sort_op)
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
	return ads;
}



