import subprocess
import time
import statsapi
from pybaseball import batting_stats_bref
import re
import sys

### UPDATE ERROR LINE NUMBERS

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

count = 0
hits = 0


def generate_wobas():
    start_time = time.time()
    try:
        subprocess.run("cd ../../bin && > ../test/bin/output.txt", shell=True)
    except Exception as e:
        print(f"Line 75: Unable to traverse directory. {e}. Exiting.")
        sys.exit()
    command = "cd ../../bin && ./swinghedge "
    output = " >> ../test/bin/output.txt"
    day = "2024-04-01"
    while(day != "2024-05-31"):
        print("Running " + day)
        full_command = command + day + output
        try:
            subprocess.run(full_command, shell=True)
        except Exception as e:
            print(f"Line 86: Unable to start SwingHedge. {e}")
        day = get_next_day(day)
    end_time = time.time()
    execution_time(start_time, end_time)

def execution_time(start_time, end_time):
    execution_time = end_time - start_time
    hours = execution_time // 3600
    minutes = (execution_time % 3600) // 60
    seconds = execution_time % 60
    print(f"Total program execution time: {int(hours)} hours {int(minutes)} minutes {seconds:.2f} seconds")
    

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

    
def generate_data():
    start_time = time.time()
    year = ''
    hitting_data = ''
    currentDate = ''
    try:
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
                    currentDate = line.strip()
                    print(f"Testing {currentDate}")
                elif ',' in line:
                    playerStat = line.split(': ')
                    reversedName = playerStat[0]
                    playerName = reverseName(reversedName)
                    playerNumbers = hitting_data[hitting_data['Name'] == playerName]                
                    teamsFrame = playerNumbers['Tm'].str.split(',', expand=True)
                    if(not teamsFrame.empty):
                        teams = teamsFrame.values.tolist()[0];
                    else:
                        continue
                    leaguesFrame = playerNumbers['Lev'].str.split(',', expand=True)
                    leagues = leaguesFrame.values.tolist()[0];
                    boxscores = getBoxscore(teams, leagues, currentDate)
                    if(statsapi.lookup_player(playerName)):
                        playerId = statsapi.lookup_player(playerName)[0]['id']
                    playerIdString = 'ID' + str(playerId)
                    if(boxscores):
                        processBoxscores(boxscores, playerIdString, teams)
        end_time = time.time()
        execution_time(start_time, end_time)
        print(f"Test success Rate: {hits}/{count} = {hits/count*100}%")
    except FileNotFoundError as e:
        print(f"Line : SwingHedge output file not found. {e} Exiting.")
        sys.exit()

def processBoxscores(boxscores, playerIdString, teams):
    for boxscore in boxscores:
        currBoxscore = {}
        for team in teams: # this doesn't pick up some boxscores for some reason
            if(teamCodes.get(team) == boxscore['away']['team']['id']):
                currBoxscore = boxscore['away']['players']
            elif(teamCodes.get(team) == boxscore['home']['team']['id']):
                currBoxscore = boxscore['home']['players']
            if(playerIdString in currBoxscore and 'hits' in currBoxscore[playerIdString]['stats']['batting']): # clean
                count+=1
                if(currBoxscore[playerIdString]['stats']['batting']['hits'] > 0):
                    hits+=1
            
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
            if teamName:
                schedule = statsapi.schedule(date=date, team=teamName, sportId=1)
                if(schedule):
                    gameId = schedule[0]['game_id']
                    boxscores.append(statsapi.boxscore_data(gameId))
            else:
                continue
        else:
            teamName = getDoubleTeamName(team, teams, leagues)
            if teamName:
                schedule = statsapi.schedule(date=date, team=teamName, sportId=1)
                if(schedule):
                    gameId = schedule[0]['game_id']
                    boxscores.append(statsapi.boxscore_data(gameId))
            else:
                continue
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
        


        
        

    
        





    
