import matplotlib.pyplot as plt
import os

def calcular_medias_por_ordem(input_dir):
    # Listas para armazenar as linhas de cada tipo
    A_linhas = []
    O_linhas = []
    D_linhas = []

    # Ler os arquivos e armazenar as linhas em suas respectivas listas
    for arquivo in os.listdir(input_dir):
        if arquivo.endswith(".txt"):
            with open(os.path.join(input_dir, arquivo), 'r') as arquivo_txt:
                linhas = arquivo_txt.readlines()
                for linha in linhas:
                    nome, ordem, tempo, tipo = linha.strip().split(',')
                    if tipo == 'A':
                        A_linhas.append((nome, float(ordem), float(tempo)))
                    elif tipo == 'O':
                        O_linhas.append((nome, float(ordem), float(tempo)))
                    elif tipo == 'D':
                        D_linhas.append((nome, float(ordem), float(tempo)))

    # Dicionários para armazenar as médias de tempo por ordem para cada tipo
    A_medias = {}
    O_medias = {}
    D_medias = {}

    # Calcular médias de tempo para cada ordem em cada tipo
    for linhas, medias in [(A_linhas, A_medias), (O_linhas, O_medias), (D_linhas, D_medias)]:
        for nome, ordem, tempo in linhas:
            if ordem not in medias:
                medias[ordem] = []
            medias[ordem].append(tempo)

    for medias in [A_medias, O_medias, D_medias]:
        for ordem, tempos in medias.items():
            medias[ordem] = sum(tempos) / len(tempos)

    return A_medias, O_medias, D_medias

def plotar_arquivos(input_dir, A_medias, O_medias, D_medias):
    cores = {'A': 'yellow', 'D': 'red', 'O': 'green'}
    for arquivo in os.listdir(input_dir):
        if arquivo.endswith(".txt"):
            nome_algoritmo = arquivo.split(".")[0]
            tamanhos_entrada = {'A': [], 'D': [], 'O': []}
            tempos_execucao = {'A': [], 'D': [], 'O': []}
            tipos = []
            with open(os.path.join(input_dir, arquivo), 'r') as arquivo_txt:
                linhas = arquivo_txt.readlines()
                for linha in linhas:
                    nome, ordem, tempo, tipo = linha.strip().split(',')
                    tamanhos_entrada[tipo].append(float(ordem))
                    tempos_execucao[tipo].append(float(tempo))
                    tipos.append(tipo)

            # Plotar os dados
            plt.figure(figsize=(10, 6))
            for tipo in ['A', 'D', 'O']:
                if tamanhos_entrada[tipo]:
                    plt.plot(tamanhos_entrada[tipo], tempos_execucao[tipo], marker='o', linestyle='-', color=cores[tipo], label=f'Tipo {tipo}')
            
            # Plotar médias
            for ordem, tempo_medio in [(ordem, A_medias[ordem]) for ordem in tamanhos_entrada['A']] + [(ordem, O_medias[ordem]) for ordem in tamanhos_entrada['O']] + [(ordem, D_medias[ordem]) for ordem in tamanhos_entrada['D']]:
                plt.plot(ordem, tempo_medio, marker='x', linestyle='', color='black')

            plt.title(f'Tempo de execução em relação à ordem para {nome_algoritmo}')
            plt.xlabel('Ordem')
            plt.ylabel('Tempo de Execução')
            plt.legend()
            plt.grid(True)

            # Exportar o plot como uma imagem PNG
            nome_saida = f"graficos/{nome_algoritmo}.png"
            plt.savefig(nome_saida)
            plt.show()

# Exemplo de uso
input_dir = ".\plot"
A_medias, O_medias, D_medias = calcular_medias_por_ordem(input_dir)
plotar_arquivos(input_dir, A_medias, O_medias, D_medias)
