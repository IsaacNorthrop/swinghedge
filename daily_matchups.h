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
 
    daily_matchups:
    Find the unique matchup links in the daily matchups html using myhtml.
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <myhtml/api.h>

mystatus_t serialization_callback_matchups(const char *data, size_t len, char* buffer);
std::vector<std::string> get_links(std::string);
