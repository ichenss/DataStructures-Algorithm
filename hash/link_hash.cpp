#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

/* 链地址哈希表实现 */

class HashTable
{
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
    {
        // 把用户传入的size调整到最近比较大的素数上
        if (primes_[0] != size)
        {
            for (; primeIdx_ < PRIME_SIZE; primeIdx_++)
            {
                if (primes_[primeIdx_] >= size)
                    break;
            }
            // 超过则调整为最后一个素数
            if (primeIdx_ == PRIME_SIZE)
            {
                primeIdx_--;
            }
        }

        table_.resize(primes_[primeIdx_]);
    }

public:
    // 增加元素 不能重复插入
    void insert(int key)
    {
        double factor = useBucketNum_ * 1.0 / table_.size();
        cout << "factor: " << factor << endl;
        if (factor > loadFactor_)
        {
            expand();
        }

        int idx = key % table_.size();
        if (table_[idx].empty())
        {
            useBucketNum_++;
            table_[idx].emplace_front(key);
        }
        else
        {
            // 使用全局::find泛型算法，而不是调用自己成员方法find
            auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
            if (it == table_[idx].end())
            {
                table_[idx].emplace_front(key);
            }
        }
    }

    // 删除元素
    void erase(int key)
    {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        if (it != table_[idx].end())
        {
            table_[idx].erase(it);
            if (table_[idx].empty()) 
                useBucketNum_--;
        }
    }

    // 搜索元素
    bool find(int key)
    {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        return it != table_[idx].end();
    }

private:
    // 扩容
    void expand()
    {
        cout << "expand" << endl;
        if (primeIdx_ + 1 == PRIME_SIZE)
        {
            throw "HashTable is too large, can not expand anymore!";
        }

        primeIdx_++;
        useBucketNum_ = 0;

        vector<list<int>> oldTable;
        // 空间配置器相同则交换两个容器成员变量, 效率高
        table_.swap(oldTable);
        table_.resize(primes_[primeIdx_]);

        for (auto list : oldTable)
        {
            for (auto key : list)
            {
                int idx = key % table_.size();
                if (table_[idx].empty())
                {
                    useBucketNum_++;
                }
                table_[idx].emplace_front(key);
            }
        }
    }

private:
    vector<list<int>> table_;   // 哈希表的数据结构
    int useBucketNum_;          // 桶的个数
    double loadFactor_;         // 装载因子

    static const int PRIME_SIZE = 10;   // 素数表大小
    static int primes_[PRIME_SIZE];     // 素数表
    int primeIdx_;  // 当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 41, 97, 251, 443, 911, 1471, 42773 };

int main()
{
    HashTable htable;
    htable.insert(21);
    htable.insert(32);
    htable.insert(14);
    htable.insert(15);
    htable.insert(22);
    htable.insert(67);
    cout << htable.find(14) << endl;
    return 0;
}
