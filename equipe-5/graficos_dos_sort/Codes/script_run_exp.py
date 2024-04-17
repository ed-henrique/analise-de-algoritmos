#!/usr/bin/python3

from os import walk
import os
import os.path
import shlex
import subprocess
import logging
import csv
from time import time

# Definindo o nível de log para INFO para evitar logs de depuração
logging.basicConfig(level=logging.INFO, filename='run_exp_data.log', filemode='w', format='%(process)d - [%(asctime)s] : %(levelname)s -> %(message)s')

BINARY_PROGRAM = "quick.exe"
INPUTS_FILE = "inputs"
TIMES_RUN = 13
PATH_FILES_INPUT_LIST = []
EXECUTION_TIMES = []

def list_files_input():    
    for (dirpath, dirnames, filenames) in walk(INPUTS_FILE):
        for file in filenames:
            full_path = os.path.abspath(dirpath) + "/" + file
            PATH_FILES_INPUT_LIST.append(full_path)   

def run_code():
    logging.info(f'Running the program with each input {TIMES_RUN} times')
    for input_path in PATH_FILES_INPUT_LIST:
        if not os.path.exists(input_path):
            logging.error(f"Input file: {input_path} not found")
            continue

        cmd = shlex.split("./" + BINARY_PROGRAM + " " + input_path)
        times = []
        for count_time in range(TIMES_RUN):
            start_time = time()
            process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
            stdout, stderr = process.communicate()
            end_time = time()

            elapsed_time = end_time - start_time
            times.append(elapsed_time)

            if stderr:
                logging.error(stderr)
            else:
                logging.debug(f"Program output: - Time {count_time}")
                logging.debug(f"---------------------------")
                logging.debug(stdout)
                logging.debug(f"---------------------------")

        average_time = sum(times) / len(times)
        EXECUTION_TIMES.append((os.path.basename(input_path), average_time))

def write_to_csv():
    with open('5000000_execution_times.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Input File', 'Average Execution Time (s)'])
        for data in EXECUTION_TIMES:
            writer.writerow(data)

def main():
    logging.info('Experiment script executed')
    logging.info('Listing input files to the program')
    list_files_input()
    run_code()
    write_to_csv()

if __name__ == "__main__":
    main()
