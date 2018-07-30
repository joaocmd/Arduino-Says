#include "LinkedList.h"

/* Operations on lists */
List newList() {
  List list = (List) malloc(sizeof(List));
  list->head = NULL;
  return list;
}

Node getListHead(List list) {
  return list->head;
}

void addNodeToList(List list, Node node) {
  node->next = list->head;
  list->head = node;
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
