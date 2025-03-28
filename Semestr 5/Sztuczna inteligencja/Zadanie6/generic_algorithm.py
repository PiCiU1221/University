import random
import numpy as np

class GenericAlgorithm:
    def __init__(self, n, fitness_function, v, c, C,
                 m=1000, T=100, crossover_prob=0.9, mutation_prob=0.001,
                 double_point_crossover=False, rank_selection=False):

        self.n = n
        self.fitness_function = fitness_function
        self.v = v
        self.c = c
        self.C = C
        self.m = m
        self.T = T
        self.crossover_prob = crossover_prob
        self.mutation_prob = mutation_prob
        self.population = self.initialize_population()
        self.best_individual = None
        self.fitness_history = []
        self.double_point_crossover_flag = double_point_crossover
        self.rank_selection_flag = rank_selection

    def initialize_population(self):
        return np.random.randint(0, 2, size=(self.m, self.n))

    def roulette_wheel_selection(self):
        fitness_values = []
        for individual in self.population:
            fitness = self.fitness_function(individual, self.v, self.c, self.C)
            fitness_values.append(fitness)

        total_fitness = sum(fitness_values)

        probabilities = []
        for fitness in fitness_values:
            probability = fitness / total_fitness
            probabilities.append(probability)

        selected = random.choices(self.population, weights=probabilities, k=self.m)
        self.population = selected

    def rank_selection(self):
        fitness_values = []
        for individual in self.population:
            fitness = self.fitness_function(individual, self.v, self.c, self.C)
            fitness_values.append(fitness)

        sorted_population = sorted(zip(self.population, fitness_values), key=lambda x: x[1])

        probabilities = []
        total_sum = 0

        for rank, (individual, fitness) in enumerate(sorted_population, 1):
            probability = (2 * rank * fitness) / (self.m * (self.m + 1))
            probabilities.append(probability)
            total_sum += probability

        selected = random.choices([individual for individual, _ in sorted_population], weights=probabilities, k=self.m)

        self.population = selected

    def single_point_crossover(self):
        new_population = []
        np.random.shuffle(self.population)

        for i in range(0, self.m, 2):
            parent1 = self.population[i]
            parent2 = self.population[i + 1]

            if random.random() < self.crossover_prob:
                crossover_point = random.randint(1, len(parent1) - 1)

                offspring1 = np.concatenate((parent1[:crossover_point], parent2[crossover_point:]))
                offspring2 = np.concatenate((parent2[:crossover_point], parent1[crossover_point:]))

                new_population.append(offspring1)
                new_population.append(offspring2)
            else:
                new_population.append(parent1)
                new_population.append(parent2)

        self.population = np.array(new_population)

    def double_point_crossover(self):
        new_population = []
        np.random.shuffle(self.population)

        for i in range(0, self.m, 2):
            parent1 = self.population[i]
            parent2 = self.population[i + 1]

            if random.random() < self.crossover_prob:
                crossover_point1 = random.randint(1, len(parent1) - 1)
                crossover_point2 = random.randint(1, len(parent1) - 1)

                while crossover_point1 == crossover_point2:
                    crossover_point2 = random.randint(1, len(parent1) - 1)

                if crossover_point1 > crossover_point2:
                    crossover_point1, crossover_point2 = crossover_point2, crossover_point1

                offspring1 = np.concatenate((parent1[:crossover_point1], parent2[crossover_point1:crossover_point2], parent1[crossover_point2:]))
                offspring2 = np.concatenate((parent2[:crossover_point1], parent1[crossover_point1:crossover_point2], parent2[crossover_point2:]))

                new_population.append(offspring1)
                new_population.append(offspring2)
            else:
                new_population.append(parent1)
                new_population.append(parent2)

        self.population = np.array(new_population)

    def mutate(self):
        for i in range(self.m):
            individual = self.population[i]
            for j in range(len(individual)):
                if random.random() < self.mutation_prob:
                    individual[j] = 1 - individual[j]

    def evolve(self):
        for generation in range(self.T):

            if self.rank_selection_flag:
                self.rank_selection()
            else:
                self.roulette_wheel_selection()

            if self.double_point_crossover_flag:
                self.double_point_crossover()
            else:
                self.single_point_crossover()

            self.mutate()

            best_individual = max(self.population, key=lambda individual: self.fitness_function(individual, self.v, self.c, self.C))
            best_fitness = self.fitness_function(best_individual, self.v, self.c, self.C)

            self.fitness_history.append(best_fitness)

            if self.best_individual is None or best_fitness > self.fitness_function(self.best_individual, self.v, self.c, self.C):
                self.best_individual = best_individual

        return self.best_individual
