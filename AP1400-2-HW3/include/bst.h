#ifndef BST_H
#define BST_H
#include <functional>
#include <iostream>
#include <type_traits>
template<typename T>
concept is_Int = std::is_same_v<T, int>;
class BST
{
    public:
    class Node
    {
        public:
	        Node(int value, Node* left, Node* right);
	        Node();
	        Node(const Node& node);
	        int value;
	        Node* left;
	        Node* right;
        friend bool operator<(const Node& node, int val);
        friend bool operator<=(const Node& node, int val);
        friend bool operator>(const Node& node, int val);
        friend bool operator>=(const Node& node, int val);
        friend bool operator<(int val, const Node& node);
        friend bool operator<=(int val, const Node& node);
        friend bool operator>(int val, const Node& node);
        friend bool operator>=(int val, const Node& node);
        friend bool operator==(int val, const Node& node);
        friend bool operator==(const Node& node, int val);
        friend std::ostream& operator<<(std::ostream& steram, const Node& node);
    };
    BST();
    BST(const BST& bst);
    BST(BST&& bst);
    ~BST();
    template<is_Int... Args>
    BST(Args... args)
    {
        root = nullptr;
        len = 0;
        (add_node(args), ...);
    }
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    BST& operator++();
    BST operator++(int);
    BST& operator=(const BST& bst);
    BST& operator=(BST&& bst);
    friend std::ostream& operator<<(std::ostream& stream, const BST& bst);
private:
    Node* root;
    size_t len;
};
#endif //BST_H
