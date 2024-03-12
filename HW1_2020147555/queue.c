#include <stdio.h>
#include <stdlib.h>
#include "./headers/queue.h"

// 연결 리스트의 노드를 나타내는 구조체
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 큐를 나타내는 구조체
typedef struct {
    Node* front; // 큐의 맨 앞을 가리키는 포인터
    Node* rear;  // 큐의 맨 뒤를 가리키는 포인터
} Queue;

// 새로운 노드를 생성하는 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 큐를 초기화하는 함수
void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

// 큐의 맨 뒤에 데이터를 삽입하는 함수 (enqueue)
void enqueue(Queue* queue, int data) {
    Node* newNode = createNode(data);
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// 큐의 맨 앞에서 데이터를 제거하고 반환하는 함수 (dequeue)
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    free(temp);
    return data;
}

// 큐의 맨 앞에 있는 데이터를 반환하는 함수 (peek)
int peek(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    return queue->front->data;
}

// 큐의 모든 요소를 출력하는 함수
void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 메인 함수
int main() {
    Queue queue;
    initializeQueue(&queue);

    // 큐에 데이터 삽입 (enqueue)
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    // 큐의 모든 요소 출력
    printf("Queue: ");
    displayQueue(&queue);

    // 큐에서 데이터 제거 및 출력 (dequeue)
    printf("Dequeued item: %d\n", dequeue(&queue));

    // 큐의 맨 앞 요소 확인 (peek)
    printf("Front item: %d\n", peek(&queue));

    // 큐의 모든 요소 출력
    printf("Queue: ");
    displayQueue(&queue);

    return 0;
}