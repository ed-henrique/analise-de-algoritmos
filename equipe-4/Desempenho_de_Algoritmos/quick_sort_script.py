import random
import time
import csv

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

def quick_sort(sequence, low, high):
    if low < high:
        pi = partition(sequence, low, high)
        quick_sort(sequence, low, pi)
        quick_sort(sequence, pi + 1, high)

def calculate_average_time(sequence):
    times = []
    for _ in range (13):
        start = time.time()
        quick_sort(sequence.copy(), 0, len(sequence) - 1)
        times.append(time.time() - start)
    return sum(times) / len(times)

def run_experiments():
    input_sizes = [1000, 10000, 100000, 1000000, 5000000]
    results = []

    for size in input_sizes:
        sequences = {
            'ascending': list(range(size)),
            'descending': list(range(size, 0, -1)),
            'random': random.sample(range(size), size)
        }

        for name, seq in sequences.items():
            avg_time = calculate_average_time(seq)
            results.append([name, size, avg_time])

            # Salvando a sequência ordenada em um arquivo TXT
            with open(f'{name}_{size}_quick_sorted.txt', 'w') as f:
                f.write('\n'.join(map(str, seq)))


if __name__ == "__main__":
    run_experiments()

