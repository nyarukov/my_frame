#include "..\include\def.h"

SA_INLINE void sa_list_init(struct sa_list *list)
{
    list->next = list;
    list->prev = list;
}

/**
 * @brief 在list的前面插入一个节点
 * 
 * @param list 
 * @param node 
 * @return no 
 */
SA_INLINE void sa_list_insert_before(struct sa_list *list, struct sa_list *node)
{
    list->prev->next = node;
    node->prev = list->prev;
    node->next = list;
    list->prev = node;
}
/**
 * @brief 在list的后面插入一个节点
 * 
 * @param list 
 * @param node 
 * @return no 
 */
SA_INLINE void sa_list_insert_later(struct sa_list *list, struct sa_list *node)
{
    list->next->prev = node;
    node->next = list->next;
    node->prev = list;
    list->next = node;
}

SA_INLINE void sa_list_remove(struct sa_list *node)
{

    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = node->prev = node;
}
