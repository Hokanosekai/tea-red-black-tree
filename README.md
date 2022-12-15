# RED BLACK TREE

## TODO

- [ ] mesurer le temps d'execution AVL TREE :
  - [ ] insertion
  - [ ] suppression
  - [ ] recherche
  - [ ] insertion `char`
  - [ ] suppression `char`
  - [ ] recherche `char`
- [x] mesurer le temps d'execution RED BLACK TREE :
  - [x] insertion
  - [x] suppression
  - [x] recherche
  - [ ] insertion `char`
  - [ ] suppression `char`
  - [ ] recherche `char`
- [ ] tracer les courbes de temps d'execution
- [ ] comparer les courbes de temps d'execution

> On va mesurer la temps d'éxécution sur un arbre de 10k noeuds à 1M noeuds et cela sur 10 itérations, on va faire la moyenne des temps d'éxécution pour chaque itération. Faudrait le faire pour de data de type `char` et `int`.

> Dans le fichier `test-rb-tree.c` on rempli un tableau d'entiers aléatoires entre 0 et 100k. On peut faire pareil pour des `char` en remplissant un tableau de `char` aléatoires.

> Pour les test pour l'arbre AVL, on peut juste réutiliser le code des test pour l'arbre rouge noir.

## Description

This is a simple implementation of a red black tree in C.

- [x] Insertion
- [x] Search
- [x] Deletion

## Usage

Start by downloading the source code and compiling it:

```bash
git clone
cd tea-red-black-tree
```
Then, create a new folder along the `src` folder and compile the source code:

```bash
$ mkdir debug
$ cd debug
$ cmake ../src/ -DCMAKE_INSTALL_PREFIX=../tmp -DCMAKE_BUILD_TYPE=Debug
$ make install
```
You can now run the tests:

```bash
$ ./test-rb-tree
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* [Red Black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
* [Help to visualize](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

## Author

* **Bash62** - *Initial work* - [bash62](https://github.com/bash62)
* **Hokanosekai** - *Initial work* - [Hokanosekai](https://github.com/Hokanosekai)
* **Moulo777** - *Initial work* - [Moulo777](https://github.com/Moulo777)
* **arthurAlade** - *Initial work* - [arthurAlade](https://github.com/arthurAlade)