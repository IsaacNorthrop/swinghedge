import subprocess
import time
import statsapi
from pybaseball import batting_stats_bref
import re

def generate_wobas():
    start_time = time.time()
    subprocess.run("cd ../../bin && > ../test/bin/output.txt", shell=True)
    command = "cd ../../bin && ./swinghedge "
    output = " >> ../test/bin/output.txt"
    day = "2024-04-01"
    while(day != "2024-04-03"):
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

def get_games(day):
    data = batting_stats_bref(2024)
    longoria = data[data['Name'] == 'Isiah Kiner-Falefa']
    print(longoria)
    
    
def generate_data():
    count = 0
    hits = 0
    with open('../bin/output.txt', 'r') as file:
        while True:
            line = file.readline()
            if not line:
                break
            pattern = r"^\d{4}-\d{2}-\d{2}$"
            if re.match(pattern, line): # date
                print("results for %s" % (line))
            elif ',' in line:
                playerStat = line.split(': ')
                playerName = playerStat[0]
                stat = playerStat[1]
            # get team from pybaseball



    
