#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include "Structs.h"
void read_users(landlord* landlords, traveler* travelers);
reservation* read_reservation();
reservation* addarr(reservation* old, int r_len, reservation res);
date stringtodate(string str);

property* read_properties();
property* addprop(property* old, int p_len, property pr);

void write_users(landlord* landlords, traveler* travelers);
void write_reservations(reservation* reservations);
void write_properties(property* properties);

traveler* traveler_login(traveler* travelers);
traveler* traveler_signup(traveler** travelers, landlord* landlords);
landlord* landlord_login(landlord* landlords);
landlord* landlord_signup(landlord** landlords, traveler* travelers);

#endif