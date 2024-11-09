#include <iostream>
#include <vector>
#include "request.h"
#include "html_parse.h"

using namespace std;

int main() {
    request req = request("https://baseballsavant.mlb.com/probable-pitchers/?date=2024-08-25");
    req.make_request();
    vector<string> links = get_links(req.response);
    return 0;
}