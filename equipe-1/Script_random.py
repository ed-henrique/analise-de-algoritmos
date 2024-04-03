import random

# Gerar 1000 números aleatórios entre 1 e 1000
numeros_aleatorios = [random.randint(1, 1000) for _ in range(1000)]

# Salvar os números aleatórios em um arquivo
with open('A.txt', 'w') as file:
    for num in numeros_aleatorios:
        file.write(f'{num}\n')

# Ordenar os números em ordem crescente
numeros_crescente = sorted(numeros_aleatorios)

# Salvar os números ordenados em ordem crescente em um arquivo
with open('O.txt', 'w') as file:
    for num in numeros_crescente:
        file.write(f'{num}\n')

# Ordenar os números em ordem decrescente
numeros_decrescente = sorted(numeros_aleatorios, reverse=True)

# Salvar os números ordenados em ordem decrescente em um arquivo
with open('D.txt', 'w') as file:
    for num in numeros_decrescente:
        file.write(f'{num}\n')

print('Arquivos criados com sucesso!')
