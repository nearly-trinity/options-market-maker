#include <boost/interprocess/ipc/message_queue.hpp>
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

MarketMaker::MarketMaker() { pnl = 0; }

bool MarketMaker::newTimeStamp(string cur_time)
{
    if (cur_time == time_stamp)
        return false;
    
    time_stamp = cur_time;
    return true;
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

int main() 
{
    MarketMaker mm = MarketMaker();
    message_queue mq (open_only, "ipc");

    string s;
    size_t ret_size;
    unsigned int prio;
    vector<string> tick;

    while (true) {
        recieveMessage(s, mq, ret_size, prio);
        tick = parseTick(s);

        if (mm.newTimeStamp(tick[options::TIME_IDX]))
        {
            cout << "new time: " << s << endl;
            // output some readable format here
        }
    }

    message_queue::remove("ipc");
    return 1;
}
