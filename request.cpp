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

        curl_easy_setopt(curl, CURLOPT_URL, "https://baseballsavant.mlb.com/probable-pitchers/?date=2024-08-25");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, request::handle_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            request::response = readBuffer;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

