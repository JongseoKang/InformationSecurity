#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef SIZE
#define SIZE(str) (strlen(str) + 1)
#endif

typedef struct Node {
    char *name;
    struct Node* next;
} Node;

// 큐를 나타내는 구조체
typedef struct {
    Node* front; // 큐의 맨 앞을 가리키는 포인터
    Node* rear;  // 큐의 맨 뒤를 가리키는 포인터
} Queue;

Node* createNode(char* name);

// 큐를 초기화하는 함수
void initializeQueue(Queue* queue);

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue* queue);

// 큐의 맨 뒤에 데이터를 삽입하는 함수 (enqueue)
void enqueue(Queue* queue, char* name);

// 큐에서 같은 데이터를 제거하는 함수 (dequeue)
int dequeue(Queue* queue, char* name);

void clearQueue(Queue* queue);
// 큐의 모든 요소를 출력하는 함수
void displayQueue(Queue* queue);

#endif