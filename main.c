#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    struct Node *q = (struct Node*)malloc(sizeof(struct Node));
    while(p != NULL){
        if(key == p->value){
            q->next = p->next;
            p->next = head;
            head = p;
            return p;
        }
        q = p;
        p = p->next;
    }
    return NULL;
}

struct Node* insertInLinkedList(struct Node *head, int pos, int x){
    struct Node *temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->value = x;

    if(pos < 0){
        return head;
    }

    if(pos == 0){
        temp->next = head;
        head = temp;
    }else{
        struct Node *p = head;
        for(int i = 0; i < pos-1; i++){
            p = p->next;
        }
        temp->next = p->next;
        p->next = temp;
    }
    return head;
}

//Doesn't check if the list is sorted or not
struct Node* insertInSortedLL(struct Node *head, int x){
    struct Node *p, *q;
    p = head;
    q = NULL;

    while(p && p->value < x){
        q = p;
        p = p->next;
    }
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->value = x;
    temp->next = p;
    q->next = temp;

    return head;
}

struct Node* deleteFromList(struct Node *head, int position){
    struct Node *p = head, *q;
    q = NULL;

    if(position == 1){ //TODO investigate why this is not printing actual list when removing from head
        printf("Removing head\n");
        printf("Current value of head: %d\n", head->value);
        head = head->next;
        printf("New value of head: %d\n", head->value);
        return head;
    }else{
        for(int i = 0; i < position-1; i++){
            q = p;
            p = p->next;
        }
        q->next = p->next;
    }
    //free(p);
    return head;
}

bool checkIsListSorted(int *head){
    struct Node *p, *q;
    p = head;
    bool result = true;
    while(p != NULL){
        q = p;
        p = p->next;
        if(p != NULL){
            int pVal = p->value;
            int qVal = q->value;
            if(pVal < qVal){
                result = false;
                return result;
            }
        }else{
            break;
        }
    }
    return result;
}

//assume list is sorted
struct Node* removedDups(struct Node *head){
    struct Node *p, *q;
    p = head->next;
    q = head;
    while(p){
        if(p->value == q->value){
            q->next = p->next;
            free(p);
            p = q->next;
        }else{
            q = p;
            p = p->next;
        }
    }
    return head;
}

struct Node* reverseLL(struct Node *head){
    struct Node *p, *q, *r;
    p = head;
    while(p){
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    return q;
}

struct Node* mergeSortedLists(struct Node *head1, struct Node *head2){
    //assume lists are already sorted, as they should be for merge to work
    struct Node *head3, *last;

    //set first node of new list
    if(head1->value > head2->value){
        last = head3 = head2;
        head2 = head2->next;
    }else{
        last = head3 = head1;
        head1 = head1->next;
    }
    last->next = NULL;

    //keep adding remaining nodes in ascending order
    while(head1 && head2){
        if(head1->value > head2->value){
            last->next = head2;
            head2 = head2->next;
        }else{
            last->next = head1;
            head1 = head1->next;
        }
        last = last->next;
        last->next = NULL;
    }

    //add remaining nodes of list 1
    while(head1){
        last->next = head1;
        head1 = head1->next;
        last = last->next;
        last->next = NULL;
    }
    //add remaining nodes of list 2
    while(head2){
        last->next = head2;
        head2 = head2->next;
        last = last->next;
        last->next = NULL;
    }
    return head3;
}

bool isListLoop(struct Node *head){
    bool result = false;
    struct Node *p, *q;
    p = q = head;

    while(p && q){
        p = p->next;
        q = q->next;
        if(q != NULL){
            q = q->next;
        }else{
            q = NULL;
        }
        if(p == q){
            result = true;
            return result;
        }
    }

    return result;
}

struct Node* createcircularList(int arr[], int arrSize){
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
    last->next = first;
    return first;
}

//show all contents of a circular linked list starting from head
void displayCircularLL(struct Node *head){
    struct Node *p = head;
    printf("Displaying circular linked list\n");
    printf("%d\n", p->value);
    p = p->next;
    while(p != head){
        printf("%d\n", p->value);
        p = p->next;
    }
}

//insert a new node in a circular linked list at a specified position
struct Node* insertInCircularLinkedList(struct Node *head, int pos, int val){
    struct Node *tracker = head;
    struct Node *temp = (struct Node*)malloc((sizeof(struct Node)));
    temp->value = val;
    temp->next = NULL;

    if(pos == 1){
        while(tracker->next != head){
            tracker = tracker->next;
        }
        temp->next = head;
        tracker->next = temp;
        head = temp;
        printf("Completed insert at head\n");
    }else{
        for(int i = 0; i < pos-2; i++){
            tracker = tracker->next;
        }
        temp->next = tracker->next;
        tracker->next = temp;
        printf("Completed insert at position %d\n", pos);
    }
    return head;
}

//Delete a node in a circular linked list from a specified position
struct Node* deleteFromCircularLinkedList(struct Node *head, int pos){
    struct Node *leading = head;
    struct Node *trailing = head;

    if(head->next == head){
        head = NULL;
        return head;
    }
    if(pos == 1){
        while(leading->next != head){
            leading = leading->next;
        }
        leading->next = head->next;
        free(head);
        head = leading->next;
        printf("Completed delete at head\n");
    }else{
        for(int i = 0; i < pos-2; i++){
            trailing = trailing->next;
        }
        for(int j = 0; j < pos; j++){
            leading = leading->next;
        }
        trailing->next = leading;
        printf("Completed remove at position %d\n", pos);
    }
    return head;
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
    displayList(s3);
    p = insertInLinkedList(p,4,9);
    displayList(s3);

    int arr2[6] = {1,3,5,7,9,11};
    struct Node *q = createList(arr2, 6);
    displayList(q);
    insertInSortedLL(q, 10);
    displayList(q);
    printf("Delete from middle\n");
    deleteFromList(q, 6);
    displayList(q);

    int arr4[6] = {1,3,5,7,9,11};
    struct Node *s = createList(arr4, 6);
    printf("Check if s sorted\n");
    if(checkIsListSorted(s)){
        printf("List is sorted\n");
    }else{
        printf("List is NOT sorted\n");
    }

    int arr5[10] = {3,3,4,4,4,5,5,8,8,8};
    struct Node *dup = createList(arr5, 10);
    displayList(dup);
    removedDups(dup);
    printf("After removing duplicates\n");
    displayList(dup);
    struct Node *new = reverseLL(dup);
    printf("After reversing\n");
    displayList(new);

    printf("Testing merged list method\n");
    int mergeArr1[5] = {1,3,5,7,147};
    int mergeArr2[6] = {2,4,6,8,10,12};
    struct Node *mList1 = createList(mergeArr1, 5);
    struct Node *mList2 = createList(mergeArr2, 6);
    struct Node *mergedList = mergeSortedLists(mList1, mList2);
    displayList(mergedList);

    struct Node *node1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *node2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *node3 = (struct Node*)malloc(sizeof(struct Node));

    struct Node *node4 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *node5 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *node6 = (struct Node*)malloc(sizeof(struct Node));

    node1->value = 1;
    node2->value = 2;
    node3->value = 3;
    node1->next = node2;
    node2->next = node3;
    node3->next = node2;

    node4->value = 1;
    node5->value = 2;
    node6->value = 3;
    node4->next = node5;
    node5->next = node6;
    node6->next = NULL;

    if(isListLoop(node1)){
        printf("Given list is a loop\n");
    }else{
        printf("Given list is NOT a loop\n");
    }

    if(isListLoop(node4)){
        printf("Given list is a loop\n");
    }else{
        printf("Given list is NOT a loop\n");
    }

    int cArr[10] = {3,3,4,4,4,5,5,8,8,8};
    struct Node *cLL = createcircularList(cArr, 10);
    displayCircularLL(cLL);
    printf("Insert at head of circular list\n");
    cLL = insertInCircularLinkedList(cLL, 1, 77);
    displayCircularLL(cLL);
    printf("Insert in the middle of circular list\n");
    cLL = insertInCircularLinkedList(cLL, 4, 99);
    displayCircularLL(cLL);
    printf("Delete head of circular list\n");
    cLL = deleteFromCircularLinkedList(cLL, 1);
    displayCircularLL(cLL);
    printf("Delete from middle of circular list\n");
    cLL = deleteFromCircularLinkedList(cLL, 3);
    displayCircularLL(cLL);

    return 0;
}


