#include <iostream>
#include "request.h"
#include <curl/curl.h>

request::request() {
    address = "";
}

request::request(string addr){
    address = addr;
}

size_t request::handle_data(void* response, size_t size, size_t num_elements, void* userp){
    return 0;
}

int request::make_request(){
    return 0;
}

