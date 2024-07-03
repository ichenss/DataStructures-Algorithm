#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

void InsertSort(int* nums, int begin, int end)
{

}

int Partation(int* nums, int l, int r)
{
	// 优化2：采用基准数的优化，采用三数取中法
	int val = nums[l];
	while (l < r)
	{
		while (l < r && val < nums[r])
		{
			r--;
		}

		if (l < r)
		{
			nums[l] = nums[r];
			l++;
		}

		while (l < r && val > nums[l])
		{
			l++;
		}

		if (l < r)
		{
			nums[r] = nums[l];
			r--;
		}
	}
	nums[l] = val;
	return l;
}

void QuickSort(int* nums, int begin, int end)
{
	if (begin >= end) return;

	// 优化1：当数据序列内元素个数小于指定数量，采用插入排序
	/*if (end - begin < 50)
	{
		InsertSort(nums, begin, end);
		return;
	}*/

	int pos = Partation(nums, begin, end);

	QuickSort(nums, begin, pos - 1);
	QuickSort(nums, pos + 1, end);
}

void QuickSort(int* nums, int size)
{
	if (nums == nullptr) return;
	QuickSort(nums, 0, size - 1);
}

int main()
{
	srand(time(0));
	int nums[10];
	for (int i = 0; i < 10; i++)
	{
		nums[i] = rand() % 100;
	}
	for (auto i : nums) cout << i << " ";
	QuickSort(nums, 10);
	cout << endl;
	for (auto i : nums) cout << i << " ";
	return 0;
}
