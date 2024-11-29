#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

int comparisonCount = 0; // �� �� Ƚ��
int moveCount = 0;       // �� �̵� Ƚ��
double totalComparisons = 0, totalMoveCount = 0; // �� �� Ƚ���� �� �̵� Ƚ���� �հ�
int isFirst = 0, rounds = 0; // ù ��° ���� ���ο� ���� ��

// �迭�� ��� ��Ҹ� ���
void printArray(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// �迭�� ���� ���ڵ��� ����
void generateRandomArray(int data[]) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000; // 0���� 999������ ���� ���� ����
    }
}

// �� ��Ҹ� ��ȯ�ϰ� �̵� Ƚ���� ������Ű�� �Լ�
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    moveCount += 3; // �̵� Ƚ�� ����
}

// �迭�� �����ϴ� �Լ�
int partition(int list[], int left, int right) {
    int pivot = list[right]; // �ǹ��� �迭�� ������ ��ҷ� ����
    int i = (left - 1);   // ���� ����� �ε���

    for (int j = left; j <= right - 1; j++) {
        comparisonCount++;  // �� Ƚ�� ����
        if (list[j] < pivot) {
            i++;  // ���� ����� �ε��� ����
            swap(&list[i], &list[j]);  // ���� ��ҿ� ���� ��� ��ȯ
        }
    }
    swap(&list[i + 1], &list[right]);  // �ǹ��� �ùٸ� ��ġ�� �̵�
    return (i + 1); // �ǹ��� ��ġ ��ȯ
}

// ��������� �� ������ �����ϴ� �Լ�
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right); // ���� ����

        doQuickSort(list, left, q - 1); // ���� �κ� �迭 ����
        doQuickSort(list, q + 1, right); // ������ �κ� �迭 ����

        // ���� ���� ��� ���� ����
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

// �ݺ������� �� ������ �����ϴ� �Լ�
void iterativeQuickSort(int list[], int left, int right) {
    int stack[SIZE];  // ������ ����Ͽ� ��� ȣ�� ��� �ݺ� ����
    int top = -1;  // ������ top �ε���

    // �ʱ� ���� �迭 ������ ���ÿ� push
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {  // ������ ������� ���� ���� �ݺ�
        right = stack[top--];  // ���� ���� �迭�� high �ε���
        left = stack[top--];   // ���� ���� �迭�� low �ε���

        int pi = partition(list, left, right);  // ��Ƽ�� ����

        // �� 10��° ���帶�� �迭�� �Ϻθ� ���
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", list[i]);
            }
            printf("\n\n");
        }
        rounds++;  // ���� �� ����

        // ���� ���� �迭�� �����ϸ� ���ÿ� push
        if (pi - 1 > left) {
            stack[++top] = left;
            stack[++top] = pi - 1;
        }

        // ������ ���� �迭�� �����ϸ� ���ÿ� push
        if (pi + 1 < right) {
            stack[++top] = pi + 1;
            stack[++top] = right;
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL)); // ���� �õ� ����
    int array[SIZE]; // ������ �迭

    for (int i = 0; i < 20; i++) { // 20�� �ݺ�
        generateRandomArray(array); // ���� �迭 ����
        comparisonCount = 0; // �� Ƚ�� �ʱ�ȭ
        moveCount = 0; // �̵� Ƚ�� �ʱ�ȭ
        if (i == 0) {
            printf("Quick Sort Run\n");
            iterativeQuickSort(array, 0, SIZE - 1); // �ݺ� �� ���� ����

            printf("Result\n");
            printArray(array, SIZE); // ���� ��� ���
            isFirst++;
        }
        else {
            iterativeQuickSort(array, 0, SIZE - 1); // �ݺ� �� ���� ����
        }
        totalComparisons += comparisonCount; // �� �� Ƚ�� ����
        totalMoveCount += moveCount; // �� �̵� Ƚ�� ����
    }
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0); // ��� �� Ƚ�� ���
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0); // ��� �̵� Ƚ�� ���
    return 0;
}
