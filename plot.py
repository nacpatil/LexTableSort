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

def plot_comparison(filename1, label1, filename2, label2, legendStr):
    """
    Reads two CSV files, converts the number of rows to millions,
    and plots their sort times on the same plot with provided labels.
    
    Parameters:
      filename1 (str): The first CSV file name.
      label1 (str): Label for the first dataset.
      filename2 (str): The second CSV file name.
      label2 (str): Label for the second dataset.
      legendStr (str): Title for the legend.
    """
    print(label1, label2, legendStr)
    # Read data from the first file and convert rows to millions
    num_rows1, sort_times1 = read_csv(filename1)
    num_rows_millions1 = [x / 1e6 for x in num_rows1]

    # Read data from the second file and convert rows to millions
    num_rows2, sort_times2 = read_csv(filename2)
    num_rows_millions2 = [x / 1e6 for x in num_rows2]

    # Plot both datasets
    plt.figure(figsize=(8, 6))
    plt.plot(num_rows_millions1, sort_times1, marker='o', linestyle='-', color='b', label=label1)
    plt.plot(num_rows_millions2, sort_times2, marker='o', linestyle='-', color='r', label=label2)
    
    plt.xlabel('Number of Rows (millions)')
    plt.ylabel('Sort Time (seconds)')
    plt.title(legendStr)
    plt.grid(True)
    
    # Use the labels from plt.plot and set a legend title
    plt.legend(title="")

# Example usage:
perm_file = 'out/build/x64-release/performance_results_perm_rand.csv'
comp_file = 'out/build/x64-release/performance_results_comp_rand.csv'
plot_comparison(perm_file, 'Forward Permutation', comp_file, 'Comparator', "Random Vectors Table")
plt.show()

perm_file = 'out/build/x64-release/performance_results_perm_preSorted.csv'
comp_file = 'out/build/x64-release/performance_results_comp_preSorted.csv'
plot_comparison(perm_file, "Forward Permutation", comp_file, 'Comparator', "Already Sorted Vectors Table")
plt.show()



perm_file = 'out/build/x64-release/performance_results_perm_seq.csv'
comp_file = 'out/build/x64-release/performance_results_comp_seq.csv'
plot_comparison(perm_file, "Forward Permutation", comp_file, 'Comparator', "Shuffled vectors Table")
plt.show()
