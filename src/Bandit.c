#include "Bandit.h"
#include <stdlib.h>

Site moveBandit(Game *game) {
  Site move = {0, 0};
  if (!game)
    return move;

  Site police = getPoliceSite(game);
  Site bandit = getBanditSite(game);
  Scenario *scenario = getScenario(game);

  int maxDist = -1;
  int dir[8][2] = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                   {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
  for (int k = 0; k < 8; ++k) {
    Site neighbor = {bandit.i + dir[k][0], bandit.j + dir[k][1]};
    if (isLegalMoveScenario(scenario, bandit, neighbor)) {
      int dist = manhattanToSite(neighbor, police);
      if (dist > maxDist) {
        maxDist = dist;
        move = neighbor;
      }
    }
  }

  return move;
}
