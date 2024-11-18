#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <myhtml/api.h>

mystatus_t serialization_callback_data(const char *data, size_t len, char* buffer);
std::vector<std::string> get_data(std::string);
