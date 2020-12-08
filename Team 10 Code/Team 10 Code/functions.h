#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include "Structs.h"
void read_users(landlord* landlords, traveler* travelers);
reservation* read_reservation();
property* read_properties();
void write_users(landlord* landlords, traveler* travelers);
void write_reservations(reservation* reservations);
void write_properties(property* properties);
#endif