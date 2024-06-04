#include "PriorityQueue.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

void pq_init(PriorityQueue *pq, int (*cmp)(const void *, const void *)) {
  pq->data = malloc(INITIAL_CAPACITY * sizeof(void *));
  pq->capacity = INITIAL_CAPACITY;
  pq->size = 0;
  pq->cmp = cmp;
}

void pq_destroy(PriorityQueue *pq) { free(pq->data); }

void pq_push(PriorityQueue *pq, void *item) {
  if (pq->size == pq->capacity) {
    pq->capacity *= 2;
    pq->data = realloc(pq->data, pq->capacity * sizeof(void *));
  }
  pq->data[pq->size] = item;
  int idx = pq->size++;
  while (idx > 0) {
    int parent = (idx - 1) / 2;
    if (pq->cmp(pq->data[parent], pq->data[idx]) <= 0)
      break;
    void *tmp = pq->data[parent];
    pq->data[parent] = pq->data[idx];
    pq->data[idx] = tmp;
    idx = parent;
  }
}

void *pq_pop(PriorityQueue *pq) {
  if (pq->size == 0)
    return NULL;
  void *item = pq->data[0];
  pq->data[0] = pq->data[--pq->size];
  int idx = 0;
  while (1) {
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int smallest = idx;
    if (left < pq->size && pq->cmp(pq->data[left], pq->data[smallest]) < 0)
      smallest = left;
    if (right < pq->size && pq->cmp(pq->data[right], pq->data[smallest]) < 0)
      smallest = right;
    if (smallest == idx)
      break;
    void *tmp = pq->data[smallest];
    pq->data[smallest] = pq->data[idx];
    pq->data[idx] = tmp;
    idx = smallest;
  }
  return item;
}

int pq_empty(PriorityQueue *pq) { return pq->size == 0; }
