
# Analisador de Desempenho de Algoritmos

Esta classe tem como objetivo analisar o desempenho de diferentes algoritmos de ordenação em categorias de entradas específicas. Ela permite executar os algoritmos repetidas vezes e salvar suas medias, visualizar os resultados em gráficos e exportar os dados de desempenho para arquivos CSV.
## Funcionalidades

- **Análise de Desempenho:** Execute diferentes algoritmos de ordenação em categorias de entradas específicas.
- **Visualização de Dados:** Visualize os resultados em gráficos para comparar o desempenho dos algoritmos.
- **Exportação de Dados:** Exporte os dados de desempenho para arquivos CSV para análises adicionais.
- **Configuração Flexível:** Defina os algoritmos a serem analisados, as categorias de entradas e o diretório de arquivos de entrada.
- **Fácil de Usar:** Basta importar a classe `Analise` e executar os métodos para realizar a análise.

## Uso

1. **Configuração:** Defina os algoritmos a serem analisados e o diretório onde os arquivos de entrada estão localizados.
2. **Execução da Análise:** Execute a análise com diferentes categorias de entradas para os algoritmos.
3. **Visualização:** Visualize os resultados em gráficos, fornecendo informações sobre o sistema em que os testes foram realizados.
4. **Exportação de Dados:** Opcionalmente, exporte os dados de desempenho para arquivos CSV para análises adicionais.

## Pré-requisitos

Certifique-se de ter o Python3 instalado em sua máquina.

## Instalação

1. Clone este repositório em sua máquina local.
2. Certifique-se de ter as bibliotecas Python necessárias instaladas. Você pode instalá-las executando `pip install -r requirements.txt`.
3. Execute o código Python conforme necessário.

## execução Rapida 
Basta executar o arquivo `analise.py` com o Python3, com estes comando:

windows: `python analise.py`
linux/macOS: `python3 analise.py`

## Exemplo de Uso

```python
# Importe a classe Analise do arquivo analise.py
from analise import Analise

# Defina os algoritmos a serem analisados e as categorias de entradas
algoritmos = ['mergeSort', 'shellSort', 'quickSort'] # nome dos binarios compilados dos algoritmos a serem executados
categorias = [['a-1000.txt', 'a-5000.txt', 'a-10000.txt'],
              ['d-1000.txt', 'd-5000.txt', 'd-10000.txt'],
              ['o-1000.txt', 'o-5000.txt', 'o-10000.txt']]

# Crie um objeto de análise
analise = Analise(algoritmos, 'inputs/')

# Execute a análise
analise.run(categorias)

# Salve os dados
analise.save_data()

# Plote os dados
analise.plot_data("sistema", "nome do processador", "quantidade de memoria ram em GB")
```

