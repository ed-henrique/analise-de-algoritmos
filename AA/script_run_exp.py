from os import walk
import os
import subprocess
import logging
import re


logging.basicConfig(level=logging.DEBUG,
                    filename='log.txt',
                    format='%(process)d - [%(asctime)s] : %(levelname)s -> %(message)s')

INPUTS_DIR = ".\\input"
SORTING_ALGORITHMS_DIR = ".\\algoritmos_ordenacao"
LOGS_DIR = ".\\logs"
TIMES_RUN = 13

#RETORNA O TIPO DE CASO: PIOR, MÉDIO OU MELHOR, BASEADO NO TIPO DE ALGORITMO
def getCaseType(caminho_arquivo):
    # Expressão regular para encontrar a letra após a barra
    padrao = r'\\([A-Za-z])_\d+\.txt'
    # Busca pelo padrão na string
    resultado = re.search(padrao, caminho_arquivo)
    # Se encontrar o padrão, extrai a letra
    if resultado:
        return resultado.group(1)
    else:
        return None

def getTipo(filename):
    return filename.split("_")[0]
    
#RETORNA OS ARQUIVOS DE INPUT NO INPUT_FILES
def list_input_files():
    input_files = []
    for (_, _, filenames) in walk(INPUTS_DIR):
        for filename in filenames:
            input_files.append(os.path.join(INPUTS_DIR, filename))
    return input_files


#EXECUTA UM ALGORITMO COM UM ARQUIVO DE INPUT
def run_algorithm(algorithm_file, input_file,timecall,typeCase):
    # start_time = time.time()
    process = subprocess.Popen(['python', algorithm_file, input_file,timecall,typeCase], stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    stdout, stderr = process.communicate()
    # end_time = time.time()
    # execution_time = end_time - start_time
    return stdout, stderr, #execution_time

def main():
    logging.debug('Starting experiment execution')
    #RECEBE ARQUIVOS DE INPUT EM input_files (LIST)
    input_files = list_input_files()
    print("INPUTFILES: "+str(input_files))
    logging.debug(f'Using inputs: {input_files}')
    if not os.path.exists(SORTING_ALGORITHMS_DIR):
        logging.error(f"Sorting algorithms directory not found: {SORTING_ALGORITHMS_DIR}")
        return 0
    
    #LISTA ALGORITMOS
    print("LISTDIR: "+str(os.listdir(SORTING_ALGORITHMS_DIR)))
    for algorithm_file in os.listdir(SORTING_ALGORITHMS_DIR):
        algorithm_name, extension = os.path.splitext(algorithm_file)
        if extension != ".py":    #Verifica se é .py
            continue
        #Caminho do algoritmo
        algorithm_path = os.path.join(SORTING_ALGORITHMS_DIR, algorithm_file)
        print("FILE"+str(algorithm_file))
        print("NAME"+str(algorithm_name))
        print("PATH"+str(algorithm_path))
        log_file = os.path.join(LOGS_DIR, f"{algorithm_name}.log") #Log que registra os tempos de execução
        debug_log = open(f'.\\testlogs\\{algorithm_name}.testlog', 'w')
        for input_file in input_files:
            for i in range(TIMES_RUN):
                input_name = os.path.split(input_file)[1]
                print("INPUT NAME: "+str(input_name))
                debug_log.write(f'Sorting: {algorithm_name} |Input: {input_name} | Time: {i+1}\n')
                caseType=getTipo(input_name)
                print("TIPO DE CASO:"+str(caseType))
                logging.debug(f'Running {algorithm_name} algorithm on {input_file} - Time {i}, | Type:{str(caseType)}')
                stdout, stderr = run_algorithm(algorithm_path, input_file,str(i),str(caseType)) #executiontime
                #if stderr:
                #    logging.error(f"Error running {algorithm_name} on {input_file} - Time {i}: {stderr}")
                #else:
                #    logging.info(f"{algorithm_name} - {input_file} - Time {i} - Execution Time: {execution_time:.6f} seconds")

if __name__ == "__main__":
    main()