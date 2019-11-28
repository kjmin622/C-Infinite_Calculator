#include <stdio.h>
#include "inter_link.h"

typedef struct DoubleList {
    LINK head, tail;
    int length;
}doubleList;

void addNode(doubleList *dL, char src) {
    LINK newNode = (LINK)malloc(sizeof(ELEMENT));
    newNode->d = src;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (dL->head == NULL && dL->tail == NULL) {
        dL->head = newNode;
        dL->tail = newNode;
        newNode->prev = dL->head;
        newNode->next = dL->tail;
    }
    else {
        dL->tail->next = newNode;
        newNode->prev = dL->tail;
        dL->tail = newNode;
    }
    dL->length += 1;
}

doubleList* getDecimalPart(doubleList* dL) {
    doubleList* decList = (doubleList*)malloc(sizeof(doubleList));
    decList->head = NULL;
    decList->tail = NULL;

    LINK temp = dL->head;
    while (temp != NULL && temp->d != '.') {
        addNode(decList, temp->d);
        temp = temp->next;
    }
    return decList;
}

doubleList* getFloatPart(doubleList* dL) {
    doubleList* floatList = (doubleList*)malloc(sizeof(doubleList));
    floatList->head = NULL;
    floatList->tail = NULL;

    LINK temp = dL->head;
    while (temp != NULL && temp->d != '.') {
        temp = temp->next;
    }
    
    if (temp == NULL || temp->d != '.') return NULL;
    temp = temp->next;
    while (temp != NULL) {
        addNode(floatList, temp->d);
        temp = temp->next;
    }

    return floatList;
    
}

int getListLength(doubleList* dL) {
    LINK temp = dL->head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

doubleList* addFunc(doubleList* dL1, doubleList* dL2, int dL1Length, int dL2Length) {
    int temp = 0, count = 0;
    LINK dL1Temp = dL1->tail, dL2Temp = dL2->tail;
    doubleList* newList = (doubleList*)malloc(sizeof(doubleList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->length = 0;


    while (count < dL1Length) {
        int addResult = (dL1Temp->d - '0') + (dL2Temp->d - '0') + temp;
        temp = addResult / 10;
        addNode(newList, (char)((addResult % 10)+'0'));

        dL1Temp = dL1Temp->prev;
        dL2Temp = dL2Temp->prev;
        ++count;
    }

    while (count < dL2Length) {
        int addResult = (dL2Temp->d - '0') + temp;
        temp = addResult / 10;
        addNode(newList, (char)((addResult % 10) + '0'));
        dL2Temp = dL2Temp->prev;
        ++count;
    }

    if (temp == 1) {
        addNode(newList, (char)(temp + '0'));
    }

    return newList;

}

void reverseOutputAllNodes(doubleList* dL, int length) {

    LINK temp = dL->tail;
    int count = 0;

    if (dL->head == dL->tail) {
        printf("%c", temp->d);
    }
    else {

        while (count < length) {
            printf("%c", temp->d);
            ++count;
            temp = temp->prev;
        }
    }
}
void outputAllNodes(doubleList* dL) {
    LINK temp = dL->head;

    if (dL->head == dL->tail) {
        printf("%c", temp->d);
    }
    else {

        while (temp != NULL) {
            printf("%c", temp->d);
            temp = temp->next;
        }
    }
}
void addDataInList(doubleList* dL1, doubleList* dL2) {
    doubleList* dL1DecPart = getDecimalPart(dL1);
    doubleList* dL1FloatPart = getFloatPart(dL1);
    doubleList* dL2DecPart = getDecimalPart(dL2);
    doubleList* dL2FloatPart = getFloatPart(dL2);

    doubleList* resDecPart = NULL, *resFloatPart = NULL;

    //Decimal part add
    int dL1DecLength = getListLength(dL1DecPart), dL2DecLength = getListLength(dL2DecPart);
    int dL1FloatLength = getListLength(dL1FloatPart), dL2FloatLength = getListLength(dL2FloatPart);
    if (dL1DecLength <= dL2DecLength) {
        resDecPart = addFunc(dL1DecPart, dL2DecPart, dL1DecLength, dL2DecLength);
    }
    else if (dL1DecLength > dL2DecLength) {
        resDecPart = addFunc(dL1DecPart, dL2DecPart, dL2DecLength, dL1DecLength);
    }

    if (dL1FloatLength <= dL2FloatLength) {
        resFloatPart = addFunc(dL1FloatPart, dL2FloatPart, dL1FloatLength, dL2FloatLength);
        if (dL2FloatLength < resFloatPart->length) {
            resDecPart->head->d += 1;
            resFloatPart->tail = resFloatPart->tail->prev;
            resFloatPart->length--;

        }
    }
    else if (dL1FloatLength > dL2FloatLength) {
        resFloatPart = addFunc(dL2FloatPart, dL1FloatPart, dL2FloatLength, dL1FloatLength);
        
        if (dL1FloatLength < resFloatPart->length) {
            resDecPart->head->d += 1;
            resFloatPart->tail = resFloatPart->tail->prev;
            resFloatPart->length--;

        }
    }

    reverseOutputAllNodes(resDecPart, resDecPart->length); printf(".");
    reverseOutputAllNodes(resFloatPart, resFloatPart->length); printf("\n");
}


int main(void) {
    doubleList* list = (doubleList*)malloc(sizeof(doubleList));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    addNode(list, '9');
    addNode(list, '2');
    addNode(list, '1');
    addNode(list, '5');
    addNode(list, '.');
    addNode(list, '9');
    addNode(list, '2');

    doubleList* list2 = (doubleList*)malloc(sizeof(doubleList));
    list2->head = NULL;
    list2->tail = NULL;
    list2->length = 0;
    addNode(list2, '1');
    addNode(list2, '9');
    addNode(list2, '3');
    addNode(list2, '3');
    addNode(list2, '.');
    addNode(list2, '1');
    addNode(list2, '2');

    addDataInList(list, list2);


    return 0;

}
