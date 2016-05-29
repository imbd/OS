#ifndef SRC_AVL_TREE_H_
#define SRC_AVL_TREE_H_

typedef struct {
	void * root;
	int (*comparator)(void * left, void *right);
}avl_tree_t;

avl_tree_t * avl_tree_create(int (*comparator)(void * left, void *right));
void avl_tree_insert(avl_tree_t * tree, void * key, void * value);
void * avl_tree_find(avl_tree_t * tree, void * key);
void avl_tree_remove(avl_tree_t * tree, void * key);



#endif /* SRC_AVL_TREE_H_ */
