#include "std_lib_facilities.h"
#include "data_correction.h"
#include "data_forecasting.h"



data_correction solution;//�������ݶ�ȡ
bp_forecasting fore;//����Ԥ�⣬������
bp net;//����ѵ��ģ�ͣ�������
//��������
vector<DATA::bp_data> bp_d;//ѵ����
vector<DATA::bp_data> bp_t;//���Լ�
vector<double> w_array;//ģ��Ȩ����
bool flag_dirty = 0;
bool flag_repair = 0;

int main()
{
	solution.assignment( bp_d, bp_t);//��ȡ����
	//ʹ��Ԥ��ģ��Ԥ��
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
	//ѵ��bpģ��
	net.a_bp(bp_d);
	net.train(bp_d);

	return 0;
}