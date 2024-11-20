#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <myhtml/api.h>
#include <nlohmann/json.hpp>


/**
 * @brief find the javascript variable in HTML response and sort it into usable json.
 * 
 * @param response - HTML response for a given pitcher-batter matchup
 * @return * std::vector<std::pair<std::string, float>> - {player_name, woba}
 */

std::vector<std::pair<std::string, float>> get_data(std::string response);

/**
 * @brief turn date argument into usable daily matchup link.
 * 
 * @param input - user provided data argument
 * @return std::string - baseball savant link to intended daily matchip
 */

std::string date_string(std::string input);


/**
 * @brief serialize tokens returned from HTML parsing.
 * 
 * @param data - char token from HTML parsing
 * @param len - length of data
 * @param buffer 
 * @return mystatus_t - status of that tokenization step
 */

mystatus_t serialization_callback_matchups(const char *data, size_t len, char* buffer);

/*

    get_links: get each pitcher better matchup from HTML response from baseball savant.

*/

/**
 * @brief get each pitcher better matchup from HTML response from baseball savant.
 * 
 * @param response - HTML response from daily matchup on baseball savant
 * @return std::vector<std::string> - all links to pitcher-batter matchups
 */

std::vector<std::string> get_links(std::string response);