#include "../include/bst.h"
#include <queue>
#include <vector>
BST::Node::Node(int value, BST::Node* left, BST::Node* right) : value(value), left(left), right(right){}

BST::Node::Node(){
    value = 0;
    left = nullptr;
    right = nullptr;
}

BST::Node::Node(const Node& node){
    *this = node;
}


bool operator<(const BST::Node& node, int val){
    return node.value < val;
}

bool operator<=(const BST::Node& node, int val){
    return node.value <= val;
}

bool operator>(const BST::Node& node, int val){
    return node.value > val;
}

bool operator>=(const BST::Node& node, int val){
    return node.value >= val;
}

bool operator<(int val, const BST::Node& node){
    return val < node.value;
}

bool operator<=(int val, const BST::Node& node){
    return val <= node.value;
}

bool operator>(int val, const BST::Node& node){
    return val > node.value;
}

bool operator>=(int val, const BST::Node& node){
    return val >= node.value;
}  

bool operator==(int val, const BST::Node& node){
    return node.value == val;
}

bool operator==(const BST::Node& node, int val){
    return node.value == val;
}

std::ostream& operator<<(std::ostream& stream, const BST::Node& node){
    stream << &node <<  " " << "=>" << "value : " << node.value << " " << "left : " << node.left << " " << "right : " << node.right;
    return stream;
}

BST::~BST()
{
 	std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes) delete node;
}
BST::BST(){
    root = nullptr;
    len = 0;
}

BST::BST(const BST& bst){
    len = bst.len;
    if(bst.root == nullptr)
    {
        root = nullptr;
    }
    else
    {
        root = new BST::Node;
        std::queue<BST::Node*> que_node;
        que_node.push(root);
        auto copy = [&que_node](const BST::Node* node){
            auto now = que_node.front();
            now->value = node->value;
            if(node->left != nullptr){
                auto left_ptr = new BST::Node;
                now->left = left_ptr;
                que_node.push(left_ptr);
            }
            if(node->right != nullptr){
                auto right_ptr = new BST::Node;
                now->right = right_ptr;
                que_node.push(right_ptr);
            }
            que_node.pop();
        };
        bst.bfs(copy);
    }
}

BST::BST(BST&& bst){
    len = bst.len;
    root = bst.root;
    bst.root = nullptr;
}

BST::Node*& BST::get_root(){
    return root;
}

void BST::bfs(std::function<void(BST::Node*& node)> func) const{
    std::queue<BST::Node*> que_node;
    if(root != nullptr) que_node.push(root);
    while(!que_node.empty())
    {
        auto cur = que_node.front();
        func(cur);
        if(cur->left != nullptr) que_node.push(cur->left);
        if(cur->right != nullptr) que_node.push(cur->right);
        que_node.pop();
    }
}

void BST::bfs(std::function<void(BST::Node*& node)> func){
    std::queue<BST::Node*> que_node;
    if(root != nullptr) que_node.push(root);
    while(!que_node.empty())
    {
        auto cur = que_node.front();
        func(cur);
        if(cur->left != nullptr) que_node.push(cur->left);
        if(cur->right != nullptr) que_node.push(cur->right);
        que_node.pop();
    }
}


size_t BST::length(){
    return len;
}

bool BST::add_node(int value){
    auto cur_pos = root;
    if(cur_pos == nullptr)
    {
        root = new BST::Node;
        root->value = value;
        len++;
    }
    while(cur_pos != nullptr)
    {
        if(value == *cur_pos) return false;
        else if(value < *cur_pos) 
        {
            if(cur_pos->left == nullptr)
            {
                auto ptr = new BST::Node;
                cur_pos->left = ptr;
                ptr->value = value;
                len++;
                return true;
            }
            else 
                cur_pos = cur_pos->left;
        }
        else 
        {
            if(cur_pos->right == nullptr)
            {
                auto ptr = new BST::Node;
                cur_pos->right = ptr;
                ptr->value = value;
                len++;
                return true;
            }
            else
                cur_pos = cur_pos->right;
        }
    }
    return false;
}

BST::Node** BST::find_node(int value){
    if(root == nullptr) return nullptr;
    if(root->value == value) return &root;
    auto cur_ptr_ptr = &root;
    while(cur_ptr_ptr != nullptr)
    {
        if(value == **cur_ptr_ptr) return cur_ptr_ptr;
        else if(value < **cur_ptr_ptr)
        {
            if((*cur_ptr_ptr)->left != nullptr)
                cur_ptr_ptr = &((*cur_ptr_ptr)->left);
            else
                cur_ptr_ptr = nullptr;
        }
        else
        {
            if((*cur_ptr_ptr)->right != nullptr)
                cur_ptr_ptr = &((*cur_ptr_ptr)->right);
            else
                cur_ptr_ptr = nullptr;            
        }
    }
    return nullptr;
}

BST::Node** BST::find_parrent(int value){;
    if(root == nullptr || root->value == value) return nullptr;
    auto cur_pos = &root;
    while(cur_pos != nullptr)
    {
        if((*cur_pos)->left != nullptr && (*cur_pos)->left->value == value)
            return cur_pos;
        else if((*cur_pos)->right != nullptr && (*cur_pos)->right->value == value)
            return cur_pos;
        else if(**cur_pos > value)
        {
            if((*cur_pos)->left == nullptr)
                cur_pos = nullptr;
            else
                cur_pos = &((*cur_pos)->left);
        }
        else if(**cur_pos < value)
        {
            if((*cur_pos)->right == nullptr)
                cur_pos = nullptr;
            else
                cur_pos = &((*cur_pos)->right);
        }  
    }
    return nullptr;
}


BST::Node** BST::find_successor(int value){
    auto ptr = find_node(value);
    if(ptr == nullptr) return nullptr;
    if((*ptr)->left != nullptr)
    {
        ptr = &((*ptr)->left);
        while((*ptr)->right != nullptr)
        {
            ptr = &((*ptr)->right);
        }
        return ptr;
    }
    else
    {
        auto par_ptr = find_parrent(value);
        while(par_ptr != nullptr && (*par_ptr)->right != *ptr)
        {
            ptr = par_ptr;
            par_ptr = find_parrent((*ptr)->value);
        }
        return par_ptr;
    }
}


bool BST::delete_node(int value){
    static int cur_minor = 0;
    auto ptr = find_node(value);
    if(ptr == nullptr) return false;
    if((*ptr)->left == nullptr && (*ptr)->right == nullptr)
    {
        auto par_ptr = find_parrent(value);
        if(par_ptr == nullptr)
            root = nullptr;
        else if((*par_ptr)->left == *ptr) 
            (*par_ptr)->left = nullptr;
        else 
            (*par_ptr)->right = nullptr;
        delete *ptr;
        len--;
    }
    else if((*ptr)->left == nullptr)
    {
        auto par_ptr = find_parrent(value);
        auto new_ptr = (*ptr)->right;
        if(par_ptr == nullptr)
        {
            delete *ptr;
            root = new_ptr;   
        }
        else if((*par_ptr)->left == *ptr) 
        {
            delete *ptr;
            (*par_ptr)->left = new_ptr;
        }
        else 
        {
            delete *ptr;
            (*par_ptr)->right = new_ptr;
        }
        len--;
    }
    else if((*ptr)->right == nullptr)
    {
        auto par_ptr = find_parrent(value);
        auto new_ptr = (*ptr)->left;
        if(par_ptr == nullptr)
        {
            delete *ptr;
            root = new_ptr;
        }
        else if((*par_ptr)->left == *ptr) 
        {
            delete *ptr;
            (*par_ptr)->left = new_ptr;
        }
        else
        {
            delete *ptr;
            (*par_ptr)->right = new_ptr; 
        }
        len--;       
    }
    else
    {
        auto suc_ptr = find_successor(value);
        int cur_val = (*suc_ptr)->value;
        if(delete_node(cur_val)) (*ptr)->value = cur_val;
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream,const BST& bst){
    bst.bfs([&stream](BST::Node*& node){stream << node << '\n';});
    return stream;  
}

BST& BST::operator++(){
    bfs([](BST::Node*& node){(node->value)++;});
    return *this;
}

BST BST::operator++(int){
    auto cop = *this;
    bfs([](BST::Node*& node){(node->value)++;});
    return cop;
}

BST& BST::operator=(const BST& bst){
    if(&bst == this) return *this;
    std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes) delete node;
    len = bst.len;
    if(bst.root == nullptr)
    {
        root = nullptr;
    }
    else
    {
        root = new BST::Node;
        std::queue<BST::Node*> que_node;
        que_node.push(root);
        auto copy = [&que_node](const BST::Node* node){
            auto now = que_node.front();
            now->value = node->value;
            if(node->left != nullptr){
                auto left_ptr = new BST::Node;
                now->left = left_ptr;
                que_node.push(left_ptr);
            }
            if(node->right != nullptr){
                auto right_ptr = new BST::Node;
                now->right = right_ptr;
                que_node.push(right_ptr);
            }
            que_node.pop();
        };
        bst.bfs(copy);
    }
    return *this;
}

BST& BST::operator=(BST&& bst){
    std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes) delete node;
    len = bst.len;
    root = bst.root;
    bst.root = nullptr;
    return *this;
}