#include "options.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

typedef unordered_map<int,Option> marketOptions;

class MarketMaker {
    double spread = .02;
    fstream underlying;
public:
    marketOptions allOptions;
    double pnl;
    string time_stamp;

    MarketMaker();
    void priceOption(int option_id);
    void showOptions(string ticker);
    bool newTimeStamp(string cur_time);
    int addOptionFromTick(vector<string>);
};


