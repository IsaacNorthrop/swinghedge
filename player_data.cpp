#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <myhtml/api.h>
#include <iostream>
#include <vector>
#include <regex>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<std::pair<std::string, float>> get_data(std::string response)
{
    std::vector<std::pair<std::string, float>> wobas;
    std::regex dataRegex(R"(var data\s*=\s*(\{.*?\});)");
    std::smatch match;
    std::string dataJson = "";
    if (std::regex_search(response, match, dataRegex)) 
        dataJson = match[1].str();
    
    json j = json::parse(dataJson);
    for(json players : j["team"]){
        std::string player_name = players["player_name"];
        float woba = players["woba"];
        wobas.push_back({player_name, woba});
    }

    return wobas;
}