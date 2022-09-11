#include "Stack.h"
#include <stdio.h>

/***************** Stack ADT Implementation *****************/

charNode* addToHead(charNode* head, charNode* tmp);

void initStack(Stack* s)
{
	s->head = NULL;
}

void destroyStack(Stack* s)
{
	charNode* tmp = NULL;
	while (s->head != NULL) {
		tmp = s->head;
		s->head = s->head->next;
		free(tmp);
	}
}

void push(Stack* s, char data)
{
	charNode* tmp = (charNode*)malloc(sizeof(charNode));
	if (tmp == NULL) {
		printf("\nError on memory allocation\n");
		return;
	}
	tmp->data = data;
	s->head = addToHead(s->head, tmp);
}

char pop(Stack* s)
{
	charNode* tmp = s->head;
	char data = '0';
	s->head = s->head->next;
	data = tmp->data;
	free(tmp);
	return data;
}


int isEmptyStack(const Stack* s)
{
	return (!(s->head));
}

/*************** Functions using stacks - Implementation/definition **************************/

void flipBetweenHashes(const char* sentence)
{
	Stack st1, st2;
	Stack* s1 = NULL, * s2 = NULL;
	char* tmp = sentence;
	char c = '\0';
	int count = 0;
	s1 = &st1;
	s2 = &st2;
	initStack(s1);
	initStack(s2);
	while (*tmp != '\0') {
		if (*tmp != '\0' && *tmp == '#') {		//count++ every time string get '#' 
			tmp = tmp + 1;
			count++;
		}
		else {
			if (tmp != '\0' && count % 2 == 0) {		//count is EVEN number - need to keep original order
				while (*tmp != '\0' && *tmp != '#') {
					push(s1, *tmp);
					tmp = tmp + 1;
				}
			}
			else {										//count os ODD number - need reverse the order. 
				while (*tmp != '\0' && *tmp != '#') {
					push(s2, *tmp);
					tmp = tmp + 1;
				}
				while (s2->head != NULL) {
					push(s1, pop(s2));
				}
			}
		}
	}
	while (s1->head != NULL) {							//insert it to stack in right order. after reorder all sentence. 
		push(s2, pop(s1));
	}
	printf("\n");
	while (s2->head != NULL) {							//print all sentence in the correct order.
		printf("%c", pop(s2));
	}
	printf("\n");
}

int isPalindrome(Stack* s)
{
	Stack s1, s2;
	char tmp = '\0';
	int count = 0;
	initStack(&s1);
	initStack(&s2);
	printf("\nThe phrase ");
	while (s->head != NULL) {		//printing the phrase, count number of elements and push it into 2 stacks - s1 and s2
		tmp = pop(s);
		printf("%c", tmp);
		push(&s1, tmp);
		push(&s2, tmp);
		count++;
	}
	printf(" ");
	while (s1.head != NULL) {		//pop all elemnts from s1 back to the original stack make sure data will be saved.
		push(s, pop(&s1));
	}
	if (count % 2 == 0) {
		count = count / 2;
		while (count != 0) {
			push(&s1, pop(&s2));	//pop half of the elements from s2 to s1
			count--;
		}
		while (s1.head != NULL) {	//compare elements from s1 and s2. if two stack are equal - return 1, if not - return 0;
			if (pop(&s1) != pop(&s2))
				return 0;
		}
		return 1;
	}
	else {								//if number of elements is ODD 
		count = count / 2;
		while (count != 0) {			//pop half of the elements from s2 to s1
			push(&s1, pop(&s2));
			count--;
		}
		pop(&s2);						//pop the middle element
		while (s1.head != NULL) {
			if (pop(&s1) != pop(&s2))	//compare elements from s1 and s2. if two stack are equal - return 1, if not - return 0;
				return 0;
		}
		return 1;
	}
}

void rotateStack(Stack* s, int n)
{
	Stack s1, s2;
	int count = 0;
	char tmp = '\0';
	initStack(&s1);
	initStack(&s2);
	if (n <= 0) {  // if n<=0 - no Stack change needed.
		return;
	}
	while (s->head != NULL) {	// move reverse s content into s1 and count numbers of elements in original stack
		tmp = pop(s);
		push(&s1, tmp);
		printf("%c\n", tmp);
		count++;
	}
	if (n > count) {	// if n>count - reverse back elements into the original stack.
		while (s1.head != NULL) {
			push(s, pop(&s1));
		}
	}
	else {
		for (int i = 0; i < n; i++)		// move n elements into s2 in order
		{
			push(&s2, pop(&s1));
		}
		while (s1.head != NULL)		//move back count-n elements need to be at the bottom of the original stack - in order
			push(s, pop(&s1));
		while (s2.head != NULL)		//move the n element into s1 in reverse order
			push(&s1, pop(&s2));
		while (s1.head != NULL)		//move the n elements into original stack - in order.
			push(s, pop(&s1));
	}
}

charNode* addToHead(charNode* head, charNode* tmp) {
	tmp->next = head;
	head = tmp;
	return head;
}