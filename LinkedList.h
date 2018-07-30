#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef struct node *Node;

struct node {
  int value;
  Node next;
};

#ifdef __cplusplus
extern "C" {
#endif
/* Operations on lists */
Node newList();
void freeList(Node head);
void addNodeToList(Node head, Node node);

/* Operations on list nodes */
Node newNode(int value);
Node getNextNode(Node node);
void setNodeValue(Node node, int newValue);
int getNodeValue(Node node);
#ifdef __cplusplus
}
#endif
#endif
