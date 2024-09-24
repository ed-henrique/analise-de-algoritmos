# Script em C Equipe 1
### Equipe: Felipe Borges, Gilberto Alexsandro e Wanderson Morais de Sousa
## Funcionamento do script

Primeiro, escolha quantos numeros vao ser criados.
Segundo, escolha qual vai ser o maior numero criado.

Entao se voce quiser criar 5000 numeros:
Insira o número de entradas que você deseja gerar: 5000
Insira o maior inteiro que pode ser gerado: 5000
e entao sera criado os 5000 numeros de forma aleatoria, crescente e decrescente.

## Atividade 2

### PRIMEIRO ARTIGO
Artigo 01 ->

Algoritmo utilizado: Algoritmos paralelos de ordenação, o Quicksort Paralelo e o Ordenação por Amostragem

Técnica de paralelismo: Quicksort em MapReduce

Linguagem de programação: Java no ambiente  Hadoop 

Avaliação Experimental: Os testes foram realizados em um cluster formado por cinco máquinas (número máximodisponível para os testes) com processadores Intel Core 2Duo  de  3.0  GHz,  disco  rígido  SATA  de  500  GB  7200RPM,  memória  RAM  de  4  GB,  placa  de  rede  GigabitEthernet,  sistema  operacional  Ubuntu  10.04  32  bits,  SunJava JDK 1.6.0 19.0-b09, Apache Hadoop 1.1.0. 

Para  a  realização  dos  testes  foram  gerados  númerosaleatórios  de  acordo  com  três  distribuições:  uniforme,normal  e  Pareto.  As  distribuições  foram  geradas  por  um programa implementado em Java para geração de chaves aleatórias  de  ponto  flutuante.  Foram  gerados  conjuntos contendo entre 106 e 1010 chaves. Os gráficos da Figura 3 exibem o  padrão  de  frequência  das  chaves  nas  três  distribuições: uniforme, normal e Pareto, respectivamente. Os algoritmos  foram  executados  em  conjuntos  de  dados  de tamanhos variados, os tempos de execução foram medidos e então foram calculadas as métricas speedup e eficiência.

Os  resultados  apontaram  de  maneira  conclusiva  o  melhor desempenho e escalabilidade do algoritmo Ordenação por  Amostragem,  que  apresentou  os  menores  tempos  de ordenação  e  uma  boa  distribuição  de  trabalho entre  as máquinas  presentes  no cluster.  O  algoritmo  Quicksort Paralelo apresentou bons resultados quando utilizado para ordenar quantidades menores de dados, uma vez que não realiza  processamento  extra,  amostrando  a  entrada,  para definir as partições. No entanto, para maiores quantidadesde  dados,  esse  algoritmo  apresenta desempenho  inferior, devido ao número reduzido de partições e uma divisão de trabalho mais limitada entre os processadores. Isso ocorre porque,  a  cada  particionamento  dos  dados,  o  algoritmo realiza maior quantidade de manipulações nos arquivos

### SEGUNDO ARTIGO
Artigo 02 ->

ALGORITMO mergesot in-place
TECNICA DE PARALELISMO 
O artigo fala sobre a paralelização do algoritmo mergesort utilizando threads em Java. A técnica de paralelismo utilizada consiste em dividir o vetor a ser ordenado em trechos menores e independentes, permitindo que cada thread trabalhe em um trecho específico sem conflitos no acesso aos elementos do vetor. Além disso, o artigo menciona que foram realizados testes com diferentes configurações do vetor de entrada para verificar a eficiência da implementação paralela. 
 
LINGUAGUEM DE PROGRAMAÇAO JAVA
 
AVALIAÇÃO EXPREMENTAL
 O artigo descreve uma avaliação experimental da paralelização do algoritmo Mergesort in-place utilizando threads em Java. Nos testes realizados, foram utilizados diferentes tamanhos de vetores e configurações, como elementos repetidos ou únicos, e vetores com elementos dispostos de forma aleatória, ordenada ou invertida. Foram realizadas mil execuções para cada configuração e calculado o tempo médio, sendo que as execuções iniciais correspondentes a 10% do total não foram consideradas no cálculo. Os resultados mostraram que a paralelização apresentou redução significativa do tempo de execução para entradas maiores, chegando a 74%, em relação à versão sequencial. Além disso, o artigo menciona que a equipe pretende investir em otimização do trecho sequencial do algoritmo e realizar comparações com outras implementações paralelas similares em relação ao desempenho e consumo de memória.
