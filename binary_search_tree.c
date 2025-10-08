#include<stdio.h>
#include<stdlib.h>

struct node {
        struct node* right;
        struct node* left;
        int val;
};

struct bin_tree {
        struct node* root;
};

struct bin_tree* init_tree(int value) {
// init a bin tree
        struct node* root_origin = malloc(sizeof(struct node));
        root_origin->val = value;
        root_origin->right = NULL;
        root_origin->left = NULL;
        struct bin_tree* tree = malloc(sizeof(struct bin_tree));
        tree->root = root_origin;
        return tree;
}


void get_val_node(struct node* tree_node) {
        int node_value = tree_node->val;
        printf("%d\n", node_value);
};


void insert(struct node* current, int value_to_insert) {
// da refattorizzare assolutamente porco due
        if(value_to_insert < current->val) {
                if(current->left == NULL) {
                        struct node* node_to_insert = malloc(sizeof(struct node));
                        node_to_insert->val = value_to_insert;
                        current->left = node_to_insert;
                } else {
                        insert(current->left,value_to_insert);
                }
        } else {
                if(current->right == NULL) {
                        struct node* node_to_insert = malloc(sizeof(struct node));
                        node_to_insert->val = value_to_insert;
                        current->right = node_to_insert;
                } else {
                        insert(current->right,value_to_insert);
                }
        }
};

struct node* findParent(int value, struct node* root) {
        if (value == root->val) {
                return NULL;
        } else if(value  < root->val) {
                if(root->left == NULL) {
                        return NULL;
                } else if(root->left->val == value) {
                        return root;
                } else {
                        return findParent(value, root->left);
                }
        } else {
                if(root->right == NULL) {
                        return NULL;
                } else if(root->right->val == value) {
                        return root;
                } else {
                        return findParent(value, root->right);
                }
        };
};


struct node* findNode(struct node* root, int value) {
        if(root == NULL) {
                return NULL;
        } else if(root->val == value) {
                return root;
        } else if (value < root->val) {
                return findNode(root->left, value);
        } else {
                return findNode(root->right, value);
        }
}

int findMin(struct node* root) {
        if (root->left == NULL) {
                return root->val;
        };

        findMin(root->left);
};


int findMax(struct node* root) {
        if (root->right == NULL) {
                return root->val;
        };

        findMax(root->right);
};

void delete_value(struct node* root,int value) {
        struct node* nodeToRemove = findNode(root,value);
        if(nodeToRemove == NULL) return;
        printf("ci arriva qui\n");
        struct node* parent = findParent(value, root);
        if(nodeToRemove == root) {
                printf("è il root\n");
                return;
        } else if(nodeToRemove->left == NULL && nodeToRemove->right == NULL) {
                printf("primo caso\n");
                if(nodeToRemove->val < parent->val) {
                        parent->left = NULL;
                } else {
                        parent->right = NULL;
                }
                free(nodeToRemove);
        } else if(nodeToRemove->left == NULL && nodeToRemove->right != NULL) {
                printf("secondo caso\n");
                if(nodeToRemove->val < parent->val) {
                        parent->left = nodeToRemove->right;
                } else {
                        parent->right = nodeToRemove->right;
                }
                free(nodeToRemove);
        } else if(nodeToRemove->left != NULL && nodeToRemove->right == NULL) {
                printf("terzo caso\n");
                if(nodeToRemove->val < parent->val) {
                        parent->left = nodeToRemove->left;
                } else {
                        parent->right = nodeToRemove->left;
                }
                free(nodeToRemove);
        } else {
                printf("quarto caso\n");
                struct node* largestVal = nodeToRemove->left;
                while(largestVal->right != NULL) {
                        largestVal = largestVal->right;
                };
                findParent(largestVal->val, largestVal)->right = NULL;
                nodeToRemove->val = largestVal->val;
                free(largestVal);
        }
};

int main(){
        struct bin_tree* bin_search = init_tree(15);
        get_val_node(bin_search->root);
        insert(bin_search->root, 30);
        insert(bin_search->root,14);
        insert(bin_search->root,50);
        insert(bin_search->root,60);
        insert(bin_search->root,3);
        insert(bin_search->root,4);
        struct node* parent_test = findParent(60, bin_search->root);
        if(parent_test != NULL) {
                printf("parent->");
                get_val_node(parent_test);
        }

        struct node* node_ref = findNode(bin_search->root, 60);
        if(parent_test != NULL) {
                printf("ref->");
                 get_val_node(node_ref);
        }

        printf("\nmin val: %d\n",findMin(bin_search->root));
        printf("\nmax val: %d\n",findMax(bin_search->root));
        printf("rigth: %d\nleft: %d", bin_search->root->right->val, bin_search->root->left->val);
        printf("\ndelete 14");
        delete_value(bin_search->root, 14);
        struct node* node_ref_del = findNode(bin_search->root, 14);
        if(node_ref_del != NULL) {
                printf("ref->");
                 get_val_node(node_ref_del);
        } else {
                printf("not found\n");
        }
return 0;
}
