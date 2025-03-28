import numpy as np
import time as time
import matplotlib.pyplot as plt

from generic_algorithm import GenericAlgorithm

def random_knapsack_problem(n=100, scale=2000, seed=None):
    if seed is not None:
        np.random.seed(seed)    
    items = np.ceil(scale * np.random.rand(n, 2)).astype("int32")
    v = items[:, 0]
    c = items[:, 1]
    C = int(np.ceil(0.5 * 0.5 * n * scale))
    return v, c, C

def knapsack_problem_dp_solve(v, c, C):
    n = v.size
    a = np.zeros((C + 1, n), dtype="int32") # a[i, j] = best pack of knapsack with capacity i using objects from set {0, ..., j - 1}
    b = np.empty((C + 1, n), dtype="object") # back pointers
    for j in range(n):
        b[0, j] = (0, 0)        
    for i in range(1, C + 1):
        if c[0] <= i:
            a[i, 0] = v[0]
            b[i, 0] = (int(i - c[0]), 0)
        else:
            b[i, 0] = (i, -1)
        for j in range(1, n):
            i_prev = int(i - c[j])
            if c[j] > i:
                a[i, j] = a[i, j - 1]
                b[i, j] = (i, j - 1)
            elif a[i, j - 1] >= a[i_prev, j - 1] + v[j]:
                a[i, j] = a[i, j - 1]
                b[i, j] = (i, j - 1)
            else:
                a[i, j] = a[i_prev, j - 1] + v[j]
                b[i, j] = (i_prev, j - 1)    
    solution = np.zeros(n, dtype="int8")
    i = C
    j = n - 1    
    while i > 0 and j >= 0:
        if b[i, j][0] < i:
            solution[j] = 1
        i, j = b[i, j]
    best_pack_value = a[C, n - 1] 
    return best_pack_value, solution

def knapsack_fitness_hard_penalty(individual, v, c, C):
    total_value = np.sum(v * individual)
    total_weight = np.sum(c * individual)
    if total_weight > C:
        return 0
    return total_value

def knapsack_fitness_with_small_penalty(individual, v, c, C):
    total_value = np.sum(v * individual)
    total_weight = np.sum(c * individual)

    if total_weight > C:
        excess_weight = total_weight - C
        penalty = excess_weight ** 2 * 0.005
        return total_value - penalty
    return total_value
            
if __name__ == '__main__':
    n = 100
    scale = 1000
    history = True
    seed_problem = 0
    v, c, C = random_knapsack_problem(n=n, scale=scale, seed=seed_problem)
    print("RANDOM KNAPSACK PROBLEM:")
    print(f"v: {v}")
    print(f"c: {c}")
    print(f"C: {C}")
    
    print("SOLVING VIA DYNAMIC PROGRAMMING...")
    t1 = time.time()
    best_pack_value, solution = knapsack_problem_dp_solve(v, c, C)
    t2 = time.time()
    print("SOLVING VIA DYNAMIC PROGRAMMING DONE IN: " + str(t2 - t1) + " s.")
    print("BEST PACK VALUE: " + str(best_pack_value))
    print("SOLUTION: " + str(solution))
    print("PACK VALUE CHECK: " + str(solution.dot(v)))
    print("PACK CAPACITY CHECK: " + str(solution.dot(c)))

    print("\nSOLVING VIA GENETIC ALGORITHM...")
    ga = GenericAlgorithm(n=n, fitness_function=knapsack_fitness_with_small_penalty, v=v, c=c, C=C,
                          m=1000, T=100, crossover_prob=0.9, mutation_prob=0.001,
                          double_point_crossover=True, rank_selection=True)

    t1 = time.time()
    best_solution_ga = ga.evolve()
    t2 = time.time()
    print("SOLVING VIA GENETIC ALGORITHM DONE IN: " + str(t2 - t1) + " s.")
    print(f"SOLUTION: {str(best_solution_ga)}")
    print("PACK VALUE CHECK: " + str(np.dot(best_solution_ga, v)))
    print("PACK CAPACITY CHECK: " + str(np.dot(best_solution_ga, c)))

    ga_pack_value = np.dot(best_solution_ga, v)
    value_ratio = ga_pack_value / best_pack_value
    print(f"VALUE RATIO (genetic/exact): {value_ratio:.5f}")

    bitwise_similarity = np.sum(best_solution_ga == solution) / n * 100
    print(f"BITWISE SIMILARITY: {bitwise_similarity:.2f}%")

    plt.plot(ga.fitness_history)
    plt.xlabel('Generation')
    plt.ylabel('Best Fitness')
    plt.title('Genetic Algorithm Fitness Over Generations')
    plt.show()