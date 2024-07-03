#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
硬币问题：1，3，5分硬币，给定价值c，组成c最少硬币数量
*/
#if 0
int main()
{
    int arr[] = {1, 3, 5};
    int size = sizeof(arr)/sizeof(arr[0]);
    int c = 11;
    sort(arr, arr + size, [](int a, int b)->bool{ return a > b; });
    int index = 0;
    int count = 0;
    while (c > 0)
    {
        if (c >= arr[index])
        {
            c -= arr[index];
            count++;
        }
        else
        {
            index++;
        }
    }
    cout << count << endl;
    return 0;
}
#endif

/*
部分背包问题: 物品可以取走一部分
*/
#if 0
struct product
{
    double getPrice()const
    {
        return v*1.0/w;
    }
    bool operator>(const product& other)const
    {
        return getPrice() > other.getPrice();
    }
    int id;
    int w;
    int v;
};

int main()
{
    int w[] = {8, 6, 4, 2, 5};
    int v[] = {6, 4, 7, 8, 6};
    const int n = sizeof(w)/sizeof(w[0]);
    int c = 12;
    int x[n] = {0};
    product pros[n];
    for (int i = 0; i < n; i++)
    {
        pros[i].id = i;
        pros[i].w = w[i];
        pros[i].v = v[i];
    }
    sort(pros, pros+n, [](const product &p1, const product &p2)->bool{ return p1 > p2; });
    double bestv = 0.0;
    for (int i = 0; i < n; ++i)
    {
        if (pros[i].w <= c)
        {
            bestv += pros[i].v;
            c -= pros[i].w;
        }
        else
        {
            bestv = bestv + pros[i].v * (c * 1.0 / pros[i].w);
            // bestv += (pros[i].w - c) * pros[i].getPrice();
            x[pros[i].id] = 1;
            break;
        }
        x[pros[i].id] = 1;
    }
    cout << bestv << endl;
    for (int v : x)
    {
        cout << v << " ";
    }
    return 0;
}
#endif

/*
柜台问题
*/
struct counter
{
    bool operator<(const counter& p)const
    {
        return time < p.time;
    }
    int id;
    int time;
};

int main()
{
    int arr[] = {3, 2, 4};
    const int m = sizeof(arr)/sizeof(arr[0]);
    int n = 15;
    counter cons[m];
    for (int i = 0; i < m; ++i)
    {
        cons[i].id = i;
        cons[i].time = arr[i];
    }
    sort(cons, cons+m);

    int mintime = 0;
    int x[m] = {0};
    for (int i = 0; i < n; i++)
    {
        
    }
    return 0;
}
