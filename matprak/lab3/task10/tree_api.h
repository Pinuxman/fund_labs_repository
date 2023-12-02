

#ifndef TREE_API_H
#define TREE_API_H

typedef struct Node {
    struct Node* parent;
    struct Node* brother;
    struct Node* son;
    char key;
} Node;

typedef struct {
    Node* root;
}Tree;

int create_node(Node** node, const char key);
int create_child(Node* node, const char key, Node** created_node);
void delete_tree_from_node(Node* node);
int create_tree(const char* str, Tree* tree);
#endif //TASK10_TREE_API_H
