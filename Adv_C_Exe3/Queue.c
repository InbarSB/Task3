#include "Queue.h"
#include "Stack.h"
#include <stdio.h>

/***************** Queue ADT Implementation *****************/


void initQueue(Queue* q)
{
	q->head = NULL;
	q->tail = NULL;
}

void destroyQueue(Queue* q)
{
	intNode* tmp = q->head;
	if (isEmptyQueue == 1) {
		printf("\nQueue is Empty\n");
		return;
	}
	while (q->head != NULL) {
		q->head = q->head->next;
		free(tmp);
		tmp = q->head;
	}
}

void enqueue(Queue* q, unsigned int data)
{
	intNode* new = (intNode*)malloc(sizeof(intNode));
	if (new == NULL) {
		printf("\nError on memory allocation\n");
		return;
	}
	new->data = data;
	new->next = NULL;
	if (isEmptyQueue(q) == 0) 	//Queue is NOT empty
		q->tail->next = new;
	else 					//queue is empty
		q->head = new;
	q->tail = new;
}

unsigned int dequeue(Queue* q)
{
	unsigned int tmp = 0;
	intNode* node = NULL;
	if (isEmptyQueue(q) == 1) {		//queue is empty
		printf("Error - Can not dequeue Empty");
		return;
	}
	else {		//queue is NOT empty
		node = q->head;
		tmp = node->data;
		q->head = q->head->next;
		free(node);
		if (q->head == NULL)
			q->tail == NULL;
		return tmp;
	}

}

int isEmptyQueue(const Queue* q)
{
	if (q->head == NULL && q->tail == NULL)
		return 1;
	return 0;
}

/***************** Functions using Queues - Implementation/definition **************************/

void rotateQueue(Queue* q)
{
	intNode* org_tail = q->tail;
	while (q->head != org_tail)		//this will move elements and insert them at the end of the queue
	{								// until we will get to the last element
		enqueue(q, dequeue(q));
	}
}

void cutAndReplace(Queue* q)
{
	Queue q1, q2;
	int count = 0, half = 0, tmp = 0, sum = 0, avg = 0;
	initQueue(&q1);
	initQueue(&q2);
	while (q->head != NULL) {		//count number of elements. at the end of the loop all elemnts will be in q1.
		tmp = dequeue(q);
		enqueue(&q1, tmp);
		sum += tmp;
		count++;
	}
	initQueue(q);
	if (count % 2 == 1) {		//for ODD elements number
		for (int i = 0; i < (count / 2) + 1; i++)		//will move (the 1st) half+1 of the element from q1 to q2
			enqueue(&q2, dequeue(&q1));
		avg = sum / count;
		enqueue(&q1, avg);				//add the result of the avg at the end of the queue
		reverseQueue(&q1);
		while (q1.head != NULL) {		//move elements to q by new order
			enqueue(q, dequeue(&q1));
		}
		while (q2.head != NULL) {
			enqueue(q, dequeue(&q2));
		}
	}
	else {						//for EVEN elements number
		for (int i = 0; i < (count / 2); i++)		//will move (the 1st) half of the element from q1 to q2
			enqueue(&q2, dequeue(&q1));
		reverseQueue(&q1);
		while (q1.head != NULL) {					//move elements to q by new order
			enqueue(q, dequeue(&q1));
		}
		while (q2.head != NULL) {
			enqueue(q, dequeue(&q2));
		}
	}
}

void sortKidsFirst(Queue* q)
{
	Queue q1, q2;
	int tmp = 0;
	intNode* org_tail = q->tail;
	initQueue(&q1);
	initQueue(&q2);
	while (q->head != NULL) {
		tmp = dequeue(q);
		// if this is the 1st element of the list.
		if (q1.head == NULL && q2.head == NULL) {
			enqueue(&q1, tmp);
		}
		//if tmp is lower then the 1st element of the in-order Queue
		else if ((q2.head == NULL && tmp <= q1.head->data) || (q1.head == NULL && tmp <= q2.head->data)) {
			if (q2.head == NULL) {
				enqueue(&q2, tmp);
				while (q1.head != NULL)
					enqueue(&q2, dequeue(&q1));
				initQueue(&q1);
			}
			else {
				enqueue(&q1, tmp);
				while (q2.head != NULL)
					enqueue(&q1, dequeue(&q2));
				initQueue(&q2);
			}
		}
		//if tmp is between the head and tail of the in-order Queue
		else if ((q2.head == NULL && tmp > q1.head->data && tmp < q1.tail->data) || (q1.head == NULL && tmp > q2.head->data && tmp < q2.tail->data)) {
			if (q2.head == NULL) {
				while (q1.head->data <= tmp)
					enqueue(&q2, dequeue(&q1));
				enqueue(&q2, tmp);
				while (q1.head != NULL)
					enqueue(&q2, dequeue(&q1));
				initQueue(&q1);
			}
			else {
				while (q2.head->data <= tmp)
					enqueue(&q1, dequeue(&q2));
				enqueue(&q1, tmp);
				while (q2.head != NULL)
					enqueue(&q1, dequeue(&q2));
				initQueue(&q2);
			}
		}
		//if tmp is bigger them the last element in the in-order queue
		else {	//  tmp > q1.tail ||  tmp > q2.tail
			if (q2.head == NULL) {
				enqueue(&q1, tmp);
			}
			else {
				enqueue(&q2, tmp);
			}
		}
	}
	// move the in-order queue to ADT original queue.
	if (q2.head == NULL) {
		q->head = q1.head;
		q->tail = q1.tail;
	}
	else {
		q->head = q2.head;
		q->tail = q2.head;
	}
}

//this function is getting queue, push it into stack, and insert it again to queue in reverse order.
void reverseQueue(Queue* q)
{
	intStack s;
	int tmp;
	initStack(&s);
	while (q->head != NULL) {
		tmp = dequeue(q);
		push_int(&s, tmp);
	}
	initQueue(q);
	while (s.head != NULL)
	{
		enqueue(q, pop_int(&s));
	}
}

//this functoin created for pushing elements into int data Stack
void push_int(Stack* s, unsigned int data)
{
	intNode* tmp = (intNode*)malloc(sizeof(intNode));
	if (tmp == NULL) {
		printf("\nError on memory allocation\n");
		return;
	}
	tmp->data = data;
	s->head = addToHead(s->head, tmp);
}

//this functoin created for poping elements from int data Stack
char pop_int(Stack* s)
{
	intNode* tmp = s->head;
	unsigned int data = 0;
	s->head = s->head->next;
	data = tmp->data;
	free(tmp);
	return data;
}

//this function is printing the queue. the head will be printing first. tail will be last. 
void printQueue(Queue* q)
{
	Queue q1;
	unsigned int data = 0;
	initQueue(&q1);
	if (isEmptyQueue(q) == 1)
		printf("\nThe Queue is empty!!!!\n");
	else {
		printf("\nThe Queue is:\n");
		while (q->head != NULL) {
			data = dequeue(q);
			printf("%u\n", data);
			enqueue(&q1, data);
		}
		q->head = q1.head;
		q->tail = q1.tail;
		printf("\n");
	}
}