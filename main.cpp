#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include "KNN.h"
using namespace std;
using namespace kedixa;

void iris()
{
	vector<vector<double>> examples;
	vector<string> target;
	string data_file_name = "iris.data";
	ifstream input(data_file_name.c_str());

	string line, tar;
	double a, b, c ,d;
	while(getline(input, line))
	{
		istringstream iss(line);
		vector<double> v;
		iss>>a>>b>>c>>d>>tar;
		examples.push_back({a, b, c, d});
		target.push_back(tar);
	}
	input.close();
	vector<vector<double>> test, train;
	vector<string> tar_test, tar_train;

	for(int i = 0; i < (int) examples.size(); ++i)
	{
		if(i%50 >= 40) test.push_back(examples[i]), tar_test.push_back(target[i]);
		else train.push_back(examples[i]), tar_train.push_back(target[i]);
	}
	KNN knn;
	knn.set_data(train, tar_train, 3);
	for(int i = 0; i < (int)test.size(); ++i)
	{
		auto ans = knn.classify(test[i]);
		cout<<'<';
		for(auto& j:test[i]) cout<<j<<", ";
		cout<<tar_test[i]<<">\t the answer is "<<ans<<endl;
	}
}

int main()
{
	iris();
	return 0;
}
