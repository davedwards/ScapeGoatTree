
#include <iostream>
#include <cmath>
#include <vector>

template <typename T>
class ScapegoatTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int size; // size of the subtree
        Node(T value) : data(value), left(nullptr), right(nullptr), size(1) {}
    };

    Node* root;
    double alpha; // balance factor
    int maxNodes;

    // Helper function to compute size of the node
    int size(Node* node) {
        return node ? node->size : 0;
    }

    // Helper function to update size of the node
    void updateSize(Node* node) {
        if (node) {
            node->size = size(node->left) + size(node->right) + 1;
        }
    }

    // Helper function to perform right rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateSize(y);
        updateSize(x);
        return x;
    }

    // Helper function to perform left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateSize(x);
        updateSize(y);
        return y;
    }

    // Insert function
    Node* insert(Node* node, T value) {
        // Standard BST insertion
        if (!node) return new Node(value);
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            return node; // Duplicates not allowed
        }

        updateSize(node);
        
        // Check if the tree needs balancing
        if (size(node) > maxNodes * alpha) {
            return rebuild(node);
        }

        return node;
    }

    // Rebuild the scapegoat tree from the given node
    Node* rebuild(Node* node) {
        std::vector<T> elements;
        storeInOrder(node, elements);
        return buildTree(elements, 0, elements.size() - 1);
    }

    // Store the elements in in-order traversal
    void storeInOrder(Node* node, std::vector<T>& elements) {
        if (!node) return;
        storeInOrder(node->left, elements);
        elements.push_back(node->data);
        storeInOrder(node->right, elements);
    }

    // Build a balanced BST from sorted elements
    Node* buildTree(std::vector<T>& elements, int start, int end) {
        if (start > end) return nullptr;
        int mid = (start + end) / 2;
        Node* node = new Node(elements[mid]);
        node->left = buildTree(elements, start, mid - 1);
        node->right = buildTree(elements, mid + 1, end);
        updateSize(node);
        return node;
    }

    // Find the minimum value node
    Node* findMin(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // Deletion function
    Node* deleteNode(Node* node, T value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            // Node with only one child or no child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        updateSize(node);
        
        // Check if the tree needs balancing after deletion
        if (size(node) < maxNodes * alpha) {
            return rebuild(node);
        }

        return node;
    }

    // Recursive destructor
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    ScapegoatTree(double alpha = 0.57) : root(nullptr), alpha(alpha), maxNodes(0) {}

    void insert(T value) {
        root = insert(root, value);
        maxNodes++;
    }

    void remove(T value) {
        root = deleteNode(root, value);
        maxNodes--;
    }

    bool search(T value) {
        Node* current = root;
        while (current) {
            if (value == current->data) return true;
            current = (value < current->data) ? current->left : current->right;
        }
        return false;
    }

    void inOrder() {
        inOrder(root);
        std::cout << std::endl;
    }

private:
    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

    ~ScapegoatTree() {
        clear(root); // Call clear to free memory
    }
};

int main() {
    ScapegoatTree<int> tree;

    // Insert elements
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(30);
    tree.insert(25);
    
    std::cout << "In-order Traversal: ";
    tree.inOrder(); // Should print the elements in sorted order

    // Search for elements
    std::cout << "Searching for 15: " << (tree.search(15) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 100: " << (tree.search(100) ? "Found" : "Not Found") << std::endl;

    // Remove an element
    tree.remove(15);
    std::cout << "In-order Traversal after deleting 15: ";
    tree.inOrder();

    return 0;
}

