#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include<bits/stdc++.h> 

using namespace std;

class Organized
{
        public:
                void makepairs(int factors, int levels);
		int totalpairs();
		int pairscovered();
		vector<int> findpair();
		void storevals(int f, int l);
		void makecovered(vector<int> &place);
		int paircount(int val, vector<int> &poss);
		vector<vector<int>> candidateselect(vector<int> &vals);
		void reset();
        private:
                unordered_map<int, vector<int>> pairsets;
		unordered_map<int, bool> cov;
		vector<int> keys;
		int levels;
		int factors;
		int covered;
};


