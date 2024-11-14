#include <iostream>
#include <vector>
#include "request.h"
#include "daily_matchups.h"

using namespace std;

int main() {
    request daily = request("https://baseballsavant.mlb.com/probable-pitchers/?date=2024-08-25");
    daily.make_request();
    vector<string> links = get_links(daily.response);
    
    request matchup = request("https://baseballsavant.mlb.com" + links[0]);
    matchup.make_request();
    cout << matchup.response << endl;

    return 0;
}