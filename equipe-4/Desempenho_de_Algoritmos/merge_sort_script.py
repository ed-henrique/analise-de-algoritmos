import random
import time

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

def calculate_average_time(sequence):
    times = []
    for _ in range(13):
        start = time.time()
        merge_sort(sequence.copy())
        times.append(time.time() - start)
    return sum(times) / len(times)

def run_experiments():
    input_sizes = [1000, 10000, 100000, 1000000, 5000000]
    for size in input_sizes:
        sequences = {
            'ascending': list(range(size)),
            'descending': list(range(size, 0, -1)),
            'random': random.sample(range(size), size)
        }

        for name, seq in sequences.items():
            avg_time = calculate_average_time(seq)
            with open(f'{name}_{size}_merge_sorted.txt', 'w') as f:
                f.write('\n'.join(map(str, seq)))

if __name__ == "__main__":
    run_experiments()







