import logging
import shlex
import subprocess
import time
import pandas as pd
import matplotlib.pyplot as plt
import logging
from tqdm import tqdm


class Analise():
    """
    Classe para realizar análises de algoritimos.

    Esta classe contém métodos para executar e fazer medições de desenpenho de algoritimo.

    :param algoritimos: Lista de algoritimos a serem analisados.
    :param diretorio: Diretório onde os arquivos de entrada estão localizados.
    """
    def __init__(self, algoritimos: list, diretorio: str):
        self.algoritimos = algoritimos
        self.diretorio = diretorio
        self.data_A = pd.DataFrame()
        self.data_O = pd.DataFrame()
        self.data_D = pd.DataFrame()
        logging.basicConfig(filename="analise.log" ,level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')
        
    
    def _get_input_size(self, input):
        """
        Método para obter o tamanho do arquivo de entrada.
        :param input: localização do arquivo de entrada.
        :return: quantidade de linhas do arquivo.
        """
        with open(input, 'r') as file:
            input_list = file.readlines()
            return len(input_list)
        
    def _run_binary(self, binary: str, input_file: str):
        """
        Método para executar um algoritimo através de um comando shell.
        :param binary: localizacao do arquivo binário ou executavel. 
        :param input_file: path do arquivo de entrada a ser passado como parametro para o algoritimo.
        :return: retorna o tempo de execução do algoritimo.
        """
        cmd = shlex.split("./" + binary + " " + input_file)
        start_time = time.time() # Start time
        process = subprocess.Popen(cmd,
                                   stdout=subprocess.PIPE,
                                   stderr=subprocess.PIPE,
                                   universal_newlines=True)
        stdout, stderr = process.communicate()
        end_time = time.time() # End time
        return end_time - start_time
    
    def run(self,input_category, num_tests: int = 13):
        """
        Método para executar os testes de desempenho é tirar as medias de tempo de execução.
        :param input_category: Lista de listas com os nomes dos arquivos de entrada. ex: [['a-1000.txt', 'a-5000.txt'], ['d-1000.txt', 'd-5000.txt']]
        :param num_tests: numero de vezes que o algoritimo será executado para tirar a media de tempo.
        :return: retorna os dataframes com os dados de tempo de execução. para cada categoria. se ouver tal categoria.
        """
        time = 0
        
        logging.debug(f'Running the program with each input {num_tests} times')
        
        #define os index das tabelas
        self.data_A = pd.DataFrame(index=self.algoritimos, columns=[])
        self.data_O = pd.DataFrame(index=self.algoritimos, columns=[])
        self.data_D = pd.DataFrame(index=self.algoritimos, columns=[])
        
        for binary in self.algoritimos:
            print("Analisando o algoritimo: {} ".format(binary) )
            for category in input_category:
                print(" Analisando a categoria: {}".format(category))
                for input_file in tqdm(category):
                    input_size = self._get_input_size(self.diretorio + input_file)
                    for test_number in range(num_tests):
                        time += self._run_binary(binary, self.diretorio + input_file)
                    media = time/num_tests
                    if 'a-' in input_file:
                        self.data_A.loc[binary, input_size] = media
                    if 'o-' in input_file:
                        self.data_O.loc[binary, input_size] = media
                    if 'd-' in input_file:   
                        self.data_D.loc[binary, input_size] = media
                    logging.debug(f"Execution {binary} - {input_file} - Time {media} seconds")
        logging.debug(f"finished the run method")
        return self.data_A, self.data_O, self.data_D

    def plot_data(self, system_info: str, cpu_info: str, ram_info: str, diretorio: str = "./", csv: bool = False):
        """
        Método para plotar os dados de tempo de execução.
        :param system_info: Sistema operacional da maquina ao qual fora executado os testes.
        :param cpu_info: processador da maquina ao qual fora executado os testes.
        :param ram_info: tamanho da memoria ram da maquina ao qual fora executado os testes.
        :param diretorio: local onde os arquivos csv estão localizados. por padrão é o diretorio atual.
        :param csv: varialvel para indicar se quer importar os dados de um arquivo csv. por padrão é False. usando o diretorio passado como local de importação.
        :return: 
        """
        logging.debug(f"Plotting the data")
        if csv:
            #importa os csv
            data_A = pd.read_csv(diretorio + 'data_A.csv', index_col=0)
            data_D = pd.read_csv(diretorio + 'data_O.csv', index_col=0)
            data_O = pd.read_csv(diretorio + 'data_D.csv', index_col=0)
        else:
            data_A = self.data_A
            data_D = self.data_D
            data_O = self.data_O
        
        # Configurações do gráfico
        plt.figure(figsize=(10, 6))  # Tamanho da figura
    
        # Plot do primeiro gráfico
        plt.subplot(3, 1, 1)  # Posição do primeiro gráfico
        for line in data_A.index:
            print(line)
            plt.plot(data_A.columns, data_A.loc[line], marker='o', label=line)  # Plot dos valores do primeiro DataFrame
        plt.title('Gráfico A (Tamanho x Tempo)')  # Título do gráfico
        plt.xlabel('Tamanho da entrada')  # Rótulo do eixo x
        plt.ylabel('Tempo (s)')  # Rótulo do eixo y
        plt.legend()  # Exibir legenda
    
        # Plot do segundo gráfico
        plt.subplot(3, 1, 2)
        for line in data_O.index:
            plt.plot(data_O.columns, data_O.loc[line], marker='o', label=line)
        plt.title('Gráfico O (Tamanho x Tempo)')
        plt.xlabel('Tamanho da entrada')
        plt.ylabel('Tempo (s)')
        plt.legend()
        
        # Plot do terceiro gráfico
        plt.subplot(3, 1, 3)
        for line in data_D.index:
            plt.plot(data_D.columns, data_D.loc[line], marker='o', label=line)
        plt.title('Gráfico D (Tamanho x Tempo)')
        plt.xlabel('Tamanho da entrada')
        plt.ylabel('Tempo (s)')
        plt.legend()
        
        # Informações do sistema
        plt.suptitle(f'Análise de desempenho dos algoritmos de ordenação\nSistema: {system_info} CPU: {cpu_info} RAM: {ram_info}')
       

    # Ajustes de layout
        plt.tight_layout()
    
        # Exibir os gráficos
        plt.show()
                        
    
    def save_data(self, diretorio: str = "./"):
        """
        Método para salvar os dados de tempo de execução em arquivos csv.
        :param diretorio: local onde os arquivos csv serão salvos. por padrão é o diretorio atual.
        :return: 
        """
        logging.debug(f"Saving the data to csv files in {diretorio}")
        self.data_A.to_csv(diretorio + 'data_A.csv')
        self.data_O.to_csv(diretorio + 'data_O.csv')
        self.data_D.to_csv(diretorio + 'data_D.csv')
                        
                
# Categorias de arquivos de entrada
categories = [['a-1000.txt', 'a-5000.txt', 'a-10000.txt', 'a-50000.txt', 'a-100000.txt', 'a-500000.txt', 'a-1000000.txt', 'a-5000000.txt'],
              ['d-1000.txt', 'd-5000.txt', 'd-10000.txt', 'd-50000.txt', 'd-100000.txt', 'd-500000.txt', 'd-1000000.txt', 'd-5000000.txt'],
              ['o-1000.txt', 'o-5000.txt', 'o-10000.txt', 'o-50000.txt', 'o-100000.txt', 'o-500000.txt', 'o-1000000.txt', 'o-5000000.txt']
              ]
# Categorias de arquivos de entrada reduzidas
categories2 = [['a-1000.txt', 'a-5000.txt', 'a-10000.txt'],
              ['d-1000.txt', 'd-5000.txt', 'd-10000.txt'],
              ['o-1000.txt', 'o-5000.txt', 'o-10000.txt']
              ]


analise = Analise(['mergeSort', 'shellSort', 'quickSort'], 'inputs/') #cria o objeto analise com os algoritimos e o diretorio das entradas
analise.run(categories)  #roda a analise passando as categorias de cada input
analise.save_data() #salva os dados em csv
analise.plot_data("MacOs", "M1 arm", 8) #plota os dados passando os parametros do sistema
