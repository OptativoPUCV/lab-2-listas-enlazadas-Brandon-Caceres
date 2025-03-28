#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista = (List*)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * list) {
    if(list == NULL || list->head == NULL){
        return NULL;
    }
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if(list == NULL || list->current == NULL) return NULL;
    list->current = list->current->next;

    if (list->current != NULL){
        return list->current->data;
    }
    return NULL;
}

void * lastList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list == NULL || list->current == NULL) return NULL;
    list->current = list->current->prev;
    if (list->current == NULL) return NULL;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node * nuevo_nodo = createNode(data);
    nuevo_nodo->data = data;
    nuevo_nodo->next = list->head;
    nuevo_nodo->prev = NULL;
    if(list->head != NULL){
        list->head->prev = nuevo_nodo;
        list->head = nuevo_nodo;
    }
    else{
        list->head = nuevo_nodo;
        list->tail = nuevo_nodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * nuevo_nodo = createNode(data);
    nuevo_nodo->prev = list->current;
    nuevo_nodo->next = list->current->next;
    if (list->current->next != NULL){
        list->current->next->prev = nuevo_nodo;
    }
    else{
        list->tail = nuevo_nodo;
    }
    list->current->next = nuevo_nodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {\
    if (list == NULL || list->current == NULL) return NULL;
    if (list->current == list->head && list->current == list->tail) { 
        list->head = list->tail = list->current = NULL;
    } 
    else if (list->current == list->head){
        list->head = list->current->next;
        list->head->prev = NULL;
    }
    else if(list->current == list->tail){
        list->tail = list->current->prev;
        list->tail->next = NULL;
    }
    else{
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
    }
    free(list->current);
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}