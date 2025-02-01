import subprocess
import time
import statsapi
from pybaseball import batting_stats_bref
import re
import pandas as pd

teamCodes = {
    "Arizona": 109,
    "Atlanta": 144,
    "Baltimore": 110,
    "Boston": 111,
    "Chicago White Sox": 145,
    "Chicago Cubs": 112,
    "Cincinnati": 113,
    "Cleveland": 114,
    "Colorado": 115,
    "Detroit": 116,
    "Houston": 117,
    "Kansas City": 118,
    "Los Angeles Angels": 108,
    "Los Angeles Dodgers": 119,
    "Miami": 120,
    "Milwaukee": 158,
    "Minnesota": 142,
    "New York Mets": 121,
    "New York Yankees": 147,
    "Oakland": 133,
    "Philadelphia": 143,
    "Pittsburgh": 134,
    "San Diego": 135,
    "San Francisco": 137,
    "Seattle": 136,
    "St. Louis": 138,
    "Tampa Bay": 139,
    "Texas": 140,
    "Toronto": 141,
}

teamLeague = {
    "Arizona": "NL",
    "Atlanta": "NL",
    "Baltimore": "AL",
    "Boston": "AL",
    "Chicago White Sox": "AL",
    "Chicago Cubs": "NL",
    "Cincinnati": "NL",
    "Cleveland": "AL",
    "Colorado": "NL",
    "Detroit": "AL",
    "Houston": "AL",
    "Kansas City": "AL",
    "Los Angeles Angels": "AL",
    "Los Angeles Dodgers": "NL",
    "Miami": "NL",
    "Milwaukee": "NL",
    "Minnesota": "AL",
    "New York Mets": "NL",
    "New York Yankees": "AL",
    "Oakland": "AL",
    "Philadelphia": "NL",
    "Pittsburgh": "NL",
    "San Diego": "NL",
    "San Francisco": "NL",
    "Seattle": "AL",
    "St. Louis": "NL",
    "Tampa Bay": "AL",
    "Texas": "AL",
    "Toronto": "AL"
}

teamAbbreviations = {
    "Arizona": "ARI",
    "Atlanta": "ATL",
    "Baltimore": "BAL",
    "Boston": "BOS",
    "Chicago White Sox": "CWS",
    "Chicago Cubs": "CHC",
    "Cincinnati": "CIN",
    "Cleveland": "CLE",
    "Colorado": "COL",
    "Detroit": "DET",
    "Houston": "HOU",
    "Kansas City": "KC",
    "Los Angeles Angels": "LAA",
    "Los Angeles Dodgers": "LAD",
    "Miami": "MIA",
    "Milwaukee": "MIL",
    "Minnesota": "MIN",
    "New York Mets": "NYM",
    "New York Yankees": "NYY",
    "Oakland": "OAK",
    "Philadelphia": "PHI",
    "Pittsburgh": "PIT",
    "San Diego": "SD",
    "San Francisco": "SF",
    "Seattle": "SEA",
    "St. Louis": "STL",
    "Tampa Bay": "TB",
    "Texas": "TEX",
    "Toronto": "TOR",
}

def generate_wobas():
    start_time = time.time()
    subprocess.run("cd ../../bin && > ../test/bin/output.txt", shell=True)
    command = "cd ../../bin && ./swinghedge "
    output = " >> ../test/bin/output.txt"
    day = "2024-04-01"
    while(day != "2024-08-31"):
        print("Testing " + day)
        full_command = command + day + output
        subprocess.run(full_command, shell=True)
        day = get_next_day(day)
    end_time = time.time()
    execution_time = end_time - start_time
    hours = execution_time // 3600
    minutes = (execution_time % 3600) // 60
    seconds = execution_time % 60
    print(f"Test execution time: {int(hours)} hours {int(minutes)} minutes {seconds:.2f} seconds")

    

def get_next_day(day):
    short_months = ("04", "06", "09")
    ymd = day.split('-')
    if(ymd[2] == "30" and ymd[1] in short_months):
        m_int = int(ymd[1]) + 1
        ymd[1] = f"{m_int:02d}"
        ymd[2] = "01"
    elif(ymd[2] == "31" and ymd[1] not in short_months):
        m_int = int(ymd[1]) + 1
        ymd[1] = f"{m_int:02d}"
        ymd[2] = "01"
    else:
        d_int = int(ymd[2]) + 1
        ymd[2] = f"{d_int:02d}"
    return ymd[0] + "-" + ymd[1] + "-" + ymd[2]

# def get_games(day):
#     data = batting_stats_bref(2024)
#     longoria = data[data['Name'] == 'Isiah Kiner-Falefa']
#     print(longoria)
    
    
def generate_data():
    count = 0
    hits = 0
    year = ''
    hitting_data = ''
    currentDate = ''
    with open('../bin/output.txt', 'r') as file:
        while True:
            line = file.readline()
            if not line:
                break
            pattern = r"^\d{4}-\d{2}-\d{2}$"
            if re.match(pattern, line): # date
                if year == '':
                    dateSplit = line.split('-')
                    year = dateSplit[0]
                    hitting_data = batting_stats_bref(int(year))
                #print("results for %s" % (line))
                currentDate = line.strip()
            elif ',' in line:
                playerStat = line.split(': ')
                reversedName = playerStat[0]
                playerName = reverseName(reversedName)
                playerNumbers = hitting_data[hitting_data['Name'] == playerName]                
                teamsFrame = playerNumbers['Tm'].str.split(',', expand=True)
                teams = teamsFrame.values.tolist()[0];
                leaguesFrame = playerNumbers['Lev'].str.split(',', expand=True)
                leagues = leaguesFrame.values.tolist()[0];
                boxscores = getBoxscore(teams, leagues, currentDate)
                playerId = statsapi.lookup_player(playerName)[0]['id']
                playerIdString = 'ID' + str(playerId)
                if(boxscores):
                    for boxscore in boxscores:
                        currBoxscore = {}
                        currStats = {}
                        for team in teams: # this doesn't pick up some boxscores for some reason
                            if(teamCodes.get(team) == boxscore['away']['team']['id']):
                                currBoxscore = boxscore['away']['players']
                            elif(teamCodes.get(team) == boxscore['home']['team']['id']):
                                currBoxscore = boxscore['home']['players']
                            if(playerIdString in currBoxscore and 'hits' in currBoxscore[playerIdString]['stats']['batting']): # clean
                                count+=1
                                if(currBoxscore[playerIdString]['stats']['batting']['hits'] > 0):
                                    hits+=1
    print(f"Success Rate: {hits}/{count} = {hits/count*100}%")


            
def reverseName(name):
    splitName = name.split(', ')
    firstName = splitName[1]
    lastName = splitName[0]
    return firstName + ' ' + lastName

def getBoxscore(teams, leagues, date):
    multiLeagueTeams = ['Chicago', 'New York', 'Los Angeles']
    boxscores = []
    for team in teams:
        if(team not in multiLeagueTeams):
            teamName = teamCodes.get(team)
            schedule = statsapi.schedule(date=date, team=teamName, sportId=1)
            if(len(schedule) == 0):
                continue
            gameId = schedule[0]['game_id']
            boxscores.append(statsapi.boxscore_data(gameId))
        else:
            teamName = getDoubleTeamName(team, teams, leagues)
            schedule = statsapi.schedule(date=date, team=teamName, sportId=1)
            if(len(schedule) == 0):
                continue
            gameId = schedule[0]['game_id']
            boxscores.append(statsapi.boxscore_data(gameId))
    return boxscores

def getDoubleTeamName(team, teams, leagues):
    multiLeagueTeams = ['Chicago', 'New York', 'Los Angeles']
    numLeagues = len(leagues)
    if(numLeagues == 1):
        if(team == 'Chicago' and 'Maj-NL' in leagues):
            return teamCodes.get('Chicago Cubs')
        if(team == 'Chicago' and 'Maj-AL' in leagues):
            return teamCodes.get('Chicago White Sox')
        if(team == 'New York' and 'Maj-NL' in leagues):
            return teamCodes.get('New York Mets')
        if(team == 'New York' and 'Maj-AL' in leagues):
            return teamCodes.get('New York Yankees')
        if(team == 'Los Angeles' and 'Maj-NL' in leagues):
            return teamCodes.get('Los Angeles Dodgers')
        if(team == 'Los Angeles' and 'Maj-AL' in leagues):
            return teamCodes.get('Los Angeles Angels')
    if(numLeagues > 2):
        otherLeagues = []
        for notMultiLeagueTeam in teams:
            if(notMultiLeagueTeam == team):
                continue
            elif(notMultiLeagueTeam in multiLeagueTeams):
                return 'invalid'
            else:
                otherLeagues.append(teamLeague.get(notMultiLeagueTeam))
        if('AL' in otherLeagues and 'NL' not in otherLeagues or
            'NL' in otherLeagues and 'AL' not in otherLeagues):
            if(team == 'Chicago' and 'Maj-NL' in leagues):
                return teamCodes.get('Chicago Cubs')
            if(team == 'Chicago' and 'Maj-AL' in leagues):
                return teamCodes.get('Chicago White Sox')
            if(team == 'New York' and 'Maj-NL' in leagues):
                return teamCodes.get('New York Mets')
            if(team == 'New York' and 'Maj-AL' in leagues):
                return teamCodes.get('New York Yankees')
            if(team == 'Los Angeles' and 'Maj-NL' in leagues):
                return teamCodes.get('Los Angeles Dodgers')
            if(team == 'Los Angeles' and 'Maj-AL' in leagues):
                return teamCodes.get('Los Angeles Angels')    
        else:
            return 'invalid'      
        


        
        

    
        





    
