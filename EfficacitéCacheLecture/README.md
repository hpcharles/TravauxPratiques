# Travaux pratique cache donnée


Ce repertoire contient un exemple de code pour mesure l'impact d'un
cache donnée.

## Faire compiler et exécuter un code

Récupérer le code suivant :
* [AccesAuxTableaux.c](AccesAuxTableaux.c)

Lire le code, le compiler et le faire fonctionner sur votre machine :
```shell
  cc -o AccesAuxTableaux  AccesAuxTableaux.c -Wall -Werror
  ./AccesAuxTableaux 1000 100
```

* À quoi servent les données d'entrée ? (par exemple 1000 100)
* Quelles sont les informations fournies par le programme ?
* À quoi servent les options -Wall et -Werror ?

## Utilisation de ```gprof```

Recompiler le programme avec les options suivantes et exécutez les commandes suivantes :

```shell
  cc -o AccesAuxTableaux  AccesAuxTableaux.c -Wall -Werror -pg
  ./AccesAuxTableaux 1000 100
  gprof AccesAuxTableaux
```

* Quelles sont les informations fournies par ```gprof``` ?
* Est-ce utile pour l'utilisation des caches ?

## Impact des niveaux d'optimisation

Exécutez les commandes suivantes :


```shell
  cc -o AccesAuxTableaux  AccesAuxTableaux.c -Wall -Werror -O0
  ./AccesAuxTableaux 1000 1000
  cc -o AccesAuxTableaux  AccesAuxTableaux.c -Wall -Werror -O3
  ./AccesAuxTableaux 1000 1000
```
* Analysez les résultats ?
* Le nombre de clock d'horloge est il plus rapide ?
* En quelle proportion ?

## Effet du cache

Chercher l'influence de la taille du L3 (comparer avec les spec de la machine)

* Utilisez la commande ```lscpu```
* Quelles sont les différentes tailles des caches données (L1, L2, L3) de votre machine ?
* Quelles sont les fréquences minimales et maximales du processeur ?
* Pourquoi est il difficile de faire le lien entre le nombre de clock
  d'horloge et le temps d'exécution d'un programme ?

## Expérimentation

Faire fonctionner le programme sur des tailles de données variées;
autour de la taille du cache L3.

Par exemple si le cache fait 8Mb, faire fonctionner le programme sur
des tailles de 1 à 32 Mb

* ```./AccesAuxTableaux 1000 i``` en faisant varier i de 1 a 32
* Tracer une courbe des résultat des temps des accès aléatoire
* Que peut on conclure ?
<!--

## Efficacité absolue du programme

Chercher à quelle distance on se trouve du débit mémoire pour la partie linéaire
-->