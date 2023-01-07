#include "hashMap.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int hashFoo(ll code, ll size) {
	return (code % MAP_SIZE + size % MAP_SIZE) % MAP_SIZE;
}

void initMap(HashMap *mp) {
	for (int i = 0; i < MAP_SIZE; i++) {
		mp->HashArr[i] = NULL;
	}
}

HashNode* newHnode_(ll code, ll size, char ch) {
	HashNode *newNode = (HashNode*) malloc(sizeof(HashNode));

	newNode->size = size;
	newNode->next = NULL;
	newNode->encodedChar = ch;
	newNode->code = code;

	return newNode;
}

int findMap(HashMap mp, ll code, ll size) {
	int hashValue = hashFoo(code, size);

	HashNode *head = mp.HashArr[hashValue];
	while (head) {
		if (head->code == code && head->size == size) {
			return head->encodedChar;
		}

		head = head->next;
	}

	return INT_MIN;
}

void insertMap(HashMap *mp, ll code, ll size, char ch) {
	int hashValue = hashFoo(code, size);

	if (mp->HashArr[hashValue] == NULL) {
		mp->HashArr[hashValue] = newHnode_(code, size, ch);
		return;
	}

	HashNode *head = mp->HashArr[hashValue];
	while (head) {
		if (head->code == code && head->size == size) {
			head->encodedChar = ch;
			return;
		}

		head = head->next;
	}

	HashNode *newNode = newHnode_(code, size, ch);
	newNode->next = mp->HashArr[hashValue];
	mp->HashArr[hashValue] = newNode;
}
