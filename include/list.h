#ifndef INPUT_H
#define INPUT_H

typedef struct Box{
    int value;
    float height, width;
    float x1, y1;
    float x2, y2;
}Box;

typedef struct Node{
    Box *box;
    struct Node *prox;
}Node;

typedef struct List{
    int size;
    Node* head;
}List;

List* lst_create();
List* lst_insert(List* list, int number);

#endif