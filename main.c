#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"
#include "pthread.h"
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int k = 0;
int k2 = 0;
int k3 = 0;
int thread_11_started = 0;

sem_t *sem_1;
sem_t *sem_2;

typedef struct{
    int thread_number;
    sem_t *sem1;
    sem_t *sem2;
    sem_t *sem3;
    sem_t *sem4;
    sem_t *sem5;
}TH_STRUCT;

void *thread_synchronization1(void *p){
     TH_STRUCT* param = (TH_STRUCT*) p;
    
    if(param->thread_number == 1) {
        sem_wait(param->sem1);
    }

    if(param->thread_number == 3){
        sem_wait(sem_2);
    }

    info(BEGIN, 9, param->thread_number);

    if(param->thread_number == 4) {
        sem_post(param->sem1);
        sem_wait(param->sem2);
    }

    info(END, 9, param->thread_number);

    if(param->thread_number == 3){
        sem_post(sem_1);
    }
    
    if(param->thread_number == 1) {
        sem_post(param->sem2);
    }
    return NULL;
}

void *thread_synchronization2(void *p){
     TH_STRUCT* param = (TH_STRUCT*) p;
     

    sem_wait(param->sem1);

    if(k3 == 41 && thread_11_started != 1 && param->thread_number != 11){
        sem_wait(param->sem5);
    }

    if(param->thread_number != 11) {
     sem_wait(param->sem4);
         k3++;
     sem_post(param->sem4);
    }

    info(BEGIN, 8, param->thread_number);

     if(param->thread_number == 11){
         thread_11_started = 1;
         for(int i = 0; i < 4; i++){
             sem_post(param->sem5);
         }
         k++;
        sem_wait(param->sem2);
        k++;
     }

     if(k == 1 && param->thread_number != 11){
        sem_wait(param->sem4);
        k2++;
        sem_post(param->sem4);

        if(k2 == 4){
            sem_post(param->sem2);
        }
        
        sem_wait(param->sem3);
     }

    info(END, 8, param->thread_number);

   

    if(param->thread_number == 11) {
        for(int i = 0; i < 4; i++) {
            sem_post(param->sem3);
        }
    }

    sem_post(param->sem1);
    return NULL;
}

void *thread_synchronization3(void *p){
     TH_STRUCT* param = (TH_STRUCT*) p;
    
    

    if(param->thread_number == 1){
        sem_wait(sem_1);
    }

    info(BEGIN, 4, param->thread_number);

  
    info(END, 4, param->thread_number);

    if (param->thread_number == 3) {
        sem_post(sem_2);
    }

  
    return NULL;
}

int main()
{
    init();

    info(BEGIN, 1, 0);

    sem_1 = sem_open("sem_1", O_CREAT, 0644, 0);
    sem_2 = sem_open("sem_2", O_CREAT, 0644, 0);

    pid_t pid2 = -1, pid3 = -1, pid4 = -1, pid5 = -1, pid6 = -1, pid7 = -1, pid8 = -1, pid9 = -1;

    pid2 = fork();
    if (pid2 == 0)
    {
        info(BEGIN, 2, 0);

        pid4 = fork();

        if (pid4 == 0)
        {
            info(BEGIN, 4, 0);

             pthread_t threads[4];
                TH_STRUCT params[4];
                
                for(int i = 0; i < 4; i++){
                    params[i].thread_number = i+1;
                    pthread_create(&threads[i], NULL, thread_synchronization3, &params[i]);
                }

                for(int i = 0; i < 4; i++){
                    pthread_join(threads[i],NULL);
                }
                
            info(END, 4, 0);
        }
        else
        {
            pid7 = fork();
            if (pid7 == 0)
            {
                info(BEGIN, 7, 0);

                info(END, 7, 0);
            }
            else {
            pid9 = fork();
            if (pid9 == 0){
                info(BEGIN, 9, 0);

                pthread_t threads[4];
                TH_STRUCT params[4];
                sem_t sem1;
                sem_t sem2;
                sem_init(&sem1, 0, 0);
                sem_init(&sem2, 0, 0);
                

                for(int i = 0; i < 4; i++){

                    params[i].sem1 = &sem1;
                    params[i].sem2 = &sem2;
                    params[i].thread_number = i+1;
                    pthread_create(&threads[i], NULL, thread_synchronization1, &params[i]);
                }

                for(int i = 0; i < 4; i++){
                    pthread_join(threads[i],NULL);
                }
                
                sem_destroy(&sem1);
                sem_destroy(&sem2);

                
                info(END, 9, 0);
  
            }
            }
        }
        if (pid4 != 0 && pid7 != 0 && pid9 != 0)
        {
            waitpid(pid4, NULL, 0);
            waitpid(pid7, NULL, 0);
            waitpid(pid9, NULL, 0);
            info(END, 2, 0);
        }
    }
    else
    {
        pid3 = fork();
        if (pid3 == 0)
        {
            info(BEGIN, 3, 0);

            pid6 = fork();

            if (pid6 == 0)
            {
                info(BEGIN, 6, 0);

                info(END, 6, 0);
            }
            else {
                pid8 = fork();
                if (pid8 == 0)
                {
                    info(BEGIN, 8, 0);

                    pthread_t threads[46];
                TH_STRUCT params[46];
                sem_t sem1;
                sem_t sem2;
                sem_t sem3;
                sem_t sem4;
                sem_t sem5;
                sem_init(&sem1, 0, 5);
                sem_init(&sem2, 0, 0);
                sem_init(&sem3, 0, 0);
                sem_init(&sem4, 0, 1);
                sem_init(&sem5, 0, 0);
                

                for(int i = 0; i < 46; i++){

                    params[i].sem1 = &sem1;
                    params[i].sem2 = &sem2;
                    params[i].sem3 = &sem3;
                    params[i].sem4 = &sem4;
                    params[i].sem5 = &sem5;
                    params[i].thread_number = i+1;
                    pthread_create(&threads[i], NULL, thread_synchronization2, &params[i]);
                }

                for(int i = 0; i < 46; i++){
                    pthread_join(threads[i],NULL);
                }
                
                sem_destroy(&sem1);
                sem_destroy(&sem2);
                sem_destroy(&sem3);
                sem_destroy(&sem4);
                sem_destroy(&sem5);

                    info(END, 8, 0);
                }
            }
            if (pid6 != 0 && pid8 != 0)
            {
                waitpid(pid6, NULL, 0);
                waitpid(pid8, NULL, 0);

                info(END, 3, 0);
            }

        }
        else
        {
            pid5 = fork();
            if (pid5 == 0)
            {
                info(BEGIN, 5, 0);

                info(END, 5, 0);
            }

           
        }
    }

     if (pid2 != 0 && pid3 != 0 && pid5 != 0){
            waitpid(pid2, NULL, 0);
            waitpid(pid3, NULL, 0);
            waitpid(pid5, NULL, 0);
            sem_close(sem_1);
            sem_close(sem_2);
            info(END, 1, 0);
    }

    return 0;
}
