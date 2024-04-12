import random
def gerar_aleatorios(n):
# Gerar um array em ordem crescente de 1 a n.
  numeros_crescente = list(range(1, n + 1))


# Gerar um array em ordem aleatória
  numeros_aleatorios = numeros_crescente.copy()
  random.shuffle(numeros_aleatorios)

# Salvar os números aleatórios em um arquivo
  with open(f'A_{n}.txt', 'w') as file:
    for num in numeros_aleatorios:
        file.write(f'{num}\n')


# Salvar os números ordenados em ordem crescente em um arquivo
  with open(f'O_{n}.txt', 'w') as file:
    for num in numeros_crescente:
        file.write(f'{num}\n')

# Ordenar os números em ordem decrescente
  numeros_decrescente = numeros_crescente[::-1]

# Salvar os números ordenados em ordem decrescente em um arquivo
  with open(f'D_{n}.txt', 'w') as file:
    for num in numeros_decrescente:
        file.write(f'{num}\n')

  print(f'Arquivos com {n} elementos criados com sucesso')

gerar_aleatorios(100)
gerar_aleatorios(1000)
gerar_aleatorios(10000)
gerar_aleatorios(100000)
gerar_aleatorios(1000000)
gerar_aleatorios(10000000)