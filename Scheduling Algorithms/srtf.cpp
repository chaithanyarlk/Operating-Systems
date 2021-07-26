#include<bits/stdc++.h>
#include<iostream>
#include<thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int times[] = {5, 2, 3, 4, 2};
int turn = 0;

int findShortestJob()     //choose the next thread to run
{	
    int min = times[0], pos = 0;
    for(int i = 1; i < 5; i = (i + 1)) {
	if(times[i] < min) {
		min = times[i];
		pos = i;
	}
    }
    if(min == 99999)
	return -1;
    return pos;
}


void sjf(int a) {
	turn = findShortestJob();
	while(turn != a-1);
	Sleep(times[a-1]);
	cout<<"Thread "<<a<<"executed for "<<times[a-1]<<" 1 seconds\n";
     if(times[a-1]-1>1)
	times[a-1] --;
     else
     times[a-1] = 99999;
	turn = findShortestJob();
}

int main() {
	thread t1(sjf, 1);
	thread t2(sjf, 2);
	thread t3(sjf, 3);
	thread t4(sjf, 4);
	thread t5(sjf, 5);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	return 0;
}