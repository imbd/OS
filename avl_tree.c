#include "avl_tree.h"
#include <stddef.h>
#include "allocator.h"

typedef struct node
{
    void * key;
    void * value;
    unsigned char height;
    struct node * left;
    struct node * right;
}node_t;

static node_t * node_create(void * key, void * value) {
	node_t * ret = malloc(sizeof(node_t));
	ret->key = key;
	ret->value = value;
	ret->left = ret->right = NULL;
	ret->height = 1;
	return ret;
}

static void node_destroy(node_t * node) {
	free(node);
}

static unsigned char height(node_t * p)
{
    return p ? p->height : 0;
}

static int bfactor(node_t* p)
{
    return height(p->right)-height(p->left);
}

static void fix_height(node_t * p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

static node_t * rotate_right(node_t * p)
{
    node_t * q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}

static node_t * rotate_left(node_t * q)
{
    node_t * p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
}

static node_t * balance(node_t * p)
{
    fix_height(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotate_right(p->right);
        return rotate_left(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotate_left(p->left);
        return rotate_right(p);
    }
    return p;
}

static node_t * insert(node_t * p, node_t * new_node, int (*comparator)(void *, void *)) // insert k key in a tree with p root
{
    if( !p )
    	return new_node;
    if( comparator(new_node->key, p->key) < 0 )
        p->left = insert(p->left, new_node, comparator);
    else
        p->right = insert(p->right, new_node, comparator);
    return balance(p);
}

static node_t * findmin(node_t * p) // find a node with minimal key in a p tree
{
    return p->left?findmin(p->left):p;
}

static node_t * removemin(node_t * p) // deleting a node with minimal key from a p tree
{
    if( p->left==NULL )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

static node_t * remove(node_t * p, void * k, int (*comparator)(void *, void *)) // deleting k key from p tree
{
    if( !p ) return 0;
    if( comparator(k, p->key) < 0 )
        p->left = remove(p->left, k, comparator);
    else if( comparator(k, p->key) > 0 )
        p->right = remove(p->right, k, comparator);
    else //  k == p->key
    {
        node_t * q = p->left;
        node_t * r = p->right;
        node_destroy(p);
        if( !r ) return q;
        node_t * min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

static node_t * find(node_t * root, void * key, int (*comparator)(void *, void *)) {
	while(1) {
		if( comparator(key, root->key) < 0) {
			root = root->left;
			continue;
		}
		if( comparator(key, root->key) > 0) {
			root = root->right;
			continue;
		}
		break;
	}
	return root;
}

avl_tree_t * avl_tree_create(int (*comparator)(void * left, void *right)){
	avl_tree_t * tree = malloc(sizeof(avl_tree_t));
	tree->comparator = comparator;
	tree->root = NULL;
	return tree;
}

void avl_tree_insert(avl_tree_t * tree, void * key, void * value) {
	tree->root = insert(tree->root, node_create(key, value), tree->comparator);
}

void * avl_tree_find(avl_tree_t * tree, void * key) {
	return find(tree->root, key, tree->comparator)->value;
}

void avl_tree_remove(avl_tree_t * tree, void * key){
	remove(tree->root, key, tree->comparator);
}
