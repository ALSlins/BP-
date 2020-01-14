//读取、调整数据并进行储存
//储存每日、每月的cnt值
//仅对2015、2016年数据进行操作
//节日与假日视为等同
//不处理天气代码

#ifndef _data_correction_h
#define _data_correction_h

#include "std_lib_facilities.h"

namespace DATA
{
	struct bp_data//储存数据用于bp网络
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
	void assignment(vector<DATA::bp_data> &ans, vector<DATA::bp_data> &test);//读入数据
};

#endif

