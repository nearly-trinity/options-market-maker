#include <boost/interprocess/ipc/message_queue.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <random>

using namespace std;

namespace consts 
{
    const int DELAY = 10;
    const std::string STOCK_PATH = "data/AMZN_STOCK_XFM";
    const std::string OPTION_PATH = "data/AMZN_OPTIONS_XFM";
    const std::string TRADED_OPTION_PATH = "data/TRADED_OPTIONS";
    const size_t MAX_MSG_SIZE = 0x100;
    const size_t MAX_NUM_MSG = 100;
    const double spread = 0.01;
    const double DELTA_T = 0.1;
    const double RISK_FREE_RATE = 0.03;
    const double ANNUALIZED_VOLITLITY = 0.2;
    const int YEARS_TO_EXPIRATION = 2;
}

namespace underlying
{
    const int TICKER_IDX = 0;
    const int TIME_IDX = 1;
    const int PRICE_IDX = 2;
}

namespace options
{
    const int TICKER_IDX = 0;
    const int TIME_IDX = 1;
    const int CALL_PUT_IDX = 2;
    const int STRIKE_IDX = 3;
    const int EXPIRY_IDX = 4;
    const int HIGH_PRICE_IDX = 5;
    const int HIGH_SIZE_IDX = 6;
    const int LOW_ASK_IDX = 7;
    const int LOW_SIZE_IDX = 8;

}

namespace tradedop
{
    const int TICKER_IDX = 0;
    const int CALL_PUT_IDX = 1;
    const int STRIKE_IDX = 2;
    const int EXPIRY_IDX = 3;
}