/*
 * Copyright (C) Kedixa Liu
 *  kedixa@outlook.com
 *
 */

#include "KNN.h"

namespace kedixa{

KNN::KNN()
{
	datas.clear();
	data_dim = 0;
	datas_size = 0;
}

int KNN::set_data(vvd& _datas, vs& _target, unsigned _k)
{
	clear();
	if(_datas.size() == 0) return 0;
	if(_datas.size() != _target.size()) return 0;
	data_dim = _datas[0].size();
	if(data_dim == 0) return 0;
	for(int i = 0; i < (int)_datas.size(); ++i)
	{
		if((int)_datas[i].size() != data_dim)
			continue;
		datas.push_back(_datas[i]);
		target.push_back(_target[i]);
		++datas_size;
	}

	if(_k <1 || _k > (unsigned)datas_size)
		k = std::min(3, datas_size);
	else k = _k;
	return datas_size;
}

int KNN::add_data(vvd& _datas, vs& _target)
{
	if(_datas.size() != _target.size()) return 0;
	for(int i = 0; i < (int)_datas.size(); ++i)
	{
		if((int)_datas[i].size() != data_dim)
			continue;
		datas.push_back(_datas[i]);
		target.push_back(_target[i]);
		++datas_size;
	}
	return datas_size;
}

void KNN::clear()
{
	datas.clear();
	target.clear();
	data_dim = 0;
	datas_size = 0;
	k = 0u;
}

double KNN::distance(vd& a, vd& b)
{
	double ans = 0;
	auto _size = std::min(a.size(), b.size());
	for(decltype(_size) i = 0; i < _size; ++i)
		ans += (a[i] - b[i]) * (a[i] - b[i]);
	return ans;
}

bool KNN::set_k(unsigned _k)
{
	if(_k == 0 || _k > (unsigned)datas_size) return false;
	k = _k;
	return true;
}

std::string KNN::classify(vd& _data)
{
	if((int)_data.size() != data_dim) return std::string();
	using pair=std::pair<double,int>;
	std::priority_queue<pair, std::vector<pair>, std::greater<pair>> que;
	for(int i = 0; i < datas_size; ++i)
	{
		double tmp = 1.0 / (1 + distance(datas[i], _data));
		if(que.size() < k) que.push(pair(tmp, i));
		else if(que.top() < pair(tmp, i))
			que.pop(), que.push(pair(tmp, i));
	}
	std::map<std::string, double> m;
	while(!que.empty())
	{
		pair tmp = que.top();
		que.pop();
		auto& h = target[tmp.second];
		auto it = m.find(h);
		if(it == m.end()) m[h] = 0;
		m[h] += tmp.first;
	}
	double max_dist = m.begin()->second;
	std::string ans = m.begin()->first;
	for(auto& i:m)
		if(i.second > max_dist)
			max_dist = i.second, ans = i.first;
	return ans;
}

KNN::~KNN()
{
	clear();
}

} // namespace kedixa
