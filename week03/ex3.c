#include <stdio.h>

struct node {
    int* value;
    struct node* next_node;
};

struct linked_list {
    int size;
    struct node* head;
};

void print_list(struct linked_list ll) {
    struct node* current_node = ll.head;
    if(ll.size>0) {
        printf("%d ", *current_node->value);
    }
    else {
        return;
    }

    for(int i = 0; i<ll.size; i++) {
        current_node = current_node->next_node;
        printf("%d ", *current_node->value);
    }
    printf("\n");
}

void insert_node(int v, int idx, struct linked_list ll) {
    if(idx>=ll.size){printf("ERROR: Incorrect index"); return;}

    struct node* current_node = ll.head;
    struct node* new_node;
    new_node->value = &v;

    for(int i = 0; i<idx; i++) {
        current_node = current_node->next_node;
    }
    new_node->next_node = current_node->next_node;
    current_node->next_node = new_node;
    ll.size++;
}

void delete_node(int idx, struct linked_list ll) {
    if(idx>=ll.size){printf("ERROR: Incorrect index"); return;}
    ll.size--;
    if(idx==0){ll.head = ll.head->next_node; return;}

    struct node* current_node = ll.head;
    for(int i = 0; i<idx-1; i++){current_node = current_node->next_node;}
    current_node->next_node = current_node->next_node->next_node;
}

int main()
{
    struct linked_kist ls;
    ls.size = 0;
    insert_node(3, 0, ls);
    print_list(ls);
    return 0;
}