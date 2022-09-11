#include <stdio.h>
#include "Stack.h"
#include "Queue.h"

void main()
{
	char str[] = "Remem#reb# thi#carp s#tice", str2[] = "#meR#embe#siht r# practice", str3[] = "MADAM", str4[] = "NOLOON", str5[] = "ABCDEF";
	char;
	Stack s1, s2, s3;
	char* tmp = NULL;
	int res = 0;
	unsigned int res_dequeue = 0;
	Queue q1, q2;

	//Queue main
	initQueue(&q1);
	initQueue(&q2);
	printQueue(&q1);
	enqueue(&q1, 1);
	enqueue(&q1, 2);
	enqueue(&q1, 3);
	enqueue(&q1, 4);
	printQueue(&q1);
	rotateQueue(&q1);
	printQueue(&q1);
	reverseQueue(&q1);
	printQueue(&q1);
	enqueue(&q2, 6);
	enqueue(&q2, 1);
	enqueue(&q2, 5);
	enqueue(&q2, 2);
	enqueue(&q2, 3);
	enqueue(&q2, 1);
	enqueue(&q2, 9);
	printQueue(&q2);
	cutAndReplace(&q2);
	printQueue(&q2);
	sortKidsFirst(&q2);
	printQueue(&q2);

	//Stuck main
	initStack(&s1);
	initStack(&s2);
	initStack(&s3);
	flipBetweenHashes(str);
	flipBetweenHashes(str2);

	tmp = str3;
	while (*tmp != '\0') {
		push(&s1, *tmp);
		tmp = tmp + 1;
	}
	res = isPalindrome(&s1);
	if (res == 0)
		printf("is not Palindrome\n");
	else
		printf("is Palindrome\n");
	tmp = str4;
	while (*tmp != '\0') {
		push(&s2, *tmp);
		tmp = tmp + 1;
	}
	res = isPalindrome(&s2);
	if (res == 0)
		printf("is not Palindrome\n");
	else
		printf("is Palindrome\n");

	printf("\nThe original stack:\n");
	tmp = str5;
	while (*tmp != '\0') {
		push(&s3, *tmp);
		tmp = tmp + 1;
	}
	rotateStack(&s3, 3);
	printf("\nThe rotate stack:\n");
	while (s3.head != NULL) {
		printf("%c\n", pop(&s3));
	}
}