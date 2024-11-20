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

 /*
 
    request class:
    Create a request instance with a URI. Use curl to send GET request.
 
 */

using namespace std;

class request {
    std::string address;

    public:
        std::string response;
        request();
        request(string addr);
        static size_t handle_data(void* response, size_t size, size_t num_elements, void* userp);
        void make_request();
};