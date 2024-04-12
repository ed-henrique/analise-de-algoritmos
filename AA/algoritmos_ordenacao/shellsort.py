# shellsort.py
import argparse
import time
import logging
import re

LOGFILE = '.\\logs\\shellsort.txt'

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

def shell_sort(arr):
    n = len(arr)
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        gap //= 2
    return arr

def usar_shell_sort(input_file):
    try:
        file = open(input_file, 'r')
        linhas = file.readlines()
        numeros = [int(linha.strip()) for linha in linhas if linha.strip()] 
        tam = getTam(file)
        res = open('.\\plot\\shellsort.txt','a')
        start = time.time()
        sorted_arr = shell_sort(numeros)
        end = time.time()
        exec_time = end - start
        logging.debug(f'Tam_entrada: {tam}| T_execução: {exec_time} | Chamado pela {timecalled} vez | Arquivo:{typeCase}')
        res.write(f'"shellsort",{tam},{exec_time},{typeCase}\n')
    except IOError:
        print(f'Erro ao ler o arquivo "{input_file}".')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Executa shellsort')
    parser.add_argument('input_file', help='Caminho do arquivo de entrada')
    parser.add_argument('timecalled', help='Caminho do arquivo de entrada')
    parser.add_argument('typeCase', help='Caminho do arquivo de entrada')
    args = parser.parse_args()
    input_file = args.input_file
    timecalled=args.timecalled
    typeCase= args.typeCase
    usar_shell_sort(input_file)