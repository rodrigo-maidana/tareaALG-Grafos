#include "Police.h"
#include "PriorityQueue.h"
#include <stdlib.h>

typedef struct {
  Site site;
  int distance;
} Node;

int compare(const void *a, const void *b) {
  return ((Node *)a)->distance - ((Node *)b)->distance;
}

Site movePolice(Game *game) {
  Site move = {0, 0};
  if (!game)
    return move;

  Scenario *scenario = game->scenario;
  Site police = getPoliceSite(game);
  Site bandit = getBanditSite(game);
  int N = scenarioSize(scenario);

  int **distances = malloc(N * sizeof(int *));
  for (int i = 0; i < N; ++i) {
    distances[i] = malloc(N * sizeof(int));
    for (int j = 0; j < N; ++j) {
      distances[i][j] = INT_MAX;
    }
  }
  distances[police.i][police.j] = 0;

  PriorityQueue pq;
  pq_init(&pq, compare);
  Node start = {police, 0};
  pq_push(&pq, &start);

  int dir[8][2] = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                   {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
  while (!pq_empty(&pq)) {
    Node current = *(Node *)pq_pop(&pq);
    Site csite = current.site;

    if (equalsSite(csite, bandit))
      break;

    for (int k = 0; k < 8; ++k) {
      Site neighbor = {csite.i + dir[k][0], csite.j + dir[k][1]};
      if (isLegalMoveScenario(scenario, csite, neighbor)) {
        int newDist = distances[csite.i][csite.j] + 1;
        if (newDist < distances[neighbor.i][neighbor.j]) {
          distances[neighbor.i][neighbor.j] = newDist;
          Node next = {neighbor, newDist};
          pq_push(&pq, &next);
        }
      }
    }
  }

  Site nextMove = police;
  int minDistance = INT_MAX;
  for (int k = 0; k < 8; ++k) {
    Site neighbor = {police.i + dir[k][0], police.j + dir[k][1]};
    if (isLegalMoveScenario(scenario, police, neighbor) &&
        distances[neighbor.i][neighbor.j] < minDistance) {
      minDistance = distances[neighbor.i][neighbor.j];
      nextMove = neighbor;
    }
  }

  for (int i = 0; i < N; ++i)
    free(distances[i]);
  free(distances);
  pq_destroy(&pq);

  return nextMove;
}
