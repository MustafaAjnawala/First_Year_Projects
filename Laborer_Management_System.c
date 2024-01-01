#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include<unistd.h>
#define max_queue 10

int worker_num = 100;
int front = 0, rear = -1;
char queue[max_queue][40]; // Max 20 characters can be stored

// all time related functions
time_t program_start_time;

struct worker
{
    char name[20];
    int worker_no;
    char task[40];
    int wage_generated;
    time_t entry_time;
    struct worker *next, *prev;
};

typedef struct worker Node;
Node *p, *head = NULL, *new;

void addQ(char task[])
{
    if (rear == max_queue - 1)
    {
        printf("\nThe Tasks queue is full\n");
    }
    else
    {
        rear++;
        strcpy(queue[rear], task);
    }
}

char *delQ()
{
    int i = 0;
    char elem[40];
    if (front == 0 && rear == -1)
    {
        printf("\nThe Task Queue has been emptied\n");
        return NULL;
    }
    else
    {
        strcpy(elem, queue[front]);
        while (i != rear)
        {
            strcpy(queue[i], queue[i + 1]);
            i++;
        }
        rear--;
    }
    char *ans = strdup(elem);
    return ans;
}

Node *accept()
{
    char s[40];
    time_t time_var;
    Node *temp;
    temp = malloc(sizeof(Node));
    if (temp == NULL)
    {
        printf("Memory not Allocated");
        exit(0);
    }
    else
    {
        printf("\nEnter Worker Name: ");
        scanf("%s", temp->name);      // Use %s to read a string
        temp->worker_no = worker_num; // Assign the worker number
        printf("Worker Number Generated = %d\n", worker_num++);

        time_var = time(NULL);
        temp->entry_time = difftime(time_var, program_start_time);
        printf("Entry Time of the Worker: %ld\n", temp->entry_time);

        strcpy(s, delQ()); // Delete the frontmost task from the queue
        strcpy(temp->task, s);
        printf("Task Allotted: %s\n", temp->task);
        temp->next = NULL;
        temp->prev = NULL;
    }
    return temp;
}

void enter_tasks()
{
    int ctr = 0, ch;
    char task[40];

    printf("\nPlease enter all tasks to be done on-site today\nMENU\n");
    printf("1. Material Handling (bricks, concrete)\n");
    printf("2. Unloading Goods Truck\n");
    printf("3. Concrete Mixing\n");
    printf("4. Site Cleanup\n");
    printf("5. Assemble Scaffoldings\n");

    do
    {
        printf("\nEnter Choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            strcpy(task, "Material Handling (bricks, concrete)");
            addQ(task);
            break;
        case 2:
            strcpy(task, "Unloading Goods Truck");
            addQ(task);
            break;
        case 3:
            strcpy(task, "Concrete Mixing");
            addQ(task);
            break;
        case 4:
            strcpy(task, "Site Cleanup");
            addQ(task);
            break;
        case 5:
            strcpy(task, "Assemble Scaffoldings");
            addQ(task);
            break;
        default:
            printf("Wrong choice\n");
            break;
        }

        printf("Want to add more tasks (yes-1 / no-0): ");
        scanf("%d", &ctr);
    } while (ctr == 1);
}

void enter_worker()
{
    int ctr2 = 0;
    if (front == 0 && rear == -1)
    {
        printf("\nThere are no tasks to be done\n");
        return;
    }

    do
    {
        new = accept();
        if (head == NULL)
            head = new;
        else
        {
            p = head;
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = new;
        }

        printf("\nWant to add another Worker? (yes-1 / no-0): ");
        scanf("%d", &ctr2);
        if (ctr2 == 1 && front == 0 && rear == -1)
        {
            printf("\nNo further tasks left to be allotted\n");
            break;
        }
    } while (ctr2 == 1);
}

void check_task(int number)
{
    // Implement code to check worker's task allocation
    Node *current = head;
    if (current == NULL)
    {
        printf("No workers added yet.\n");
        return;
    }
    while (current != NULL)
    {
        if (current->worker_no == number)
        {
            printf("\nWorker Name: %s, Worker Number: %d, Task Allotted: %s\n", current->name, current->worker_no, current->task);
        }
        current = current->next;
    }
}

void assign_new_task(int number)
{
    char s[40];
    Node *current = head;
    if (current == NULL)
    {
        printf("No workers added yet\n");
        return;
    }
    while (current != NULL)
    {
        if (current->worker_no == number)
        {
            printf("Finished Task = %s", current->task);
            strcpy(s, delQ()); // Delete the frontmost task from the queue
            strcpy(current->task, s);
            printf("\n\nNewly allocated Task = %s\n", current->task);
            return;
        }
        current = current->next;
    }
}

void del_Node(int num)
{
    Node *q, *r;
    if (head == NULL)
    {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    if (head->worker_no == num)
    {
        p = head;
        printf("%d%s please collect you pay and exit\n", p->name);
        head = head->next;
        if (head != NULL)
        {
            head->prev = NULL;
        }
        p->next = NULL;
        free(p);
    }
    else // for deleting the node in between
    {
        p = head;
        while (p != NULL && p->worker_no != num)
        {
            p = p->next;
        }
        if (p == NULL)
        {
            printf("Worker not found in the list.\n");
            return;
        }
        printf("%s please collect you pay and exit", p->name);
        q = p->prev;
        if (p->next != NULL)
        {
            r = p->next;
            p->prev = NULL;
            p->next = NULL;
            q->next = r;
            r->prev = q;
            free(p);
        }
        else // separate logic for deleting the node at the last
        {
            p->prev = NULL;
            q->next = NULL;
            free(p);
        }
    }
}
void wage_calc_all()
{
    time_t now_time, sub;
    double pay;

    Node *current = head;
    while (current != NULL)
    {
        now_time = time(NULL);
        now_time = difftime(now_time, program_start_time);
        sub = difftime(now_time, current->entry_time);
        sub = sub / 6;   // simulating 1s for 1/6 hrs
        printf("\nsub is:%f",sub);
        pay = sub * 170; // and giving 170rs for 1 hr`
        printf("Worker Name: %s, Worker Number: %d, Wage Generated: %d\n", current->name, current->worker_no, pay);
        current = current->next;
    }
}

void wage_calc(int number, int arg)
{
    if (arg == 0)
    {
        Node *current = head;
        while (current != NULL)
        {
            if (current->worker_no == number)
            {
                time_t now_time, sub;
                int pay;

                now_time = time(NULL);
                now_time = difftime(now_time, program_start_time);
                sub = difftime(now_time, current->entry_time);
                sub = sub / 10;   // simulating 1s for 1/6 hrs
                pay = sub * 170; // and giving 170rs for 1 hr
                printf("The wage generated for Worker %d (%s) is: %d\n", current->worker_no, current->name, pay);

                printf("Does the worker want to receive pay and exit (y-1/n-0): ");
                int del_ctr;
                scanf("%d", &del_ctr);
                if (del_ctr == 1)
                {
                    del_Node(number);
                }
                return;
            }
            current = current->next;
        }
    }
    else if (arg == 1)
    {
        wage_calc_all();
        // del_Node_all();
    }
}

void end_day()
{
    Node *ahead;
    wage_calc_all();

    do
    {
        ahead = head->next;
        del_Node(head->worker_no);
    } while (ahead != NULL);
}

int main()
{
    program_start_time = time(NULL);
    // printf("\nProgram start time:%ld\n",program_start_time);
    int ch, end = 1;
    char pass[10];
    int num;
 
    printf("*****************************************\n"); 
    printf("*Welcome to the Worker Management System*\n");
    printf("*****************************************\n");
    printf("\nPlease enter the password to authorize as a Supervisor: ");
    scanf("%s", pass);

    if (strcmp(pass, "construct") == 0)
    {
        printf("\nAuthorization Complete\n");

        // Now to take the tasks from the supervisor for the workers
        enter_tasks();

        do
        {
            printf("\n******************************************************************\n");
            printf("|                             MENU                               |\n");
            printf("|0.Enter More Tasks                                              |\n");
            printf("|1. Make a Worker entry                                          |\n");
            printf("|2. Check Workers Task Allocation                                |\n");
            printf("|3. Assign new task to Worker                                    |\n");
            printf("|4. Wage Status                                                  |\n");
            printf("|5. Stop the system and generate wages to pay for working workers|\n");
            printf("|6.Exit                                                          |\n");
            printf("******************************************************************\n");
            // // Then show the wage generated and 2 options -> request for pay and exit (yes / no)
            //
            printf("Enter your choice: ");
            scanf("%d", &ch);

            switch (ch)
            {
            case 0:
                enter_tasks();
                break;
                // to Add a worker
            case 1:
                if (front == 0 && rear == -1)
                {
                    printf("\nCan't Enter Worker\nThere are no tasks to be done\n");
                }
                else
                {
                    enter_worker();
                    //sleep(3);
                }
                break;
            case 2: // to check worker task

                printf("\nPlease enter the worker number:");
                scanf("%d", &num);
                check_task(num);
                sleep(3);
                break;

            case 3: // to assign new task to the worker
                printf("\nPlease enter Worker number:");
                scanf("%d", &num);
                assign_new_task(num);
                sleep(3);
                break;

            case 4: // to check the wages and pay is asked to
                printf("\nPlease enter Worker number:");
                scanf("%d", &num);
                wage_calc(num, 0);
                break;

            case 5: // stop the system and genrate the wages for all left workers
                end_day();
                exit(0);

            case 6:
                exit(0);

            default:
                printf("\nWrong choice, please enter again\n");
                break;
            }
            
        } while (end == 1);
    }
    else
    {
        printf("\nAuthorization Failed\n");
    }

    return 0;
}



