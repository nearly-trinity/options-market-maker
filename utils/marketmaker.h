#include "utils/options.h"
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

public:
    MarketMaker();
};

MarketMaker::MarketMaker() { pnl = 0; }
