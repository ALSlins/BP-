//��ȡ���������ݲ����д���
//����ÿ�ա�ÿ�µ�cntֵ
//����2015��2016�����ݽ��в���
//�����������Ϊ��ͬ
//��������������

#ifndef _data_correction_h
#define _data_correction_h

#include "std_lib_facilities.h"

namespace DATA
{
	struct bp_data//������������bp����
	{
		double month;
		double day;
		double vacation;
		double season;
		vector<double> t;
		vector<double> hum;
		vector<double> wind_speed;
		vector<double> cnt;

		bp_data(int m = 0, int d = 0, bool v = 0, double s = 0) :month(m), day(d), vacation(v), season(s) {}
	};
}

class data_correction
{
public:
	data_correction() {}
	void assignment(vector<DATA::bp_data> &ans, vector<DATA::bp_data> &test);//��������
};

#endif

