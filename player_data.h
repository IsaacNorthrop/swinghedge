#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <myhtml/api.h>
#include <nlohmann/json.hpp>

std::vector<std::pair<std::string, float>> get_data(std::string);
