#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
	vector<string> topKFrequent(vector<string>& words, int k) 
	{
		map<string, int> count_map;
		for (auto k : words)
		{
			count_map[k]++;
		}
		multimap<int, string, greater<int> >sort_map;
		for (auto kv : count_map)
		{
			sort_map.insert(make_pair(kv.second, kv.first));
		}
		auto it = sort_map.begin();
		vector<string> s;
		while (it != sort_map.end())
		{
			if (k == 0)
				break;
			s.push_back(it->second);
			it++;
			k--;
		}
		return s;
	}
};