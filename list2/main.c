#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct DblLinkedList {
    unsigned int size;
    Node *head;
    Node *tail;
} DblLinkedList;

DblLinkedList* createDblLinkedList(void) {
    DblLinkedList *tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}

void deleteDblLinkedList(DblLinkedList **list) {
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while(tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void pushFront(DblLinkedList *list, void *data) {
    Node *tmp = (Node*)malloc(sizeof(Node));
    if(tmp == NULL) {
        return;
    }
    tmp->value = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if(list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;
    if(list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
}

void* popFront(DblLinkedList *list) {
    Node *prev;
    void* tmp;
    if(list->head == NULL) {
        return NULL;
    }
    prev = list->head;
    list->head = list->head->next;
    if(list->head) {
        list->head->prev = NULL;
    }
    if(prev == list->tail) {
        list->tail = NULL;
    }
    tmp = prev->value;
    free(prev);
    list->size--;
    return tmp;
}

void pushBack(DblLinkedList *list, void *data) {
    Node *tmp = (Node*)malloc(sizeof(Node));
    if(tmp == NULL) {
        return;
    }
    tmp->value = data;
    tmp->prev = list->tail;
    tmp->next = NULL;
    if(list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;
    if(list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}

void* popBack(DblLinkedList *list) {
    Node *next;
    void* tmp;
    if(list->tail == NULL) {
        return NULL;
    }
    next = list->tail;
    list->tail = list->tail->prev;
    if(list->tail) {
        list->tail->next = NULL;
    }
    if(next == list->head) {
        list->head = NULL;
    }
    tmp = next->value;
    free(next);
    list->size--;
    return tmp;
}

Node* getNth(DblLinkedList *list, unsigned int index) {
    Node *tmp = NULL;
    unsigned int i;

    if(index < list->size/2) {
        i = 0;
        tmp = list->head;
        while(tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    }
    else {
        i = list->size - 1;
        tmp = list->tail;
        while(tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }
    return tmp;
}

void insert(DblLinkedList *list, void *value, unsigned int index) {
    Node *elm = NULL;
    Node *ins = NULL;
    elm = getNth(list, index);
    if (elm == NULL) {
        return;
    }
    ins = (Node*)malloc(sizeof(Node));
    ins->value = value;
    ins->prev = elm;
    ins->next = elm->next;
    if(elm->next) {
        elm->next->prev = ins;
    }
    elm->next = ins;
    if (!elm->prev) {
        list->head = elm;
    }
    if(!elm->next) {
        list->tail = elm;
    }
    list->size++;
}

void* deleteNth(DblLinkedList *list, unsigned int index) {
    Node *elm = NULL;
    Node *tmp = NULL;
    elm = getNth(list, index);
    if (elm == NULL) {
        return NULL;
    }
    if(elm->prev) {
        elm->prev->next = elm->next;
    }
    if(elm->next) {
        elm->next->prev = elm->prev;
    }
    tmp = elm->value;

    if(!elm->prev) {
        list->head = elm->next;
    }
    if(!elm->next) {
        list->tail = elm->prev;
    }
    free(elm);
    list->size--;
    return tmp;
}

void printInt(void *value) {
    printf("%d ", *((int*)value));
}

void printDblLinkedList(DblLinkedList *list, void (*print)(void*)) {
    Node *tmp = list->head;
    while(tmp) {
        print(tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

DblLinkedList* fromArray(void *arr, unsigned int n, unsigned int size) {
    DblLinkedList *tmp = NULL;
    unsigned int i = 0;
    if(arr == NULL) {
        return NULL;
    }

    tmp = createDblLinkedList();
    while(i < n) {
        pushBack(tmp, ((char*)arr + i*size));
        i++;
    }
    return tmp;
}

int main(void) {
    DblLinkedList *list = createDblLinkedList();
    int a, b, c, d, e, f, g;
    a = 10;
    b = 20;
    c = 30;
    d = 40;
    e = 50;
    f = 60;
    g = 70;
    pushFront(list, &a);
    pushFront(list, &b);
    pushFront(list, &c);
    pushBack(list, &d);
    pushBack(list, &e);
    pushBack(list, &f);
    printDblLinkedList(list, printInt);
    printDblLinkedList(list, printInt);
    insert(list, &g, 1);
    printDblLinkedList(list, printInt);
    deleteNth(list, 1);
    printDblLinkedList(list, printInt);
    deleteDblLinkedList(&list);
    return 0;
}
