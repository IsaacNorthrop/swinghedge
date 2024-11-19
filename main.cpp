#include <iostream>
#include <vector>
#include "request.h"
#include "daily_matchups.h"
#include "player_data.h"

using namespace std;

int main()
{
    vector<pair<string, float>> wobas;
    request daily = request("https://baseballsavant.mlb.com/probable-pitchers/?date=2024-08-25");
    daily.make_request();
    vector<string> links = get_links(daily.response);

    for (size_t i = 0; i < links.size(); i++)
    {
        string temp = "https://baseballsavant.mlb.com" + links[i];
        request matchup = request(temp);
        matchup.make_request();

        vector<pair<string, float>> data = get_data(matchup.response);
        wobas.insert(wobas.end(), data.begin(), data.end());
    }

    std::sort(wobas.begin(), wobas.end(), [](const std::pair<string, float> &a, const std::pair<string, float> &b)
              {
                  return a.second > b.second;
              });

    for(int i = 0; i<=10; i++){
        cout << wobas[i].first + ": ";
        cout << wobas[i].second << endl;
    }

    return 0;
}