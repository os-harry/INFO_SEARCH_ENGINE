#ifndef EVALUATE_H
#define EVALUATE_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include "include/thulac.h"
#define pb push_back
#define mp make_pair
typedef long long LL;

namespace EVL
{
	using namespace std;
	
	const LL TLV = 3;
	const LL LENG_PARA = 65536;
	const LL MAX_SIZE = 8192;

	class PLN
	{
		public:
			PLN *pre, *next;
			LL diff,num;
			PLN();
	};

	class Node
	{
		public:
			LL snum,sum;
			PLN *dtl;
			Node();
	};
	
	bool Blank(const char);
	void Add(const string&, LL&);
	string To_String(LL);
	void Input_Query(const string&, map<string,Node*>&, LL&, THULAC&);
	void Count(map<string,Node*>&, double deno_t[MAX_SIZE], double nume_t[MAX_SIZE], const string, double, const LL);
	void Evaluate(const string&, map<string,Node*>&, vector<LL>&, LL&, const LL, THULAC&);
}

#endif
