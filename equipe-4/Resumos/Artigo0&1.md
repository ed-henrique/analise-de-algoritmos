Artigo 0

Algoritmo
•	Quicksort Paralelo: Este algoritmo usa uma abordagem de dividir para conquistar, que é naturalmente apta para paralelização. Utiliza pivôs para o particionamento recursivo dos dados entre os processadores, não necessitando de sincronização durante a separação, pois cada sublista é processada independentemente.
•	Ordenação por Amostragem: Divide o arquivo de entrada em múltiplos subconjuntos, assegurando que as chaves em um subconjunto são sempre menores que as chaves no subconjunto. Este método visa um balanceamento de carga ideal, onde cada processador recebe uma carga de dados aproximadamente igual para processar e ordenar localmente.
Técnica de Paralelismo
•	O paralelismo é implementado através do modelo MapReduce no ambiente Hadoop. Ambos os algoritmos, Quicksort e Ordenação por Amostragem, utilizam as funções Map para processar os dados de entrada e produzir pares chave-valor, e Reduce para combinar esses valores e produzir um conjunto de dados ordenado.
Linguagem de Programação
•	Os algoritmos foram implementados em Java, aproveitando as capacidades de gerenciamento de falhas e balanceamento de carga do Hadoop, o que é essencial para processar grandes volumes de dados (Big Data) e executar operações complexas de ordenação em um ambiente distribuído e paralelo.
Avaliação Experimental
•	Ambiente de Teste: Usou-se um cluster de cinco máquinas com processadores Intel Core 2 Duo, demonstrando a aplicabilidade em sistemas não especializados.
•	Métricas de Avaliação: Incluem o tempo de execução, speedup (comparativo de tempo de execução entre execuções paralelas e sequenciais idealizadas), e eficiência (uma relação entre o speedup obtido e o número de processadores).
•	Resultados: O algoritmo de Ordenação por Amostragem mostrou melhor desempenho em comparação ao Quicksort Paralelo, especialmente com o aumento no volume de dados, devido à sua habilidade em manter um balanceamento de carga mais uniforme entre os processadores.

Artigo 1

Algoritmo
•	Mergesort In-place Paralelo: O Mergesort é um algoritmo de ordenação que utiliza a metodologia de divisão e conquista, consistindo de duas etapas principais: divisão do vetor de entrada em subvetores menores e mescla desses subvetores de modo a resultar em um vetor final ordenado. A versão in-place do Mergesort realiza a mescla sem utilizar memória adicional significativa, o que é uma vantagem em termos de eficiência de espaço.
Técnica de Paralelismo
•	Uso de Threads em Java: A paralelização foi implementada através de threads em Java, que permitem a execução concorrente de múltiplos trechos do código. Especificamente, o processo de separação dos elementos maiores e menores que um pivô (elemento X) foi paralelizado. Esta abordagem explora eficientemente a arquitetura multinúcleo dos processadores modernos, dividindo o trabalho de mescla entre os núcleos disponíveis e reduzindo significativamente o tempo de execução.
Linguagem de Programação
•	Java foi escolhida por sua capacidade nativa de gerenciamento de threads e portabilidade, facilitando a implementação de paralelismo e a execução em diferentes plataformas. A linguagem suporta alto nível de abstração para manipulação de threads, o que simplifica o desenvolvimento e teste de aplicações paralelas.
Avaliação Experimental
•	Ambiente de Teste: Os testes foram realizados em um sistema com Windows 7 Ultimate 64 Bits e Java JDK 7u9, utilizando um processador Intel® Core™ i7 com 8 núcleos.
•	Frameworks e Metodologia: Utilizou-se um framework de teste em Java para variar a configuração do vetor de entrada (números únicos, repetidos, ordenados, aleatórios, invertidos) e medir o impacto no desempenho do algoritmo.
•	Tamanhos dos Vetores Testados: 100 mil, 1 milhão, e 10 milhões de elementos.
•	Métricas de Desempenho: O tempo de execução foi a principal métrica, com a paralelização proporcionando reduções significativas de tempo, especialmente para os vetores maiores. O speedup obtido mostrou melhorias conforme aumentava o número de threads até um ponto ótimo de 8 threads, dado o número de núcleos do processador utilizado.
•	Resultados: A implementação paralela mostrou redução de até 74% no tempo de execução em comparação com a versão sequencial para o vetor de 10 milhões de elementos. O speedup máximo ocorreu com 8 threads, o que coincide com o número de núcleos do processador, demonstrando uma utilização eficiente dos recursos disponíveis. A eficácia do paralelismo diminui com o aumento do número de threads além de 8, devido à sobrecarga de gerenciamento das threads e à parte do algoritmo que não foi paralelizada (movimentação inicial dos elementos).
