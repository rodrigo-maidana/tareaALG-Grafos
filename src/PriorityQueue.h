#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct {
  void **data;
  int capacity;
  int size;
  int (*cmp)(const void *, const void *);
} PriorityQueue;

void pq_init(PriorityQueue *pq, int (*cmp)(const void *, const void *));
void pq_destroy(PriorityQueue *pq);
void pq_push(PriorityQueue *pq, void *item);
void *pq_pop(PriorityQueue *pq);
int pq_empty(PriorityQueue *pq);

#endif // PRIORITY_QUEUE_H
