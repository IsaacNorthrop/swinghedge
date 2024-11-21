# SwingHedge

C++ Program that predicts batter pitcher matchups in MLB using Statcast data.

## Table of Contents
- [Project Overview](#project-overview)
- [Installation and Usage](#installation-and-usage)
- [Versions](#versions)
- [Contact](#contact)

## Project Overview

Baseball Savant provides a Daily Matchups page, whose data isn't accessible by a standard API.

![alt text](images/image.png)

Each matchup is contained in a tag which includes a matchup link. Each of those links contains the batter matchup data between that batter and the pitcher they are facing that day.

![alt text](images/image-1.png)

This program sends a request to Baseball Savant, finds the link to each matchup, sends a request to each matchup, gets the Weighted On Base Average (WOBA) of that batter against that pitcher, compiles them all, and then displays the top 10 values.

## Installation and Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/IsaacNorthrop/swinghedge.git

2. Make the program:
    ```bash
    make

3.  Run the program for your specified date that has MLB games between 2015-2024.
    ```bash
    ./swinghegde <YYYY-MM-DD>

## Versions

### Current Version

- **v1.0.0** - November 19th, 2024
    - Initial Release: Show top 10 WOBA for a given day

### Released
### Future Releases

- **v1.1.0** - Late 2024
    - Performance Improvements

## Contact

Isaac Northrop - isaac.northrop88@gmail.com