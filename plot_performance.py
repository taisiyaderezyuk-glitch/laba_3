import csv
import matplotlib.pyplot as plt

# Чтение CSV
data = {}
with open('performance.csv', 'r') as f:
    reader = csv.DictReader(f)
    for row in reader:
        adt = row['ADT']
        size = int(row['Size'])
        if adt not in data:
            data[adt] = {
                'sizes': [],
                'MutableArray': [],
                'ImmutableArray': [],
                'MutableList': [],
                'ImmutableList': []
            }
        data[adt]['sizes'].append(size)
        for col in ['MutableArray', 'ImmutableArray', 'MutableList', 'ImmutableList']:
            data[adt][col].append(float(row[col]))

# Построение графиков
for adt, values in data.items():
    plt.figure(figsize=(8, 5))
    plt.plot(values['sizes'], values['MutableArray'], 'o-', label='MutableArray')
    plt.plot(values['sizes'], values['ImmutableArray'], 's-', label='ImmutableArray')
    plt.plot(values['sizes'], values['MutableList'], '^-', label='MutableList')
    plt.plot(values['sizes'], values['ImmutableList'], 'd-', label='ImmutableList')
    
    plt.xlabel('Number of elements')
    plt.ylabel('Time (seconds)')
    plt.title(f'{adt} Performance (Push+Pop / Enqueue+Dequeue)')
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    
    filename = f'{adt}_graph.png'
    plt.savefig(filename, dpi=150)
    print(f'Saved {filename}')
    