#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

int comparisonCount = 0; // 총 비교 횟수
int moveCount = 0;       // 총 이동 횟수
double totalComparisons = 0, totalMoveCount = 0; // 총 비교 횟수와 총 이동 횟수의 합계
int isFirst = 0, rounds = 0; // 첫 번째 실행 여부와 라운드 수

// 배열의 모든 요소를 출력
void printArray(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 배열에 랜덤 숫자들을 삽입
void generateRandomArray(int data[]) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000; // 0부터 999까지의 랜덤 숫자 생성
    }
}

// 두 요소를 교환하고 이동 횟수를 증가시키는 함수
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    moveCount += 3; // 이동 횟수 증가
}

// 배열을 분할하는 함수
int partition(int list[], int left, int right) {
    int pivot = list[right]; // 피벗을 배열의 마지막 요소로 설정
    int i = (left - 1);   // 작은 요소의 인덱스

    for (int j = left; j <= right - 1; j++) {
        comparisonCount++;  // 비교 횟수 증가
        if (list[j] < pivot) {
            i++;  // 작은 요소의 인덱스 증가
            swap(&list[i], &list[j]);  // 작은 요소와 현재 요소 교환
        }
    }
    swap(&list[i + 1], &list[right]);  // 피벗을 올바른 위치로 이동
    return (i + 1); // 피벗의 위치 반환
}

// 재귀적으로 퀵 정렬을 수행하는 함수
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right); // 분할 수행

        doQuickSort(list, left, q - 1); // 왼쪽 부분 배열 정렬
        doQuickSort(list, q + 1, right); // 오른쪽 부분 배열 정렬

        // 정렬 과정 출력 조건 수정
        if (isFirst == 0) {
            rounds++;
            if (rounds % 10 == 0) {
                for (int i = 40; i < 60; i++) {
                    printf("%d ", list[i]);
                }
                printf("\n\n");
            }
        }
    }
}

// 반복적으로 퀵 정렬을 수행하는 함수
void iterativeQuickSort(int list[], int left, int right) {
    int stack[SIZE];  // 스택을 사용하여 재귀 호출 대신 반복 구현
    int top = -1;  // 스택의 top 인덱스

    // 초기 하위 배열 범위를 스택에 push
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {  // 스택이 비어있지 않은 동안 반복
        right = stack[top--];  // 현재 하위 배열의 high 인덱스
        left = stack[top--];   // 현재 하위 배열의 low 인덱스

        int pi = partition(list, left, right);  // 파티션 수행

        // 매 10번째 라운드마다 배열의 일부를 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", list[i]);
            }
            printf("\n\n");
        }
        rounds++;  // 라운드 수 증가

        // 왼쪽 하위 배열이 존재하면 스택에 push
        if (pi - 1 > left) {
            stack[++top] = left;
            stack[++top] = pi - 1;
        }

        // 오른쪽 하위 배열이 존재하면 스택에 push
        if (pi + 1 < right) {
            stack[++top] = pi + 1;
            stack[++top] = right;
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL)); // 랜덤 시드 설정
    int array[SIZE]; // 정렬할 배열

    for (int i = 0; i < 20; i++) { // 20번 반복
        generateRandomArray(array); // 랜덤 배열 생성
        comparisonCount = 0; // 비교 횟수 초기화
        moveCount = 0; // 이동 횟수 초기화
        if (i == 0) {
            printf("Quick Sort Run\n");
            iterativeQuickSort(array, 0, SIZE - 1); // 반복 퀵 정렬 수행

            printf("Result\n");
            printArray(array, SIZE); // 정렬 결과 출력
            isFirst++;
        }
        else {
            iterativeQuickSort(array, 0, SIZE - 1); // 반복 퀵 정렬 수행
        }
        totalComparisons += comparisonCount; // 총 비교 횟수 누적
        totalMoveCount += moveCount; // 총 이동 횟수 누적
    }
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0); // 평균 비교 횟수 출력
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0); // 평균 이동 횟수 출력
    return 0;
}
