#include <stdio.h>

// Si RBTREE_H n'a pas encore été défini, le définir
#ifndef RBTREE_H
#define RBTREE_H

// Définition d'un type pour le pointeur vers un arbre rouge-noir
typedef struct RBTree *RBTree;

/**
 * @brief Crée un nouvel arbre rouge-noir
 * @return Un pointeur vers l'arbre rouge-noir créé
 */
RBTree RBTree_create();

/**
 * @brief Libère l'espace mémoire utilisé par l'arbre rouge-noir donné
 * @param tree L'arbre rouge-noir à libérer
 */
void RBTree_free(RBTree tree);

/**
 * @brief Vide l'arbre rouge-noir
 */
void RBTree_destroy();

/**
 * @brief Insère une nouvelle clé dans l'arbre rouge-noir donné
 * @param tree L'arbre rouge-noir dans lequel insérer la clé
 * @param key La clé à insérer
 * @return 0 si l'insertion a réussi, -1 sinon
 */
int RBTree_insert(RBTree tree, void *key);

/**
 * @brief Supprime une clé de l'arbre rouge-noir donné
 * @param tree L'arbre rouge-noir dans lequel supprimer la clé
 * @param key La clé à supprimer
 * @return 0 si la suppression a réussi, -1 sinon
 */
int RBTree_delete(RBTree tree, void *key);

/**
 * @brief Recherche une clé dans l'arbre rouge-noir donné
 * @param tree L'arbre rouge-noir dans lequel rechercher la clé
 * @param key La clé à rechercher
 * @return 0 si la clé n'a pas été trouvée, 1 sinon
*/
int RBTree_search(RBTree tree, void *key);

/**
 * @brief Lit un arbre rouge-noir depuis un fichier
 * @param fname Le nom du fichier à lire
 * @return Un pointeur vers l'arbre rouge-noir lu
 */
RBTree RBTree_read(char *fname);

#endif /* RBTREE_H */

// Si RBTREE_PRIV_H n'a pas encore été défini, le définir
#ifndef RBTREE_PRIV_H
#define RBTREE_PRIV_H

// Définition d'une enumération pour les couleurs
typedef enum
{
	RED, // Rouge
	BLACK // Noir
} RBColor;

// Définition d'un type pour un noeud de l'arbre rouge-noir
typedef struct RBNode {
	char *key; // Clé du noeud
	struct RBNode *parent; // Pointeur vers le parent du noeud
	struct RBNode *left, *right; // Pointeurs vers les enfants du noeud
	RBColor color; // Couleur du noeud
} *RBNode;

// Définition d'un type pour le pointeur vers un arbre rouge-noir
struct RBTree {
	RBNode root; // Racine de l'arbre
	RBNode nil; // Noeud nil
};

/* Fonctions privées */

// Initialise une Node pool à NIL dans la mémoire
static RBNode RBNode_mem_pool = NULL;

/* Section 1: Création et destruction d'un arbre rouge-noir */
/**
 * @brief Détruit le sous-arbre rouge-noir dont la racine est donnée
 * @param tree L'arbre rouge-noir
 * @param node La racine du sous-arbre rouge-noir
 */
static void RBNode_free_subtree(RBTree tree, RBNode node);
/**
 * @brief Crée un nouveau noeud rouge-noir
 * @param tree L'arbre rouge-noir
 * @param key La clé du noeud
 * @return Le noeud créé
 */
static RBNode RBNode_new_node(RBTree tree, void *data);
/**
 * @brief Détruit un noeud rouge-noir et le met dans la Node pool
*/
static void RBNode_free_node(RBNode node);

/* Section 2: Insertion d'un noeud rouge-noir */
/**
 * @brief Corrigé les violations de propriétés de l'arbre rouge-noir
 * @param tree L'arbre rouge-noir
 * @param node Le noeud qui a été inséré
 */
static void RBNode_insert_fix(RBTree tree, RBNode n);
/**
 * @brief Récupère l'oncle du noeud donné
 * @param tree L'arbre rouge-noir
 * @param node Le noeud dont on veut récupérer l'oncle
 * @return L'oncle du noeud
 */
static RBNode RBNode_get_uncle(RBTree tree, RBNode n);

/* Section 3: Suppression d'un noeud rouge-noir */
/**
 * @brief Transplante une node `from` vers une node `to`
 * @param tree L'arbre rouge-noir
 * @param to La node vers laquelle on veut transplanter
 * @param from La node à transplanter
 */
static void RBNode_transplant(RBTree tree, RBNode to, RBNode from);
/**
 * @brief Corrigé les violations de propriétés de l'arbre rouge-noir
 * @param tree L'arbre rouge-noir
 * @param n Le noeud qui a été supprimé
 */
static void RBNode_delete_fix(RBTree tree, RBNode n);

/* Section 4: I/O */
/**
 * @brief Lit un arbre rouge-noir à partir d'un fichier
 * @param tree L'arbre rouge-noir
 * @param next Le noeud suivant à lire
 * @param max La clé maximale
 * @param fp Le fichier à lire
 * @return Le noeud lu
 */
static RBNode RBNode_read_subtree(RBTree tree, RBNode *next, int max, FILE *fp);
/**
 * @brief Lit un noeud rouge-noir à partir d'un fichier
 * @param tree L'arbre rouge-noir
 * @param fp Le fichier à lire
 * @return Le noeud lue
 */
static RBNode RBNode_read_node(RBTree tree, FILE *fp);

/* Section 5: Fonctions de tri */
/**
 * @brief Parcours l'arbre rouge-noir en pre-ordre
 * @param tree L'arbre rouge-noir
 * @param n Le noeud à parcourir
 */
static void RBNode_pre_order(RBTree tree, RBNode n);
/**
 * @brief Parcours l'arbre rouge-noir en in-ordre
 * @param tree L'arbre rouge-noir
 * @param n Le noeud à parcourir
 */
static void RBNode_in_order(RBTree tree, RBNode n);
/**
 * @brief Parcours l'arbre rouge-noir en post-ordre
 * @param tree L'arbre rouge-noir
 * @param n Le noeud à parcourir
 */
static void RBNode_post_order(RBTree tree, RBNode n);

/* Section 6: Recherche d'un noeud rouge-noir */
/**
 * @brief Récupère le noeud par sa clé
 * @param haystack L'arbre rouge-noir
 * @param needle La clé à rechercher
 * @return Le noeud trouvé
 */
static RBNode RBNode_get_node_by_key(RBTree haystack, void *needle);

/* Section 7: Fonctions diverses */
/**
 * @brief Fait rotater l'arbre rouge-noir 
 * @param tree L'arbre rouge-noir
 * @param root La racine de l'arbre à faire rotater
 * @param go_left Si vrai, fait une rotation gauche, sinon fait une rotation droite
 */
static void RBNode_rotate(RBTree tree, RBNode root, int go_left);
/**
 * @brief Récupère le noeud le plus à gauche
 * @param tree L'arbre rouge-noir
 * @param node Le noeud à partir duquel on veut récupérer le noeud le plus à gauche
*/
static RBNode RBNode_min(RBTree tree, RBNode node);
/**
 * @brief Récupère la hauteur de l'arbre rouge-noir
 * @param tree L'arbre rouge-noir
 * @param n Le noeud à partir duquel on veut récupérer la hauteur
 * @return La hauteur de l'arbre rouge-noir
 */
static int RBNode_height(RBTree tree, RBNode n);

#endif /* RBTREE_PRIV_H */
