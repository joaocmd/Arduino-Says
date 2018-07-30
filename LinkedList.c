#include "LinkedList.h"

/* Operations on lists */
Node newList() {
  return NULL;
}

void freeList(Node head) {
  Node x = head;
  Node next;
  while (x != NULL) {
    next = x->next;
    free(x);
    x = next;
  }
}

void addNodeToList(Node head, Node node) {
  node->next = head;
  head = node;
}

/* Operations on list nodes */
Node newNode(int value) {
  Node node = (Node) malloc(sizeof(Node));
  node->value = value;
  return node;
}

Node getNextNode(Node node) {
  return node->next;
}

void setNodeValue(Node node, int newValue) {
  node->value = newValue;
}

int getNodeValue(Node node) {
  return node->value;
}
