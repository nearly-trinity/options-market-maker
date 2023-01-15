#include <string>
using namespace std;

class Option {
protected:
    static int nextID;
public:
    int id;
    string ticker;
    char callPut;
    string expiration;
    double strikePrice;

    Option(string ticker, char callPut, string expiary, double strike);
    bool operator==(const Option &other);
};

int Option::nextID = 0;

Option::Option(string t, char cp, string e, double s) 
{
    id = ++nextID;
    ticker = ticker;
    callPut = cp;
    expiration = e;
    strikePrice = s;
}

bool Option::operator==(const Option &other)
{
    return other.id == this->id;
}
