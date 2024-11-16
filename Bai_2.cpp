#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//1.Khai báo cấu trúc
typedef struct Node
{
    const char *word;  // Đảm bảo từ là một chuỗi không thay đổi
    int count;
    struct Node *next;
} Node;

typedef struct list {
    Node *head;
} list;

void initList(list *L) {
    L->head = NULL;
}

//thêm từ vào danh sách, nếu có thì tăng biến đếm
void addWord(list *L, const char *word) {
    Node *temp = L->head;
    
    // Kiểm tra nếu từ đã tồn tại trong danh sách
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            temp->count++;  
            break;  
        }
        temp = temp->next;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->word = strdup(word);  // Tạo bản sao của từ
    newNode->count = 1;  
    newNode->next = NULL;  

 
    if (L->head == NULL) {
        L->head = newNode;
    } else {
        // Duyệt qua danh sách đến cuối và thêm node mới vào cuối
        Node *last = L->head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;  // Chèn node mới vào cuối
    }
}


//2.Từ xuất hiện nhiều nhất trong câu 
Node* findmax(list *L){
    Node *tempNode1 = L->head;
    Node *maxCount = L->head;
    while (tempNode1 != NULL) {
        if(tempNode1->count > maxCount->count) {
            maxCount = tempNode1;
        }
        tempNode1 = tempNode1->next;
    }
    return maxCount;
}

//3.Loại bỏ từ láy 
void remove(list *L){
    Node *temp = L->head;
    while (temp != NULL && temp->next != NULL) {
        if(strcmp(temp->word, temp->next->word) == 0) {
            Node *removeNode = temp->next;
            temp->next = removeNode->next;
            free((void*)removeNode->word);
            free(removeNode); 
        } else {
            temp = temp->next;
        }
    }
}

//4.đếm số từ 
int countWords(list *L) {
    int count = 0;
    Node *temp = L->head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

// Hàm in ra câu từ danh sách từ
void printSentence(list *L) {
    Node *temp = L->head;
    int first = 1; 
    while (temp != NULL) {
        if (!first) {
            printf(" "); 
        }
        printf("%s", temp->word);
        first = 0; 
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    list myList;
    initList(&myList);
    addWord(&myList, "hello");
    addWord(&myList, "hello");
    addWord(&myList, "test");
    addWord(&myList, "test");
    addWord(&myList, "world");
    addWord(&myList, "hello");

    Node *maxNode = findmax(&myList);
    printf("\nTu xuat hien nhieu nhat: %s, So lan xuat hien: %d\n", maxNode->word, maxNode->count);

    printf("\nCau truoc khi xoa la: ");
    printSentence(&myList);
    int wordCount1 = countWords(&myList);
    printf("\nTong so tu trong cau: %d\n", wordCount1);
    remove(&myList);
    printf("\nCau sau khi xoa la: ");
    printSentence(&myList);

    int wordCount2= countWords(&myList);
    printf("\nTong so tu trong cau: %d\n", wordCount2);

    return 0;
}
