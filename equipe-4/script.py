import random

def gerar_sequencias(tamanho):
    # Gerar sequência ascendente
    ascendente = list(range(1, tamanho + 1))

    # Gerar sequência descendente
    descendente = list(range(tamanho, 0, -1))

    # Gerar sequência aleatória
    aleatoria = random.sample(range(1, tamanho + 1), tamanho)

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


tamanho_da_sequencia = int(input("Digite o número para gerar as sequências: "))
gerar_sequencias(tamanho_da_sequencia)
