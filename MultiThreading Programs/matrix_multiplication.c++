#include<bits/stdc++.h>
using namespace std;

#define MAX 4
#define MAX_THREAD 4

int matA[MAX][MAX]; 
int matB[MAX][MAX]; 
int matC[MAX][MAX]; 
int step_i = 0;

void* multi (void*args){
     int core = step_i++;
     for (int i = core * MAX / 4; i < (core + 1) * MAX / 4; i++)  
        for (int j = 0; j < MAX; j++)  
            for (int k = 0; k < MAX; k++){  
                matC[i][j] += matA[i][k] * matB[k][j];}
     
     return NULL;
}

int main(){
     for(int i =0;i<MAX;i++){
          for(int j = 0;j<MAX ; j++){
               matA[i][j] = rand()%10;
               matB[i][j]= rand()%10;
          }
     }
     cout<<"Matrice A"<<endl;
     for(int i =0;i<MAX;i++){
          for(int j=0;j<MAX;j++){
               cout<<matA[i][j]<<"\t";
          }
          cout<<"\n";
     }
     cout<<"Matrice B"<<endl;
     for(int i =0;i<MAX;i++){
          for(int j=0;j<MAX;j++){
               cout<<matB[i][j]<<"\t";
          }
          cout<<"\n";
     }
     pthread_t threads[MAX_THREAD];
     for(int i =0;i<MAX_THREAD;i++){
          pthread_create(&threads[i],NULL,multi,NULL);
     }
     for (int i = 0; i < MAX_THREAD; i++)  
        pthread_join(threads[i], NULL);
     cout<<"Matrice C final "<<endl;
     for(int i =0;i<MAX;i++){
          for(int j=0;j<MAX;j++){
               cout<<matC[i][j]<<"\t";
          }
          cout<<"\n";
     }
}
