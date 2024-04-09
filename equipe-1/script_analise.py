#!/usr/bin/python3
import csv
from os import walk
import os
import os.path
import shlex
import subprocess
import logging
import time

logging.basicConfig(level=logging.DEBUG, filename='run_exp_data.log', filemode='w', format='%(process)d - [%(asctime)s] : %(levelname)s -> %(message)s')

"""
Usage mode:
1) all inputs should be inside of inputs directory
2) all inputs are executed 13 times
3) all outputs are save in the file called execution_log.txt
"""


INPUTS_FILE = "inputs"
TIMES_RUN = 13
PATH_FILES_INPUT_LIST = []

def list_files_input():    
    for (dirpath, dirnames, filenames) in walk(INPUTS_FILE):
        for file in filenames:
            full_path = os.path.abspath(dirpath) + "/" + file
            PATH_FILES_INPUT_LIST.append(full_path)   

def get_input_size():
    with open(PATH_FILES_INPUT_LIST[0], 'r') as file:
        input_list = file.readlines()
        return len(input_list)

def run_code(BINARY_PROGRAM):
    M_time = []
    logging.debug(f'Running the program with each input {TIMES_RUN} times')
    for input_file in PATH_FILES_INPUT_LIST:
        if not os.path.exists(input_file):
            logging.error(f"Input file: {input_file} not found")            
        else:
            cmd = shlex.split("./" + BINARY_PROGRAM + " " + input_file)
            for count_time in range(TIMES_RUN):
                logging.debug(f"Running input: {input_file} - Time {count_time}")
                start_time = time.time() # Start time
                process = subprocess.Popen(cmd,
                        stdout=subprocess.PIPE, 
                        stderr=subprocess.PIPE,
                        universal_newlines=True)
                stdout, stderr = process.communicate()            
                end_time = time.time() # End time
                execution_time = end_time - start_time # Execution time
                M_time.append(execution_time)
                if not stderr:
                    logging.debug(f"Program output: - Time {count_time}")
                    logging.debug(f"Execution time: {execution_time} seconds")
                    logging.debug(f"---------------------------")
                    logging.debug(stdout)
                    logging.debug(f"---------------------------")
            media = sum(M_time)/len(M_time)
            logging.debug(f'Media total de tempo de execução: {media}')
            algorithm_name = BINARY_PROGRAM
            for input_file in PATH_FILES_INPUT_LIST:
                input_size = get_input_size()
                average_time = media if M_time else 0
                write_to_csv(algorithm_name, input_size, average_time)

def write_to_csv(algorithm_name, input_size, average_time):
    csv_filename = 'execution_data.csv'
    with open(csv_filename, mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([algorithm_name, input_size, average_time])
    logging.debug(f'Data written to CSV: Algorithm: {algorithm_name}, Input size: {input_size}, Average time: {average_time}')

def main():
    logging.debug('Experiment script executed')
    logging.debug('Listing input files to the program')
    list_files_input()
    algs = ["mergeSort", "quickSort", "shellSort"]
    for algorithm in algs:
        run_code(algorithm)
    

if __name__ == "__main__":
    main()


