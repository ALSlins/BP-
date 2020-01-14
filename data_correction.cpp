/*
"timestamp" - timestamp field for grouping the data
"cnt" - the count of a new bike shares   //int
"t1" - real temperature in C    //double
"t2" - temperature in C "feels like"    //double
"hum" - humidity in percentage    //double
"wind_speed" - wind speed in km/h     //double
"weather_code" - category of the weather
"is_holiday" - boolean field - 1 holiday / 0 non holiday
"is_weekend" - boolean field - 1 if the day is weekend
"season" - category field meteorological seasons: 0-spring ; 1-summer; 2-fall; 3-winter.

"weathe_code" category description:
1 = Clear ; mostly clear but have some values with haze/fog/patches of fog/ fog in vicinity
2 = scattered clouds / few clouds
3 = Broken clouds
4 = Cloudy
7 = Rain/ light Rain shower/ Light rain
10 = rain with thunderstorm
26 = snowfall
94 = Freezing Fog
*/
#include "data_correction.h"

void data_correction::assignment( vector<DATA::bp_data> &ans, vector<DATA::bp_data> &test)
{
	ifstream infile;
	infile.open("london_merged.csv");
	string temp;//读取csv
	getline(infile, temp);//跳过开头

	string temp_month, temp_day, temp_hour, temp_cnt, temp_t, temp_hum, temp_wind;
	string later_month = "01", later_day = "03", later_hour = "00";
	int line = 1;

	while (getline(infile, temp))
	{
		++line;
		int flag = 0;//,的数目
		if (temp[3] == '7') break;

		temp_month += temp[5], temp_day += temp[8], temp_hour += temp[11];//计算月份天数小时
		temp_month += temp[6], temp_day += temp[9], temp_hour += temp[12];

		for (int i = 0; i < temp.length(); ++i)
		{
			if (temp[i] == ',')++flag;
			if (flag == 1 && temp[i] != ',') temp_cnt += temp[i];
			if (flag == 2 && temp[i] != ',')temp_t += temp[i];
			if (flag == 4 && temp[i] != ',')temp_hum += temp[i];
			if (flag == 5 && temp[i] != ',')temp_wind += temp[i];
			if (flag == 6)break;
		}

		//修改ans
		if (later_day != temp_day) ans.push_back(DATA::bp_data(stod(temp_month), stod(temp_day), temp[temp.length() - 7] - '0' + temp[temp.length() - 11] - '0', temp[temp.length() - 3] - '0'));
		ans[ans.size() - 1].cnt.push_back(stod(temp_cnt));
		ans[ans.size() - 1].t.push_back(stod(temp_t));
		ans[ans.size() - 1].hum.push_back(stod(temp_hum));
		ans[ans.size() - 1].wind_speed.push_back(stod(temp_wind));

		//初始化相关值
		temp_t.clear(), temp_hum.clear(), temp_wind.clear();
		later_day = temp_day, later_hour = temp_hour, later_month = temp_month;
		temp_day.clear(), temp_hour.clear(), temp_month.clear(), temp_cnt.clear();
	}

	//将17年数据输入测试集
	while (1)
	{
		++line;
		int flag = 0;//,的数目

		temp_month += temp[5], temp_day += temp[8], temp_hour += temp[11];//计算月份天数小时
		temp_month += temp[6], temp_day += temp[9], temp_hour += temp[12];

		for (int i = 0; i < temp.length(); ++i)
		{
			if (temp[i] == ',')++flag;
			if (flag == 1 && temp[i] != ',') temp_cnt += temp[i];
			if (flag == 2 && temp[i] != ',')temp_t += temp[i];
			if (flag == 4 && temp[i] != ',')temp_hum += temp[i];
			if (flag == 5 && temp[i] != ',')temp_wind += temp[i];
			if (flag == 6)break;
		}

		//修改test
		if (later_day != temp_day) test.push_back(DATA::bp_data(stod(temp_month), stod(temp_day), temp[temp.length() - 7] - '0' + temp[temp.length() - 11] - '0', temp[temp.length() - 3] - '0'));
		test[test.size() - 1].cnt.push_back(stod(temp_cnt));
		test[test.size() - 1].t.push_back(stod(temp_t));
		test[test.size() - 1].hum.push_back(stod(temp_hum));
		test[test.size() - 1].wind_speed.push_back(stod(temp_wind));

		//初始化相关值
		temp_t.clear(), temp_hum.clear(), temp_wind.clear();
		later_day = temp_day, later_hour = temp_hour, later_month = temp_month;
		temp_day.clear(), temp_hour.clear(), temp_month.clear(), temp_cnt.clear();

		if (!getline(infile, temp)) break;
	}

	infile.close();
}