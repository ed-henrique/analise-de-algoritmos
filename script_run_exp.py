#!/usr/bin/python3

from os import walk
import os
import os.path
import shlex
import subprocess
import logging

logging.basicConfig(level=logging.DEBUG, filename='run_exp_data.log', filemode='w', format='%(process)d - [%(asctime)s] : %(levelname)s -> %(message)s')

"""
Usage mode:
1) all inputs should be inside of inputs directory
2) all inputs are executed 13 times
3) all outputs are save in the file called execution_log.txt
"""

BINARY_PROGRAM = "otimo"
INPUTS_FILE = "inputs"
TIMES_RUN = 13
PATH_FILES_INPUT_LIST = []

def list_files_input():    
    for (dirpath, dirnames, filenames) in walk(INPUTS_FILE):
        for file in filenames:
            full_path = os.path.abspath(dirpath) + "/" + file
            PATH_FILES_INPUT_LIST.append(full_path)   


def run_code():
    logging.debug(f'Running the program with each input {TIMES_RUN} times')
    for input in PATH_FILES_INPUT_LIST:
        if not os.path.exists(input):
            logging.error(f"Input file: {input} not found")            
        else:
            cmd = shlex.split("./" + BINARY_PROGRAM + " " + input)
            for count_time in range(TIMES_RUN):
                logging.debug(f"Running input: {input} - Time {count_time}")
                process = subprocess.Popen(cmd,
                        stdout=subprocess.PIPE, 
                        stderr=subprocess.PIPE,
                        universal_newlines=True)
                stdout, stderr = process.communicate()            
                if not stderr:
                    logging.debug(f"Program output: - Time {count_time}")
                    logging.debug(f"---------------------------")
                    logging.debug(stdout)
                    logging.debug(f"---------------------------")


def main():
    logging.debug('Experiment script executed')
    logging.debug('Listing input files to the program')
    list_files_input()
    run_code()

if __name__ == "__main__":
    main()
