#include "utils/marketmaker.h"
#include "utils/utils.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>

using namespace boost::interprocess;
using namespace std;

int main() 
{
    // writer

    message_queue::remove("ipc");
    message_queue mq(
        create_only,
        "ipc",
        consts::MAX_NUM_MSG,
        consts::MAX_MSG_SIZE
    );

    fstream options(consts::OPTION_PATH, ios::in);

    string s;
    while(getline(options,s)) {
        mq.send(s.data(), s.size(), 0);
        this_thread::sleep_for(chrono::milliseconds(consts::DELAY));
    }
    
    return 0;

}