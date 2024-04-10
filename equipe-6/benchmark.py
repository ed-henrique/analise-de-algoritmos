#!/usr/bin/python3

from os import walk
import os
import os.path
import shlex
import subprocess
import sys
import logging

formatter = logging.Formatter('%(process)d - [%(asctime)s] : %(levelname)s -> %(message)s')
csvFormatter = logging.Formatter('%(message)s')

file_logger = logging.getLogger('file_logger')
file_logger.setLevel(logging.DEBUG)

stdout_logger = logging.getLogger('stdout_logger')
stdout_logger.setLevel(logging.DEBUG)

stdout_handler = logging.StreamHandler(sys.stdout)
stdout_handler.setLevel(logging.DEBUG)
stdout_handler.setFormatter(formatter)

stdout_logger.addHandler(stdout_handler)

"""
Usage mode:
1) all inputs should be inside of inputs directory
2) all inputs are executed 13 times
3) all outputs are save in the file called execution_log.txt
"""

BINARY_PROGRAM = ["quick"]
INPUTS_FILE = "inputs"
TIMES_RUN = 13
PATH_FILES_INPUT_LIST = []

def list_files_input():    
    for (dirpath, _, filenames) in walk(INPUTS_FILE):
        for file in filenames:
            full_path = os.path.abspath(dirpath) + "/" + file
            PATH_FILES_INPUT_LIST.append(full_path)   


def run_code():
    file_handler = logging.FileHandler("results.csv")
    file_handler.setLevel(logging.DEBUG)
    file_handler.setFormatter(csvFormatter)
    file_logger.addHandler(file_handler)

    file_logger.debug(f"Algoritmo;Entrada;Tempo")

    for input in PATH_FILES_INPUT_LIST[14:]:

        if not os.path.exists(input):
            stdout_logger.error(f"Input file: {input} not found")            
        else:
            for binary in BINARY_PROGRAM:
                cmd = shlex.split("./" + binary + " " + input[:-4])

                times = []

                for count_time in range(TIMES_RUN):
                    stdout_logger.debug(f"Binary: {binary} - Input file: {input.split('/')[-1][:-4]} - Time {count_time+1}")            

                    process = subprocess.Popen(cmd,
                            stdout=subprocess.PIPE, 
                            stderr=subprocess.PIPE,
                            universal_newlines=True)
                    stdout, stderr = process.communicate()            

                    if not stderr:
                        stdout_logger.debug(f"Time elapsed: {stdout}-----------------------------------------------------------------")
                        times.append(float(stdout))
                    else:
                        print(stderr)

                time_average = sum(times) / len(times)
                file_logger.debug(f"{binary};{input.split('/')[-1][:-4]};{time_average}")

def main():
    list_files_input()
    PATH_FILES_INPUT_LIST.sort()
    run_code()

if __name__ == "__main__":
    main()
