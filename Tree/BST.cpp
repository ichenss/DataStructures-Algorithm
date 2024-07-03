#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

// BST代码实现
template< typename T, typename Compare = less<T> >
class BSTree
{
public:
    BSTree(Compare comp = Compare()) 
        : root_(nullptr)
        , comp_(comp)
    {
        
    }
    ~BSTree() 
    {
        if (root_ != nullptr)
        {
            queue<Node*> s;
            s.push(root_);
            while (!s.empty())
            {
                Node *front = s.front();
                s.pop();

                if (front->left_) s.push(front->left_);
                if (front->right_) s.push(front->right_);
                delete front;
            }
        }
    }

    void n_insert(const T &val)
    {
        if (root_ == nullptr)
        {
            root_ = new Node(val);
            return;
        }

        Node *parent = nullptr;
        Node *cur = root_;
        while(cur != nullptr)
        {
            if (cur->data_ == val) return;  // 不能插入相同元素值
            else if (!comp_(cur->data_, val))
            {
                parent = cur;
                cur = cur->left_;
            }
            else 
            {
                parent = cur;
                cur = cur->right_;
            }
        }
        if (comp_(val, parent->data_)) parent->left_ = new Node(val);
        else parent->right_ = new Node(val);
    }

    void insert(const T& val)
    {
        root_ = insert(root_, val);
    }

    void n_remove(const T &val)
    {
        if (root_ == nullptr) return;

        Node *parent = nullptr;
        Node *cur = root_;
        while (cur != nullptr)
        {
            if (cur->data_ == val) break;   // 找到待删除节点
            else if (!comp_(cur->data_, val))
            {
                parent = cur;
                cur = cur->left_;
            }
            else 
            {
                parent = cur;
                cur = cur->right_;
            }
        }
        if (cur == nullptr) return; // 没找到待删除节点

        // 情况3
        if (cur->left_ != nullptr && cur->right_ != nullptr)
        {
            parent = cur;
            Node *pre = cur->left_;
            while(pre->right_ != nullptr)
            {
                parent = pre;
                pre = pre->right_;
            }
            cur->data_ = pre->data_;
            cur = pre;  // 让cur指向前驱节点，转化成情况1，2
        }

        // 统一处理cur指向的节点，情况1或2；cur指向删除节点，parent指向其父节点
        Node *child = cur->left_;
        if (child == nullptr) child = cur->right_;

        if (parent == nullptr)  // 特殊情况，表示删除的是根节点
        {
            root_ = child;
        }
        else 
        {
            if (parent->left_ == cur) parent->left_ = child;
            else parent->right_ = child;
        }
        delete cur;
    }

    void remove(const T &val)
    {
        root_ = remove(root_, val);
    }

    bool n_query(const T &val)
    {
        Node *cur = root_;
        while (cur != nullptr)
        {
            if (cur->data_ == val)
            {
                return true;
            }
            else if (comp_(cur->data_, val))
            {
                cur = cur->right_;
            }
            else
            {
                cur = cur->left_;
            }
        }
        return false;
    }

    bool query(const T& val)
    {
        return nullptr != query(root_, val);
    }
    
    void preOrder()
    {
        cout << "preOrder: ";
        preOrder(root_);
        cout << endl;
    }

    void n_preOrder()
    {
        cout << "n_preOrder: ";
        if (root_ == nullptr) return;
        stack<Node*> s;
        s.push(root_);
        while (!s.empty())
        {
            Node *top = s.top();
            s.pop();
            cout << top->data_ << " ";
            if (top->right_) s.push(top->right_);
            if (top->left_) s.push(top->left_);
        }
        cout << endl;
    }

    void inOrder()
    {
        cout << "inOrder: ";
        inOrder(root_);
        cout << endl;
    }

    void n_inOrder()
    {
        cout << "n_inOrder: ";
        if (root_ == nullptr) return;
        stack<Node*> s;
        Node *cur = root_;
        while (!s.empty() || cur)
        {
            while (cur)
            {
                s.push(cur);
                cur = cur->left_;
            }
            Node *top = s.top();
            s.pop();
            cout << top->data_ << " ";
            cur = top->right_;
        }
        cout << endl;
    }

    void postOrder()
    {
        cout << "postOrder: ";
        postOrder(root_);
        cout << endl;
    }
    
    void n_postOrder()
    {
        cout << "n_postOrder: ";
        if (root_ == nullptr) return;
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(root_);
        while (!s1.empty())
        {
            Node *top = s1.top();
            s1.pop();

            s2.push(top);
            if (top->left_) s1.push(top->left_);
            if (top->right_) s1.push(top->right_);
        }
        while (!s2.empty())
        {
            cout << s2.top()->data_ << " ";
            s2.pop();
        }
        cout << endl;
    }

    void levelOrder()
    {
        int h = high();
        for (int i = 0; i < h; i++)
        {
            levelOrder(root_, i);
        }
        cout << endl;
    }

    void n_levelOrder()
    {
        if (root_ == nullptr) return;
        queue<Node*> que;
        que.push(root_);
        while (!que.empty())
        {
            Node *front = que.front();
            que.pop();

            cout << front->data_ << " ";
            if (front->left_) que.push(front->left_);
            if (front->right_) que.push(front->right_);
        }
    }

    int high()
    {
        return high(root_);
    }

    int number()
    {
        return number(root_);
    }
    // --------面试题---------
    // 求满足区间的元素值[i, j]
    void findValues(vector<T> &vec, int i, int j)
    {
        findValues(root_, vec, i, j);
    }

    // 判断是否是BST树
    bool isBSTree()
    {
        Node *pre = nullptr;
        return isBSTree(root_, pre);
    }

    // 判断子树问题
    bool isChildTree(BSTree<T, Compare>& child)
    {
        // 在当前二叉树找child根节点
        if (child.root_ == nullptr) return true;
        Node *cur = root_;
        while (cur)
        {
            if (cur->data_ == child.root_->data_)
            {
                break;
            }
            else if (comp_(cur->data_, child.root_->data_))
            {
                cur = cur->right_;
            }
            else 
            {
                cur = cur->left_;
            }
        }
        if (cur == nullptr) return false;
        return isChildTree(cur, child.root_);
    }

    // 最近公共祖先节点
    int getLCA(int val1, int val2)
    {
        Node* node = getLCA(val1, val2);
        if (node == nullptr) throw "no LCA!";
        else return node->data_;
    }

    // 镜像翻转
    void mirror01()
    {
        mirror01(root_);
    }

    // 镜像对称
    bool mirror02()
    {
        if (root_ == nullptr) return true;
        return mirror02(root_->left_, root_->right_);
    }

    // 重建二叉树
    void rebuild(int pre[], int i, int j, int in[], int m, int n)
    {
        root_ = _rebuild(pre, i, j, in, m, n);
    }

    // 判断平衡树
    bool isBalance()
    {
        int l = 0;
        bool flag = true;
        isBalance02(root_, l, flag);
        return flag;
    }

    // 求中序倒数第k个节点
    int getValue(int k)
    {
        Node *node = getValue(root_, k);
        if (node == nullptr)
        {
            throw "node error!";
        }
        return node->data_;
    }

private:
    struct Node
    {
        Node( T data = T() ) 
            : data_(data)
            , left_(nullptr)
            , right_(nullptr)
        {}
        T data_;
        Node *left_;
        Node *right_;
    };
    
    void preOrder(Node *node)
    {
        if (node != nullptr)
        {
            cout << node->data_ << " ";
            preOrder(node->left_);
            preOrder(node->right_);
        }
    }
    
    void inOrder(Node *node)
    {
        if (node != nullptr)
        {
            inOrder(node->left_);
            cout << node->data_ << " ";
            inOrder(node->right_);
        }
    }
    
    void postOrder(Node *node)
    {
        if (node != nullptr)
        {
            postOrder(node->left_);
            postOrder(node->right_);
            cout << node->data_ << " ";
        }
    }
   
    void levelOrder(Node *node, int i)
    {
        if (node == nullptr) return;
        if (i == 0)
        {
            cout << node->data_ << " ";
            return;
        }
        levelOrder(node->left_, i - 1);
        levelOrder(node->right_, i - 1);
    }
    
    int high(Node *node)
    {
        if (node == nullptr) return 0;
        int left = high(node->left_);
        int right = high(node->right_);
        return left > right ? left + 1 : right + 1;
    }
    
    int number(Node *node)
    {
        if (node == nullptr) return 0;
        int left = number(node->left_);
        int right = number(node->right_);
        return left + right + 1;
    }
    
    Node* insert(Node *node, const T& val)
    {
        if (node == nullptr)
        {
            // 递归结束，找到插入val的位置
            return new Node(val);
        }
        // 不插入相同元素
        if (node->data_ == val) return node;
        else if (comp_(node->data_, val))
        {
            node->right_ = insert(node->right_, val);
        }
        else 
        {
            node->left_ = insert(node->left_, val);
        }
        return node;
    }

    Node* query(Node *node, const T& val)
    {
        if (node == nullptr) return nullptr;
        if (node->data_ == val) return node;
        else if (comp_(node->data_, val))
        {
            return query(node->right_, val);
        }
        else
        {
            return query(node->left_, val);
        }
    }

    Node* remove(Node *node, const T &val)
    {
        if (node == nullptr) return nullptr;
        
        // 找到待删除节点
        if (node->data_ == val)
        {
            if (node->left_ != nullptr && node->right_ != nullptr)
            {
                // 找前驱节点
                Node *pre = node->left_;
                while (pre->right_ != nullptr)
                {
                    pre = pre->right_;
                }
                node->data_ = pre->data_;
                node->left_ = remove(node->left_, pre->data_);
            }
            else
            {
                if (node->left_ != nullptr)
                {
                    Node *left = node->left_;
                    delete node->left_;
                    return left;
                }
                else if (node->right_ != nullptr)
                {
                    Node *right = node->right_;
                    delete node->right_;
                    return right;
                }
                else
                {
                    delete node;
                    return nullptr;
                }
            }
        }
        else if (comp_(node->data_, val))
        {
            node->right_ = remove(node->right_, val);
        }
        else
        {
            node->left_ = remove(node->left_, val);
        }
        return node;    // 把当前节点返回给父节点，更新父节点相应的地址域
    }

    void findValues(Node *node, vector<T> &vec, int i, int j)
    {
        if (node == nullptr) return;
        if (node->data_ > i)
        {
            findValues(node->left_, vec, i, j);
        }
        if (node->data_ >= i && node->data_ <= j)
        {
            vec.push_back(node->data_);
        }
        if (node->data_ < j)
        {
            findValues(node->right_, vec, i, j);
        }
    }

    bool isBSTree(Node *node, Node *&pre)
    {
        if (node == nullptr) return true;
        if (!isBSTree(node->left_, pre))
        {
            return false;
        }
        if (pre != nullptr) 
        {
            if (comp_(node->data_, pre->data_))
            {
                return false;
            }
        }
        pre = node;
        return isBSTree(node->right_, pre);
    }

    bool isChildTree(Node *father, Node *child)
    {
        if (father == nullptr && child == nullptr)
        {
            return true;
        }

        if (father == nullptr)
        {
            return false;
        }

        if (child == nullptr) 
        {
            return true;
        }

        // 判断值不相同
        if (father->data_ != child->data_)
        {
            return false;
        }

        return isChildTree(father->left_, child->left_) 
            && isChildTree(father->right_, child->right_);
    }

    Node* getLCA(Node *node, int val1, int val2)
    {
        if (node == nullptr) return nullptr;
        if (comp_(node->data_, val1) && comp_(node->data_, val2))
        {
            return getLCA(node->right_, val1, val2);
        }
        else if (comp_(val1, node->data_) && comp_(val2, node->data_))
        {
            return getLCA(node->left_, val1, val2);
        }
        else
        {
            return node;
        }
    }

    void mirror01(Node *node)
    {
        if (node == nullptr) return;

        Node *tmp = node->left_;
        node->left_ = node->right_;
        node->right_ = tmp;

        mirror01(node->left_);
        mirror01(node->right_);
    }

    bool mirror02(Node *node1, Node *node2)
    {
        if (node1 == nullptr && node2 == nullptr) return true;
        if (node1 == nullptr || node2 == nullptr) return false;
        if (node1->data_ != node2->data_) return false;
        return mirror02(node1->left_, node2->right_) && mirror02(node1->right_, node2->left_);
    }

    Node* _rebuild(int pre[], int i, int j, int in[], int m, int n)
    {
        if (i > j || n > m)
        {
            return nullptr;
        }
        // 创建当前子树根节点
        Node *node = new Node(pre[i]);  // 拿前序的第一个数据创建根节点
        for (int k = m; k <= n; ++k)
        {
            if (pre[i] == in[k])    // 在中序遍历中找子树下标k
            {
                node->left_ = _rebuild(pre, i+1, i+(k-m), in, m, k-1);
                node->right_ = _rebuild(pre, i+(k-m)+1, j, in, k+1, n);
                return node;
            }
        }
        return node;
    }

    // 判断平衡树
    bool isBalance(Node *node)
    {
        if (node == nullptr)
            return true;
        if (!isBalance(node->left_))
            return false;
        if (!isBalance(node->right_))
            return false;

        int left = high(node->left_);
        int right = high(node->right_);
        return abs(left - right) <= 1;
    }

    // 判断平衡树 高效率
    int isBalance02(Node *node, int l, bool &flag)
    {
        if (node == nullptr)
            return l;

        int left = isBalance02(node->left_, l + 1, flag);
        if (!flag) 
            return left;
        int right = isBalance02(node->right_, l + 1, flag);
        if (!flag) 
            return right;

        if (abs(left - right) > 1)
            flag = false;

        return max(left, right);
    }

    // 中序遍历倒数第k个节点
    int i = 1;
    Node* getValue(Node* node, int k)
    {
        if (node == nullptr) return nullptr;

        Node *left = getValue(node->right_, k);
        if (left != nullptr) return left;
        if (i++ == k)
            return node;
        return getValue(node->left_, k);
    }

    Node *root_;
    Compare comp_;
};

int main()
{
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for (int v : arr)
    {
        bst.n_insert(v);
    }
    bst.insert(12);
    cout << bst.getValue(4) << endl;
    return 0;
}
