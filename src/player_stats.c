//
// Created by benedikt on 2/21/20.
//

#include "../include/defender.h"

int is_enemy_past_goal(enemy_t *enemy, objects_t *objects)
{
    for (int i = 0; i < objects->map.goal.total; i++) {
        switch (objects->map.goal.tiles[i].type) {
        case 0:
            if (enemy->position.y <=
                objects->map.goal.tiles[i].position.y - 100 &&
                enemy->position.x == objects->map.goal.tiles[i].position.x)
                return (1);
            break;
        case 1:
            if (enemy->position.x <=
                objects->map.goal.tiles[i].position.x - 100 &&
                enemy->position.y == objects->map.goal.tiles[i].position.y)
                return (1);
            break;
        case 2:
            if (enemy->position.x >=
                objects->map.goal.tiles[i].position.x + 100 &&
                enemy->position.y == objects->map.goal.tiles[i].position.y)
                return (1);
            break;
        case 3:
            if (enemy->position.y >= objects->map.goal.tiles[i].position.y + 100 && enemy->position.x == objects->map.goal.tiles[i].position.x)
                return (1);
            break;
        default:
            break;
        }
    }
    return (0);
}