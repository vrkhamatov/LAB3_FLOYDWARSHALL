#include "gtest/gtest.h"
#include "../../../headers/FloydWarshallAlgo/FloydWarshallAlgo.h"
#include "../../../headers/list/list.h"
#include "../../../src/FloydWarshallAlgo/FloydWarshallAlgo.cpp"
#include "../headers/flightTreatment/flightTreatment.h"

class TestFloyd : public ::testing::Test {
protected:
    List<Flight> flight;

};

TEST_F(TestFloyd,testCalculatePathFunction1){
    flight.push_back(Flight("Saint - Petersburg", "Moscow", "1200", "1100"));
    flight.push_back(Flight("Moscow", "Vladivostok", "15000", "14000"));
    flight.push_back(Flight("Saint - Petersburg", "Novosibirsk", "20000", "N/A"));
    flight.push_back(Flight("Novosibirsk", "Vladivostok", "3000", "2700"));

    double cost = calculatePath(flight, "Saint - Petersburg", "Vladivostok").second;

    GTEST_ASSERT_EQ(cost, 16200.0);

}

TEST_F(TestFloyd,testCalculatePathFunction2){

    flight.push_back(Flight("Ufa", "Kazan", "5000", "4900"));
    flight.push_back(Flight("Saint-Petersburg", "Moscow", "1200", "1100"));
    flight.push_back(Flight("Moscow", "Kazan", "3000", "2900"));
    flight.push_back(Flight("Kazan", "Ufa", "1000", "900"));

    double cost = calculatePath(flight, "Saint - Petersburg", "Vladivostok").second;

    GTEST_ASSERT_EQ(cost, 5200.0);


}
