#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

// AVL树 二叉平衡搜索树
template<typename T>
class AVLTree
{
public:
    AVLTree() : root_(nullptr) {}

    // 插入操作
    void insert(const T &val)
    {
        
    }

private:
    struct Node
    {
        Node(T data = T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr)
            , height_(1)
        {}
        T data_;
        Node *left_;
        Node *right_;
        int height_;
    };

    // 返回节点高度值
    int height(Node *node)
    {
        return node == nullptr ? 0 : node->height_;
    }

    // 右旋
    Node* rightRotate(Node *node)
    {
        // 节点旋转操作
        Node *child = node->left_;
        node->left_ = child->right_;
        child->right_ = node;
        // 高度更新
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;
        // 返回新根节点
        return child;
    }

    // 左旋
    Node* leftRotate(Node *node)
    {
        // 节点旋转操作
        Node *child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;
        // 高度更新
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;
        // 返回新根节点
        return child;
    }

    // 左平衡，左右旋转
    Node* leftBalance(Node *node)
    {
        node->left_ = leftRotate(node->left_);
        return rightRotate(node);
    }

    // 右平衡，右左旋转
    Node* rightBalance(Node *node)
    {
        node->right_ = rightBalance(node->right_);
        return rightRotate(node);
    }

    // 插入实现
    Node* insert(Node *node, const T &val)
    {
        if (node == nullptr)
        {
            return new Node(val);
        }
        if (node->data_ > val)
        {
            node->left_ = insert(node->left_, val);
            if (height(node->left_) - height(node->right_) > 1)
            {
                if (height(node->left_->left_) >= height(node->left_->right_))
                {
                    // 节点失衡，由于左孩子的左子树太高了
                    rightRotate(node);
                }
            }
        }
        else if (node->data_ < val)
        {
            node->right_ = insert(node->right_, val);
        }
        else 
        {
            ;   // 找到相同节点了
        }
        return node;
    }
    
    Node *root_;
};
