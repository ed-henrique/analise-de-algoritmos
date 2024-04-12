# Artigo 1
## [*Analisando o Desempenho da Paralelização no Algoritmo de Ordenação Mergesort In-place*](https://www.researchgate.net/profile/Adriano-Garcia-4/publication/277143727_Analisando_o_Desempenho_da_Paralelizacao_no_Algoritmo_de_Ordenacao_Mergesort_In-place/links/5578b8d308aeb6d8c01f1a17/Analisando-o-Desempenho-da-Paralelizacao-no-Algoritmo-de-Ordenacao-Mergesort-In-place.pdf)
*por Adriano M. Garcia, Márcia C. Cera, Sérgio L. S. Mergen*

Esse trabalho teve como objetivo reduzir o tempo de execução do algoritmo Mergesort *in-place* utilizando paralelização com threads. 
O resultado foi a redução de até 74% no tempo de execução.


## Algoritmos usados
O algoritmo em que se baseia esse artigo é o **Mergesort versão *in-place***. O *in-place* se refere
a algoritmos que utilizam uma quantia constante de memória durante sua execução.
O Mergesort é dividido em duas etapas: primeiro ele divide o vetor de entrada em trechos menores e depois mescla esses trechos. 
Na etapa de mescla, assume-se que os trechos já estão previamente ordenados. De modo geral, o algoritmo encontra
o elemento intermediário do primeiro trecho, depois procura o primeiro elemento do segundo trecho, que é superior ao elemento selecionado, e move 
todos os elementos do segundo trecho que aparecem antes do primeiro e segundo trecho. 
Isso diminui o problema de desordenação em pequenos trechos que podem ser tratados recursivamente.

## Técnica de Paralelismo Utilizada
A técnica de paralelização usada foi a implementação de threads. Essa técnica permite que vários trechos de um algoritmo executem ao mesmo tempo, 
em paralelo, tornando programas mais eficazes ao lidar com a tecnologia multinúcleo, dividindo trechos paralelos em relação à quantia de núcleos de um processador.

## Linguagem da implementação
A linguagem de programação utlizada foi Java, por implementar nativamente threads.

## Resultados e experimentos
A partir da análise feita pelo estudo, foi realmente possível melhorar o desempenho e a eficiência do algoritmo de ordenação MergeSort aplicando Java Threads. 
Foi alcançada uma  redução  de  até  74%  no  tempo  execução  do algoritmo sequencial quando executado com 8 threads.
O uso da paralelização foi testado utilizando 2 a 64 threads e embora o maior ganho obtido tenha sido ao utilizar 8 threads paralelas, 
foi ao criar apenas 2 que o speedup se aproximou mais do ideal. Foi observado também que a ordenação de um vetor ordenado possui um tempo
de execução desprezível, não se observando ganhos na versão paralela (vetores pequenos, com menos de 100 mil elementos,também se incluem
nesse caso) e que o tempo de execução com o vetor invertido não difere do tempo com um vetor aleatório, comprovando que não há pior caso
específico.