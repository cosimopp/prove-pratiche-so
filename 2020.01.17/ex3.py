# Scrivere un programma python o uno script bash che consenta di lanciare parallelamente comandi
# para.py sleep 20 // ls -l // ps // sleep 3
# para.sh sleep 20 // ls -l // ps // sleep 3
# deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti
import subprocess
import threading

def run(cmd):
    subproc = subprocess.run(cmd, shell=True, capture_output=True)
    print(subproc.stdout)

