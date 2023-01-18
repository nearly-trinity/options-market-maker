#include <string>

using namespace std;


class Stock {
public:
    string ticker;
    double price;

    Stock(string t, double p) {
        ticker = t;
        price = p;
    }
};