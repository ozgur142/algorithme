# Voyageur de Commerce - OZGUR DOGAN

## Execution Instructions

### Metaheuristique
    ```bash
    python3 metaheuristique.py <nom_fichier>
    ```

    Remplacez `<nom_fichier>` avec le fichier que vous voulez tester. 

    Example:

    ```bash
    python3 metaheuristique.py voyageur_de_commerce/tsp50.txt
    ```

    Pour afficher le graphe d'evolution des resultat de steppest hil climb, vous pouvez décommanté la ligne 101:
    #drawEvolution(voisines)

### PLNE (Programming Linear)
    Pour changer le fichier à tester changer la partie :

        ```bash
        param fichier := path+"tsp5.txt";
        ```
    avec le fichier que vous voulez tester. Assurez-vous que 
        param path := "voyageur_de_commerce/";
    est bien indiqué la chemin vers les fichier.