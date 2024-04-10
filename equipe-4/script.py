import random

def gerar_sequencias(limite_inferior, limite_superior, tamanho):
    # Gerar sequência aleatória
    aleatoria = [random.randint(limite_inferior, limite_superior) for _ in range(tamanho)]

    # Gerar sequência ascendente
    ascendente = sorted(aleatoria)

    # Gerar sequência descendente
    descendente = sorted(aleatoria, reverse=True)

    # Escrever as sequências nos arquivos
    with open(f"o-{tamanho}.txt", 'w') as file:
        for number in ascendente:
            file.write(str(number) + '\n')

    with open(f"d-{tamanho}.txt", 'w') as file:
        for number in descendente:
            file.write(str(number) + '\n')

    with open(f"a-{tamanho}.txt", 'w') as file:
        for number in aleatoria:
            file.write(str(number) + '\n')

    print("Arquivos gerados com sucesso!")


tamanho_da_sequencia = int(input("Digite o número para gerar as sequências: "))
limite_inferior = int(input("Digite o número para limite inferior: "))
limite_superior = int(input("Digite o número para limite superior: "))
gerar_sequencias(limite_inferior, limite_superior, tamanho_da_sequencia)
