#include <stdio.h>

//struct for a Linked List Node
struct Node{
    int value;
    struct Node *next;
};

struct Node* createList(int arr[], int arrSize){
    struct Node *first, *last, *temp;
    int i = 0;
    first = (struct Node*)malloc(sizeof(struct Node));
    first->value = arr[0];
    first->next = NULL;
    last = first;

    for(i=1; i<arrSize; i++){
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->value = arr[i];
        temp->next = NULL;
        last->next = temp;
        last = temp;
    }

    return first;
}

void displayList(struct Node *p) {
    while(p){
        printf(" Node value: %d\n", p->value);
        p = p->next;
    }
}

void displayListRecursive(struct Node *p) {
    //not while since last node would keep printing and never quit
    if(p != NULL){
        printf(" Node value: %d\n", p->value);
        displayListRecursive(p->next);
    }
}

void displayListReverse(struct Node *p) {
    //not while since last node would keep printing and never quit
    if(p != NULL){
        displayListReverse(p->next);
        printf(" Node value: %d\n", p->value);
    }
}

int countNodesInList(struct Node *p){
    int count = 0;
    while(p != NULL){
        count++;
        p = p->next;
    }
    return count;
}

int sumNodesInList(struct Node *p){
    int sum = 0;
    while(p != NULL){
        sum += p->value;
        p = p->next;
    }
    return sum;
}

int maxInList(struct Node *p){
    int max = -32768;
    while(p != NULL){
        if(max < p->value){
            max = p->value;
        }
        p = p->next;
    }
    return max;
}

struct Node* searchInList(struct Node *p, int key){
    while(p != NULL){
        if(key == p->value){
            return p;
        }
        p = p->next;
    }
    return NULL;
}

struct Node* searchInListLRU(struct Node *p, int key){
    struct Node *head = p;
    struct Node *q;
    while(p != NULL){
        if(key == p->value){
            q->next = p->next;
            p->next = head;
            head = p;
            return head;
        }
        q = p;
        p = p->next;
    }
    return NULL;
}

int main() {

    int arr[6] = {2,4,6,8,10,12};
    struct Node *p = createList(arr, 6);
    printf("Iterative\n");
    displayList(p);
    printf("Recursive\n");
    displayListRecursive(p);
    printf("Reverse\n");
    displayListReverse(p);
    printf("Count: %d\n", countNodesInList(p));
    printf("Sum: %d\n", sumNodesInList(p));
    printf("Max: %d\n", maxInList(p));
    int num1 = 10;
    struct Node *s1 = searchInList(p, num1);
    if(s1 != NULL){
        printf("Found value %d in list\n", num1);
    }else{
        printf("Did not find value %d in list\n", num1);
    }
    int num2 = 11;
    struct Node *s2 = searchInList(p, num2);
    if(s2 != NULL){
        printf("Found value %d in list\n", num2);
    }else{
        printf("Did not find value %d in list\n", num2);
    }
    int num3 = 8;
    struct Node *s3 = searchInListLRU(p, num3);
    if(s3 != NULL){
        printf("Found value %d in list\n", s3->value);
    }else{
        printf("Did not find value %d in list\n", s3->value);
    }
    return 0;
}


