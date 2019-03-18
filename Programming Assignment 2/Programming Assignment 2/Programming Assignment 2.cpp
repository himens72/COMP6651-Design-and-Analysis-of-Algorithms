// Programming Assignment 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

int *cost;

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
	}
	return 0;
}
void generateOutputFile(/*char* outputFile*/) {

}
int main(int argc, char* argv[])
{
	if (readInputFile(/*argv[1]*/) == -1) {
	
	}
	if (readCostFile(/*argv[3]*/) == -1) {

	}
	for (int i = 0; i <= 10000; i++) {
		
		cout << cost[i] << endl;
	}
	generateOutputFile(/*argv[2]*/);
}