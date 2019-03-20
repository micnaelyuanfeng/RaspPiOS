#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_entry
{
    struct list_entry* p_prev;
    struct list_entry* p_next;
}list_entry_t;

bool      list_add(list_entry_t *this_element, list_entry_t* list_head);
bool      list_del(list_entry_t *this_element, list_entry_t* list_head); 
void*     list_search(list_entry_t* this_element, list_entry_t* list_head);

#endif