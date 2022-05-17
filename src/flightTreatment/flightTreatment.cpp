#include "../../headers/flightTreatment/flightTreatment.h"
#include "../../headers/FloydWarshallAlgo/FloydWarshallAlgo.h"

#include <cfloat>
#include <fstream>
#include <string>


Map<string, int> getCityUnique(List<Flight>& ticketsList)
{
    auto* cityNumerics = new Map<string, int>();

    auto itr = ticketsList.create_iterator();
    int cityCount = 0;
    while (itr->has_next())
    {
        Flight ticket = itr->next();

        try
        {
            cityNumerics->Insert(ticket.firstFlight_, cityCount);
            cityCount++;
        }
        catch (const std::exception&){}

        try
        {
            cityNumerics->Insert(ticket.secondFlight_, cityCount);
            cityCount++;
        }
        catch (const std::exception&){}
    }
    delete itr;

    return *cityNumerics;
}

List<string> tokenize(string line, string separator = " ")
{
    int start = 0;
    int end = line.find(separator);
    List<string> splittedLines;

    while (end != -1)
    {
        splittedLines.push_back(line.substr(start, end - start));
        start = end + separator.size();
        end = line.find(separator, start);
    }

    splittedLines.push_back(line.substr(start, end - start));

    return splittedLines;
}

List<Flight> parseFile(string filename)
{
    setlocale(LC_ALL,"ru_RU.UTF-8");
    List<Flight> ticketsList;

    ifstream finput;
    finput.open(filename);

    string line;
    while (getline(finput, line))
    {
        List<string> newTicket = tokenize(line, ";");

        auto newTicket_itr = newTicket.create_iterator();
        string token1 = newTicket_itr->next();
        string token2 = newTicket_itr->next();
        string token3 = newTicket_itr->next();
        string token4 = newTicket_itr->next();
        delete newTicket_itr;

        Flight ticket(token1, token2, token3, token4);
        ticketsList.push_back(ticket);
    }

    return ticketsList;
}

Graph makeGraphWithFlight(List<Flight>& flight, Map<string, int>& cityNumerics)
{
    auto* graph = new Graph(cityNumerics.size);

    for (int i = 0; i < graph->size; i++)
    {
        graph->matrix[i][i] = 0;
    }

    auto ticket_itr = flight.create_iterator();
    while (ticket_itr->has_next())
    {
        Flight ticket = ticket_itr->next();

        int numCity1 = cityNumerics.Find(ticket.firstFlight_);
        int numCity2 = cityNumerics.Find(ticket.secondFlight_);

        if (ticket.price1 == "N/A")
            graph->matrix[numCity1][numCity2] = DBL_MAX;
        else
            graph->matrix[numCity1][numCity2] = stod(ticket.price1);

        if (ticket.price2 == "N/A")
            graph->matrix[numCity2][numCity1] = DBL_MAX;
        else
            graph->matrix[numCity2][numCity1] = stod(ticket.price2);
    }
    delete ticket_itr;

    return *graph;
}

List<string> findOptimalPath(Graph& pathGraph, Map<string, int>& numberOfCities, int i, int j)
{
    auto* optimalPath = new List<string>();

    optimalPath->push_back(numberOfCities.FindKeysByData(i)->getHead());

    double** pathMatrix = pathGraph.matrix;

    int k = i;
    while (pathMatrix[k][j] != j)
    {
        if (pathMatrix[k][j] == DBL_MAX)
            throw invalid_argument("No way");
        string subCity = numberOfCities.FindKeysByData(pathMatrix[k][j])->getHead();
        optimalPath->push_back(subCity);
        k = pathMatrix[k][j];
    }

    optimalPath->push_back(numberOfCities.FindKeysByData(j)->getHead());
    return *optimalPath;
}

Pair<List<string>, double> calculatePath(List<Flight>& ticketsList, string city1, string city2)
{
    Map<string, int> cityNumerics = getCityUnique(ticketsList);

    int size = cityNumerics.size;

    int numCity1 = cityNumerics.Find(city1);
    int numCity2 = cityNumerics.Find(city2);

    Graph graph = makeGraphWithFlight(ticketsList, cityNumerics);

    Graph pathGraph(size);
    FloydWarshall(graph, pathGraph);

    Pair<List<string>, double> optimalSoulution;

    double optimalWay = graph.matrix[numCity1][numCity2];
    if (optimalWay == DBL_MAX)
        throw invalid_argument("No way");

    optimalSoulution.second = optimalWay;

    List<string> optimalPath = findOptimalPath(pathGraph, cityNumerics, numCity1, numCity2);
    optimalSoulution.first = optimalPath;

    return optimalSoulution;
}