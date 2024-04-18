//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////   linked list /////////////////////////////////

typedef struct _listnode {
	int item;
	struct _listnode* next;
} ListNode;

typedef struct _linkedlist {
	int size;
	ListNode* head;
	ListNode* tail;
} LinkedList;

////////////////////////////////// stack    ///////////////////////////////////////////////////////

typedef struct stack {
	LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////////////////

typedef struct _queue {
	LinkedList ll;
} Queue;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void reverse(Queue* q);

void push(Stack* s, int item);
int pop(Stack* s);
int peek(Stack* s);
int isEmptyStack(Stack* s);

void enqueue(Queue* q, int item);
int dequeue(Queue* q);
int isEmptyQueue(Queue* s);

///////////////////////////////////////////////////////////////////////////////////////////////////
void printList(LinkedList* ll);
ListNode* findNode(LinkedList* ll, int index);
int insertNode(LinkedList* ll, int index, int value);
int removeNode(LinkedList* ll, int index);
void removeAllItems(LinkedList* ll);

///////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	int c, value;

	Queue q;

	//initialize the queue
	q.ll.head = NULL;
	q.ll.size = 0;
	q.ll.tail = NULL;

	c = 1;

	printf("1: Insert an integer into the queue;\n");
	printf("2: Reverse the queue;\n");
	printf("0: Quit;\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the queue: ");
			scanf("%d", &value);
			enqueue(&q, value);
			printf("The queue is: ");
			printList(&(q.ll));
			break;
		case 2:
			reverse(&q); // You need to code this function
			printf("The resulting queue after reversing its elements is: ");
			printList(&(q.ll));
			removeAllItems(&(q.ll));
			break;
		case 0:
			removeAllItems(&(q.ll));
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void reverse(Queue* q)
{
	// Initialize a stack
	Stack s;
	s.ll.head = NULL;
	s.ll.size = 0;
	s.ll.tail = NULL;

	// Empty the stack if it's not already empty
	while (!isEmptyQueue(q)) {
		push(&s, dequeue(q));
	}

	// Enqueue elements from the stack back into the queue
	while (!isEmptyStack(&s)) {
		enqueue(q, pop(&s));
	}
	/* 
(reverseQueue) Write a C function reverseQueue () to reverse a queue using a stack.
Note that the reverseQueue () function only uses push () and pop () when adding or removing integers from the stack and only uses enqueue () and dequeue () when adding or removing integers from the queue. Remember to empty the stack at the beginning, it the stack is not empty.
remember to initialize the stack.
The function prototype is given as follows: void reverseQueue (Queue *q);
For example, if the queue is (1, 2, 3, 4, 5) the resulting queue will be (5, 4, 3, 2, 1).
	*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void push(Stack* s, int item) {
	insertNode(&(s->ll), 0, item);
}

int pop(Stack* s) {
	int item;
	if (!isEmptyStack(s)) {
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	return INT_MIN;
}

int peek(Stack* s) {
	return ((s->ll).head)->item;
}

int isEmptyStack(Stack* s) {
	if ((s->ll).size == 0)
		return 1;
	return 0;
}

void enqueue(Queue* q, int item) {
	insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue* q) {
	int item;
	item = ((q->ll).head)->item;
	removeNode(&(q->ll), 0);
	return item;
}

int isEmptyQueue(Queue* q) {
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList* ll) {

	ListNode* cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode* findNode(LinkedList* ll, int index) {

	ListNode* temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0) {
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList* ll, int index, int value) {

	ListNode* pre, * cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0) {
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL) {
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList* ll, int index) {

	ListNode* pre, * cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0) {
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL) {

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList* ll)
{
	ListNode* cur = ll->head;
	ListNode* tmp;

	while (cur != NULL) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}