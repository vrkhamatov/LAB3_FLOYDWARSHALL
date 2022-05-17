#ifndef AIRTICKET_H
#define AIRTICKET_H

using namespace std;

#include <string>

#include <utility>

struct Flight {
public:

    string firstFlight_;
    string secondFlight_;

    string price1;
    string price2;


    Flight(string firstFlight_, string secondFlight_, string price1, string price2) {

        if (firstFlight_ == secondFlight_)
            throw std::invalid_argument("You can fly only in different place");

        this->firstFlight_ = std::move(firstFlight_);

        this->price1 = std::move(price1);

        this->secondFlight_ = std::move(secondFlight_);

        this->price2 = std::move(price2);
    }

    Flight() {
        this->firstFlight_ = "";
        this->secondFlight_ = "";
        this->price1 = "N/A";
        this->price2 = "N/A";
    }
};

#endif