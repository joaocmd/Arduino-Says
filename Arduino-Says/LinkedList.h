#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef struct node *Node;
typedef struct list *List;

struct node {
    int value;
    Node next;
};

struct list {
    Node head, tail;
};

#ifdef __cplusplus
extern "C" {
#endif
/* Operations on lists */
List newList();
void freeList(List list);
Node getListHead(List list);
void addNodeToList(List list, Node node);

/* Operations on list nodes */
Node newNode(int value);
Node getNextNode(Node node);
void setNodeValue(Node node, int newValue);
int getNodeValue(Node node);
#ifdef __cplusplus
}
#endif
#endif
