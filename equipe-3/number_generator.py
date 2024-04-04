import random

def embaralhar(start, end, num):
  embaralhado = random.sample(range(start, end + 1), num)
  return embaralhado

def ordenar_crescente(nome_arquivo):
  with open(nome_arquivo, 'r') as arquivo:
    dados = [int(linha) for linha in arquivo]
    dados.sort()
  
  with open(f'o-{num}.txt', 'w') as arquivo_saida:
    for item in dados:
      arquivo_saida.write(str(item) + '\n')

def ordenar_decrescente(nome_arquivo):
  with open(nome_arquivo, 'r') as arquivo:
    dados = [int(linha) for linha in arquivo]
    dados.sort(reverse=True)
  
  with open(f'd-{num}.txt', 'w') as arquivo_saida:
    for item in dados:
      arquivo_saida.write(str(item) + '\n')

inicio = int(input("Digite o número inicial do intervalo: "))
fim = int(input("Digite o número final do intervalo: "))
num = int(input("Digite o número de elementos a serem embaralhados: "))

embaralhado = [random.randint(inicio, fim) for _ in range(num)]

with open(f'a-{num}.txt', 'w') as arquivo_saida:
  for item in embaralhado:
    arquivo_saida.write(str(item) + '\n')

ordenar_crescente(f'a-{num}.txt')
ordenar_decrescente(f'a-{num}.txt')
