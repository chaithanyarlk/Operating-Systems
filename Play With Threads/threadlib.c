#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threadlib.h"
#define PROCESS 5
#define Q 2

int times[PROCESS];
char pros[PROCESS] = {'a', 'b', 'c', 'd', 'e'};
int turn = 0;

void execute_next(int i) {
	int next = (i + 1) % PROCESS;
	while (times[next] <= 0) {
		if (next == i) {
			return;
		}
		next = (next + 1) % PROCESS;
	}
	turn = next;
}

void* execute (void* arg) {
	int i = (int)arg;
	while (times[i] != 0) {
		while (turn != i);
		if (times[i] >= Q) {
			printf("%c executed for %dms\n", pros[i], Q);
			times[i] -= Q;
		}else {
			if (times[i] > 0 && times[i] < Q) {
				printf ("%c executed for %dms\n", pros[i], (times[i]));
				times[i] = 0;
			}
		}
		execute_next(i);
	}
	exit_pt(NULL);
}

int main() {
	printf("Assumption: No. of processes = 5\nArrival times of all processes = 0ms\n");
	printf("Enter burst times of 5 processes:\n");
	for (int i = 0; i < PROCESS; i++) {
		scanf ("%d", &times[i]);
	}
	pthread_t pt[PROCESS];
	for (int i = 0; i < PROCESS; i++) {
		create_pt(&pt[i], NULL, &execute, (void*)i);
	}
	for (int i = 0; i < PROCESS; i++) {
		join_pt(pt[i], NULL);
	}
}
