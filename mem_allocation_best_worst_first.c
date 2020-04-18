#include<stdio.h>
#include <stdlib.h>

#define ram_size 50
#define num_process 5
int ram[ram_size] = {0};

void show_ram()
{
    printf("\nstatus of RAM\n");
    for(int i = 0; i < 50; i++)
    {
        printf("%d ", ram[i]);
    }
    printf("\n\n");
}
void refresh() //situation of ram present before operation of any algo
{
    printf("RAM is refreshed. -1 indicates occupied position , and 0 indicates free\n");
    //ram is occupied in few patches. I have arbitarily chosen where to preoccupy ram
    for(int i = 5; i < 10; i++)
        ram[i] = -1; //occupied
    for(int i = 15; i < 21; i++)
        ram[i] = -1; //occupied
    for(int i = 35; i < 41; i++)
        ram[i] = -1; //occupied
    //rest everywhere free
    show_ram();
}

void best_fit(int process[])
{
    printf("best fit algo allocating the memory. Enjoy the process\n");
    show_ram();
    for(int i = 0; i < num_process; i++)
    {
        printf("\ncurrent process %d, size = %d.\n", i, process[i]);
        int lower = 49, higher = 0, start = 0, min_space = 50, diff, index1, index2;
        for(int j = 0; j < ram_size; j++)
        {
            if(ram[j] == 0)
            {
                if(start == 0)
                {
                    start = 1;
                    index1 = j;
                    index2 = j;

                }
                else if(start == 1)
                {
                    index2 = j;
                }
                diff = index2 - index1 + 1;
                if(diff < min_space && diff >= process[i])
                {
                    min_space = diff;
                    lower = index1;
                    higher = index2;
                }
            }
            else
            {
                start = 0;
            }    
        }
        if(min_space == 50)
            printf("sorry. Can't allocate process %d\n", i);
        else
        {
            for(int j = lower; j <= higher; j++)
                ram[j] = i; // i th process stored in ram

            show_ram();
        }
        
    }
    printf("\n\n-------------------------------------------------\n\n");
}
void first_fit(int process[])
{
    printf("first fit algo allocating the memory. Enjoy the process!\nStatus before allocation : \n\n");
    show_ram();
    for(int i = 0; i < num_process; i++)
    {
        printf("\ncurrent process %d, size = %d\n", i, process[i]);
        int index1 = 0, index2 = 0, start = 0, diff;
        for(int j = 0; j < ram_size; j++)
        {
            if(ram[j] == 0)
            {
                if(start == 0)
                {
                    start = 1;
                    index1 = j;
                    index2 = j;

                }
                else if(start == 1)
                {
                    index2 = j;
                }
                diff = index2 - index1 + 1;
                if(diff >= process[i])
                {
                    for(int k = index1; k<= index2; k++)
                        ram[k] = i;//allocated process i to ram
                    break;
                }
            }
            else
            {
                start = 0;
            }
        }
        show_ram();
    }
    printf("\n\n-------------------------------------------------\n\n");
}
void worst_fit(int process[])
{
    printf("worst fit algo allocating the memory. Enjoy the process\n");
    show_ram();
    for(int i = 0; i < num_process; i++)
    {
        printf("\ncurrent process %d, size = %d\n", i, process[i]);
        int lower = 49, higher = 0, start = 0, max_space = 0, diff, index1, index2;
        for(int j = 0; j < ram_size; j++)
        {
            if(ram[j] == 0)
            {
                if(start == 0)
                {
                    start = 1;
                    index1 = j;
                    index2 = j;

                }
                else if(start == 1)
                {
                    index2 = j;
                }
                diff = index2 - index1 + 1;
                if(diff > max_space && diff >= process[i])
                {
                    max_space = diff;
                    lower = index1;
                    higher = index2;
                }
            }
            else
            {
                start = 0;
            }    
        }
        if(max_space == 0)
            printf("sorry. Can't allocate process %d\n", i);
        else
        {
            for(int j = lower; j <= higher; j++)
                ram[j] = i; // i th process stored in ram

            show_ram();
        }
        
    }
    printf("\n\n-------------------------------------------------\n\n"); 
}


int main()
{
    //1. best fit
    //2. worst fit
    //3. first fit
    printf("RAM size is 50. Numbers in the array represent status of RAM.\n");
    printf("'0' : free position\n");
    printf("'-1' : NOT free position\n");
    printf("any other number : preoccupied by that process number\n\n\n");
    int process[num_process]; //array for storing process sizes of various processes
    for(int i = 0; i < num_process; i++)
    {
        process[i] = rand()%51; //taken max size of process to be 50, 
                                //anyways if its > 50,
                                //I would have discarded it
    }
    refresh();

    best_fit(process);
    refresh();  //to free ram

    worst_fit(process);
    refresh();  // to free ram

    first_fit(process);
    return 0;
}