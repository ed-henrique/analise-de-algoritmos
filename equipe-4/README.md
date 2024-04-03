Equipe: Jasson, Guilherme, Leonardo e João Lucas

# Gerador de Sequências Numéricas

Este script Python gera três arquivos de texto, cada um contendo uma sequência de números em ordem ascendente, descendente e aleatória, respectivamente. É uma ferramenta útil para criar conjuntos de dados de teste ou para fins educacionais relacionados ao aprendizado de algoritmos de ordenação e aleatoriedade.

## Requisitos

Para executar este script, você precisará de:

- Python 3.x

## Como Executar

1. Clone o repositório para sua máquina local ou baixe o arquivo `script.py`.
2. Abra um terminal ou prompt de comando.
3. Navegue até o diretório onde o arquivo `generate_numbers.py` foi salvo.
4. Execute o script usando o comando: `python generate_numbers.py`
5. Após a execução, três arquivos de texto (`ascending_order.txt`, `descending_order.txt`, `random_order.txt`) serão criados no mesmo diretório do script.

## Personalização

Você pode personalizar o intervalo dos números gerados modificando o seguinte trecho de código no arquivo `generate_numbers.py`:

```python
# Gera números com um intervalo de 1.000
numbers = list(range(1, 10001, 1000))
