
//KNN
#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

//knn大类
class knn
{
private:
	double traindata[11][2] = {};  //test data
	double testdata[2] = {};	   //训练集{ 2.0, -1.0 }
	char labels[11] = {};		   //标签
	map<int, pair<double, double>>data;
	//  map<int, pair<double, double>>::iterator iter = data.begin(); 这里的data还没被初始化不能给首地址，因为初始化后会变的。
	int k;							//k类
	struct distance
	{
		int dex;
		double distances;
	};
	distance s[11];

public:
	knn();
	double get_distance();//距离
	char k_results();
	/*struct cmp
	{*/
	static  bool fuc(distance x, distance y)//这个地方要加static，在类外定义用于sort函数就不用
	{
		return x.distances < y.distances;
	}
	//};
	/*struct cmp//sort(s,s+10,cm());
	{
	bool fuc(distance x, distance y)
	{
	return x.distances < y.distances;
	}
	};*/
};

knn::knn()
{
	//读文件数据
	ifstream infile;
	infile.open("D:\\code\\test\\data.txt");   //将文件流对象与文件连接起来 
	if (!infile)							   //若失败,则输出错误消息,并终止程序运行 
	{
		cout << "there are errors during reading file " << endl;
	}
	for (int i = 0; i < 11; i++)
	{
		infile >> traindata[i][0] >> traindata[i][1] >> labels[i];
		data.insert({ i, { traindata[i][0], traindata[i][1] } });
		//iter->first = i;这个地方是错的，因为键值在map里面是const变量，不能这样赋值
		//(iter->second).first = traindata[i][0];  这个可以这样赋值
		//(iter->second).second = traindata[i][1];
		//iter++;
	}
	infile.close();             //关闭文件输入流 

	cout << "please input the testdata" << endl;
	cin >> testdata[0] >> testdata[1];
	cout << "please input the K" << endl;
	cin >> k;

}
//计算距离  
double knn::get_distance()
{
	map<int, pair<double, double>>::iterator iter = data.begin();
	for (int i = 0; i < 11; i++)
	{

		s[i].dex = i;
		s[i].distances = sqrt(pow((traindata[i][0] - testdata[0]), 2) + pow((traindata[i][1] - testdata[1]), 2));
		cout << "the index :" << iter->first << ' ' << (iter->second).first << ',' << (iter->second).second << " the distance =" << s[i].distances << "the label is" << labels[i] << endl;
		iter++;
	}
	return 0.0;
}
//输出结果
char knn::k_results()
{
	int a = 0, b = 0;
	sort(s, s + 10, fuc);
	for (int i = 0; i < k; i++)
	{
		cout << "the index :" << s[i].dex << " the distance =" << s[i].distances << "the label is" << labels[s[i].dex] << endl;
		{
			switch (labels[s[i].dex])
			{
			case 'A':a++; break;
			case 'B':b++; break;
			}
		}
	}
	if (a >= b)
		return 'A';
	else
		return 'B';
}


int main()
{
	while (1)
	{
		knn h;
		h.get_distance();
		cout << h.k_results() << endl;
	}
	return 0;
}