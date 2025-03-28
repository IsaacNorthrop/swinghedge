/*
 * Copyright (C) 2024 Isaac Northrop
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Isaac Northrop - isaac.northrop88@gmail.com
 */

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include "request.h"
#include "savant.h"

using namespace std;
auto start = chrono::steady_clock::now();
vector<playerData> wobas;
mutex mtx;

void data_thread(string uri)
{
    request matchup = request(uri);
    matchup.make_request();
    vector<playerData> data = get_data(matchup.response); // get batter data from matchup

    mtx.lock();
    wobas.insert(wobas.end(), data.begin(), data.end()); // add matchup wobas to daily wobas
    mtx.unlock();
}

int main(int argc, char *argv[])
{

    if (argc < 2)
        std::cerr << "Usage: " << argv[0] << " <YYYY-MM-DD>" << std::endl;
    else if (argc > 2)
        std::cerr << "Too many arguments." << std::endl;

    std::string input = argv[1];
    std::string link = date_string(input); // get specified day of stats

    request daily = request(link);
    daily.make_request();
    vector<string> links = get_links(daily.response); // get all matchups from that day

    vector<thread> threads;

    for (size_t i = 0; i < links.size(); i++)
    {
        string temp = "https://baseballsavant.mlb.com" + links[i]; // build request for each matchup
        threads.push_back(thread(data_thread, temp));
    }

    for (auto &t : threads)
        t.join();

    std::sort(wobas.begin(), wobas.end(), [](const playerData &a, const playerData &b)
              { return a.woba > b.woba; }); // sort player wobas by woba

    std::cout << argv[1] << std::endl;
    for (int i = 0; i <= 10; i++)
    {
        cout << wobas[i].player_name + ": ";
        cout << wobas[i].woba;
        cout << " over " + std::to_string(wobas[i].pa) + " PA" << endl;
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    printf("SwingHedge executed in %f s\n\n", chrono::duration<double, milli>(diff).count() / 1000);

    return 0;
}