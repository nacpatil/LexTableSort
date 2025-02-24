import csv
import matplotlib.pyplot as plt

def read_csv(filename):
    """
    Reads a CSV file with columns 'NumRows' and 'SortTime(seconds)'.
    Returns two lists: one for the number of rows and one for the sort times.
    """
    num_rows = []
    sort_times = []
    with open(filename, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            num_rows.append(int(row['NumRows']))
            sort_times.append(float(row['SortTime(seconds)']))
    return num_rows, sort_times

def add_comparison_to_plot(filename1, label1, filename2, label2, color):
    """
    Reads two CSV files, converts the number of rows to millions,
    and plots their sort times on the current axes using the same color.
    Uses an 'x' marker for the first dataset (perm) and an 'o' marker for the second dataset (comp).
    
    Parameters:
      filename1 (str): The CSV file for the first dataset.
      label1 (str): Label for the first dataset.
      filename2 (str): The CSV file for the second dataset.
      label2 (str): Label for the second dataset.
      color (str): Color to be used for both datasets in this pair.
    """
    # Read and convert data for the first file
    num_rows1, sort_times1 = read_csv(filename1)
    num_rows_millions1 = [x   for x in num_rows1]

    # Read and convert data for the second file
    num_rows2, sort_times2 = read_csv(filename2)
    num_rows_millions2 = [x  for x in num_rows2]

    # Plot the data for the first dataset with marker 'x'
    plt.plot(num_rows_millions1, sort_times1, marker='x', linestyle='-', color=color, label=label1)
    # Plot the data for the second dataset with marker 'o'
    plt.plot(num_rows_millions2, sort_times2, marker='o', linestyle='-', color=color, label=label2)

# Create one figure to hold all comparisons.
plt.figure(figsize=(10, 8))

# Add each dataset comparison with a designated color.
 
add_comparison_to_plot(
    'out/build/x64-release/performance_results_perm_rand_coltest.csv',
    'Forward Permutation (PreSorted)',
    'out/build/x64-release/performance_results_comp_rand_coltest.csv',
    'Comparator (PreSorted)',
    color='red'
)




# Configure plot labels, title, and grid.
plt.xlabel('Number of Columns')
plt.ylabel('Sort Time (seconds)')
plt.title('Table Sorting Time vs NumColumns on Random Ints')
plt.grid(True)
plt.legend(title="Legend")
plt.show()
