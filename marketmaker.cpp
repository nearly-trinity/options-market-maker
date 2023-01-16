#include "utils/marketmaker.h"
#include "utils/utils.h"
#include <sstream>
#include <iostream>
#include <string>
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

void MarketMaker::priceOption(int option_id)
{
    this->allOptions[option_id].bidPrice   = getRand();
    this->allOptions[option_id].askPrice   = getRand();
    this->allOptions[option_id].position   = getRand();
    this->allOptions[option_id].longPrice  = getRand();
    this->allOptions[option_id].shortPrice = getRand();
}

void MarketMaker::showOptions(string ticker)
{
    system("clear");
    
    int col = 0; int cols = 2;
    int row = 50;
    cout << fixed << setprecision(2);
    // HEADER 
    for (int i = 0; i < cols; i++)
    {
        cout << setw(9) << left;
        cout << "STRIKE";
        cout << setw(3) << left;
        cout << "T";
        cout << setw(10) << left;
        cout << "EXPIRY";
        cout << setw(9) << left;
        cout << "BID";
        cout << setw(9) << left;
        cout << "ASK";
        cout << setw(9) << left;
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
        if (++col == cols) {
            col = 0;
            cout << endl;
        }
        if(--row == 0) break;
    } 
}

MarketMaker::MarketMaker() { 
    pnl = 0; 
    underlying = fstream(consts::STOCK_PATH);
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

int MarketMaker::addOptionFromTick(vector<string> tick) 
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

bool MarketMaker::newTimeStamp(string cur_time)
{
    if (cur_time == time_stamp)
        return false;
    
    time_stamp = cur_time;
    return true;
}

int main() 
{
    MarketMaker *mm = new MarketMaker();
    message_queue mq (open_only, "ipc");

    string s;
    int option_id;
    size_t ret_size;
    unsigned int prio;
    vector<string> tick;

    while (true) {
        recieveMessage(s, mq, ret_size, prio);
        tick = parseTick(s);

        if (mm->newTimeStamp(tick[options::TIME_IDX]))
        {
            mm->showOptions(tick[options::TICKER_IDX]);
        }

        option_id = mm->addOptionFromTick(tick);
        mm->priceOption(option_id);
    }

    message_queue::remove("ipc");
    return 1;
}
