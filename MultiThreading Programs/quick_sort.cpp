#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

using namespace std;

int i=0;
pthread_t threads[5];


int x[20];

struct thread_data{
    int  upper_bound;
    int lower_bound;
    int *arr;
};
int semid;



void set_sem()
{
    semid=semget(12345,1,IPC_CREAT|0666);
    perror("semget");
    semctl(semid,0,SETVAL,5);
}
int get_sem()
{
    return semctl(semid,0,GETVAL,0);
}

void create_thread(int x[20], int first, int last);


sembuf psembuf={0,-1,SEM_UNDO};
sembuf vsembuf={0,1,SEM_UNDO};


void *quicksort(void *threadarg)
{

    int getv;
    semop(semid,&psembuf,1);
    getv=get_sem();
    cout<<"semaphore value  decrease to  "<<getv;
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    int first,last;
    first=my_data->upper_bound;
    last=my_data->lower_bound;
     int pivot,j,temp,i;
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        cout<<"\nbefore done firts loop i = "<<i<<"j="<<j<<endl;
        for(int w=first;w<=last;w++) {
         
            cout<<endl<<"x["<<w<<"] ="<< *((my_data->arr) +w)<<endl;
        }
        while(i<j){
            while(*((my_data->arr)+i) <= *((my_data->arr)+pivot) && i<last)
                i++;
            while(*((my_data->arr)+j) > *((my_data->arr)+pivot) && j>first)
                j--;
            if(i<j){
                temp=*((my_data->arr)+i);
                *((my_data->arr)+i)=*((my_data->arr)+j);
                *((my_data->arr)+j)=temp;
            }
         
        }
        cout<<"\ndone firts loop\n"<<endl<<first<<endl<<last<<endl;

        temp=*((my_data->arr)+pivot);
        *((my_data->arr)+pivot)=*((my_data->arr)+j);
        *((my_data->arr)+j)=temp;
        for(int t = first;t<=last;t++)
            cout<<*((my_data->arr)+t)<<endl;
        for(int w=first;w<=last;w++) {
         
            cout<<endl<<"x["<<w<<"] ="<< my_data->arr[w]<<endl;
        }
        if (first < j-1) {
            cout<<"create thread first = "<<first<<"last = "<<j-1<<endl;
            create_thread(x,first,j-1);
        }
        else if (first == j-1 && my_data->arr[first]>my_data->arr[j]) {
            temp = my_data->arr[first];
            my_data->arr[first] = my_data->arr[j];
            my_data->arr[j] = temp;
        }

        if (j+1<last)
        {
            cout<<"create thread first = "<<j+1<<"last = "<<last<<endl;
            create_thread(x,j+1,last);
        }
        else if (j+1 == last && my_data->arr[last]< my_data->arr[j])
        {
            temp = my_data->arr[last];
            my_data->arr[last] = my_data->arr[j];
            my_data->arr[j] = temp;
        }
     
    }

 
 
 
    semop(semid,&vsembuf,1);

    // pthread_exit(NULL);
}


void create_thread(int x[20],int first, int last)
{
    int rc=0;
    i++;

    pthread_attr_t attr;
    void *status;
    int  getv;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    cout<<" entered create thread" << i <<endl<<"first"<<first<<"last"<<last;
    struct thread_data td;
    td.upper_bound=first;
    td.lower_bound=last;
    td.arr=x;
    getv=get_sem();
    cout<<"semaphore value is  "<<getv<<endl;
    if(getv <  1 )
    {
        sleep(5);
    } 
    rc = pthread_create(&threads[i], NULL,
            quicksort, (void *)&td);
    if (rc){
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }


    pthread_attr_destroy(&attr);
    rc = pthread_join(threads[i], &status);
    if (rc){
        cout << "Error:unable to join," << rc << endl;
        exit(-1);
    }

    cout<<"existing";

 
}


int main()
{

    int size,i;

    cout<<"Enter size of the array: ";
    cin>>size;

    cout<<"Enter  elements: ";
    for(i=0;i<size;i++)
        cin>>x[i];
    cout<<" hello "<<endl;


    set_sem();

    cout<<"semaphore set to "<<get_sem();
    create_thread(x,0,size-1);

    cout<<"Sorted elements: "<<endl;
    for(i=0;i<size;i++)
        cout<<x[i]<<" "<<endl;

    return 0;
}
