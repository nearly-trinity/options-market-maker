#include "stock.h"
#include <iostream>
#include <iomanip>

using namespace std;

class Option {
protected:
    static int nextID;
    double bidPrice;
    double askPrice;
    double position;
    double longPrice;
    double shortPrice;

public:
    int id;
    string ticker;
    char callPut;
    string expiration;
    double strikePrice;


    Option();
    Option(string ticker, char callPut, string expiary, double strike);
    
    string toString();
    double calcPrice(Stock stock);
    void setOptionPrice(Stock baseline, double spread);
    
    bool operator==(const Option &other) { return other.id == this->id; }
    friend ostream& operator<<(ostream& os, const Option& op);
};

int Option::nextID = 0;

Option::Option()
{
    id = ++nextID;
}

string Option::toString()
{
    string s = this->ticker + ": " + to_string(this->strikePrice);
    return s;
}

Option::Option(string t, char cp, string e, double s) 
{
    id = ++nextID;
    ticker = t;
    callPut = cp;
    expiration = e;
    strikePrice = s;
}

ostream& operator<<(ostream& os, const Option& op)
{
    os << setw(9) << left
       << op.strikePrice 
       << setw(3) << left
       << op.callPut
       << setw(10) << left
       << op.expiration
       << setw(9) << left
       << op.bidPrice
       << setw(9) << left
       << op.askPrice
       << setw(9) << left
       << op.position
       << setw(11) << left
       << op.longPrice
       << setw(11) << left
       << op.shortPrice;
    return os;
}