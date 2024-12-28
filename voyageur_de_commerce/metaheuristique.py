# Voyageur de commerce - Ozgur DOGAN

import random
import numpy as np
import math
import sys
import os
import matplotlib.pyplot as plt
import time


CENTER = (0, 0, 0)

def lire_fichier(filename):
    cities = []
    with open(filename, 'r') as file:
        lines = file.readlines()
        n = int(lines[0])
        for line in lines[1:]:
            city_info = line.split()
            city_id = int(city_info[0])
            x, y = map(int, city_info[1:])
            cities.append((city_id, x, y))

    cities = np.array(cities)
    return cities, n

def distance_euclidienne(city1, city2):
    x1, y1 = city1[1], city1[2]
    x2, y2 = city2[1], city2[2]
    distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    return distance

def solution_initiale_random(n):
    sequence = list(range(1, n + 1))  
    random.shuffle(sequence)  
    return sequence

def distance_total(cities, solution):
    total_distance = 0
    #distance de 0,0 et city1 
    total_distance += distance_euclidienne(CENTER, cities[solution[0]-1])

    N = len(solution)
    for i in range(N-1):
        city1 = cities[solution[i] - 1]
        city2 = cities[solution[i + 1] - 1]
        total_distance += distance_euclidienne(city1, city2)
    
    #distance de dernier city et 0,0
    total_distance += distance_euclidienne(cities[solution[-1]-1], CENTER)

    return total_distance 

def meilleur_voisin(cities, solution, method='2-opt'):
    best_sol = solution.copy()
    best_dist = distance_total(cities, solution)

    for i in range(len(solution)):
        for j in range(i + 1, len(solution)):
            sol = solution.copy()

            if method == '2-swap':
                sol[i], sol[j] = sol[j], sol[i]
            elif method == '2-opt':
                sol[i:j+1] = reversed(sol[i:j+1])

            distance = distance_total(cities, sol)
            if distance < best_dist:
                best_dist = distance
                best_sol = sol.copy()

    return best_sol

def drawEvolution(voisines):
    # Tracer les solutions au fur et à mesure des itérations
    plt.figure(figsize=(8, 6))
    plt.plot(voisines, linestyle='-', color='b')
    plt.title('Évolution des solutions')
    plt.xlabel('iterations')
    plt.ylabel('distance de solution')
    plt.grid(True)
    plt.show()

def steepest_hill_climbing(cities, solution, MAX_depl, method='2-opt'):
    s = solution.copy()
    nb_depl = 0
    STOP = False
    voisines = [distance_total(cities, s)]

    while nb_depl < MAX_depl and not STOP:
        s_p = meilleur_voisin(cities, s, method)
        if distance_total(cities, s_p) < distance_total(cities, s):
            s = s_p.copy()
            a = distance_total(cities, s)
            voisines.append(a)
        else:
            STOP = True
        nb_depl += 1

    #drawEvolution(voisines)
    return s, nb_depl


def steepest_hill_climbing_Restart(cities, solution, MAX_depl, Max_restart):
    best_s = solution.copy()
    best_s, best_pas = steepest_hill_climbing(cities, best_s, MAX_depl)

    for _ in range(Max_restart):
        new_X = solution_initiale_random(len(cities))
        X_hil, pas = steepest_hill_climbing(cities, new_X, MAX_depl)
        if distance_total(cities, X_hil) < distance_total(cities, best_s):
            best_s = X_hil.copy()
            best_pas = pas

    return best_s, best_pas

"""
# version un peu modifié de steepest_hill_climbing_Restart car pusiqe l'algo steepest_hill_climbing est une algorithme deterministe pas besoin de 
# calculer la steepest_hill_climbing pour chaque solution random initialisé donc
# dans cetter version on compare "Max_restart" nombre de solution initiale et quand on trouve la meilleur initiale on applique la steepest_hill_climbing
def steepest_hill_climbing_Restart(cities, solution, MAX_depl, Max_restart):
    best_s = solution.copy()

    for _ in range(Max_restart):
        new_s = solution_initiale_random(len(cities))
        if distance_total(cities, new_s) < distance_total(cities, best_s):
            best_s = new_s.copy()

    best_s, best_pas = steepest_hill_climbing(cities, best_s, MAX_depl)

    return best_s, best_pas
"""

def tabou_search(villes, solution, MAX_depl, k):
    s = solution.copy()
    tabou = []
    nb_depl = 0
    msol = s.copy()
    stop = False

    while nb_depl < MAX_depl and not stop:
        if len(tabou) > k:
            tabou.pop(0)
        voisins = [s_p for s_p in [meilleur_voisin(villes, s)] if s_p not in tabou]
        if len(voisins) > 0:
            s_p = voisins[0]
            tabou.append(s_p.copy())
            if distance_total(villes, s_p) < distance_total(villes, msol):
                msol = s_p.copy()
            s = s_p.copy()
        else:
            stop = True

        nb_depl += 1

    return msol, nb_depl




def draw(cities, solution):
    x_coords = [city[1] for city in cities]
    y_coords = [city[2] for city in cities]
    # Plotting the cities
    plt.figure(figsize=(8, 6))
    plt.scatter(x_coords, y_coords, color='red', s=80)  

    # Plotting the route
    for i in range(len(solution) - 1):
        city1 = cities[solution[i] - 1]
        city2 = cities[solution[i + 1] - 1]
        plt.plot([city1[1], city2[1]], [city1[2], city2[2]], color='blue')

    last_city = cities[solution[-1] - 1]
    first_city = cities[solution[0] - 1]
    plt.plot([CENTER[1], first_city[1]], [CENTER[2], first_city[2]], color='blue')
    plt.plot([CENTER[1], last_city[1]], [CENTER[2], last_city[2]], color='blue')

    distance = distance_total(cities, solution)

    plt.xlabel('X Coord')
    plt.ylabel('Y Coord')
    plt.title(f'Voyageur de Commerce\nDistance: {distance}')

    plt.grid(visible=True)
    plt.show()





if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 ex2.py <filename>")
        sys.exit(1)
    filename = sys.argv[1]
    if not os.path.isfile(filename):
        print(f"File '{filename}' not found.")
        sys.exit(1)

    villes, N = lire_fichier(filename)

    #######################################################
    #2.1
    print("Q 2.1) solution initiale au hasard") 
    sol_initiale = solution_initiale_random(N) #sol_initiale = [5, 3, 4, 1, 2] # pour tous les exercice on part de cette solution aléatoire initiale.
    #sol_initiale = [20, 34, 50, 22, 21, 2, 8, 40, 26, 31, 24, 46, 23, 27, 5, 48, 14, 6, 18, 41, 43, 4, 37, 45, 35, 11, 28, 16, 30, 9, 7, 12, 25, 47, 19, 44, 42, 15, 3, 10, 17, 38, 33, 36, 49, 29, 39, 13, 32, 1]
    #sol_initiale = [98, 60, 88, 14, 10, 11, 12, 16, 17, 18, 48, 15, 13, 54, 99, 89, 61, 79, 74, 80, 8, 9, 6, 4, 2, 46, 5, 47, 7, 3, 71, 101, 56, 69, 62, 42, 43, 45, 44, 41, 37, 36, 38, 39, 40, 73, 55, 82, 97, 72, 94, 95, 68, 63, 51, 35, 32, 30, 28, 27, 29, 31, 33, 34, 90, 77, 52, 64, 86, 85, 57, 96, 93, 92, 81, 1, 91, 70, 83, 66, 67, 65, 84, 100, 53, 87, 75, 58, 25, 23, 21, 50, 20, 19, 49, 22, 24, 26, 78, 59, 76]
    #sol_initiale = [76, 59, 78, 26, 24, 22, 49, 19, 20, 50, 21, 23, 25, 58, 84, 66, 67, 65, 57, 96, 85, 86, 64, 52, 77, 90, 34, 33, 31, 29, 27, 28, 30, 32, 35, 51, 63, 68, 94, 72, 73, 42, 40, 39, 38, 36, 37, 41, 44, 45, 43, 62, 69, 82, 55, 97, 95, 93, 92, 81, 1, 91, 70, 99, 89, 56, 101, 71, 3, 7, 5, 2, 4, 6, 46, 47, 9, 8, 80, 74, 79, 61, 54, 83, 100, 53, 87, 75, 60, 88, 10, 11, 12, 13, 15, 48, 18, 17, 16, 14, 98]
    print("solution initiale: ", sol_initiale)

    #2.2
    print("\nQ 2.2) distance parcouru au total de commence de (0,0) et termine à (0,0)") 
    distance = distance_total(villes, sol_initiale)
    print("Distance Parcouru: ", distance)

    #2.3
    print("\nQ 2.3) fonction meilleur_voisin") 
    sol = meilleur_voisin(villes, sol_initiale)
    print("solution: ", sol)
    print("distance: ", distance_total(villes, sol))

    #2.4
    print("\nQ 2.4) Steepest Hill-Climbing") 
    MAX_depl = 150
    start_time = time.time()
    sol, pas = steepest_hill_climbing(villes, sol_initiale, MAX_depl)
    elapsed_time = time.time() - start_time
    print("solution de stephest hill climb: ", sol)
    print("distance: ", distance_total(villes, sol), " avec ", pas, " pas.")
    print(f"Time steepest hill climb: {elapsed_time} seconds")

    start_time = time.time()
    sol_2swap, pas_2swap = steepest_hill_climbing(villes, sol_initiale, MAX_depl, "2-swap")
    elapsed_time = time.time() - start_time
    print("\nsolution de stephest hill climb avec 2-swap: ", sol)
    print("distance avec 2-swap: ", distance_total(villes, sol), " avec ", pas, " pas.")
    print(f"Time steepest hill climb avec 2-swap: {elapsed_time} seconds")

    #avec restart
    print("\nAvec restart")
    MAX_essais = 3
    sol2, pas2 = steepest_hill_climbing_Restart(villes, sol_initiale, MAX_depl, MAX_essais)
    print("solution de stephest hill climb avec restart: ", sol2)
    print("distance avec", MAX_essais, " restart: ", distance_total(villes, sol2), " avec ", pas2, " pas.")

    #2.5
    print("\nQ 2.5) la méthode Tabou") 
    MAX_depl = 150
    k = 20
    start_time = time.time()
    sol_tabu, pas = tabou_search(villes, sol_initiale, MAX_depl, k)
    elapsed_time = time.time() - start_time
    print("solution de Tabou: ", sol_tabu)
    print("distance avec Tabou: ", distance_total(villes, sol_tabu),  " avec ", pas, " pas.")
    print(f"Time Tabou: {elapsed_time} seconds")

    # plot chemin
    sol_opt = sol_tabu
    if distance_total(villes, sol2) < distance_total(villes, sol_tabu):
    	sol_opt = sol2
    draw(villes, sol_opt)