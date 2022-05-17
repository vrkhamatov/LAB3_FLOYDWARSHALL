#ifndef LAB_3_FLIGHTTREATMENT_H
#define LAB_3_FLIGHTTREATMENT_H


#include "../list/list.h"
#include "../flights/flights.h"
#include "../pair/pair.h"

List<Flight> parseFile(string filename);

Pair<List<string>, double> calculatePath(List<Flight> &ticketsList, string city1, string city2);

#endif //LAB_3_FLIGHTTREATMENT_H
