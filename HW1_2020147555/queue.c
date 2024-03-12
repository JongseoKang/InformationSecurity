#include "./headers/queue.h"
#include <stdio.h>

// 새로운 노드를 생성하는 함수
Node* createNode(char* name) {
    Node* newNode = malloc(sizeof(Node));

    newNode->name = malloc(SIZE(name));
    strcpy(newNode->name, name);
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
void enqueue(Queue* queue, char* name) {
    Node* newNode = createNode(name);
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// 큐의 맨 앞에서 데이터를 제거하고 반환하는 함수 (dequeue)
int dequeue(Queue* queue, char* name) {
    if (isEmpty(queue)) return 0;

    Node* current = queue->front;
    Node* prev = NULL;

    // 큐를 순회하면서 주어진 값과 같은 노드를 찾음
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) { // 삭제할 노드가 맨 앞에 있는 경우
                queue->front = current->next;
                free(current->name);
                free(current);
                return 1;
            } else { // 삭제할 노드가 중간이나 끝에 있는 경우
                prev->next = current->next;
                free(current->name);
                free(current);
                return 1;
            }
        }

        prev = current;
        current = current->next;
    }    
    
    return 0;
}

// 큐의 모든 요소를 출력하는 함수
void displayQueue(Queue* queue) {
    Node* current = queue->front;
    while (current != NULL) {
        printf("%s ", current->name);
        current = current->next;
    }
    printf("\n");
}

// 메인 함수
int main() {
    Queue queue;
    initializeQueue(&queue);

    // 큐에 데이터 삽입 (enqueue)
    enqueue(&queue, "1asdfasdfasdfasdfasdfadsf0");
    enqueue(&queue, "20");
    enqueue(&queue, "30");

    // 큐의 모든 요소 출력
    printf("Queue: ");
    displayQueue(&queue);

    // 큐에서 데이터 제거 및 출력 (dequeue)
    printf("Dequeued item: %d\n", dequeue(&queue, "10"));

    // 큐의 맨 앞 요소 확인 (peek)

    // 큐의 모든 요소 출력
    printf("Queue: ");
    displayQueue(&queue);
    printf("Dequeued item: %d\n", dequeue(&queue, "20"));

    printf("Queue: ");
    displayQueue(&queue);

    printf("Dequeued item: %d\n", dequeue(&queue, "30"));
    return 0;
}