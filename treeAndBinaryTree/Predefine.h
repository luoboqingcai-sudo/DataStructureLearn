#pragma once
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW_B -2

typedef int Status;

using namespace std;

//class Visit {
//public:
//	template<class DataType>
//	int operator()(const DataType data)const {
//		cout << data << " ";
//		return 1;
//	}
//};



/*
* return 
*/
class Compare {
public:
	template<class DataType>
	bool operator()(const DataType data, const DataType standard)const {
		return data < standard;
	}
};