import subprocess

def generate_wobas():
    subprocess.run("cd ../../bin && ./swinghedge 2024-08-22 > ../test/bin/output.txt", shell=True)
