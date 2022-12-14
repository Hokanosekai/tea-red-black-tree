#include "rb-tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

/******************************************************************************
 * Section 1: Creation et Destruction
 *****************************************************************************/
/* Création d'un arbre rouge-noir vide */
RBTree RBTree_create() {
	RBTree ret; // arbre à retourner
	if ((ret = malloc(sizeof(*ret))) == NULL) {
		//fprintf(stderr, "Error: out of memory.\n");
		return NULL;
	}
	/* On ne peut pas utilisé RBNode_new_node() car il veut mettre certaines valeurs
	 * à tree->nil */
	if ((ret->nil = malloc(sizeof(*ret->nil))) == NULL) {
		//fprintf(stderr, "Error: out of memory.\n");
		// Allocation de ret a réussi; on doit le libérer
		free(ret);
		return NULL;
	}
	ret->nil->color = BLACK;
	ret->nil->left = ret->nil;
	ret->nil->right = ret->nil;
	ret->nil->parent = ret->nil;
	ret->root = ret->nil;
	return ret;
}
/* Détruit un arbre rouge-noir. */
void RBTree_free(RBTree tree) {
	RBNode_free_subtree(tree, tree->root);
	RBNode_free_node(tree->nil);
	free(tree);
}
/* Détruit le sous-arbre rouge-noir dont la racine est donnée. */
static void RBNode_free_subtree(RBTree tree, RBNode node) {
	if (node == tree->nil) return; // On ne fait rien si le noeud est NIL
	RBNode_free_subtree(tree, node->left);
	RBNode_free_subtree(tree, node->right);
	RBNode_free_node(node);
}
/* Création d'un noeud rouge. */
static RBNode RBNode_new_node(RBTree tree, void * data) {
	RBNode ret;
	// On prend les noeuds du pool de mémoire si on peut; sinon on alloue
	if (RBNode_mem_pool != NULL) {
		ret = RBNode_mem_pool;
		RBNode_mem_pool = ret->parent;
	} else {
		if ((ret = malloc(sizeof(*ret))) == NULL) {
			//fprintf(stderr, "Error: out of memory.\n");
			return NULL;
		}
	}
	//ret->key = data;
	//ret->key = malloc(sizeof(char)*strlen(data));
	strcpy(ret->key, data);
	ret->parent = tree->nil;
	ret->left = tree->nil;
	ret->right = tree->nil;
	ret->color = RED;
	return ret;
}
/* Libère un noeud dans le pool de mémoire. */
static void RBNode_free_node(RBNode node) {
	node->parent = RBNode_mem_pool;
	RBNode_mem_pool = node;
}
/* Libère tout le pool de mémoire. */
void RBTree_destroy() {
	while (RBNode_mem_pool != NULL) {
		RBNode cur = RBNode_mem_pool;
		RBNode_mem_pool = cur->parent;
		free(cur);
	}
}

/******************************************************************************
 * Section 2: Insertion
 *****************************************************************************/
/* Insert un nouveau noeud dans l'arbre. */
int RBTree_insert(RBTree tree, void * key) {
	// Le noeud que nous allons créer
	RBNode newnode;
	// Le parent du noeud que nous allons créer
	RBNode newparent = tree->nil;
	// La position dans laquelle nous allons mettre newnode
	RBNode pos = tree->root;
	// On cherche la position où insérer le noeud
	while (pos != tree->nil) {
		newparent = pos;
		int cmp = strcmp(key, newparent->key);
		if (cmp < 0) {
			pos = pos->left;
		} else if (cmp > 0) {
			pos = pos->right;
		} else {
			// On ne supporte pas deux noeuds avec la même valeur
			// (on pourrait, mais ce n'est pas le but de cet exemple)
			// /!\ Note: On désactive cette partie pour ne pas voir les messages /!\
			//fprintf(stderr, "Error: node %i already in the tree.\n", key);
			return 0;
		}
	}
	// On crée le noeud
	newnode = RBNode_new_node(tree, key);
	if (newnode == NULL) {
		return 0;
	}
	// On affecte le parent au noeud
	newnode->parent = newparent;
	int cmp = strcmp(key, newparent->key);
	if (newparent == tree->nil) {
		tree->root = newnode;
	} else if (cmp < 0) {
		newparent->left = newnode;
	} else {
		newparent->right = newnode;
	}
	// On corrige les propriétés de l'arbre
	RBNode_insert_fix(tree, newnode);
	return 1;
}
/* Corriges les propriétés violées lors d'une insertion. */
static void RBNode_insert_fix(RBTree tree, RBNode n) {
	RBNode gp = n->parent->parent, // grandparent
		uncle = RBNode_get_uncle(tree, n);
	// Cas 1: le oncle est rouge
	while (n->parent->color == RED && uncle->color == RED) {
		gp->color = RED;
		uncle->color = BLACK;
		n->parent->color = BLACK;
		n = gp;
		gp = n->parent->parent;
		uncle = RBNode_get_uncle(tree, n);
	}
	
	if (n->parent->color == BLACK) {
		if (n == tree->root) n->color = BLACK;
		return;
	}

	// Cas 2: le noeud est "proche" de l'oncle
	if ((n->parent->left == n) == (gp->left == uncle)) {
		RBNode new_n = n->parent;
		RBNode_rotate(tree, new_n, new_n->right == n);
		n = new_n;
	}
	// Cas 3: le noeud est "loin" de l'oncle
	n->parent->color = BLACK;
	gp->color = RED;
	RBNode_rotate(tree, gp, gp->left == uncle);
	tree->root->color = BLACK;
}
/* Récupère l'oncle d'un noeud. */
static RBNode RBNode_get_uncle(RBTree tree, RBNode n) {
	RBNode gp;
	if (n->parent == tree->nil || n->parent->parent == tree->nil) {
		return tree->nil;
	}
	gp = n->parent->parent;
	return (gp->left == n->parent) ? gp->right : gp->left;
}

/******************************************************************************
 * Section 3: Suppression
 *****************************************************************************/
/* Supprime un noeud de l'arbre. */
int RBTree_delete(RBTree tree, void * key) {
	// Le noeud que nous allons supprimer
	RBNode dead = RBNode_get_node_by_key(tree, key);
	// Le noeud où nous allons réparer la structure de l'arbre
	RBNode fixit;
	// La couleur du noeud que nous allons supprimer
	RBColor orig_col = dead->color;
	// Le noeud n'existe pas, on ne peut donc pas le supprimer
	if (dead == tree->nil) {
		// /!\ Note: On désactive cette partie pour ne pas voir les messages /!\
		//fprintf(stderr, "Error: node %i does not exist.\n", key);
		return 0;
	}
	// Ici nous supprimons le noeud comme dans un arbre binaire
	if (dead->left == tree->nil) {
		fixit = dead->right;
		RBNode_transplant(tree, dead, fixit);
	} else if (dead->right == tree->nil) {
		fixit = dead->left;
		RBNode_transplant(tree, dead, fixit);
	} else {
		// Le successeur du noeud que nous allons supprimer
		RBNode successor = RBNode_min(tree, dead->right);
		orig_col = successor->color;
		fixit = successor->right;
		if (successor->parent == dead) {
			fixit->parent = successor;
		} else {
			// On remplace le successeur par son fils droit
			RBNode_transplant(tree, successor, successor->right);
			successor->right = dead->right;
			successor->right->parent = successor;
		}
		RBNode_transplant(tree, dead, successor);
		successor->left = dead->left;
		successor->left->parent = successor;
		successor->color = dead->color;
	}
	RBNode_free_node(dead);
	// Si le noeud que nous avons supprimé était noir, nous devons réparer
	if (orig_col == BLACK) {
		RBNode_delete_fix(tree, fixit);
	}
	return 1;
}
/* Remplace le noeud `from' par le noeud `to'. */
static void RBNode_transplant(RBTree tree, RBNode to, RBNode from) {
	if (to->parent == tree->nil) {
		tree->root = from;
	} else if (to == to->parent->left) {
		to->parent->left = from;
	} else {
		to->parent->right = from;
	}
	from->parent = to->parent;
}
/* Corrige les propriétés violées lors d'une suppression. */
static void RBNode_delete_fix(RBTree tree, RBNode n) {
	/* C'est toujours sûr de changer la racine en noir, et si nous
	 * atteignons un noeud rouge, nous pouvons réparer l'arbre en le
	 * changeant en noir. */
	while (n != tree->root && n->color == BLACK) {
		/* Au lieu de dupliquer le code, nous avons juste un flag
		 * pour tester dans quelle direction nous sommes. */
		int is_left = (n == n->parent->left);
		RBNode sibling = (is_left) ? n->parent->right : n->parent->left;
		// Cas 1: le frère est rouge
		if (sibling->color == RED) {
			sibling->color = BLACK;
			sibling->parent->color = RED;
			RBNode_rotate(tree, sibling->parent, is_left);
			sibling = (is_left) ? n->parent->right : n->parent->right;
		}
		// Cas 2: le frère est noir et ses enfants sont noirs
		if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
			sibling->color = RED;
			n = n->parent;
		} else {
			// Cas 3: le frère est noir et son petit-fils est noir
			if (( is_left && sibling->right->color == BLACK) ||
			    (!is_left && sibling->left->color == BLACK)) {
				if (is_left) {
					sibling->left->color = BLACK;
				} else {
					sibling->right->color = BLACK;
				}
				sibling->color = RED;
				RBNode_rotate(tree, sibling, !is_left);
				sibling = (is_left) ? n->parent->right : n->parent->left;
			} 
			// Cas 4: le frère est noir et son petit-fils est rouge
			sibling->color = n->parent->color;
			n->parent->color = BLACK;
			if (is_left) {
				sibling->right->color = BLACK;
			} else {
				sibling->left->color = BLACK;
			}
			RBNode_rotate(tree, n->parent, is_left);
			// Nous avons terminé, donc nous mettons n à la racine
			n = tree->root;
		}
	}
	n->color = BLACK;
}

/******************************************************************************
 * Section 5: Fonctions de tri
 *****************************************************************************/
/* Trie les éléments de l'arbre en utilisant l'algorithme de tri par pre-processing. */
static void RBNode_pre_order(RBTree tree, RBNode n) {
	if (n == tree->nil) return;
	printf("%c ", n->key);
	RBNode_pre_order(tree, n->left);
	RBNode_pre_order(tree, n->right);
}
/* Trie les éléments de l'arbre en utilisant l'algorithme de tri par in-processing. */
static void RBNode_in_order(RBTree tree, RBNode n) {
	if (n == tree->nil) return;
	RBNode_in_order(tree, n->left);
	printf("%c ", n->key);
	RBNode_in_order(tree, n->right);
}
/* Trie les éléments de l'arbre en utilisant l'algorithme de tri par post-processing. */
static void RBNode_post_order(RBTree tree, RBNode n) {
	if (n == tree->nil) return;
	RBNode_post_order(tree, n->left);
	RBNode_post_order(tree, n->right);
	printf("%c ", n->key);
}

/******************************************************************************
 * Section 6: Recherche
 *****************************************************************************/
/* Recherche un élément avec une clé particulière. */
int RBTree_search(RBTree tree, void * key) {
	RBNode n = RBNode_get_node_by_key(tree, key);
	if (n == tree->nil) {
		//fprintf(stderr, "Error: node %i does not exist.\n", key);
		return 0;
	}
	// Copie le noeud trouvé dans node
	return 1;
}
/* Retourne un noeud avec la clé donnée. */
static RBNode RBNode_get_node_by_key(RBTree haystack, void * needle) {
	RBNode pos = haystack->root; /* our current position */
	while (pos != haystack->nil) {
		int cmp = strcmp(needle, pos->key);
		if (cmp == 0) {
			return pos;
		} else if (cmp < 0) {
			pos = pos->left;
		} else {
			pos = pos->right;
		}
	}
	return haystack->nil;
}

/******************************************************************************
 * Section 7: Fonctions diverses
 *****************************************************************************/
/* Rotate un arbre autour du noeud donné. */
static void RBNode_rotate(RBTree tree, RBNode root, int go_left) {
	/* Aulieu de dupliquer le code, on a juste un flag pour indiquer
	 * la direction du rotation. */
	// Le nouveau noeud racine
	RBNode newroot = (go_left) ? root->right : root->left;
	// On échange les enfants du nouveau noeud racine et l'ancien noeud racine
	if (go_left) {
		root->right = newroot->left;
		if (root->right != tree->nil) {
			root->right->parent = root;
		}
		newroot->left = root;
	} else {
		root->left = newroot->right;
		if (root->left != tree->nil) {
			root->left->parent = root;
		}
		newroot->right = root;
	}
	// On affecte le parent de la nouvelle racine
	newroot->parent = root->parent;
	root->parent = newroot;
	// On met à jour le parent de l'ancien noeud racine pour pointer vers le nouveau noeud racine
	if (newroot->parent == tree->nil) {
		tree->root = newroot;
	} else if (newroot->parent->left == root) {
		newroot->parent->left = newroot;
	} else {
		newroot->parent->right = newroot;
	}
}
/* Retourne le noeud minimum dans l'arbre. */
static RBNode RBNode_min(RBTree tree, RBNode node) {
	while (node->left != tree->nil)
		node = node->left;
	return node;
}
/* Retourne la hauteur de l'arbre récursivement. */
static int RBNode_height(RBTree tree, RBNode n) {
	int l, r;
	if (n == tree->nil) return 0;
	l = RBNode_height(tree, n->left);
	r = RBNode_height(tree, n->right);
	return 1 + ((l > r) ? l : r);
}