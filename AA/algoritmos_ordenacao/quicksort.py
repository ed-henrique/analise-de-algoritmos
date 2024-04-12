# quicksort.py
import argparse
import time
import logging
import re

LOGFILE = '.\\logs\\quicksort.txt'

logging.basicConfig(filename=LOGFILE,
                    encoding='utf-8',
                    level=logging.DEBUG,
                    format='%(process)d - [%(asctime)s] : %(levelname)s -> %(message)s')

# Função para extrair tamanho de inputs
def getTam(file):
    nome = file.name
    padrao = r"[A-Za-z]_(\d+)\.txt"
    resultado=re.search(padrao,nome)
    numero = int(resultado.group(1))
    return numero

def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr)//2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def usar_quick_sort(input_file):
    try:
        file= open(input_file, 'r')
        linhas = file.readlines()
        numeros = [int(linha.strip()) for linha in linhas]
        tam = getTam(file)
        res = open('.\\plot\\quicksort.txt','a')
        start = time.time() 
        sorted_arr = quick_sort(numeros)
        end = time.time()
        exec_time = end - start
        logging.debug(f'Tam_entrada: {tam}| T_execução: {exec_time} | Chamado pela {timecalled} vez | Arquivo:{typeCase}')
        res.write(f'"quicksort",{tam},{exec_time},{typeCase}\n')
    except IOError:
        print(f'Erro ao ler o arquivo "{input_file}".')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Executa quicksort')
    parser.add_argument('input_file', help='Caminho do arquivo de entrada')
    parser.add_argument('timecalled', help='Caminho do arquivo de entrada')
    parser.add_argument('typeCase', help='Caminho do arquivo de entrada')
    args = parser.parse_args()
    input_file = args.input_file
    timecalled= args.timecalled
    typeCase= args.typeCase
    usar_quick_sort(input_file)