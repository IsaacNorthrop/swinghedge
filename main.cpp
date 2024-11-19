#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "request.h"
#include "daily_matchups.h"
#include "player_data.h"

using namespace std;

mutex mtx;
vector<pair<string, float>> wobas;

void thread_func(string link){
    request matchup = request("https://baseballsavant.mlb.com" + link);
    matchup.make_request();
    vector<pair<string, float>> matchup_wobas = get_data(matchup.response);
    unique_lock<mutex> lock(mtx);
        wobas.insert(wobas.end(), matchup_wobas.begin(), matchup_wobas.end());
    lock.unlock();
    cout << "fuck" << endl;
}

int main() {
    request daily = request("https://baseballsavant.mlb.com/probable-pitchers/?date=2024-08-25");
    daily.make_request();
    vector<string> links = get_links(daily.response);
    vector<thread> threads;
    
    
    for(size_t i = 0; i<links.size(); i++){
        string temp = "https://baseballsavant.mlb.com" + links[i];
        request matchup = request(temp);
        matchup.make_request();
        
        vector<pair<string, float>> data = get_data(matchup.response);
        for(pair<string, float> player : data){
            cout << player.first + ": ";
            cout << player.second << endl;
            wobas.push_back(player);
        }
    }

    return 0;
}