#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "list.h"

List *list_construct(){
    List *l = (List *)calloc(1,sizeof(List));
    l->size = 0;
    l->head = NULL;
    l->last = NULL;
    return l;
}

void list_push_front(List *l, data_type data){
    l->size = l->size + 1;
    l->head = node_construct(data,NULL,l->head);
    if(l->last == NULL){
        l->last = l->head;
    }else{
         l->head->next->prev = l->head;
    }
}

int list_size(List *l){
    return l->size;
}

void list_print(List *l, void (*print_fn)(data_type)){
    Node *n = l->head;
    printf("[");
    for(int i = 0;i<l->size;i++){
        print_fn(n->value);
        n = n->next;
        if(i != (l->size-1)){
            printf(", ");
        }
    }
    printf("]");
}

void list_destroy(List *l){
    Node *n = l->head,*next;
    for(int i = 0; i<list_size(l);i++){
        next = n->next;
        node_destroy(n);
        n = next;
    }
    free(l);
}

void list_print_reverse(List *l, void (*print_fn)(data_type)){
    Node *n = l->last;
    printf("[");
    for(int i = 0;i<l->size;i++){
        print_fn(n->value);
        n = n->prev;
        if(i != (l->size-1)){
            printf(", ");
        }
    }
    printf("]");
}

data_type list_pop_front(List *l){
    if(l->size > 0){
        Node *n = l->head;
        data_type d = l->head->value;
        l->head = l->head->next;
        node_destroy(n);
        l->size = l->size - 1;
        if(l->size == 0){
            l->last = NULL;
        }else{
            l->head->prev = NULL;
        }
        return d;
    }else{
       //Não soube usar o exit mas deveria dar um erro fatal
       printf("\nLista Vazia\n");
       data_type d = l->head->value;
       return d;
    }   
}

void list_push_back(List *l, data_type data){
    Node *n = l->last;
    l->size = l->size + 1;
    l->last = node_construct(data,l->last,NULL);
    if(l->head == NULL){
        l->head = l->last;
    }else{
        n->next = l->last;
    }
}

data_type list_pop_back(List *l){
    if(l->size > 0){
        Node *n = l->last;
        data_type d = l->last->value;
        l->last = l->last->prev;
        node_destroy(n);
        l->size = l->size - 1;
        if(l->size == 0){
            l->last = NULL;
        }else{
            l->last->next = NULL;
        }
        return d;
    }else{
       //Não soube usar o exit mas deveria dar um erro fatal
       printf("\nLista Vazia\n");
       data_type d = l->head->value;
       return d;
    } 
}

ListIterator *list_front_iterator(List *l){
    ListIterator *it = (ListIterator *)calloc(1,sizeof(ListIterator));
    it->current = l->head;
    return it;
}

ListIterator *list_back_iterator(List *l){
    ListIterator *it = (ListIterator *)calloc(1,sizeof(ListIterator));
    it->current = l->last;
    return it;
}

data_type *list_iterator_next(ListIterator *it){
    data_type *data = &(it->current->value);
    it->current = it->current->next;
    return data;
}

data_type *list_iterator_previous(ListIterator *it){
    data_type *data = &(it->current->value);
    it->current = it->current->prev;
    return data;
}

bool list_iterator_is_over(ListIterator *it){
    if(it->current == NULL){
        return 1;
    }else{
        return 0;
    }
}

void list_iterator_destroy(ListIterator *it){
    free(it);
}