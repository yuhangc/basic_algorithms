#include <iostream>

#define RED 0
#define BLACK 1

template <class T>
struct Node {
    T value;
    int color;
    Node *left;
    Node *right;
    Node *parent;

    // constructors
    Node() {
        this->color = BLACK;
        left = right = parent = NULL;
    }

    Node(T val, Node<T> *parent = NULL, int color = RED) {
        this->value = val;
        this->color = color;
        this->parent = parent;
    }

    Node(T val, int color, Node<T> *left, Node<T> *right, Node<T> *parent) {
        this->value = val;
        this->color = color;
        this->left = left;
        this->right = right;
        this->parent = parent;
    }
};

template <class T>
class RedBlackTree {
    private:
        Node<T> *root;
        Node<T> *NIL;

        void print_tree(Node<T> *root) {
            if (root == this->NIL)
                return;

            print_tree(root->left);
            std::cout << root->value << ", ";
            print_tree(root->right);
        }

        Node<T> **insert_node(Node<T> *&node, Node<T> *&parent, T val) {
            if (node == this->NIL) {
                if (parent == this->NIL)
                    node = new Node<T>(val, this->NIL, BLACK);
                else
                    node = new Node<T>(val, parent, RED);
                node->left = this->NIL;
                node->right = this->NIL;
                return &node;
            }

            if (val < node->value)
                return insert_node(node->left, node, val);
            else
                return insert_node(node->right, node, val);
        }

        void left_rotate(Node<T> *node) {
            Node<T> *rchild = node->right;

            // output warning if no right child
            if (rchild == this->NIL) {
                std::cout << "Invalid left rotate!" << std::endl;
                return;
            }

            // left rotate
            rchild->parent = node->parent;

            if (node->parent == this->NIL)
                this->root = rchild;
            else if (node == node->parent->left)
                node->parent->left = rchild;
            else
                node->parent->right = rchild;

            node->parent = node->right;
            node->right = rchild->left;
            rchild->left = node;
        }

        void right_rotate(Node<T> *node) {
            Node<T> *lchild = node->left;

            if (lchild == this->NIL) {
                std::cout << "Invalid right rotate" << std::endl;
                return;
            }

            lchild->parent = node->parent;

            if (node->parent == this->NIL)
                this->root = lchild;
            else if (node->parent->left == node)
                node->parent->left = lchild;
            else
                node->parent->right = lchild;

            node->parent = node->left;
            node->left = lchild->right;
            lchild->right = node;
        }

        void insert_fix(Node<T> *node) {
            // no need to fix if parent is black
            if (node->parent->color == BLACK)
                return;

            if (node->parent == node->parent->parent->left) {
                Node<T> *uncle = node->parent->parent->right;
                if (uncle->color == RED) {
                    // case 1
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    insert_fix(node->parent->parent);
                } else {
                    if (node == node->parent->right) {
                        this->left_rotate(node->parent);
                        insert_fix(node->left);
                    } else {
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        this->right_rotate(node->parent->parent);
                    }
                }
            } else {
                Node<T> *uncle = node->parent->parent->left;
                if (uncle->color == RED) {
                    // case 1
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    insert_fix(node->parent->parent);
                } else {
                    if (node == node->parent->left) {
                        this->right_rotate(node->parent);
                        insert_fix(node->right);
                    } else {
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        this->left_rotate(node->parent->parent);
                    }
                }
            }
        }

        int get_height(Node<T> *node) {
            if (node == this->NIL)
                return 0;

            return 1 + std::max(get_height(node->left), get_height(node->right));
        }

    public:
        // constructor
        RedBlackTree() {
            NIL = new Node<T>();
            root = NIL;
        }

        ~RedBlackTree() {
            delete NIL;
        }

        void insert(T val) {
            Node<T> **node = this->insert_node(this->root, this->NIL, val);
            this->insert_fix((*node));
            this->root->color = BLACK;
        }

        void print_tree() {
            this->print_tree(this->root);
            std::cout << std::endl;
        }

        T get_min() {
            Node<T> *node = this->root;

            if (node == this->NIL) {
                // warn user
                std::cout << "no element in tree!" << std::endl;
                return 0;
            }

            while (node->left != this->NIL)
                node = node->left;

            return node->value;
        }

        T get_max() {
            Node<T> *node = this->root;

            if (node == this->NIL) {
                // warn user
                std::cout << "no element in tree!" << std::endl;
                return 0;
            }

            while (node->right != this->NIL)
                node = node->right;

            return node->value;
        }

        int get_height() {
            return this->get_height(this->root);
        }
};

int main() {
    // create a red black tree
    RedBlackTree<int> *rbt = new RedBlackTree<int>();

    for (int i = 0; i < 100; i++)
        rbt->insert(i);

    std::cout << rbt->get_height() << std::endl;
    rbt->print_tree();

    return 0;
}

