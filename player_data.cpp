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

std::string get_data(std::string response)
{
    std::regex dataRegex(R"(var data\s*=\s*(\{.*?\});)");
    std::smatch match;
    std::string dataJson = "fuck";
    if (std::regex_search(response, match, dataRegex)) 
        dataJson = match[1].str();
    
    //std::cout << dataJson << std::endl;

    json j = json::parse(dataJson);
    for(json players : j["team"]){
        std::cout << players["player_name"];
        std::cout << " : ";
        std::cout << players["woba"] << std::endl;
    }

    return dataJson;
}