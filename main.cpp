#include <iostream>
#include "request.h"

using namespace std;

int main() {
    request req = request("https://baseballsavant.mlb.com/probable-pitchers/?date=2024-08-25");
    req.make_request();
    std::cout << req.response << std::endl;
    return 0;
}