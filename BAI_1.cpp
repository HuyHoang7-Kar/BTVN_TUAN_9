#include <stdio.h>
#include <stdlib.h>
//1. Khai báo cấu trúc
typedef struct Node {
    const char *name;  
    int time;
    int size;
    Node* next;
} Node;

typedef struct {
    Node *head;
} List;

void initList(List *L) {
    L->head = NULL;
}
// Thêm file 
void addFile(List *L, Node* file) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->name = file->name;
    newNode->time = file->time;
    newNode->size = file->size;
    newNode->next = NULL;
    if(L->head == NULL) {
        L->head = newNode;
    }
    else {
        newNode->next = L->head;
        L->head = newNode;
    }
}
// Sắp xếp fi;e theo thứ tự thời gian 
void Sort(List *L) {
    if (L->head == NULL || L->head->next == NULL) return;

    int swapped;
    Node *j;
    int tempTime, tempSize;
    const char *tempName;

    do {
        swapped = 0;
        for (j = L->head; j->next != NULL; j = j->next) {
            if (j->time > j->next->time) {
                tempTime = j->time;
                j->time = j->next->time;
                j->next->time = tempTime;

                tempSize = j->size;
                j->size = j->next->size;
                j->next->size = tempSize;

                tempName = j->name;
                j->name = j->next->name;
                j->next->name = tempName;

                swapped = 1;
            }
        }
    } while (swapped);
}
//2. coppy file 
void Coppy(List *L, Node* file) {
    addFile(L, file);
    Sort(L);
}
//3. Tính kích thước các file
int sumSize(List *L) {
    Node* temp = L->head;
    int sum = 0;
    while (temp != NULL) {
        sum += temp->size;
        temp = temp->next;
    }
    return sum;
}
//4. Loại bỏ file 
void removefile(List *L) {  
    int sum = sumSize(L);
    if (sum <= 32) {
        return;
    }

    while (sum > 32) {
        Node *temp = L->head;
        Node *prev = NULL;
        Node *min = L->head;
        Node *minPrev = NULL; 
        while (temp != NULL) {
            if (temp->size < min->size) {
                min = temp;
                minPrev = prev;  
            }
            prev = temp;
            temp = temp->next;
        }

        if (minPrev == NULL) {  
            L->head = min->next;  
        } else {
            minPrev->next = min->next;  
        }

        sum -= min->size;  
        free(min);  
    }
}

void printList(List *L) {
    Node *temp = L->head;
    while (temp != NULL) {
        printf("Name: %s, Time: %d, Size: %d\n", temp->name, temp->time, temp->size);
        temp = temp->next;
    }
}

int main() {
    List L;
    initList(&L);

    Node file1 = {"File1", 10, 12, NULL};
    Node file2 = {"File2", 20, 20, NULL};
    Node file3 = {"File3", 8, 10, NULL};
    Node file4 = {"File4", 12, 5, NULL};
    
    Coppy(&L, &file1);
    Coppy(&L, &file2);
    Coppy(&L, &file3);
    Coppy(&L, &file4);

    printf("file sau khi coppy:\n");
    printList(&L);

    removefile(&L);

    printf("\nfile sau khi cho vao USB:\n");
    printList(&L);

    return 0;
}
