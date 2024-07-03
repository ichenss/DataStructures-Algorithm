#include <iostream>
using namespace std;

/* 线性探测哈希表实现 */

// 桶的状态
enum State
{
    STATE_UNUSE,
    STATE_USING,
    STATE_DEL,
};

// 桶的类型
struct Bucket
{
    Bucket(int key = 0, State state = STATE_UNUSE)
        : key_(key)
        , state_(state)
    {}

    int key_;   // 数据
    State state_;   // 桶当前状态
};

// 线性探测哈希表类型
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
        tableSize_ = primes_[primeIdx_];
        table_ = new Bucket[tableSize_];
    }

    ~HashTable()
    {
        delete[] table_;
        table_ = nullptr;
    }

public:
    // 插入元素
    bool insert(int key)
    {
        double factor = useBucketNum_ * 1.0 / tableSize_;
        cout << "useBucketNum_: " << useBucketNum_ << endl;
        cout << "tableSize_: " << tableSize_ << endl;
        cout << "factor: " << factor << endl;
        if (factor > loadFactor_)
        {
            expand();
        }

        int idx = key % tableSize_;

        int i = idx;
        do
        {
            if (table_[i].state_ != STATE_USING)
            {
                table_[i].key_ = key;
                table_[i].state_ = STATE_USING;
                useBucketNum_++;
                return true;
            }
            i = (i + 1) % tableSize_;
        } while (i != idx);

        return false;
    }
    // 删除元素
    bool erase(int key)
    {
        int idx = key % tableSize_;

        int i = idx;
        do
        {
            if (table_[i].state_ == STATE_USING && table_[i].key_ == key)
            {
                table_[i].state_ = STATE_DEL;
                useBucketNum_--;
            }
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != STATE_UNUSE && i != idx);

        return true;
    }
    // 查询元素
    bool find(int key)
    {
        int idx = key % tableSize_;

        int i = idx;
        do
        {
            if (table_[i].state_ == STATE_USING && table_[i].key_ == key)
            {
                return true;
            }
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != STATE_UNUSE && i != idx);

        return false;
    }

private:
    // 扩容
    void expand()
    {
        ++primeIdx_;
        if (primeIdx_ == PRIME_SIZE)
        {
            throw "HashTable is too large, can not expand anymore!";
        }

        Bucket* newTable = new Bucket[primes_[primeIdx_]];
        for (int i = 0; i < tableSize_; i++)
        {
            if (table_[i].state_ == STATE_USING)
            {
                int idx = table_[i].key_ % primes_[primeIdx_];

                int k = idx;
                do
                {
                    if (newTable[k].state_ != STATE_USING)
                    {
                        newTable[k].state_ = STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                    k = (k + 1) % primes_[primeIdx_];
                } while (k != idx);
            }
        }

        delete[]table_;
        table_ = newTable;
        tableSize_ = primes_[primeIdx_];
    }

private:
    Bucket* table_;     // 指向动态开辟的哈希表
    int tableSize_;     // 哈希表当前长度
    int useBucketNum_;  // 已使用桶的个数
    double loadFactor_; // 装载因子

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
    cout << htable.find(14) << endl;
    return 0;
}
