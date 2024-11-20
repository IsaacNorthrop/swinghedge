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

#include "savant.h"

std::string date_string(std::string input)
{
    std::tm date = {};

    std::stringstream ss(input);
    ss >> std::get_time(&date, "%Y-%m-%d");

    if (ss.fail())
        std::cerr << "Failed to parse date!" << std::endl;
    else
    {
        if (date.tm_year + 1900 > 2025 || date.tm_year + 1900 < 2015)
            std::cerr << "Statcast data is only available from 2015 and later." << std::endl;
        if (date.tm_mon < 2 || date.tm_mon > 10)
            std::cerr << "The MLB season runs from March to November." << std::endl;
    }

    return "https://baseballsavant.mlb.com/probable-pitchers/?date=" + input;

}