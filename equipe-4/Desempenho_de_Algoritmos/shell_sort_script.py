import random
import time
import csv

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

def calculate_average_time(sequence):
    times = []
    for _ in range(13):
        start = time.time()
        shell_sort(sequence.copy())
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
            with open(f'{name}_{size}_shell_sorted.txt', 'w') as f:
                f.write('\n'.join(map(str, seq)))
                
if __name__ == "__main__":
    run_experiments()

