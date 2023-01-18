#include "options.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

typedef unordered_map<int,Option> marketOptions;

class MarketMaker {
    double spread = 0.02;
    fstream underlying;
    fstream past_options;
public:
    marketOptions allOptions;
    double pnl;
    string time_stamp;

    MarketMaker();
    void showOptions();
    bool newTimeStamp(string cur_time);
    int addOptionFromParts(vector<string> tick);
    int addTradedOptionFromParts(vector<string> tick);
    void closeStreams() { underlying.close(); }
};


