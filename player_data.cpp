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
        std::cerr << "Invalid Reponse: player_data.cpp:15." << std::endl;
    
    std::string delimeter = "var data =";
    size_t start_pos = response.find(delimeter) + delimeter.length(); // find the start and end position of the script
    size_t end_pos = response.find(";", start_pos);
    std::string dataJson = response.substr(start_pos, end_pos - start_pos);

    if(!start_pos || !end_pos || dataJson.empty())
        std::cerr << "Script not found: player_data.cpp:23." << std::endl;

    json j = json::parse(dataJson);
    if(j.empty())
        std::cerr << "JSON Parsing failed: player_data.cpp:26." << std::endl;

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
        wobas.push_back({player_name, woba}); // add a pair including player_name and woba
    }

    return wobas;
}