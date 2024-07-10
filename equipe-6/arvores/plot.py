import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file into a DataFrame
df = pd.read_csv("results.csv", sep=";")

# Create separate DataFrames for each algorithm
avl_df = df[df['Algoritmo'] == 'avl']
red_black_df = df[df['Algoritmo'] == 'red_black']

# Create separate DataFrames for each type of data (ascendente, descendente, aleatorio)
avl_ascendente = avl_df[avl_df['Entrada'].str.contains('ascendente')].reset_index(drop=True)
red_black_ascendente = red_black_df[red_black_df['Entrada'].str.contains('ascendente')].reset_index(drop=True)

# Sort values by 'Entrada' for each algorithm and input type
avl_ascendente = avl_ascendente.sort_values(by='Entrada').reset_index(drop=True)
red_black_ascendente = red_black_ascendente.sort_values(by='Entrada').reset_index(drop=True)

# Create plots for each algorithm type
fig, axs = plt.subplots(3, figsize=(10, 15))

# avl Sort
axs[0].plot(avl_ascendente['Entrada'].apply(lambda x: x.split('-')[0]), avl_ascendente['Tempo'], label='avl', color='red')
axs[0].plot(red_black_ascendente['Entrada'].apply(lambda x: x.split('-')[0]), red_black_ascendente['Tempo'], label='red_black', color='green')
axs[0].set_title('Entrada Ascendente')
axs[0].set_xlabel('Tamanho da Entrada')
axs[0].set_ylabel('Tempo (s)')
axs[0].legend()

# Adjust layout
plt.tight_layout()

# Save or show the plot
plt.savefig('sorting_comparison.png')  # Save the plot as a PNG file
plt.show()  # Show the plot
