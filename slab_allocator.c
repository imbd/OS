
#include "slab_allocator.h"
#include <stddef.h>
#include "list.h"
#include "memory.h"
#include "utils.h"
#include "buddy_allocator.h"
#include "print.h"

#define SLAB_BIG_BOUND ( PAGE_SIZE >> 3)

typedef struct {
	struct list_head list_desc;
}slab_small_descriptor_t;

typedef struct {
	struct list_head list_desc;
	virt_t addr;
}slab_big_descriptor_t;


static slab_pool * helper_desc_slab_pool = NULL;
static slab_t * slab_pool_alloc = NULL;

static void helper_desc_slab_pool_check_create(){
	if(helper_desc_slab_pool == NULL)
		helper_desc_slab_pool = slab_pool_init(MAX( (sizeof (slab_big_descriptor_t)), (sizeof(slab_t))), 1);
}

static void * helper_desc_slab_pool_allocate(){
	helper_desc_slab_pool_check_create();
	return slab_pool_allocate(helper_desc_slab_pool);
}

static void helper_desc_slab_pool_free(void * ptr) {
	helper_desc_slab_pool_check_create();
	slab_pool_free(ptr);
}

static bool is_slab_empty(slab_t * slab){
	return list_empty(&slab->desc_list);
}

static slab_pool *  new_slab_pool(){
	if(slab_pool_alloc == NULL || is_slab_empty(slab_pool_alloc)){
		slab_pool_alloc = slab_init(sizeof(slab_pool), 1);
	}
	return (slab_pool *) slab_allocate(slab_pool_alloc);
}

static int is_small(uint64_t size){
	return size < SLAB_BIG_BOUND;
}

static slab_t * slab_init_small(uint64_t size, uint64_t align){
	void * page = buddy_allocate_page(0);
	if(page == NULL){
		return NULL;
	}
	slab_t * ret = (slab_t *) page;
	buddy_set_slab(page, ret);
	ret->size = size;
	list_init(&ret->desc_list);
	list_init(&ret->slab_list);
	ret->pool_ptr = NULL;
	for(virt_t i = get_aligned_addr(((virt_t)page) + sizeof(slab_t), align);
			   i + sizeof(slab_small_descriptor_t) + size  <= ((virt_t)page) + PAGE_SIZE ;
			   i = get_aligned_addr(i + sizeof(slab_small_descriptor_t) + size,
					   align) ){
		slab_small_descriptor_t * new_desc = (slab_small_descriptor_t * ) i;
		list_init(&new_desc->list_desc);
		list_add(&new_desc->list_desc, &ret->desc_list);
	}
	return ret;
}

static void * slab_allocate_small(slab_t * slab){
	if(list_empty(&slab->desc_list)){
		return NULL;
	}
	slab_small_descriptor_t * ret_desc = LIST_ENTRY(slab->desc_list.next, slab_small_descriptor_t, list_desc);
	list_del(&ret_desc->list_desc);

	return (void *)(((uint64_t )ret_desc) + sizeof (slab_small_descriptor_t));
}

static void slab_free_small(slab_t * slab, void * addr){
	slab_small_descriptor_t * ins_desc = (slab_small_descriptor_t * )(((uint64_t)addr) - sizeof(slab_small_descriptor_t));
	list_add(&ins_desc->list_desc, &slab->desc_list);
}

static void slab_create_big_desc(slab_t * big_slab, virt_t addr){
	slab_big_descriptor_t * new_desc = (slab_big_descriptor_t * ) helper_desc_slab_pool_allocate();
	list_init(&new_desc->list_desc);
	new_desc->addr = addr;
	list_add(&new_desc->list_desc, &big_slab->desc_list);
}

static slab_t * slab_init_big(uint64_t size, uint64_t align){
	slab_t * ret = (slab_t * ) helper_desc_slab_pool_allocate();
	ret->size = size;
	list_init(&ret->desc_list);
	list_init(&ret->slab_list);
	ret->pool_ptr = NULL;
	void * page = buddy_allocate_page(0);
	if(page == NULL){
		return NULL;
	}
	buddy_set_slab(page, ret);
	for(virt_t i = get_aligned_addr((virt_t) page, align);
			i <= ((virt_t)page) + PAGE_SIZE - size;
			i = get_aligned_addr(i + size, align)){
		slab_create_big_desc(ret, i);
	}
	return ret;
}

static void * slab_allocate_big(slab_t * slab){
	if(list_empty(&slab->desc_list)){
		return NULL;
	}
	slab_big_descriptor_t * ret_desc = LIST_ENTRY(slab->desc_list.next, slab_big_descriptor_t, list_desc);
	list_del(&ret_desc->list_desc);
	void * ret =  (void *)ret_desc->addr;
	helper_desc_slab_pool_free(ret_desc);
	return ret;
}

static void slab_free_big(slab_t * slab, void * addr){
	slab_create_big_desc(slab, (virt_t) addr);
}

slab_t * slab_init(uint64_t size, uint64_t align){
	if(size >= PAGE_SIZE) {
		return NULL;
	}
	if(is_small(size)){
		return slab_init_small(size, align);
	} else {
		return slab_init_big(size, align);
	}
}

void * slab_allocate(slab_t * slab){
	void * ret = NULL;
	if(is_small(slab->size)){
		ret = slab_allocate_small(slab);
	} else {
		ret = slab_allocate_big(slab);
	}
	if(is_slab_empty(slab)) {
		list_del(&slab->slab_list);
	}
	return ret;
}

void slab_free(slab_t * slab, void * addr){
	if(slab->pool_ptr != NULL && is_slab_empty(slab)){
		slab_pool * pool = (slab_pool * ) slab->pool_ptr ;
		list_add(&slab->slab_list, &pool->slab_list_head);
	}
	if(is_small(slab->size)){
		slab_free_small(slab, addr);
	} else {
		slab_free_big(slab, addr);
	}
}

slab_pool * slab_pool_init(uint64_t size, uint64_t align) {
	slab_pool * pool = new_slab_pool();
	pool->size = size;
	pool->align = align;
	list_init(&pool->slab_list_head);
	return pool;
}


void * slab_pool_allocate(slab_pool * pool) {
	if(list_empty(&pool->slab_list_head)) {
		slab_t * new_slab = slab_init(pool->size, pool->align);
		new_slab->pool_ptr = pool;

		list_add(&new_slab->slab_list, &pool->slab_list_head);
	}
	return slab_allocate(LIST_ENTRY(pool->slab_list_head.next, slab_t, slab_list));
}

void slab_pool_free(void * addr){
	slab_free(buddy_get_slab(addr), addr);
}
