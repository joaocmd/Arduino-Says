#include "LinkedList.h"

/* Operations on lists */
List newList() {
    List x = (List) malloc(sizeof(struct list));
    x->head = NULL;
    x->tail = NULL;
    return x;
}

void freeList(List list) {
    Node x = list->head;
    Node next;
    while (x != NULL) {
        next = x->next;
        free(x);
        x = next;
    }
    free(list);
}

Node getListHead(List list) {
    return list->head;
}

void addNodeToList(List list, Node node) {
    if (list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
}

/* Operations on list nodes */
Node newNode(int value) {
    Node node = (Node) malloc(sizeof(struct node));
    node->value = value;
    node->next = NULL;
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
