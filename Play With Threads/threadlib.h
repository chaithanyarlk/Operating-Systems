#include<pthread.h>
#include<signal.h>
int create_pt (pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg){
     return pthread_create(thread, attr,start_routine,arg);
}
int join_pt(pthread_t thread, void **value_ptr){
     return pthread_join( thread,value_ptr);
}
void exit_pt(void *value_ptr){
     pthread_exit(value_ptr);
}
void (*signal(int sig, void (*func)(int)))(int);

