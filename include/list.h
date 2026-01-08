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
    Node *head;
}List;

List* lst_create();
List* lst_append(List* list, int value);
List* lst_generate(int size, int min, int max);
void lst_print(List* list);

#endif