from os import walk
import os
import os.path
import shlex
import subprocess
import sys
import logging

formatter = logging.Formatter('%(process)d - [%(asctime)s] : %(levelname)s -> %(message)s')

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

BINARY_PROGRAM = ["merge","quick","shell"]
INPUTS_FILE = "inputs"
TIMES_RUN = 13
PATH_FILES_INPUT_LIST = []

def list_files_input():    
    for (dirpath, dirnames, filenames) in walk(INPUTS_FILE):
        for file in filenames:
            full_path = os.path.abspath(dirpath) + "/" + file
            PATH_FILES_INPUT_LIST.append(full_path)   


def run_code():
    for input in PATH_FILES_INPUT_LIST:
        file_handler = logging.FileHandler("logs/" + input[:-4] + '-ok.csv')
        file_handler.setLevel(logging.DEBUG)
        file_handler.setFormatter(formatter)

        file_logger.addHandler(file_handler)

        file_logger.debug(input + ";")

        if not os.path.exists(input):
            stdout_logger.error(f"Input file: {input} not found")            
        else:
            for binary in BINARY_PROGRAM:
                cmd = shlex.split("./" + BINARY_PROGRAM + " " + input)
            for count_time in range(TIMES_RUN):
                stdout_logger.debug(f"Input file: {input} - Time {count_time}")            
                file_logger.debug(f"Running input: {input} - Time {count_time}")

                process = subprocess.Popen(cmd,
                        stdout=subprocess.PIPE, 
                        stderr=subprocess.PIPE,
                        universal_newlines=True)
                stdout, stderr = process.communicate()            
                if not stderr:
                    file_logger.debug(f"Program output: - Time {count_time}")
                    file_logger.debug(f"---------------------------")
                    file_logger.debug(stdout)
                    file_logger.debug(f"---------------------------")

        file_logger.removeHandler(file_handler)


def main():
    logging.debug('Experiment script executed')
    logging.debug('Listing input files to the program')
    list_files_input()
    run_code()

if __name__ == "__main__":
    main()
