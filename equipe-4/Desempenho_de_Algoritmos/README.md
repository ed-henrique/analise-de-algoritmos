# Projeto de Comparação de Algoritmos de Ordenação

Este projeto compara o desempenho de três diferentes algoritmos de ordenação (Merge Sort, Shell Sort e Quick Sort) usando várias sequências e tamanhos de entrada. O objetivo é analisar a eficiência desses algoritmos sob diversas condições e visualizar os resultados em um gráfico comparativo.

## Estrutura do Projeto

O projeto inclui quatro scripts Python principais:

- `merge_sort_script.py`: Implementa e executa o algoritmo Merge Sort.
- `shell_sort_script.py`: Implementa e executa o algoritmo Shell Sort.
- `quick_sort_script.py`: Implementa e executa o algoritmo Quick Sort.
- `analysis_script.py`: Executa todos os scripts de ordenação, compila os resultados, e gera um gráfico de desempenho.

Além disso, os resultados de cada script de ordenação são salvos em arquivos TXT para cada tipo de sequência (`ascending`, `descending`, `random`) e cada tamanho de entrada especificado.

## Pré-requisitos

- Python 3.6 ou superior
- Matplotlib (para geração de gráficos)
- Subprocess (usualmente incluído com Python)

Você pode instalar as dependências necessárias com o seguinte comando:

```bash
pip install matplotlib
```

## Executando os Scripts
Clone o Repositório

Primeiro, clone este repositório para sua máquina local usando o seguinte comando:

```bash
git clone <URL-do-repositório>
cd <diretório-do-projeto>
```

### Execute os Scripts de Ordenação

Você pode executar cada script de ordenação individualmente para gerar os arquivos de sequências ordenadas:

```bash
python merge_sort_script.py
python shell_sort_script.py
python quick_sort_script.py
```

Cada script irá criar arquivos .txt para diferentes tamanhos e tipos de sequências.

### Compile os Resultados e Gere o Gráfico

Após executar os scripts de ordenação, execute o script de análise para compilar os resultados em um arquivo CSV e gerar o gráfico de desempenho:

```bash
python analysis_script.py
```
Isso irá criar um arquivo combined_results.csv com os tempos de execução e um gráfico sorting_performance_comparison.png que mostra o desempenho comparativo.

## Output Esperado

Arquivos TXT: Cada um contendo as sequências ordenadas para cada tipo e tamanho de entrada.

CSV: combined_results.csv contendo os métodos de ordenação, tamanhos de entrada, tipos de sequência, e tempos médios de execução.

Gráfico PNG: sorting_performance_comparison.png mostrando os tempos médios de execução em relação ao tamanho das sequências para cada algoritmo de ordenação.
