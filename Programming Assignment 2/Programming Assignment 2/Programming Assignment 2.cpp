// Programming Assignment 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include<vector>

using namespace std;
//ofstream OUTPUT_FILE22("outputqqqq.txt");
int *cost;
vector < int > possibleCheque;
vector < vector < int > > optimalPayment;
vector < int > optimalCost;
int PREVIOUS_COST = 10000000;
int *finalPay;

void calculateOptimalPayment(int period, int credit, int balance, vector < int > ways) {
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
		if (!(balance >= (payment - (credit * (i + 1))))) {
			flag = true;
			break;
		}
	}
	if (!flag && payment == (period * credit) && payment >= credit * (ways.size())) {
		vector < int > temp;
		for (int i = 0; i < ways.size(); i++) {
			temp.push_back(ways[i]);
			oCost += cost[ways[i]];
		}
		optimalCost.push_back(oCost);
		optimalPayment.push_back(temp);
	}
}
void paymentUtil(int period, int credit, int balance, int arr[], int data[], int start, int end, int index, int r, int firstCheque) {
	if (index == r) {
		vector < int > temp;
		int tempCost = 0;
		for (int j = 0; j < r; j++) {
			temp.push_back(data[j]);
			tempCost += data[j];
			//		OUTPUT_FILE22 << data[j] << " ";
		}
		//		OUTPUT_FILE22 << " index : " << index<<endl;
		if (tempCost == period * credit)
			calculateOptimalPayment(period, credit, balance, temp);
		temp.clear();
		return;
	}
	for (int i = start; i <= end && end - i >= r - index && arr[i] >= 0; i++) {
		//cout << " i " << i<< endl;
		data[index] = arr[i];
		if (data[0] == firstCheque) {
			//if (index == 0) {
				//	cout << "start ---> " << i << " : end ---> " << end << endl;
			int count = 0;
			bool flag = false;
			for (int k = 0; k < index; k++) {
				count += data[k];
			}
			if (count >= credit * (index)) {
				if (count >= credit * period && index != period) {
					for (int j = index; j < period; j++) {
						data[j] = 0;
					}
					vector < int > temp;
					int tempCost = 0;
					for (int k = 0; k < r; k++) {
						temp.push_back(data[k]);
						tempCost += data[k];
						//				OUTPUT_FILE22 << data[k] << " ";
					}
					//		OUTPUT_FILE22 << " index : " << index << endl;
					if (tempCost == period * credit)
						calculateOptimalPayment(period, credit, balance, temp);
					temp.clear();
					return;
				}
				else if (period == index) {
					data[period - 1] = period * credit - count >= 0 ? period * credit - count : 0;
					vector < int > temp;
					int tempCost = 0;
					for (int k = 0; k < r; k++) {
						temp.push_back(data[k]);
						tempCost += data[k];
						//			OUTPUT_FILE22 << data[k] << " ";
					}
					//		OUTPUT_FILE22 << " index : " << index << endl;
					if (tempCost == period * credit)
						calculateOptimalPayment(period, credit, balance, temp);
					temp.clear();
					return;
				}
				else if (balance >= count - (credit * index)) {
					paymentUtil(period, credit, balance, arr, data, 0, end, index + 1, r, firstCheque);
				}

			}
		}

	}
}
void generateOptimalPayment(int period, int credit, int balance, int arr[], int n, int r, int firstCheque) {
	int *data = new int[r];
	paymentUtil(period, credit, balance, arr, data, 0, n + 1, 0, r, firstCheque);
}

int generateOptimalCost() {
	if (optimalPayment.size() >= 1) {
		int minimumCost = optimalCost[0];
		int index = 0;
		for (int i = 1; i < optimalPayment.size(); i++) {
			if (optimalCost[i] < minimumCost) {
				index = i;
				minimumCost = optimalCost[i];
			}
		}
		for (int i = 0; i < optimalPayment[index].size(); i++) {
			cout << optimalPayment[index][i] << " ";
		}
		cout << endl;
		return minimumCost;
	}
}
int readCostFile(/*char* costFile*/) {
	//ifstream file(costFile);
	ifstream file("cost.txt");
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
void generateCheque(int mainBalance, int period, int amount, int balance, int arr[], int index, int total) {
	int *pay = new int[period];
	int newTotal = total;
	int newBalance = balance;
	pay = arr;
	for (int i = amount * (index + 1) - newTotal; i <= amount * period && index < period && newBalance >= 0; i++) {

		if (((newBalance - newTotal + i + amount * (index + 1)) >= 0)) {
			newTotal += i;
			pay[index] = i;
			newBalance += amount * (index + 1) - newTotal;
			generateCheque(mainBalance, period, amount, newBalance, pay, index + 1, newTotal);
			if (index == (period - 1) && newTotal == amount * period) {
				int tempCost = 0;
				for (int j = 0; j < period; j++) {
					tempCost += cost[pay[j]];
				}
				if (tempCost < PREVIOUS_COST) {
					PREVIOUS_COST = tempCost;
					vector < int > temp;
					int newTempCost = 0;
					int xxx = 0;
					for (int j = 0; j < period; j++) {
						temp.push_back(pay[j]);
						newTempCost += pay[j];
						xxx += cost[pay[j]];
					}
					if (newTempCost == period * amount)
						calculateOptimalPayment(period, amount, mainBalance, temp);
					temp.clear();
				}
			}
			if (newTotal > amount * period) {
				newTotal = total;
				break;
			}
		}
		newTotal = total;
		newBalance = balance;
	}
}

void generateFirstOptimalCheque(int period, int amount, int balance) {
	for (int i = balance + amount; i >= amount; i--) {
		if (/*cost[i] == minimum && */balance >= i - amount) {
			possibleCheque.push_back(i);
		}
	}
}

int readInputFile(/* char* inputFile,  char* outputFile */) {
	
	//ifstream file(inputFile);
	//ofstream OUTPUT_FILE(outputFile);
	ifstream file("intest.txt");
	ofstream OUTPUT_FILE("output.txt");
	if (!file) {
		cout << "Unable to load Input file" << endl;
		return -1;
	}
	int data;
	file >> data;
	for (int i = 0; i < data; ++i) {
		int period;
		int amount;
		int balance;
		file >> period >> amount >> balance;
		if (balance >= 3 && amount >= 50) {
			int *array = new int[period];
			finalPay = new int[period];
			generateCheque(balance, period, amount, balance, array, 0, 0);
			PREVIOUS_COST = 10000000;
		}
		else {
			generateFirstOptimalCheque(period, amount, balance);
			for (int j = 0; j < possibleCheque.size(); j++) {
				int *array = new int[possibleCheque[j] + 2];
				int count = 0;
				for (int k = possibleCheque[j]; k >= 0; k--) {
					array[count] = k;
					count++;
				}
				array[possibleCheque[j] + 1] = -1;
				generateOptimalPayment(period, amount, balance, array, possibleCheque[j] + 2, period, possibleCheque[j]);
				free(array);
			}
		}
		OUTPUT_FILE << generateOptimalCost();
		possibleCheque.clear();
		optimalCost.clear();
		optimalPayment.clear();
		if (i != data - 1)
			OUTPUT_FILE << endl;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if (readCostFile(/*argv[3]*/) == -1) {
		return -1;
	}
	if (readInputFile(/*argv[1],argv[2]*/) == -1) {
		return -1;
	}
	return 0;
}
