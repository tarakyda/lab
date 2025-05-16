#include <iostream>
#include <fstream>
#include <vector>
#include <initializer_list>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val, Node* p = nullptr) : value(val), left(nullptr), right(nullptr), parent(p) {}
};

class BSTree {
private:
    Node* root;

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    bool addElement(Node*& node, int value, Node* parent = nullptr) {
        if (!node) {
            node = new Node(value, parent);
            return true;
        }
        if (value < node->value) return addElement(node->left, value, node);
        if (value > node->value) return addElement(node->right, value, node);
        return false;
    }

    bool deleteElement(Node*& node, int value) {
        if (!node) return false;
        if (value < node->value) return deleteElement(node->left, value);
        if (value > node->value) return deleteElement(node->right, value);

        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        } else if (!node->left) {
            Node* temp = node;
            node = node->right;
            node->parent = temp->parent;
            delete temp;
        } else if (!node->right) {
            Node* temp = node;
            node = node->left;
            node->parent = temp->parent;
            delete temp;
        } else {
            Node* minRight = findMin(node->right);
            node->value = minRight->value;
            deleteElement(node->right, minRight->value);
        }
        return true;
    }

    bool findElement(Node* node, int value) const {
        if (!node) return false;
        if (value < node->value) return findElement(node->left, value);
        if (value > node->value) return findElement(node->right, value);
        return true;
    }

    void print(Node* node) const {
        if (node) {
            print(node->left);
            std::cout << node->value << " ";
            print(node->right);
        }
    }

    void saveToFile(Node* node, std::ofstream& file) const {
        if (node) {
            file << node->value << " ";
            saveToFile(node->left, file);
            saveToFile(node->right, file);
        }
    }

    Node* loadFromFile(std::ifstream& file, Node* parent = nullptr) {
        int value;
        if (file >> value) {
            Node* node = new Node(value, parent);
            node->left = loadFromFile(file, node);
            node->right = loadFromFile(file, node);
            return node;
        }
        return nullptr;
    }

public:
    BSTree() : root(nullptr) {}
    BSTree(std::initializer_list<int> list) : root(nullptr) { for (int val : list) addElement(val); }
    ~BSTree() { clear(root); }

    bool addElement(int value) { return addElement(root, value); }
    bool deleteElement(int value) { return deleteElement(root, value); }
    bool findElement(int value) const { return findElement(root, value); }
    void print() const { print(root); std::cout << std::endl; }

    bool save_to_file(const std::string& path) {
        std::ofstream file(path);
        if (!file) return false;
        saveToFile(root, file);
        return true;
    }

    bool load_from_file(const std::string& path) {
        std::ifstream file(path);
        if (!file) return false;
        clear(root);
        root = loadFromFile(file);
        return true;
    }
};