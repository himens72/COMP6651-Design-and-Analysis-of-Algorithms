// Programming Assignment 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include<vector>

using namespace std;

int *cost;
vector < vector < int > > optimalPayment;
vector < int > optimalCost;
ofstream OUTPUT_FILE("output.txt");


/* arr[] ---> Input Array
data[] ---> Temporary array to
store current combination
start & end ---> Staring and
Ending indexes in arr[]
index ---> Current index in data[]
r ---> Size of a combination to be printed */
void calculateOptimalCost(int period, int credit, int balance, vector < int > ways) {
	vector< int > tempOptimalPayment;
	int newBalance = balance;
	bool flag = false;
	int payment = 0;
	int oCost = 0;
	for (int i = 0; i < ways.size(); i++) {
		tempOptimalPayment.push_back(ways[i]);
		newBalance += ways[i];
		payment = 0;
		for (int j = 0; j < tempOptimalPayment.size(); j++) {
			payment += tempOptimalPayment[j];
		}
		if (!(balance >= (payment - (credit * (i+ 1))))) {
			flag = true;
			break;
		}
	}
	if (!flag && payment == (period * credit) && payment >= credit * (ways.size())) {
		vector < int > temp;
		OUTPUT_FILE << payment << " =  " << (period * credit) << " : Balance " << newBalance << " - > ";
		for (int i = 0; i < ways.size(); i++) {
			temp.push_back(ways[i]);
			oCost += cost[ways[i]];
			OUTPUT_FILE << ways[i] << " ";
		}
		OUTPUT_FILE << "Cost : " << oCost << endl;
		optimalCost.push_back(oCost);
		optimalPayment.push_back(temp);
	}
}
void combinationUtil(int period, int credit, int balance, int arr[], int data[], int start, int end, int index, int r)
{
	// Current combination is ready 
	// to be printed, print it  
	if (index == r)
	{
		vector < int > temp;
		for (int j = 0; j < r; j++) {
			temp.push_back(data[j]);
	//		OUTPUT_FILE << j << " ---- > " << data[j] << " ";

		}
		calculateOptimalCost(period,credit,balance,temp);
		temp.clear();
		//OUTPUT_FILE << endl;
		return;
	}

	// replace index with all possible  
	// elements. The condition "end-i+1 >= r-index" 
	// makes sure that including one element  
	// at index will make a combination with  
	// remaining elements at remaining positions  
	for (int i = start; i <= end && end - i >= r - index && arr[i] >= 0; i++)
	{
		data[index] = arr[i];
		combinationUtil(period, credit, balance, arr, data, i, end, index + 1, r);
	}
}

// The main function that prints  
// all combinations of size r  
// in arr[] of size n. This function 
// mainly uses combinationUtil()  
void generateCombination(int period, int credit, int balance, int arr[], int n, int r)
{
	// A temporary array to store 
	// all combination one by one  
	int *data = new int[r];

	// Print all combination using 
	// temprary array 'data[]'  
	combinationUtil(period, credit, balance,arr, data, 0, n + 1 , 0, r);
}

void calculateOptimalCost(int n, int a, int b) {

	for (int i = 0; i < n; i++) {
		int index = 0;
		for (int k = n * a; k >= 0; k--) {
			int cheque = k;
		}
	}
	
}
int readCostFile(/*char* costFile*/) {
	//ifstream file(costFile);
	ifstream file("cost.txt");
	cout << "Inside Cost File " << endl;
	if (!file) {
		cout << "Unable to load Cost file" << endl;
		return -1;
	}
	cost = new int[10001];
	for (int i = 0; i <= 10000; i++) {
		int d;
		int c;
		file >> d >> c;
		cost[i] = c;
	}
	return 0;
}
int readInputFile(/* char* inputFile */) {
	//ifstream file(inputFile);
	ifstream file("intest.txt");
	if (!file) {
		cout << "Unable to load Input file" << endl;
		return -1;
	}
	int data;
	file >> data;
	for (int i = 0; i < data; ++i) {
		int n;
		int a;
		int b;
		file >> n >> a >> b;
		cout << n << " " << a << " " << endl;
		int *array = new int[(n * a) + 2];
		int count = 0;
		for (int i = n * a; i >= 0; i--) {
			array[count] = i;
			count++;
		}
		array[(n * a) + 1] = -1;
		generateCombination(n , a, b,array, (n*a) + 2, n);
		OUTPUT_FILE << "------------------------------->" << endl;
		calculateOptimalCost(n, a, b);
	}
	return 0;
}
void generateOutputFile(/*char* outputFile*/) {

}
int main(int argc, char* argv[])
{
	if (readCostFile(/*argv[3]*/) == -1) {

	}
	if (readInputFile(/*argv[1]*/) == -1) {
	
	}
	
	generateOutputFile(/*argv[2]*/);
}