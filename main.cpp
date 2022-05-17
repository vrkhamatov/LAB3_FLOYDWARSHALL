#include <string>
#include <iostream>

#include "headers/flightTreatment/flightTreatment.h"

using namespace std;


int main()
{
    setlocale(LC_CTYPE, "rus");

    List<Flight> ticketsList = parseFile("../flight.txt");

    Pair<List<string>, double> optimalSolution = calculatePath(ticketsList, "Saint-Petersburg", "Ufa");

    cout << "��������� ���� �� " << optimalSolution.first.head->value << " � " << optimalSolution.first.last->value << endl;

    cout << "����������� ���� ��� ����� ����: " << optimalSolution.second << endl;

    if (optimalSolution.first.size > 2){
        cout << "����������� ����: " << endl;
        auto itr = optimalSolution.first.create_iterator();
        while (itr->has_next())
        {
            cout << itr->next();
            if(itr->has_next())
                cout << " -> ";
        }
    }
    else
        cout << "����������� ���� - ������: " << optimalSolution.first.head->value << " -> " << optimalSolution.first.last->value;
}