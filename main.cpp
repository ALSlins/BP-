#include "std_lib_facilities.h"
#include "data_correction.h"
#include "data_forecasting.h"



data_correction solution;//用于数据读取
bp_forecasting fore;//用于预测，任务四
bp net;//用于训练模型，任务四
//储存数据
vector<DATA::bp_data> bp_d;//训练集
vector<DATA::bp_data> bp_t;//测试集
vector<double> w_array;//模型权矩阵
bool flag_dirty = 0;
bool flag_repair = 0;

int main()
{
	solution.assignment( bp_d, bp_t);//读取数据
	//使用预设模型预测
	fore.a_bp_forecasting();
	vector<int> a, b;
	for (int i = 0; i < bp_t.size(); ++i)
	{
		for (int j = 0; j < bp_t[i].cnt.size(); ++j)
		{
			a.push_back(fore.forcecast_cnt(bp_t[i].month, bp_t[i].day, j, bp_t[i].vacation, bp_t[i].season, bp_t[i].t[j], bp_t[i].hum[j], bp_t[i].wind_speed[j])), b.push_back(bp_t[i].cnt[j]);
			cout << "forecast: " << a[a.size() - 1] << "  reality: " << bp_t[i].cnt[j];
			cout << "  error: " << a[a.size() - 1] - bp_t[i].cnt[j];
			cout << "  rate: " << (a[a.size() - 1] - bp_t[i].cnt[j]) / bp_t[i].cnt[j] << endl;
		}
	}
	//训练bp模型
	net.a_bp(bp_d);
	net.train(bp_d);

	return 0;
}