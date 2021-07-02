#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
pthread_mutex_t widelce[6]; //widelce
int iter = 1;
void *ZajecieFilozofa(void *args) {
    int p = iter;
    iter++;
    //int *p = &args;
    printf("Jestem filozofem nr: %d\n",p);
    time_t tt;
    int zarodek = time(&tt);
    srand(zarodek);   // za zarodek wstawiamy pobrany czas w sekundach
    while(1)
    {
        pthread_mutex_lock(&widelce[(int)p]); //blokada lewego widelca
        printf("Filozof %d podniosl lewy widelec\n",(int)p);

        pthread_mutex_lock(&widelce[(int)(p+1)%5]);
        printf("Filozof %d podnosi prawy widelec\n",(int)p);

        printf("Rozpoczecie jedzenia przez %d filozofa\n",(int)p);
        usleep(rand()%700);
        printf("Zakonczenie jedzenie przez %d filozofa\n",(int)p);

        pthread_mutex_unlock(&widelce[(int)p]);
        printf("Filozof %d odlozyl lewy widelec\n",(int)p);

        pthread_mutex_unlock(&widelce[(int)(p+1)%5]);
        printf("Filozof %d odlozyl prawy widelec\n",(int)p);

        printf("Filozof %d zaczyna myslenie\n", p);
        usleep(rand()%700);
        printf("Filozof %d zakonczyl myslene\n",p);

    }
    return 0;
}

int main(int argc, char* argv[])
{
    int zarodek, i, filozof = 6, pom;
    time_t tt;
    zarodek = time(&tt);
    srand(zarodek);   // za zarodek wstawiamy pobrany czas w sekundach
    //rand()%200 -> to już będzie rand


    pthread_t tid[6];   //filozofowie

    for(i = 1; i<=5; i++)
    {
        if(0 != pthread_mutex_init(&widelce[i],NULL))
        {
            printf("Blad inicjalizacji mutexa %d\n",i);
            return -1;
        }
        if(0 != pthread_create(&tid[i], NULL, ZajecieFilozofa,&i))
        {
            printf("Blad inicjalizacji %d filozofa\n",i);
            return -1;
        }
    }
    
    for(i=0;i<5;i++)
    {
        pthread_join(tid[i], NULL);
    }
    return 0;
}