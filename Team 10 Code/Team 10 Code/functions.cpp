#define _CRT_SECURE_NO_WARNINGS
#define BREAK "****************************************************"
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
	traveler** temp = new traveler * [size];//����� ���� ���� �����
	for (int i = 0; i < size - 1; i++)
	{
		temp[i]->email = travelers[i]->email;//����� ����� ����� �����
		temp[i]->f_name = travelers[i]->f_name;
		temp[i]->id = travelers[i]->id;
		temp[i]->l_name = travelers[i]->l_name;
		temp[i]->password = travelers[i]->password;
		temp[i]->p_num = travelers[i]->p_num;
	}
	temp[size]->id = id;//����� �� ���� ���� �����
	temp[size]->f_name = f_name;
	temp[size]->l_name = l_name;
	temp[size]->password = password;
	temp[size]->p_num = p_num;
	temp[size]->email = email;
	delete[] * travelers;//����� �����
	travelers = new traveler * [size];//����� ���� ���� �����
	for (int i = 0; i < size; i++)
	{
		travelers[i]->email = temp[i]->email;//����� ����� ����� �����
		travelers[i]->f_name = temp[i]->f_name;
		travelers[i]->id = temp[i]->id;
		travelers[i]->l_name = temp[i]->l_name;
		travelers[i]->password = temp[i]->password;
		travelers[i]->p_num = temp[i]->p_num;;//����� ����� ����� �����
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




bool check_id(string id)
{
	//the function returns true if the string is made of numbers only. else - false.
	if (id.length() != 9)
		return false;
	for (int i = 0; i < id.length(); ++i)
	{
		if (isdigit(id[i]) == false)
			return false;
	}
	return true;
}


landlord** landlord_signup(landlord** landlords, traveler** travelers , int* size_of_landlords, int size_of_travelers)
{
	
	int i = 0;
	landlord new_lanlord;
	bool flag = true;
	do
	{
		cout << "Enter I.D. : ";
		cin >>new_lanlord.info.id;
		if (check_id(new_lanlord.info.id))
		{
			for (i; i < size_of_travelers; i++)
			{
				if (new_lanlord.info.id == travelers[i]->id)
				{
					flag = false;
					break;
				}

			}
			for (i = 0; i < *size_of_landlords && flag; i++)
			{
				if (new_lanlord.info.id == landlords[i]->info.id)
				{
					flag = false;
					break;
				}
			}
			if (!flag)
				cout << "The ID is already registerd. " << endl;
		}
		else
			flag = false;

	} while (flag = false);
	
	bool flag1 = false;
	flag = true;
	cout << "Enter your first name please:" << endl;
	cin >> new_lanlord.info.f_name;
	cout << "Enter your last name please:" << endl;
	cin >> new_lanlord.info.l_name;
	do
	{
		cout << "Enter your phone nunber please:" << endl;
		cin >> new_lanlord.info.p_num;
		for (int i = 0; i < new_lanlord.info.p_num.length(); ++i)
		{
			if (isdigit(new_lanlord.info.p_num[i]) == false)
			{
				flag = false;
				break;
			}
		}

	} while (flag =false);
	
	cout << "Enter your password please:" << endl;
	cin >> new_lanlord.info.password;
	cout << "Enter your email please:" << endl;
	cin >> new_lanlord.info.email;
	landlord** temp = new landlord* [(*size_of_landlords)+1];//����� ���� ���� �����
	for (int i = 0; i < *size_of_landlords; i++)
	{
		temp[i] = landlords[i];

	}
	temp[(*size_of_landlords)++] = &new_lanlord;
	delete[] landlords;//����� �����
	landlords = new landlord* [*size_of_landlords];//����� ���� ���� �����
	landlords = temp;

	return landlords;
}

void print_properties(property** properties, int size_of_properties) // print all the properties in the properties list
{
	for (int i = 0; i < size_of_properties; i++)
	{
		cout << i + 1;
		print_property(properties[i]);
	}
};

void print_property(property* prop) // print all the details about a property
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
	cout << "___________________________________" << endl;
};

void print_confirmation(property* booked, date from, date to, int nights) // print a confirmation with order main details
{
	print_property(booked);
	cout << "Dates: " << from.day << '/' << from.month << '/' << from.year << " - " << to.day << '/' << to.month << '/' << to.year << endl;
	cout << "Number of nights: " << nights << endl;
	cout << "Final price: " << nights * booked->price << endl;
};

property* search(property** prop_list, reservation** res_list) // search process. RETURN: pointer to the chosen property to rent
{
	string loc; // location
	date checkin; // date for checkin
	date checkout; // date for checkout
	int travelers; // number of travelers
	property** ads; // relevant ads list
	bool available = true; // availability
	int count = 0; // number of relevant ads
	int choice, am; // menu choice 
	string amenities[10]; // array of selected amenities for search process
	time_t current = time(0); 
	tm* ltm = localtime(&current);
	date current_date; // current date 
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
		if (compDates(current_date, checkin) == 1)
			cout << "Error: this date is due. Please enter new dates." << endl;
		if (compDates(checkin, checkout) != 2)
			cout << "Error: checkout must be after checkin. Please enter new dates." << endl;
	} while (compDates(current_date, checkin) == 1 || compDates(checkin, checkout) != 2);
	cout << "Enter number of travelers: ";
	cin >> travelers;
	for (int i = 0; i < sizeof(prop_list); i++)
	{
		if (prop_list[i]->location == loc && prop_list[i]->capacity >= travelers) // search by location and capacity
			for (int j = 0; j < sizeof(res_list); j++) 
				if (prop_list[i]->p_name == res_list[j]->p_name) // verifing availability
					if (compDates(res_list[j]->check_out, checkin) == 1 && compDates(checkout, res_list[j]->check_in) == 1)
						available = false;
		if (available)
		{
			count++;
			ads = new property * [count];
			ads[count - 1] = prop_list[i]; // add the property to the relevant ads list
		}
	}
	do {
		print_properties(ads, count); 
		cout << endl << count + 1 << ". Filters" << count + 2 << ". Sort" << endl;
		cout << "Choose an ad or option: ";
		cin >> choice;
		if (choice <= count) // if a property is chosen
			return ads[choice]; // return it
		if (choice == count + 1) // if filter option selected 
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
			ads = filter(amenities, ads, count);
		}
		if (choice == count + 2) // if sort option selected
		{
			cout << "Choose sort option:\n1.Price low to high   2.Price high to low   3.Rank high to low" << endl;
			cin >> am;
			ads = sort(ads, count, am);
		}
	} while (choice > count); 
}

void yes_no(string am[10], int index) // help to convert 1 tp Yes and 2 to No
{
	int choice;
	cin >> choice;
	if (choice == 1)
		am[index] = "Yes";
	else am[index] = "No";
}

property** filter(string* filters, property** properties, int& sizeof_properties)  // return list of relevant ads after applicate filters on the properties list
{
	property** ads; // returned list
	bool relevant; 
	int count = 0; // number of relevant ads
	for (int i = 0; i < sizeof_properties; i++)
	{
		relevant = true;
		for (int j = 0; j < 10; j++)
			if (!(properties[i]->amenities[j] == filters[j])) // verif each filter according to each property in the list
				relevant = false;
		if (relevant)
		{
			count++;
			ads = new property*[count];
			ads[count - 1] = properties[i];
		}
	}
	sizeof_properties = count;
	return ads;
}

property** sort(property** ads, int sizeof_ads ,int sort_op) // return list of relevant ads after applicate sorting to the properties list
{
	property* temp;
	if (sort_op == 1) // by price low to high
	{
		for (int i = 0; i < sizeof_ads - 1; i++)
			for (int j = i + 1; j < sizeof_ads; j++)
				if (ads[i]->price > ads[j]->price)
				{
					temp = ads[i];
					ads[i] = ads[j];
					ads[j] = temp;
				}
	}
	else if (sort_op == 2) // by price high to low
	{
		for (int i = 0; i < sizeof_ads - 1; i++)
			for (int j = i + 1; j < sizeof_ads; j++)
				if (ads[i]->price < ads[j]->price)
				{
					temp = ads[i];
					ads[i] = ads[j];
					ads[j] = temp;
				}
	}
	else if (sort_op == 3) // by rank high to low
	{
		for (int i = 0; i < sizeof_ads - 1; i++)
			for (int j = i + 1; j < sizeof_ads; j++)
				if (ads[i]->num_of_rates < ads[j]->num_of_rates)
				{
					temp = ads[i];
					ads[i] = ads[j];
					ads[j] = temp;
				}
	}
	return ads;
}

reservation** payment(property* chosen, traveler renter, reservation** reservations, int* size_of_reservations, date chek_in, date chek_out)
{
	//לבדןק!!
	string cvv, card_num, card_owner_id;
	date due;
	cout << "Number of card:" << endl;
	cin >> card_num;
	cout << "Card owner ID:" << endl;
	cin >> card_owner_id;
	cout << "Due date number:" << endl;
	cout << "Month: ";
	cin >> due.month;
	int courrent_month = 12;
	int courrent_year = 2020;
	while (due.month > 12 || due.month < 1 || due.month < courrent_month)
	{
		cout << "Incorrect month. Please enter again" << endl;
		cin >> due.month;
	}
	cout << "Year: ";
	cin >> due.year;
	while (due.year < courrent_year)
	{
		cout << "Invalid year. Please enter again" << endl;
		cin >> due.year;
	}
	cout << "CVV: " << endl;
	cin >> cvv;
	while (sizeof(cvv) != 4)
	{
		cout << "Wrong input, CVV should be only for 3 digits. Please enter again" << endl;
		cin >> cvv;
	}
	reservation temp_res;
	reservation* new_reservation = &temp_res; // Creating new reservation.
	(*new_reservation).p_name = (*chosen).p_name;
	(*new_reservation).renter_id = renter.id;
	(*new_reservation).loc = (*chosen).location;
	(*new_reservation).check_in = chek_in;
	(*new_reservation).check_out = chek_out;
	(*new_reservation).rate = 0;
	(*new_reservation).israted = false; 

	reservation** temp = new reservation * [*size_of_reservations + 1];
	for (int i = 0; i < *size_of_reservations; i++)
	{
		temp[i] = reservations[i];
	}
	temp[*size_of_reservations + 1] = new_reservation;
	*size_of_reservations += 1;
	for (int i = 0; i < *size_of_reservations; i++)
	{
		delete reservations[i];
	}
	reservation* reservations = new reservation[*size_of_reservations];
	for (int i = 0; i < *size_of_reservations; i++)
	{
		reservations[i] = temp[i];
	}
	for (int i = 0; i < *size_of_reservations; i++)
	{
		delete temp[i];
	}

	return reservations;

}
property** add_property(landlord *host, property** properties, int* size_of_properties)
{
	int x;
	property new_prop;
	property* new_property = &new_prop;
	cout << "Description: " << endl;
	cin >> (*new_property).description;
	cout << endl;
	cout << "Property name: " << endl;
	cin >> (*new_property).p_name;
	cout << endl;
	cout << "Location: " << endl;
	cin >> (*new_property).location;
	cout << endl;
	do
	{
		cout << "Price per night. A possitive number: " << endl;
		cin >> (*new_property).price;
	} while ((*new_property).price <= 0);
	do
	{
		cout << endl << "Capacity. A possitive number: " << endl;
		cin >> (*new_property).capacity;

	} while ((*new_property).capacity <= 0);
	cout <<endl<< "Nearby Attractions: " << endl;
	cin >> (*new_property).near; 
	cout <<endl<< "Availability: \n1.Yes \n else-No" << endl;
	cin >> x;
	if (x == 1)
		new_property->status = true;
	else
	{
		new_property->status = false;
	}
	new_property->num_of_rates = 0;
	cout << "Acessability: \n1.Yes \n else-No" << endl;
	cin >> x;
	if (x == 1)
		new_property->amenities[0] = "Yes";
	else
	{
		new_property->amenities[0] = "No";
	}
	cout << "Smoke: \n1.Yes \n else-No" << endl;
	cin >> x;
	if (x == 1)
		new_property->amenities[1] = "Yes";
	else
	{
		new_property->amenities[1] = "No";
	}
	cout << "Pet: \n1.Yes \n else-No" << endl;
	cin >> x;
	if (x == 1)
		new_property->amenities[2] = "Yes";
	else
	{
		new_property->amenities[2] = "No";
	}
	cout << "Balcony: \n1.Yes \n else-No" << endl;
	cin >> x;
	if (x == 1)
		new_property->amenities[3] = "Yes";
	else
	{
		new_property->amenities[3] = "No";
	}
	cout << "Wash: \n1.Yes \n else-No" << endl;
	cin >> x;
	if (x == 1)
		new_property->amenities[4] = "Yes";
	else
	{
		new_property->amenities[4] = "No";
	}
	cout << "Wi-Fi: \n1.Yes \n else-No" << endl;
	cin >> x;
	if (x == 1)
		new_property->amenities[5] = "Yes";
	else
	{
		new_property->amenities[5] = "No";
	}
	cout << "Pool: \n1.Yes \n else-No" << endl;
	cin >> x;
	if (x == 1)
		new_property->amenities[6] = "Yes";
	else
	{
		new_property->amenities[6] = "No";
	}
	cout << "Numbers of beds: ";
	int y;
	cin >> y;
	while (y < 0)
	{
		cout << "Wrong input. Please enter again" << endl;
		cin >> y;
	}
	new_property->amenities[7] = to_string(y);
	cout << "Numbers of rooms: ";
	while (y < 0)
	{
		cout << "Wrong input. Please enter again" << endl;
		cin >> y;
	}
	new_property->amenities[8] = to_string(y);
	new_property->amenities[9] = '0';
	property** temp = new property * [*size_of_properties + 1];
	for (int i = 0; i < *size_of_properties; i++)
	{
		temp[i] = properties[i];
	}
	temp[(*size_of_properties) ++] = new_property;
	delete[] properties;
	properties = temp;

	return properties;
}

property** editMenu(landlord* host, property** properties, int& size_of_properties)
{
	int x, y;
	int flag = 0;
	int check = 0;
	string name;
	cout << "Properties list:" << endl;
	for (int i = 0; i < size_of_properties; i++)
		if (host->info.id == properties[i]->owner_id)
			print_property(properties[i]);
	cout << "For Edit property press 1" << endl;
	cout << "For Delete property press 2" << endl;
	cout << "For Exit press 0" << endl;
	cin >> x;
	while (x != 0)
	{
		while (x != 1 || x != 2)
		{

			cout << "Wrong input. Please enter again" << endl;
			cin >> x;
		}
		if (x == 0)
			break;
		cout << "Enter the name of the property you want to Edit/Delete" << endl;
		cin >> name;
		for (int i = 0; i < size_of_properties; i++)
		{
			flag++;
			if (name == properties[i]->p_name)
			{
				check = 1;
				break;
			}

		}
		flag--;
		if (check == 1)
		{
			if (x == 1)
			{
				edit((properties[flag]));
				cout << "Property updated." << endl;
			}
			if (x == 2)
			{
				deletep(properties[flag], properties, size_of_properties);
				cout << "Property deleted." << endl;
			}
		}
		else
		{
			cout << "Name was not found in the list." << endl;
		}
		cout << "For Edit property press 1" << endl;
		cout << "For Delete property press 2" << endl;
		cout << "For Exit press 0" << endl;
		cin >> x;
	}

	return properties;

}
property* edit(property* old_prop)
{
	int x;
	cout << "Edit Property:" << endl;
	cout << " Press: \n 1-Exit \n 2-Description \n 3- Property name \n 4-Location \n 5- Price per night \n 6-Capasity \n 7-Nearby Attractions \n 8- Availability \n 9-Amenities \n10-Number of rates" << endl;
	cin >> x;
	while (x != 1)
	{
		switch (x)
		{
		case 2:
			cout << "Enter a new Description: " << endl;
			cin >> (*old_prop).description;
			cout << endl;
			break;
		case 3:
			cout << "Enter a new Property name: " << endl;
			cin >> (*old_prop).p_name;
			cout << endl;
			break;
		case 4:
			cout << "Enter a new Location: " << endl;
			cin >> (*old_prop).location;
			cout << endl;
			break;
		case 5:
			cout << "Enter a new Price per night: " << endl;
			cin >> (*old_prop).price;
			while ((*old_prop).price < 0)
			{
				cout << "Wrong input, price should be a possitive number. Please enter again" << endl;
				cin >> (*old_prop).price;
			}
			cout << endl;
			break;
		case 6:
			cout << "Enter a new Capasity: " << endl;
			cin >> (*old_prop).capacity;
			while ((*old_prop).capacity < 0)
			{
				cout << "Wrong input, capasity should be a possitive number. Please enter again" << endl;
				cin >> (*old_prop).capacity;
			}
			cout << endl;
			break;
		case 7:
			cout << "Enter a new Nearby Attractions: " << endl;
			cin >> (*old_prop).near;
			cout << endl;
			break;
		case 8:
			cout << "Availability: \n1.Yes \n else-No" << endl;
			cin >> x;
			if (x == 1)
				(*old_prop).status = true;
			else
			{
				(*old_prop).status = false;
			}
			cout << endl;
			break;
		case 9:
			int y;
			cout << "Amenities: \n Press: \n 0-Exit\n1-Accessability \n2-Smoke \n3-Pet \n4-Balcony \n5-Wash \n6-Wi-Fi \n 7-Pool \n 8-Number of beds \n9-Number of rooms \n10-Rate \n";
			cin >> y;
			while (y != 0)
			{
				switch (y)
				{
				case 1:
					cout << "Edit Acessability: \n1.Yes \n else-No" << endl;
					cin >> x;
					if (x == 1)
						(*old_prop).amenities[0] = "Yes";
					else
					{
						(*old_prop).amenities[0] = "No";
					}
					break;
				case 2:
					cout << "Smoke: \n1.Yes \n else-No" << endl;
					cin >> x;
					if (x == 1)
						(*old_prop).amenities[1] = "Yes";
					else
					{
						(*old_prop).amenities[1] = "No";
					}
					break;
				case 3:
					cout << "Pet: \n1.Yes \n else-No" << endl;
					cin >> x;
					if (x == 1)
						(*old_prop).amenities[2] = "Yes";
					else
					{
						(*old_prop).amenities[2] = "No";
					}
					break;
				case 4:
					cout << "Balcony: \n1.Yes \n else-No" << endl;
					cin >> x;
					if (x == 1)
						(*old_prop).amenities[3] = "Yes";
					else
					{
						(*old_prop).amenities[3] = "No";
					}
					break;
				case 5:
					cout << "Wash: \n1.Yes \n else-No" << endl;
					cin >> x;
					if (x == 1)
						(*old_prop).amenities[4] = "Yes";
					else
					{
						(*old_prop).amenities[4] = "No";
					}
					break;
				case 6:
					cout << "Wi-Fi: \n1.Yes \n else-No" << endl;
					cin >> x;
					if (x == 1)
						(*old_prop).amenities[5] = "Yes";
					else
					{
						(*old_prop).amenities[5] = "No";
					}
					break;
				case 7:
					cout << "Pool: \n1.Yes \n else-No" << endl;
					cin >> x;
					if (x == 1)
						(*old_prop).amenities[6] = "Yes";
					else
					{
						(*old_prop).amenities[6] = "No";
					}
					break;
				case 8:
					int s;
					cout << "Edit number of beds: ";
					cin >> s;
					while (s < 0)
					{
						cout << "Wrong input. Please enter again" << endl;
						cin >> s;
					}
					(*old_prop).amenities[7] = to_string(s);
					break;
				case 9:
					int k;
					cout << "Edit Number of rooms: ";
					while (k < 0)
					{
						cout << "Wrong input. Please enter again" << endl;
						cin >> k;
					}
					(*old_prop).amenities[8] = to_string(k);
					break;
				case 10:
					int z;
					cout << "Edit rate: ";
					while (z < 0)
					{
						cout << "Wrong input. Please enter again" << endl;
						cin >> z;
					}
					(*old_prop).amenities[9] = to_string(z);
					break;

				default:
					cout << "Wrong input. Please enter again" << endl;
					break;
				}
				cout << "Amenities: \n Press: \n 0-Exit\n1-Accessability \n2-Smoke \n3-Pet \n4-Balcony \n5-Wash \n6-Wi-Fi \n 7-Pool \n 8-Number of beds \n9-Number of rooms \n10-Rate \n";
				cin >> y;

			}
		case 10:
			cout << "Edit  number of rates: ";
			cin >> (*old_prop).num_of_rates;
			while ((*old_prop).num_of_rates < 0)
			{
				cout << "Wrong input. Please enter again" << endl;
				cin >> (*old_prop).num_of_rates;
			}
			break;

		default:
			cout << "Wrong input. Please enter again" << endl;
			break;
		}
		cout << " Press: \n 0-Exit \n 1-Owner Id \n 2-Description \n 3- Property name \n 4-Location \n 5- Price per night \n 6-Capasity \n 7-Nearby Attractions \n 8- Availability \n 9-Amenities \n10-Number of rates" << endl;
		cin >> x;

	}

	return old_prop;

}
property** deletep(property* p_chosen, property** properties, int& size_of_properties)
{
	int check = 0;
	for (int i = 0; i < size_of_properties; i++)
	{
		if ((*properties[i]).p_name == (*p_chosen).p_name)
		{
			check = 1;
		}
	}
	if (check == 1)
	{
		
		property** temp = new property * [size_of_properties-1];
		for (int i = 0, j =0 ; i < size_of_properties; ++i, ++j)
		{
			if ((*properties[i]).p_name != (*p_chosen).p_name)
			{
				temp[j] = properties[i];
			}
			else
				--j;

		}
		delete[]properties;
		size_of_properties -= 1;
		properties = temp;
	}
	return properties;
}
// ********* print the traveler's resrvatios history *********
void print_reservations(reservation* reservations, int size_res, property* properties, int size_pro, string id)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);  // get the local time 
	date today;   // create today's  date
	today.year = ltm->tm_year + 1900;
	today.month = ltm->tm_mon + 1;
	today.day = ltm->tm_mday;

	int j;     // index for the traveler's reservations
	for (int i = 0; i < size_res; ++i) // go over the reservations array
	{
		if (id == reservations[i].renter_id)   // if the reservation belong to the currently registered traveler
		{
			// printing the reservation details
			++j;
			cout << "reservation number: " << j << "\n";
			cout << "property's name: " << reservations[i].p_name << endl;
			cout << "check in: " << reservations[i].check_in.day << "/" << reservations[i].check_in.month << "/" << reservations[i].check_in.year << endl;
			cout << "check out: " << reservations[i].check_out.day << "/" << reservations[i].check_out.month << "/" << reservations[i].check_out.year << "\n";
			cout << "property's location: " << reservations[i].loc << "\n";
			if (reservations[i].israted == true)  // check if the reservation was rated
				cout << "personal rating: " << reservations[i].rate << "\n";
			else
			{
				cout << "personal rating: not rated yet\n";
				if (compDates(today, reservations[i].check_out) == 1)   // check that the check out date 
				{
					int flag;  //  keep 1 if the traveler want to rate the property
					cout << "would you like to rate the property?\n1 - Yes\nelse - No " << endl;
					cin >> flag;
					if (flag == 1)
						rate((reservations + i), properties, size_pro);   // sent to get rate
				}
			}

			cout << BREAK << endl;   // print the line breaker between each reservation
		}
	}
}

// ********* get rating from user **********
void rate(reservation* res, property** properties, int size_pro)
{
	int per_rate;
	int i;  // keep the index of the wanted property
	for (i = 0; i < size_pro; ++i)   // go over the properties array
		if (res->p_name == properties[i]->p_name)    // check for the right property
			break;
	do {
		cout << "please rate the property, enter a number between 5 to 1\n";
		cin >> per_rate;    // get the rating
	} while (per_rate < 1 || per_rate > 5);   // check for invalid rating

	res->rate = per_rate;
	res->israted = true;
	int newRate = stoi(properties[i]->amenities[9]);    // get the current rating of the property
	newRate = ((properties[i]->num_of_rates * newRate) + per_rate) / (properties[i]->num_of_rates + 1);   // calc the new rate
	++(properties[i]->num_of_rates);  // update the number of people who rated the property
	properties[i]->amenities[9] = to_string(newRate);  // // update the rating
}


/* compare between dates */
int compDates(date a, date b)
/* the function compare two dates, return 0 if the dates are equal, 1 if the first is bigger than the second or else it return 2 */
{
	// check who is bigger by year
	if (a.year > b.year)
		return 1;
	else if (a.year < b.year)
		return 2;

	// check by month
	else if (a.month > b.month)
		return 1;
	else if (a.month < b.month)
		return 2;

	// check by day
	else if (a.day > b.day)
		return 1;
	else if (a.day < b.day)
		return 2;

	// the dates are equal
	else
		return 0;
}


// ****** Main Menu ****** 
void mainMenu()
{
	traveler** travelers = NULL;        // travelers array
	int size_travel = 0;     // the size of the travelers array

	landlord** landlords = NULL;        // landlords array
	int size_land = 0;       // the size of the landlords array

	reservation** reservations = NULL;  // reservations array
	int size_res = 0;        // the size of the reservaions array

	property** properties = NULL;       // reservations property
	int size_pro = 0;        // the size of the reservations property

	// the  reading from files functions needs to get the sizes by reference' 
	read_users(travelers, landlords, size_travel, size_land);   // initialize users arrays
	*reservations = read_reservation(size_res);   // initialize reservations array
	*properties = read_properties(size_pro);  // initialize properties array

	int choice;
	cout << "Welcome to RentMe" << endl;
	do {
		cout << "Main Menu" << endl << "1 - enter as a landlord" << endl << "2 - enter as a traveler" << endl << "3 - exit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			break;   // activate landlord menu
		case 2:
			break;  // activate traveler menu
		case 3:
			cout << "Goodbye!" << endl;
			freeMemory();  // delete allocated memory
			break;
		default:
			cout << "no such option" << endl;
		}
	} while (choice != 3);   // do as long as the user didnt choose exit
}

void LandlordMenu(traveler** travelers, int size_travel, landlord** landlords, int size_land, reservation** reservations, int size_res, property** properties, int size_pro)
{
	int choice;
	do {
		cout << "Landlord Menu" << endl;
		cout << "1 - ";

	} while (choice != 4);
}


void travelerdMenu(traveler** travelers, int size_travel, landlord** landlords, int size_land, reservation** reservations, int size_res, property** properties, int size_pro)
{
	int choice;
	do {
		cout << "Traveler Menu" << endl;
		cout << "1 - search for  ";

	} while (choice != 3);
}

// free all allocted memory
void freeMemory(traveler** travelers, int size_travel, landlord** landlords, int size_land, reservation** reservations, int size_res, property** properties, int size_pro)
{
	delete[] travelers;
	travelers = NULL;
	delete[] landlords;
	landlords = NULL;
	delete[] reservations;
	reservations = NULL;
	delete[] properties;
	properties = NULL;

}