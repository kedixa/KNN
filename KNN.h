/*
 * Copyright (C) Kedixa Liu
 *  kedixa@outlook.com
 *
 */

#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<map>
#ifndef KNN_H_
#define KNN_H_

namespace kedixa{

class KNN
{
	typedef std::vector<std::string> vs;
	typedef std::vector<vs>          vvs;
	typedef std::vector<double>         vd;
	typedef std::vector<vd>          vvd;
private:
	vvd datas;
	vs target;
	int data_dim;
	int datas_size;
	unsigned k;
	static double distance(vd&, vd&);

public:
	KNN();
	KNN(const KNN&) = delete;
	int set_data(vvd&, vs&, unsigned);
	int add_data(vvd&, vs&);
	bool set_k(unsigned);
	void clear();
	std::string classify(vd&);
	~KNN();
};

} // namespace kedixa
#endif // KNN_H_
