#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<std::pair<std::string, float>> get_data(std::string response)
{
    std::vector<std::pair<std::string, float>> wobas;
    if (response.empty())
        return wobas;
    
    std::string delimeter = "var data =";
    size_t start_pos = response.find(delimeter) + delimeter.length();
    size_t end_pos = response.find(";", start_pos);
    std::string dataJson = response.substr(start_pos, end_pos - start_pos);

    json j = json::parse(dataJson);
    for (json players : j["team"])
    {
        std::string player_name;
        float woba = 0;
        if (players.contains("player_name"))
            player_name = players["player_name"];
        else
            player_name = "";
        if (players.contains("woba") && players["woba"].is_number())
            woba = players["woba"];
        wobas.push_back({player_name, woba});
    }

    return wobas;
}