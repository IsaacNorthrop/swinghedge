#include <iostream>
#include <vector>
#include <thread>
#include "request.h"
#include "daily_matchups.h"

using namespace std;

void thread_func(string link){
    request matchup = request("https://baseballsavant.mlb.com" + link);
    matchup.make_request();
    cout << matchup.response << endl << endl << endl;
}

int main() {
    request daily = request("https://baseballsavant.mlb.com/probable-pitchers/?date=2024-08-25");
    daily.make_request();
    vector<string> links = get_links(daily.response);
    vector<thread> threads;
    
    string temp = "https://baseballsavant.mlb.com" + links[0];
    cout << temp << endl;
    request matchup = request(temp);
    matchup.make_request();
    cout << matchup.response << endl;

    // for(int i = 0; i<links.size(); i++){
    //     threads.push_back(thread(thread_func, links[i]));
    // }

    // for(int i = 0; i<threads.size(); i++){
    //     threads[i].join();
    // }

    return 0;
}