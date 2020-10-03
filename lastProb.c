#include <stdio.h>
#include <stdlib.h>

struct digit {
    int num;
    struct digit *next;
};


// Add a prototype for countRedun() here
struct digit * createDigit(int);
struct digit * append(struct digit * end, struct digit * newDigptr);
void printNumber(struct digit *);
void freeNumber(struct digit *);
struct digit *readNumber(void); 
int divisibleByThree(struct digit * start);
int changeThrees(struct digit * start);
int countRedun(struct digit *);
struct digit * addNumber(struct digit *);



// Do not modify this main() function
int main(void) {
    struct digit *start;
    start = readNumber();
    struct digit *ptr;
    ptr = start;
    while(ptr->next != NULL)

    //made circular linked list
    ptr = ptr->next;
    ptr->next = start;

    printf("The number ");
    printNumber(start);
    //printf("contains %d redundancies.\n", countRedun(start));

    //inserting element into the circular linked list
    int n;
    printf("Enter the number of values to be added ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        start = addNumber(start);
        printNumber(start);
    }

    freeNumber(start);

    return 0;
}
struct digit *readNumber(void) {
    char c;
    int d;
    struct digit *start, *end, *newptr;
    start = NULL;
    scanf("%c", &c);
    while (c != '\n') {
        d = c-48;
        newptr = createDigit(d);
        if (start == NULL) {
            start = newptr;
            end = start;
        } else {
            end = append(end, newptr);
        }
        scanf("%c", &c);
    }
    return(start);
}

struct digit *createDigit(int dig) {
    struct digit *ptr;
    ptr = (struct digit *) malloc(sizeof(struct digit));
    ptr->num = dig;
    ptr->next = NULL;
    return ptr;
}

struct digit * append(struct digit * end, struct digit * newDigptr) {
    end->next = newDigptr;
    return(end->next);
}

void printNumber(struct digit *start) {
    struct digit * ptr = start;
    while (ptr->next != start) {
        printf("%d", ptr->num);
        ptr = ptr->next;
    }
    printf("%d", ptr->num);
    printf("\n");
}

struct digit * addNumber(struct digit * start){
    int n, num;
    printf("Enter the position where the number is to be added and the number to be added: ");
    scanf("%d %d", &n, &num);
    if(n == 1){
        struct digit *end = start;
        while(end->next != start)
        end = end->next;
        struct digit *numptr;
        numptr = (struct digit *) malloc(sizeof(struct digit));
        numptr->num = num;
        numptr->next = start;
        end->next = numptr;
        return numptr;
    }
    struct digit *tmp = start;
    int i = 2;
    while(i < n){
        tmp = tmp->next;
        i++;
    }
    struct digit *numptr;
    numptr = (struct digit *) malloc(sizeof(struct digit));
    numptr->num = num;
    numptr->next = tmp->next;
    tmp->next = numptr;
    return start;    
}
    

void freeNumber(struct digit *start) {
    struct digit * ptr = start;
    struct digit * tmp;
    while (ptr->next != start) {
        tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}



int divisibleByThree(struct digit * start) {
    struct digit * ptr = start;
    int qsum = 0;
    while (ptr!=NULL) {
        qsum += ptr->num;
        ptr = ptr->next;
    }
    if (qsum%3==0) return 1;
    else return 0;
}

int changeThrees(struct digit * start) {
    struct digit * ptr = start;
    int sum = 0;
    while (ptr!=NULL) {
        if (ptr->num == 3) {
            ptr->num = 9;
            sum++;
        }
        ptr = ptr->next;
    }
    return(sum);
}

// Write your countRedun() function here
int countRedun(struct digit * start){
    struct digit * tmpstart, * tmpend, * newptr, * tmps;
    newptr = createDigit(start->num);
    tmpstart = newptr;
    tmps = tmpstart;
    tmpend = tmpstart;
    start = start->next;
    int count = 0, boolean = 1;
    while(start != NULL){
        while((tmps != NULL) && boolean){
            if(tmps->num == start->num){
                count++;
                boolean = 0;
            }
            tmps = tmps->next;
        }
        if(boolean){
            newptr = createDigit(start->num);
            tmpend = append(tmpend, newptr);
        }
        start = start->next;
        tmps = tmpstart;
        boolean = 1;
    }
    return count;
}