#include<iostream>
#include<bits/stdc++.h>
#include<thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int times[] = {1, 2, 3, 4, 2};
int turn = 0;

void fcfs(int a) {

	while(turn != a-1);
	Sleep(times[a-1]);
	turn = a;
	cout<<"Thread "<<a<<"executed for "<<times[a-1]<<" seconds\n";
}

int main() {
	thread t1(fcfs, 1);
	thread t2(fcfs, 2);
	thread t3(fcfs, 3);
	thread t4(fcfs, 4);
	thread t5(fcfs, 5);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	return 0;
}