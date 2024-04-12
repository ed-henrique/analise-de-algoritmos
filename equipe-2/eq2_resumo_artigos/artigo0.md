# Artigo 0
## [*Implementação e Avaliação de Algoritmos de Ordenação Paralela em MapReduce*](https://sol.sbc.org.br/index.php/wscad/article/view/16768/16610)
*por Cristina Duarte Murta, Mariane Raquel Silva Gonçalves, Paula de Morais Pinhão*

O objetivo desse artigo foi realizar uma análise comparativa de dedesempenho dos algoritmos de ordenação com paralelismo, Ordenação por Amostragem e 
Quicksort Paralelo, que foram implementados no modelo MapReduce, em ambiente Hadoop.

Os resultados indicam que o desempenho do algoritmo de Ordenação por Amostragem supera o desempenho do Quicksort Paralelo nas escalas testadas.

## Algoritmos usados
Os algoritmos usados nesse trabalho foram a **Ordenação por Amostragem** e o **Quicksort Paralelo**, ambos sendo métodos de ordenação baseados 
na divisão do arquivo de entrada em subconjuntos.

O Quicksort paralelo utiliza pivôs para realizar o particionamento recursivo dos dados no conjunto de processadores. 
O algoritmo não necessita de sincronização, pois cada sublista gerada é associada a um único processo, que não precisa 
comunicar-se com os demais, uma vez que os dados são independentes. Desse modo, várias partiçõessão processadas em paralelo
por diferentes threads ou processos. Isso permite que o algoritmo aproveite melhor os recursos de hardware modernos, como CPUs
com vários núcleos ou clusters de computadores.
O Quicksort paralelo pode oferecer melhor desempenho em comparação com a versão sequencial, especialmente para conjuntos de dados
grandes, mas assim como na versão desparalelizada, a seleção do pivô é essencial para o bom desempenho do algoritmo.
Nesse trabalho, o pivô é a mediana entre *n* valores aleatórios do conjunto de dados.
Após a ordenação local de cada partição, os conjuntos ordenados são concatenados, fornecendo o arquivo final ordenado.

A ordenação por amostragem algoritmo tem como etapa chave a divisão das partições de de maneira balanceada, para que cada
processador receba aproximadamente a mesma carga de dados.
Para isso, o algoritmo divide o arquivo de forma que as chaves de um subconjunto *i* sejam menores que as chaves do subconjunto *i* + 1. 
Após a divisão, cada subconjunto é enviado  a  um  processador, que ordena esses dados localmente. 
Ao final, todos os subconjuntos são concatenados e formam um arquivo globalmente ordenado.


## Técnica de Paralelismo Utilizada
O MapReduce é um modelo de programação e um sistema de processamento de dados
distribuído usado para lidar com grandes volumes de dados de forma eficiente.
Ele divide tarefas em duas etapas principais: o mapeamento (map) e a redução (reduce).

No estágio de mapeamento, os dados são divididos em partes menores e processados em paralelo
em várias máquinas. Cada máquina aplica uma função de mapeamento aos dados e gera uma lista de
pares chave-valor intermediários.

Em seguida, no estágio de redução, os dados intermediários são agrupados com base em suas chaves
e processados para produzir resultados finais. Cada grupo de valores associados à mesma chave é
passado para uma função de redução, que combina esses valores em um único resultado.

O MapReduce permite distribuir e paralelizar o processamento de grandes conjuntos de dados em um cluster
de computadores, oferecendo escalabilidade e tolerância a falhas. É amplamente utilizado em sistemas de
análise de dados, processamento de logs, indexação da web e em muitos outros cenários onde lidar com grandes
volumes de dados é essencial.

## Linguagem da implementação
A linguagem de programação utilizada foi Java.

## Resultados e experimentos
O artigo define que, em relação ao de ordenação por amostragem, o algoritmo Quicksort Paralelo,
no quesito de estabilidade, apresenta um tempo de execução quase similar ao do algoritmo de Ordenação por Amostragem. Além disso, 
as partições formadas são balanceadas para ambos os algoritmos, com um número de elementos iguais. Assim, os tempos de ordenação 
são similares. Adicionalmente, a distribuição dos valores não influencia na ordenação e formação de partições. Também há um jeito de modificar 
o tempo de ordenação, que consiste em aumentar o conjunto de dados de forma a melhorar o tempo de ordenação como resultado. A eficiência do algoritmo de
ordenação por amostragem apresenta uma eficiência de 93% sobre o Quicksort Paralelo, de acordo com os valores de speedup e eficiência subliminares.