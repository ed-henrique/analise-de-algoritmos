import random

# Gerar os número no intervalo
numbers = list(range(1, 10001, 1000))

# Crescente
ascending_order = sorted(numbers)

# Decrescente
descending_order = sorted(numbers, reverse=True)

# Aleatorio
random_order = numbers.copy()
random.shuffle(random_order)

# Escrever os numeros no arquivo
with open('ascending_order.txt', 'w') as file:
    for number in ascending_order:
        file.write(f"{number}\n")

with open('descending_order.txt', 'w') as file:
    for number in descending_order:
        file.write(f"{number}\n")

with open('random_order.txt', 'w') as file:
    for number in random_order:
        file.write(f"{number}\n")

print("Files created successfully.")
