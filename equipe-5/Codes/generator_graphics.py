import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter, FixedLocator

tamanhos_entrada = [100, 1000, 5000, 100000, 1000000, 5000000]

tempos_A = []
tempos_D = []
tempos_O = []

def format_func(value, tick_number):
    return f"{int(value):,}"

plt.figure(figsize=(10, 6))
plt.plot(tamanhos_entrada, tempos_A, marker='o', linestyle='-', color='r', label='A.txt')
plt.plot(tamanhos_entrada, tempos_D, marker='o', linestyle='-', color='g', label='D.txt')
plt.plot(tamanhos_entrada, tempos_O, marker='o', linestyle='-', color='b', label='O.txt')
plt.title('Tempo de Execução do Algoritmo por Tamanho de Entrada para A, O e D')
plt.xlabel('Tamanho da Entrada')
plt.ylabel('Tempo de Execução (s)')
plt.xscale('log')
plt.yscale('log')
plt.gca().xaxis.set_major_formatter(FuncFormatter(format_func))
plt.gca().xaxis.set_major_locator(FixedLocator(tamanhos_entrada))
plt.gca().yaxis.set_major_formatter(FuncFormatter(format_func))
plt.legend()
plt.grid(True)
plt.show()
