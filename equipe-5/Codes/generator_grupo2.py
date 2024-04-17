
import random

def generate(n, max_val):
    inputs = []
    for _ in range(n):
        number = random.randint(0, max_val)
        inputs.append(number)
    return inputs

def save_numbers(filename, numbers):
    with open(filename, "w") as file:
        for number in numbers:
            file.write(str(number) + "\n")

def main():
    n = int(input("Insira o número de entradas que você deseja gerar: "))
    max_val = int(input("Insira o maior inteiro que pode ser gerado: "))

    # Gerar números aleatórios
    numbers = generate(n,max_val)

    # Salvar números gerados em um arquivo
    save_numbers("inputs/O.txt", numbers)

    # Salvar números gerados em ordem decrescente
    sorted_numbers_desc = sorted(numbers, reverse=True)
    save_numbers("inputs/D.txt", sorted_numbers_desc)

    # Salvar números gerados em ordem crescente
    sorted_numbers_asc = sorted(numbers)
    save_numbers("inputs/A.txt", sorted_numbers_asc)

    print("Done")

if __name__ == "__main__":
    main()
