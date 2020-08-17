#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <ctime>
#include "AETGhelp.h"

using namespace std;

int main()
{
	srand(time(NULL)); //prep for random number generator

	//list of variables to be used
	int levels, factors, randompick;
	double timepassed;
	vector<int> pairfound;
	int coveredpairs=0;
	int possiblepairs=0;
	vector<int> candidates;

	//prompt user for factor and levels
	cout << "Enter number of factors: ";
	cin >> factors;
	cout << "Enter number of levels: ";
	cin >> levels;

	Organized org;

	//starts clock to see how long program will take
	clock_t begin = clock();

	org.storevals(factors, levels);//stores the factors and levels into class
	org.makepairs(factors, levels);//makes all pairs possible for given information

	vector<vector<int>> overallbest(1023940);//holder for the best 
	vector<vector<int>> testingsuites;//temp holder for all test suites
	vector<vector<int>> worstsuite(0);//holder for the highest number of test cases
	vector<int> average;//vector of all lengths
	vector<vector<int>> temptest;//temporary value to compare
	vector<int> candidbest;//best candidate picked
	int maxedpair=0;//maked number of pairs

	for(int runs=0; runs<100; runs++)//makes 100 testsuites
	{

		testingsuites.clear();//clears the temporary holder
		//continously loops until all pairs are covered
		while(org.pairscovered() < org.totalpairs())
		{
			//creates 50 candidates to see which is the best
			for(int rands=0; rands<50; rands++)
			{
				int place =0;

				pairfound = org.findpair();//gets a random pair to start
				candidates.resize(factors,-1);//sets the vector to -1 for searching purposes

				place = pairfound[0]/levels;//finds the correct place in the test case to put the value
				candidates[place]=pairfound[0];//places the value in the test case

				place = pairfound[1]/levels;//finds the correct place in the test case to put the value
				candidates[place]=pairfound[1];//places the value in the test case

				temptest=org.candidateselect(candidates);//generates a full test case with max pairs matched

				if(temptest[1][0]>maxedpair)
				{
					candidbest.clear();//get rid of old best
					candidbest=temptest[0];//sets the new best
					maxedpair=temptest[1][0];//updates max
				}
				else if(temptest[1][0] == maxedpair)
				{
					int tr = rand()%2;//randomly picks if to keep the old best or the new best
					if(tr==0)
					{
						candidbest.clear();//get rid of old best
						candidbest=temptest[0];//set with new best
					}
				}
				candidates.clear();
				temptest.clear();

			}


			testingsuites.push_back(candidbest);//inserts new best to the test suite
			org.makecovered(candidbest);//makes all pairs covered permenately
			maxedpair=0;//resets max to 0 for next loop

		}

		average.push_back(testingsuites.size());//pushes back the size to averages for later

		if(testingsuites.size() < overallbest.size())//check if new test suite has less then previous best
		{
			overallbest.resize(testingsuites.size());
			overallbest=testingsuites;
		}
		else if(testingsuites.size() > worstsuite.size())//checks if new test suite has more the previous worst
		{
			worstsuite.resize(testingsuites.size());
			worstsuite=testingsuites;
		}

		testingsuites.clear();//clean completely
		org.reset();//reset the covered pairs for reloop
	}

	timepassed = (clock()-begin)/(double)CLOCKS_PER_SEC;//gets the total time

	cout << "Time elapsed: " << timepassed << endl;//prints total time spent
	cout << "Best Test Suite Size: " << overallbest.size() <<endl; // prints the size of the best
	cout << "Worst Test Suite Size: " << worstsuite.size() <<endl; //prints the size of the worst
	int avgval=0;//variable for average

	//loop to calculate average
	for(int i=0; i< average.size(); i++)
	{
		avgval+=average.at(i);
	}

	cout <<"Average Test Suite Size:"<<avgval/(average.size()) <<endl;//prints the average

	cout << "Wiriting best suite to 'testsuitefile.txt'" << endl;

	ofstream senddata;//opening stream
	senddata.open("4^40");//creating file

	senddata << overallbest.size() << endl<<endl;;//sends the size
	//looping through the overall best send
	for(int i=0; i< overallbest.size(); i++)
	{
		for(int j=0; j<overallbest[i].size(); j++)
		{
			senddata << overallbest[i][j] << " ";
		}
		senddata << endl;
	}

	return 0;
}
