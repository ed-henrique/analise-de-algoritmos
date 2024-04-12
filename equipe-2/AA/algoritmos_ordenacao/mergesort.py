# mergesort.py
import argparse
import time
import logging
import re

LOGFILE = '.\\logs\\mergesort.txt'

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

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def usar_merge_sort(input_file):
    try:
        file = open(input_file, 'r')
        linhas = file.readlines()
        numeros = [int(linha.strip()) for linha in linhas]
        #logging.info(f'Array bagunçado:OK')
        tam = getTam(file)
        res = open('.\\plot\\mergesort.txt','a')
        start = time.time()
        sorted_arr = merge_sort(numeros)
        #logging.info(f'Array ordenado:OK')
        end = time.time()
        exec_time = end - start
        logging.debug(f'Tam_entrada: {tam}| T_execução: {exec_time} | Chamado pela {timecalled} vez | Arquivo:{typeCase}')
        res.write(f'"mergesort",{tam},{exec_time},{typeCase}\n')
    except IOError:
        print(f'Erro ao ler o arquivo "{input_file}".')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Executa mergesort')
    parser.add_argument('input_file', help='Caminho do arquivo de entrada')
    parser.add_argument('timecalled', help='Caminho do arquivo de entrada')
    parser.add_argument('typeCase', help='Caminho do arquivo de entrada')
    args = parser.parse_args()
    input_file = args.input_file
    #logging.debug(f'INPUT: {input_file}')
    timecalled=args.timecalled
    typeCase= args.typeCase
    usar_merge_sort(input_file)