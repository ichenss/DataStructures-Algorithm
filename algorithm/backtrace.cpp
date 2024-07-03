#include <iostream>
#include <vector>
using namespace std;

// 回溯学习
#if 0
void func(int arr[], int i, int length, int x[])
{
    if (i == length)
    {
        for (int i = 0; i < length; i++)
        {
            if (x[i] == 1)
            {
                cout << arr[i] << " ";
            }
        }
        cout << endl;
    }
    else
    {
        x[i] = 1;
        func(arr, i + 1, length, x);
        x[i] = 0;
        func(arr, i + 1, length, x);
    }
}

int main()
{
    int arr[] = {1,2,3};
    int x[3] = {0};
    func(arr, 0, 3, x);
    return 0;
}
#endif

/*
整数选择问题：给定一组整数，从里面挑选出一组整数，让选择的整数的和，和剩下的整数的和的差最小
*/
#if 0
int arr[] = {12, 6, 7, 11, 16, 3, 8};
const int length = sizeof(arr)/sizeof(arr[0]);
int x[length] = {0};
int bestX[length] = {0};
int r = 0;
int sum = 0;
unsigned int minRes = 0xFFFFFFFF;

void func(int i)
{
    if (i == length)
    {
        int res = abs(sum - r);
        if (res < minRes) 
        {
            minRes = res;
            for (int i = 0; i < length; ++i)
            {
                bestX[i] = x[i];
            }
        }
    }
    else
    {
        x[i] = 1;
        sum += arr[i];
        r -= arr[i];
        func(i+1);
        r += arr[i];
        sum -= arr[i];

        x[i] = 0;
        func(i+1);
    }
}

int main()
{
    for (int i = 0; i < length; ++i)
    {
        r += arr[i];
    }
    func(0);
    cout << minRes << endl;
    for (int i = 0; i < length; i++)
    {
        if (bestX[i] == 1)
        {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
    return 0;
}
#endif

/*
整数选择问题：给定2n个整数，从里面挑选出n个整数，让选择的整数的和，和剩下的整数的和的差最小
*/
#if 0
int arr[] = {12, 6, 7, 11, 16, 3, 8, 4};
const int length = sizeof(arr)/sizeof(arr[0]);
vector<int> x;
vector<int> bestX;
int sum = 0;
int r = 0;
unsigned int _min = 0xFFFFFFFF;
int left_ = length;   // 未处理数字的个数

void func(int i)
{
    if (i == length)
    {
        if (x.size() != length/2)
        {
            return;
        }
        int result = abs(sum - r);
        if (result < _min) 
        {
            _min = result;
            bestX = x;
        }
    }
    else
    {
        left_--;
        if (x.size() < length/2)    // 剪左树枝，提高算法效率
        {
            x.push_back(arr[i]);
            sum += arr[i];
            r -= arr[i];
            func(i+1);
            r += arr[i];
            sum -= arr[i];
            x.pop_back();
        }

        if (x.size() + left_ >= length/2)   // 剪右树枝
        {
            func(i+1);
        }
        left_++;
    }
}

int main()
{
    for (int v : arr)
    {
        r += v;
    }
    func(0);
    for (int v : bestX)
    {
        cout << v << " ";
    }
    cout << endl;
    cout << "min: " << _min << endl;
    return 0;
}
#endif

/*
挑数字：一组值，挑选一组数字，和等于指定值
*/
#if 0
int arr[] = {4, 8, 16, 7, 9, 3};
int length = sizeof(arr)/sizeof(arr[0]);
int number = 18;
vector<int> x;
int sum = 0;
int r = 0;  // 未处理元素的和

void func(int i)
{
    if (i == length)
    {
        if (sum != number) return;
        for (auto v : x)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    else
    {
        r -= arr[i];    // 处理当前节点i
        if (sum + arr[i] <= number)
        {
            sum += arr[i];
            x.push_back(arr[i]);
            func(i+1);
            x.pop_back();
            sum -= arr[i];
        }
        
        if (sum + r >= number)
        {
            func(i+1);
        }
        r += arr[i];
    }
}

int main()
{
    for (int v : arr) r += v;
    func(0);
    return 0;
}
#endif

/*
挑数字：一组值，挑选一组数字，和等于指定值
*/
#if 0
int arr[] = {4, 8, 16, 7, 9, 3};
int length = sizeof(arr)/sizeof(arr[0]);
int number = 18;
vector<int> vec;

void func(int i, int number)
{
    if (number == 0)
    {
        for (int v : vec) 
            cout << v << " ";
        cout << endl;
    }
    else
    {
        for (int k = i; k < length; ++k)
        {
            if (number >= arr[k])   // 剩余的元素要小于number(待组成的元素值)
            {
                vec.push_back(arr[k]);
                // func(k, number - arr[k]);
                func(k + 1, number - arr[k]);
                vec.pop_back();
            }   
        }
    }
}

int main()
{
    func(0, number);
    return 0;
}
#endif

/*
01背包：有一组物品，重量w1, w2..., 价值v1, v2...; 现在有一个背包其容量是c
问怎么把物品装入背包，让背包价值最大化？
*/
#if 0
int w[] = {12, 5, 8, 9, 6};
int v[] = {9, 11, 4, 7, 8};
const int length = sizeof(w)/sizeof(w[0]);
int c = 20;
int cw = 0; // 已选择物品重量
int cv = 0; // 已选择物品价值
vector<int> x;
vector<int> bestx;
int bestv = 0;
int r = 0;

void func(int i)
{
    if (i == length)
    {
        if (cv > bestv)
        {
            bestv = cv;
            bestx = x;
        }
    }
    else
    {
        r -= v[i];
        if (cw + w[i] <= c)
        {
            cw += w[i];
            cv += v[i];
            x.push_back(w[i]);
            func(i+1);
            x.pop_back();
            cw -= w[i];
            cv -= v[i];
        }
        
        if (cv + r > bestv)
        {
            func(i+1);
        }
        r += v[i];
    }
}

int main()
{
    for (int val : v) r += val;
    func(0);
    for (int n : bestx) 
    {
        cout << n << " ";
    }
    return 0;
}
#endif

/*
排列树: 全排列问题
*/
#if 0
void swap(int arr[], int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void func(int arr[], int i, int length)
{
    if (i == length)
    {
        for (int j = 0; j < length; ++j)
        {
            cout << arr[j] << " ";
        }
        cout << endl;
    }
    else
    {
        for (int k = i; k < length; ++k)
        {
            swap(arr, i, k);
            func(arr, i + 1, length);   // 遍历i的一个孩子
            swap(arr, i, k);
        }
    }
}

int main()
{
    int arr[] = {1, 2, 3, 4};
    int length = sizeof(arr)/sizeof(arr[0]);
    func(arr, 0, length);
    return 0;
}
#endif

/*
八皇后
*/
#if 0
void swap(int arr[], int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

bool judge(int arr[], int i)
{
    for (int j = 0; j < i; j++)
    {
        if (j == i || arr[i] == arr[j] || abs(i - j) == abs(arr[i] - arr[j]))
        {
            return false;
        }
    }
    return true;
}

void func(int arr[], int i, int length)
{
    if (i == length)
    {
        for (int j = 0; j < length; j++)
        {
            cout << arr[j] << " ";
        }
        cout << endl;
    }
    else
    {
        for (int k = i; k < length; k++)
        {
            swap(arr, i, k);
            if (judge(arr, i))
            {
                func(arr, i+1, length);
            }
            swap(arr, i, k);
        }
    }
}

int main()
{
    // 下标当作行，元素值当作列
    int arr[] = {1,2,3,4,5,6,7,8};
    int n = 8;
    func(arr, 0, n);
    return 0;
}
#endif

/*
另一种全排列算法: 满足leetcode测试用例
*/
int arr[] = {1, 2, 3};
const int N = 3;
bool state[N];
vector<int> vec;
void func(int i)
{
    if (i == N)
    {
        for (auto v : vec)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    else
    {
        for (int k = 0; k < N; ++k)
        {
            if (!state[k])
            {
                state[k] = true;
                vec.push_back(arr[k]);
                func(i + 1);    // k: 表示可选择的元素起始下标    i: 表示层数
                vec.pop_back();
                state[k] = false;
            }
        }
    }
}

int main()
{
    func(0);
    return 0;
}
