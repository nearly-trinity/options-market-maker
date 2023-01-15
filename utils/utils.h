#include <string>
#include <filesystem>
#include <fstream>


namespace constants 
{
    const int DELAY = 2000;
    const std::string STOCK_PATH = "data/AMZN_STOCK_XFM";
    const std::string OPTION_PATH = "data/AMZN_OPTIONS_XFM";
    const std::string FIFO_PATH = "fifo";
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