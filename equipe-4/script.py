import random

# Gerar sequência ascendente
ascendente = list(range(1, 1001))

# Gerar sequência descendente
descendente = list(range(1000, 0, -1))

# Gerar sequência aleatória
aleatoria = random.sample(range(1, 1001), 1000)

# Escrever as sequências nos arquivos
with open('ascendente.txt', 'w') as file:
    for number in ascendente:
        file.write(str(number) + '\n')

with open('descendente.txt', 'w') as file:
    for number in descendente:
        file.write(str(number) + '\n')

with open('aleatoria.txt', 'w') as file:
    for number in aleatoria:
        file.write(str(number) + '\n')

print("Arquivos gerados com sucesso!")
