import subprocess
import matplotlib.pyplot as plt
import csv
import time

def call_sort_scripts():
    # Chamando os scripts de ordenação
    subprocess.run(['python', 'merge_sort_script.py'])
    subprocess.run(['python', 'shell_sort_script.py'])
    subprocess.run(['python', 'quick_sort_script.py'])

def compile_results():
    sort_methods = ['merge', 'shell', 'quick']
    input_sizes = [1000, 10000, 100000, 1000000, 5000000]
    order_types = ['ascending', 'descending', 'random']
    results = []

    for method in sort_methods:
        for size in input_sizes:
            for order in order_types:
                file_name = f'{order}_{size}_{method}_sorted.txt'
                sequence = []
                with open(file_name, 'r') as file:
                    sequence = [int(line.strip()) for line in file]
                avg_time = calculate_average_time(sequence, method)
                results.append([method, size, order, avg_time])

    # Escrevendo os resultados no CSV com delimitador de ponto e vírgula
    with open('combined_results.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter=';')
        writer.writerow(['Sort Method', 'Input Size', 'Order Type', 'Average Time (s)'])
        writer.writerows(results)

def calculate_average_time(sequence, method):
    # Re-executa o algoritmo de ordenação para calcular o tempo médio
    start_time = time.time()
    if method == 'merge':
        merge_sort(sequence)
    elif method == 'shell':
        shell_sort(sequence)
    elif method == 'quick':
        quick_sort(sequence, 0, len(sequence) - 1)
    end_time = time.time()
    return end_time - start_time

def merge_sort(sequence):
    if len(sequence) > 1:
        mid = len(sequence) // 2
        left_half = sequence[:mid]
        right_half = sequence[mid:]
        merge_sort(left_half)
        merge_sort(right_half)
        i = j = k = 0
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                sequence[k] = left_half[i]
                i += 1
            else:
                sequence[k] = right_half[j]
                j += 1
            k += 1
        while i < len(left_half):
            sequence[k] = left_half[i]
            i += 1
            k += 1
        while j < len(right_half):
            sequence[k] = right_half[j]
            j += 1
            k += 1

def shell_sort(sequence):
    n = len(sequence)
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = sequence[i]
            j = i
            while j >= gap and sequence[j - gap] > temp:
                sequence[j] = sequence[j - gap]
                j -= gap
            sequence[j] = temp
        gap //= 2

def quick_sort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi)
        quick_sort(arr, pi + 1, high)

def partition(arr, low, high):
    pivot = arr[(low + high) // 2]
    i = low - 1
    j = high + 1
    while True:
        i += 1
        while arr[i] < pivot:
            i += 1
        j -= 1
        while arr[j] > pivot:
            j -= 1
        if i >= j:
            return j
        arr[i], arr[j] = arr[j], arr[i]

def plot_results():
    input_sizes = [1000, 10000, 100000, 1000000, 5000000]
    methods = ['merge', 'shell', 'quick']
    colors = ['b', 'g', 'r']
    plt.figure(figsize=(10, 5))
    
    for method, color in zip(methods, colors):
        times = []
        for size in input_sizes:
            with open('combined_results.csv', newline='') as csvfile:
                reader = csv.reader(csvfile, delimiter=';')
                next(reader)  # Skip header
                for row in reader:
                    if row[0] == method and int(row[1]) == size:
                        times.append(float(row[3]))
        plt.plot(input_sizes, times, label=f'{method.capitalize()} Sort', marker='o', color=color)
    
    plt.xlabel('Input Size')
    plt.ylabel('Average Time (s)')
    plt.title('Sorting Performance Comparison')
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.grid(True)
    plt.savefig('sorting_performance_comparison.png')
    plt.show()

if __name__ == "__main__":
    call_sort_scripts()
    compile_results()
    plot_results()

