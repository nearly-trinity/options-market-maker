#include "options.h"
#include <unordered_map>

using namespace std;

typedef unordered_map<int,Option> tickerOptions;
typedef unordered_map<string,tickerOptions> marketOptions; 

class MarketMaker {
    /*
    What does a market need:
    - way to store all options contracts
    - profit loss
    */

    marketOptions allOptions;
    double pnl;
    string time_stamp;

public:
    MarketMaker();

    bool newTimeStamp(string cur_time);
};
