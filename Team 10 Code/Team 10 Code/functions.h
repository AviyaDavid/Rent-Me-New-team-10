#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include "Structs.h"
void read_users(landlord* landlords, traveler* travelers);
reservation* read_reservation();
reservation* addarr(reservation* old, int r_len, reservation res);
date stringtodate(string str);

property* read_properties();
property* addprop(property* old, int p_len, property pr);

string datetostring(date d);
void write_users(landlord* landlords, int land_len, traveler* travelers, int trav_len);
void write_reservations(reservation* reservations, int res_len);
void write_properties(property* properties, int p_len);

traveler* traveler_login(traveler* travelers);
traveler* traveler_signup(traveler** travelers, landlord* landlords);
landlord* landlord_login(landlord* landlords);
landlord* landlord_signup(landlord** landlords, traveler* travelers);

#endif