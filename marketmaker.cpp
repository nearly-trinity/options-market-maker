#include "utils/marketmaker.h"
#include "utils/utils.h"
#include <sstream>
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace boost::interprocess;
using namespace std;

void recieveMessage(string &s, message_queue &mq, size_t size, unsigned int prio)
{
    s.resize(consts::MAX_MSG_SIZE);
    mq.receive(&s[0], s.size(), size, prio);
    s.resize(size);
}

double Option::calcPrice(Stock stock)
{
    int b = callPut == 'C' ? 1 : -1;
    int y = consts::YEARS_TO_EXPIRATION;
    double deltaT = consts::DELTA_T;
    double s = stock.price;
    double k = strikePrice;
    double sigma = consts::ANNUALIZED_VOLITLITY;
    double r = consts::RISK_FREE_RATE;

    double u = exp(sigma * sqrt(deltaT));
    double d = exp(-sigma * sqrt(deltaT));
    double p = (exp(r * deltaT) - d) / (u - d);
    int n = y / deltaT;

    double lambda[n];

    for (int i = 0; i < n; ++i)
    {
        lambda[i] = b * ((s * pow(u, 2 * i - n)) - k);
        lambda[i] = max(lambda[i], 0.0);
    }

    for (int j = n - 1; j >= 0; --j)
    {
        for (int i = 0; i < j; ++i)
        {
            lambda[i] = p * lambda[i+1] + (1 - p) * lambda[i];
            double e = b * ((s * pow(u, 2 * i - j)) - k);
            lambda[i] = max(lambda[i],e);
        }
    }
    return lambda[0];
}

void Option::setOptionPrice(Stock baseline, double spread)
{
    double price = calcPrice(baseline);
    bidPrice   = price - price*spread;
    askPrice   = price + price*spread;
    position   = 0;
    longPrice  = 0;
    shortPrice = 0;
}

Stock getStockFromParts(vector<string> parts) 
{
    return Stock(parts[underlying::TICKER_IDX], 
                 stod(parts[underlying::PRICE_IDX]));
}

vector<string> parseTick(string tick)
{
    string s;
    vector<string> parts;
    stringstream stream(tick);

    while (getline(stream, s, ','))
        parts.push_back(s);

    return parts;
}

int MarketMaker::addTradedOptionFromParts(vector<string> tick)
{
    Option op = Option(
        tick[tradedop::TICKER_IDX],
        tick[tradedop::CALL_PUT_IDX][0],
        tick[tradedop::EXPIRY_IDX],
        stod(tick[tradedop::STRIKE_IDX])
    );

    this->allOptions[op.id] = op;

    return op.id;
}

int MarketMaker::addOptionFromParts(vector<string> tick)
{
    Option op = Option(
        tick[options::TICKER_IDX],
        tick[options::CALL_PUT_IDX][0],
        tick[options::EXPIRY_IDX],
        stod(tick[options::STRIKE_IDX])
    );

    this->allOptions[op.id] = op;

    return op.id;
}

MarketMaker::MarketMaker() { 
    pnl = 0; 
    underlying = fstream(consts::STOCK_PATH);
    past_options = fstream(consts::TRADED_OPTION_PATH);

    string line;
    int option_id;
    double option_price;
    getline(underlying, line);
    vector<string> parts = parseTick(line);
    Stock baseline_stock = getStockFromParts(parts);

    while (getline(past_options, line))
    {
        parts = parseTick(line);
        option_id = addTradedOptionFromParts(parts);
        this->allOptions[option_id].setOptionPrice(baseline_stock, this->spread);
    }

    past_options.close();
    // underlying.close();
}

bool MarketMaker::newTimeStamp(string cur_time)
{
    if (cur_time == time_stamp)
        return false;
    
    time_stamp = cur_time;
    return true;
}

void MarketMaker::showOptions()
{
    system("clear");
    
    int col = 0; int cols = 2;
    int row = 50;
    cout << fixed << setprecision(2);
    // HEADER 
    for (int i = 0; i < cols; i++)
    {
        cout << setw(9)  << left;
        cout << "STRIKE";
        cout << setw(3)  << left;
        cout << "T";
        cout << setw(10) << left;
        cout << "EXPIRY";
        cout << setw(9)  << left;
        cout << "BID";
        cout << setw(9)  << left;
        cout << "ASK";
        cout << setw(9)  << left;
        cout << "POS";
        cout << setw(11) << left;
        cout << "LONG";
        cout << setw(11) << left;
        cout << "SHORT";
    }
    cout << endl;

    // BODY
    for (auto &[id,op] : this->allOptions)
    {
        cout << op;
        if ((++col % cols) == 0) cout << endl;
        if (--row == 0) break;
    } 
}

int main() 
{
    MarketMaker *mm = new MarketMaker();
    mm->showOptions();
    message_queue mq (open_only, "ipc");

    string s;
    int option_id;
    size_t ret_size;
    unsigned int prio;
    vector<string> parts;

    while (true) {
        recieveMessage(s, mq, ret_size, prio);
        parts = parseTick(s);

        if (mm->newTimeStamp(parts[options::TIME_IDX]))
        {
            mm->showOptions();
        }

        option_id = mm->addOptionFromParts(parts);
    }

    mm->closeStreams();
    message_queue::remove("ipc");
    return 1;
}
