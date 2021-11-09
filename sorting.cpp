#include <functional>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>
#include <array>
using namespace std;

typedef std::vector<int> List;

void print(const List& ls)
{
	cout << '[';
	for (size_t i = 0; i < ls.size(); i++)
	{
		cout << ls[i];
		if (i + 1 != ls.size())
			cout << ", ";
	}
	cout << "]\n";
}

List sort_native(const List& ls)
{
	auto copy = ls;
	sort(copy.begin(), copy.end());
	return copy;
}

List sort_cstr(const List& ls)
{
	auto out = List{ ls.front() };
	for (size_t i = 1; i < ls.size(); ++i)
	{
		size_t j = 0;
		for ( ; j < out.size(); ++j)
		{
			if (out[j] > ls[i])
			{
				out.insert(out.begin() + j, ls[i]);
				break;
			}
		}
		if (j == out.size())
			out.emplace_back(ls[i]);
	}
	return out;
}

List sort_min(const List& ls)
{
	auto copy = ls;
	List out;
	for (size_t i = 0; i < ls.size(); ++i)
	{
		size_t min_j = 0;
		for (size_t j = 1; j < copy.size(); ++j)
		{
			if (copy[j] < copy[min_j])
				min_j = j;
		}
		out.emplace_back(copy[min_j]);
		copy.erase(copy.begin() + min_j);
	}
	return out;
}

List sort_bubble(const List& ls)
{
	auto copy = ls;
	for (size_t i = 1; i < copy.size(); ++i)
	{
		for (size_t j = 1; j < copy.size(); ++j)
		{
			if (copy[j - 1] > copy[j])
				swap(copy[j - 1], copy[j]);
		}
	}
	return copy;
}

List merge_sorted(const List& lhs, const List& rhs)
{
	size_t li, ri;
	li = ri = 0;
	List out;
	while (li < lhs.size() && ri < rhs.size())
	{
		if (lhs[li] < rhs[ri])
			out.emplace_back(lhs[li++]);
		else
			out.emplace_back(rhs[ri++]);
	}
	if (li < lhs.size())
		out.insert(out.end(), lhs.begin() + li, lhs.end());
	else
		out.insert(out.end(), rhs.begin() + ri, rhs.end());
	return out;
}

List sort_fusion(const List& ls)
{
	if (ls.size() < 2)
		return ls;
	else
	{
		size_t mid = (size_t)(ls.size() / 2);
		List lhs(ls.begin(), ls.begin() + mid);
		List rhs(ls.begin() + mid, ls.end());
		return merge_sorted(sort_fusion(lhs), sort_fusion(rhs));
	}
}

int main()
{
	// List lref{ 7, 4, 9, 6, 1, 2, 4, 0 };
	// print(lref);
	// print(sort_cstr(lref));
	// print(sort_min(lref));
	// print(sort_bubble(lref));
	// print(sort_fusion(lref));

	array<List(*)(const List&), 5> funcs = { sort_native, sort_cstr, sort_min, sort_bubble, sort_fusion };
	for (size_t size = 999; size < 1000; ++size)
	{
		List tab(size);
		generate(tab.begin(), tab.end(), []() { return (int)rand() % 1000; });
		for (size_t i = 0; i < funcs.size(); ++i)
		{
			auto ta = chrono::high_resolution_clock::now();
			auto res = funcs[i](tab);
			auto tb = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> dt_ms = tb - ta;
			if (size == 999)
				cout << dt_ms.count() << "ms elapsed for func " << i << endl;
		}
	}
	return 0;
}