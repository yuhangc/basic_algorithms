#include <iostream>

template <class T>
struct TreeNode {
    T value;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    
    // constructor
    TreeNode(T val, TreeNode<T> *parent = NULL) {
        this->value = val;
        this->parent = parent;
    }
    
    TreeNode(T val, TreeNode<T> *left, TreeNode<T> *right, TreeNode<T> *parent) {
        this->value = val;
        this->left = left;
        this->right = right;
        this->parent = parent;
    }
};

template <class T>
class BST {
    private:
        TreeNode<T> *root;
    
        void print_tree(TreeNode<T> *root) {
            if (root == NULL)
                return;
                
            print_tree(root->left);
            std::cout << root->value << ", ";
            print_tree(root->right);
        }
        
        TreeNode<T> **search_tree(TreeNode<T> *&root, T val) {
            if (root == NULL || root->value == val)
                return &root;
            
            if (val < root->value)
                return search_tree(root->left, val);
            else
                return search_tree(root->right, val);
        }
        
        void add(TreeNode<T> *&root, TreeNode<T> *parent, T val) {
            if (root == NULL) {
                root = new TreeNode<T>(val, parent);
            } else {
                if (val < root->value)
                    add(root->left, root, val);
                else
                    add(root->right, root, val);
            }
        }
        
        bool delete_node(TreeNode<T> *&node) {
            if (node == NULL)
                return false;
                
            // if node is a leaf
            if (node->left == NULL && node->right == NULL) {
                delete node;
                node = NULL;
                return true;
            }
            
            // only has left tree
            if (node->right == NULL) {
                if (node->parent != NULL) {
                    if (node == node->parent->left)
                        node->parent->left = node->left;
                    else
                        node->parent->right = node->left;
                } else {
                    this->root = node->left;
                }
                
                node->left->parent = node->parent;
                delete node;
                node = NULL;
                return true;
            } else {
                TreeNode<T> **succ = &node->right;
                while ((*succ)->left != NULL)
                    succ = &(*succ)->left;
                
                node->value = (*succ)->value;
                return delete_node((*succ));
            }
        }
        
    public:
        BST() {
            this->root = NULL;
        }
        
        void print_tree() {
            this->print_tree(this->root);
            std::cout << std::endl;
        }
        
        void add(T val) {
            this->add(this->root, NULL, val);
        }
        
        T get_min() {
            TreeNode<T> *node = this->root;
            
            if (node == NULL) {
                // warn user
                std::cout << "no element in tree!" << std::endl;
                return 0;
            }
            
            while (node->left != NULL)
                node = node->left;
                
            return node->value;
        }
        
        T get_max() {
            TreeNode<T> *node = this->root;
            
            if (node == NULL) {
                // warn user
                std::cout << "no element in tree!" << std::endl;
                return 0;
            }
            
            while (node->right != NULL)
                node = node->right;
                
            return node->value;
        }
        
        bool delete_val(T val) {
            TreeNode<T> **node = this->search_tree(this->root, val);
            
            return this->delete_node((*node));
        }
};

int main() {
	// create a BST
	BST<int> *bst = new BST<int>();
	bst->add(11);
    bst->add(1);
    bst->add(6);
    bst->add(-1);
    bst->add(-10);
    bst->add(100);
    
    bst->print_tree();
    std::cout << bst->get_min() << "  " << bst->get_max() << std::endl;
    
    bst->delete_val(11);
    bst->delete_val(-10);
    bst->print_tree();
    
    std::cout << bst->get_min() << "  " << bst->get_max() << std::endl;
	
	return 0;
}
