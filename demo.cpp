#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> trainingPlan(vector<int> &nums)
    {
        if (nums.size() <= 0)
            return {};
        int front = 0;
        int back = nums.size() - 1;
        while (front != back)
        {
            if (nums[front] % 2 == 0)
            {
                while (nums[back] % 2 == 0 && back >= 0)
                {
                    back--;
                }
                int tmp = nums[front];
                nums[front] = nums[back];
                nums[back] = tmp;
            }
            front++;
        }
        return nums;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1, 2, 3, 4, 5};
    nums = s.trainingPlan(nums);
    for (auto i : nums)
    {
        cout << i << " ";
    }
}
