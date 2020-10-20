#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution 
{
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
	{
		unordered_set<int> CountSet1;
		unordered_set<int> CountSet2;
		for (auto v : nums1)
		{
			CountSet1.insert(v);
		}
		for (auto v : nums2)
		{
			CountSet2.insert(v);
		}
		vector<int> vc;
		for (auto v : CountSet1)
		{
			if (CountSet2.find(v) != CountSet2.end())
			{
				vc.push_back(v);
			}
		}
		return vc;
	}
	int repeatedNTimes(vector<int>& A) 
	{
		unordered_map<int, int> CountMap;
		for (auto v : A)
		{
			CountMap[v]++;
		}
		size_t N = A.size() / 2;
		for (auto v : CountMap)
		{
			if (v.second == N)
				return v.first;
		}
		return -1;
	}
};