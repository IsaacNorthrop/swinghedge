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
#include "request.h"
#include <curl/curl.h>

request::request() {
    address = "";
    response = "";
}

request::request(string addr){
    address = addr;
    response = "";
}

size_t request::handle_data(void* response, size_t size, size_t num_elements, void* userp){
    ((std::string*)userp)->append((char*)response, size*num_elements);
    return size *num_elements;
}

void request::make_request(){
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, request::address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, request::handle_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: request.cpp:52: " << curl_easy_strerror(res) << std::endl;
        } else {
            request::response = readBuffer;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

