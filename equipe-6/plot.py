import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file into a DataFrame
df = pd.read_csv("results.csv", sep=";")

# Create separate DataFrames for each algorithm
merge_df = df[df['Algoritmo'] == 'merge']
quick_df = df[df['Algoritmo'] == 'quick']
shell_df = df[df['Algoritmo'] == 'shell']

# Create separate DataFrames for each type of data (ascendente, descendente, aleatorio)
merge_ascendente = merge_df[merge_df['Entrada'].str.contains('ascendente')].reset_index(drop=True)
merge_descendente = merge_df[merge_df['Entrada'].str.contains('descendente')].reset_index(drop=True)
merge_aleatorio = merge_df[merge_df['Entrada'].str.contains('aleatoria')].reset_index(drop=True)

quick_ascendente = quick_df[quick_df['Entrada'].str.contains('ascendente')].reset_index(drop=True)
quick_descendente = quick_df[quick_df['Entrada'].str.contains('descendente')].reset_index(drop=True)
quick_aleatorio = quick_df[quick_df['Entrada'].str.contains('aleatoria')].reset_index(drop=True)

shell_ascendente = shell_df[shell_df['Entrada'].str.contains('ascendente')].reset_index(drop=True)
shell_descendente = shell_df[shell_df['Entrada'].str.contains('descendente')].reset_index(drop=True)
shell_aleatorio = shell_df[shell_df['Entrada'].str.contains('aleatoria')].reset_index(drop=True)

# Sort values by 'Entrada' for each algorithm and input type
merge_ascendente = merge_ascendente.sort_values(by='Entrada').reset_index(drop=True)
merge_descendente = merge_descendente.sort_values(by='Entrada').reset_index(drop=True)
merge_aleatorio = merge_aleatorio.sort_values(by='Entrada').reset_index(drop=True)

quick_ascendente = quick_ascendente.sort_values(by='Entrada').reset_index(drop=True)
quick_descendente = quick_descendente.sort_values(by='Entrada').reset_index(drop=True)
quick_aleatorio = quick_aleatorio.sort_values(by='Entrada').reset_index(drop=True)

shell_ascendente = shell_ascendente.sort_values(by='Entrada').reset_index(drop=True)
shell_descendente = shell_descendente.sort_values(by='Entrada').reset_index(drop=True)
shell_aleatorio = shell_aleatorio.sort_values(by='Entrada').reset_index(drop=True)

# Create plots for each algorithm type
fig, axs = plt.subplots(3, figsize=(10, 15))

# Merge Sort
axs[0].plot(merge_ascendente['Entrada'].apply(lambda x: x.split('-')[0]), merge_ascendente['Tempo'], label='Merge', color='red')
axs[0].plot(quick_ascendente['Entrada'].apply(lambda x: x.split('-')[0]), quick_ascendente['Tempo'], label='Quick', color='green')
axs[0].plot(shell_ascendente['Entrada'].apply(lambda x: x.split('-')[0]), shell_ascendente['Tempo'], label='Shell', color='blue')
axs[0].set_title('Entrada Ascendente')
axs[0].set_xlabel('Tamanho da Entrada')
axs[0].set_ylabel('Tempo (s)')
axs[0].legend()

# Quick Sort
axs[1].plot(merge_aleatorio['Entrada'].apply(lambda x: x.split('-')[0]), merge_aleatorio['Tempo'], label='Merge', color='red')
axs[1].plot(quick_aleatorio['Entrada'].apply(lambda x: x.split('-')[0]), quick_aleatorio['Tempo'], label='Quick', color='green')
axs[1].plot(shell_aleatorio['Entrada'].apply(lambda x: x.split('-')[0]), shell_aleatorio['Tempo'], label='Shell', color='blue')
axs[1].set_title('Entrada Aleatória')
axs[1].set_xlabel('Tamanho da Entrada')
axs[1].set_ylabel('Tempo (s)')
axs[1].legend()

# Shell Sort
axs[2].plot(merge_descendente['Entrada'].apply(lambda x: x.split('-')[0]), merge_descendente['Tempo'], label='Merge', color='red')
axs[2].plot(quick_descendente['Entrada'].apply(lambda x: x.split('-')[0]), quick_descendente['Tempo'], label='Quick', color='green')
axs[2].plot(shell_descendente['Entrada'].apply(lambda x: x.split('-')[0]), shell_descendente['Tempo'], label='Shell', color='blue')
axs[2].set_title('Entrada Descendente')
axs[2].set_xlabel('Tamanho da Entrada')
axs[2].set_ylabel('Tempo (s)')
axs[2].legend()

# Adjust layout
plt.tight_layout()

# Save or show the plot
plt.savefig('sorting_comparison.png')  # Save the plot as a PNG file
plt.show()  # Show the plot
