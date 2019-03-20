#include "Include\types.h"
#include "Include\list.h"

bool list_add(list_entry_t* this_element, list_entry_t* list_head)
{
    if(list_head != NULL)
    {
        list_head = this_element;

        this_element->p_next = NULL;
        this_element->p_prev = NULL;
    }
    else
    {
        list_entry_t* curr = list_head;

        for(; curr->p_next != NULL; curr = curr->p_next);

        curr->p_next = this_element;

        this_element->p_prev = curr;
        this_element->p_next = NULL;
    }

    return 0;
}

bool list_del(list_entry_t *this_element, list_entry_t* list_head)
{
    bool result = -1;

    if(list_search(this_element, list_head) != NULL)
    {
        if(list_head == this_element)
        {
            list_head = this_element->p_next;
            this_element->p_next->p_prev = list_head;

            this_element->p_prev = NULL;
            this_element->p_next = NULL;
        }
        else if(this_element->p_next == NULL)
        {
            this_element->p_prev->p_next = NULL;
            
            this_element->p_next = NULL;
            this_element->p_next = NULL;
        }
        else
        {
            this_element->p_prev->p_next = this_element->p_next;
            this_element->p_next->p_prev = this_element->p_prev;

            this_element->p_next = NULL;
            this_element->p_prev = NULL;
        }
        
    }

    return result;
}

void* list_search(list_entry_t* this_element, list_entry_t* list_head)
{
    list_entry_t* curr = list_head;

    for(; curr != NULL; curr = curr->p_next)
    {
        if(curr == this_element)
        {
            return curr;
        }
    }

    return NULL;
}