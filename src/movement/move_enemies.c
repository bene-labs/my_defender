//
// Created by benedikt on 2/14/20.
//

#include "../../include/defender.h"

void move_enemy(enemy_t *enemy, objects_t *objects)
{
    for (int i = 0; i < objects->map.total_tiles; i++) {
        if (objects->map.tileset[i].position.x == enemy->position.x &&
            objects->map.tileset[i].position.y == enemy->position.y) {
            if (enemy->move.y == -1) {
                switch (objects->map.tileset[i].type) {
                case 0:
                    sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][1], sfTrue);
                    sfSprite_setTextureRect(enemy->sprite, enemy->walk.rect[enemy->walk.frame]);
                    enemy->walk.is_mirrored = 0;
                    enemy->move.x = 1;
                    enemy->move.y = 0;
                    break;
                case 1:
                    enemy->move.x = -1;
                    enemy->move.y = 0;
                    sfSprite_setTexture(enemy->sprite,objects->enemies.textures[enemy->type][0], sfTrue);
                    sfSprite_setTextureRect(enemy->sprite, enemy->walk.mirrored_rect[enemy->walk.frame]);
                    enemy->walk.is_mirrored = 1;
                    break;
                case 2:
                    exit(84);
                case 4:
                    randomly_move_left_or_right(enemy, objects);
                    break;
                case 5:
                    for (int i = 0; i < objects->map.goal.total; i++) {
                        if (enemy->position.y == objects->map.goal.tiles[i].position.y) {
                            enemy->move.y = 0;
                            enemy->move.x = -1;
                            sfSprite_setTexture(enemy->sprite,
                                objects->enemies.textures[enemy->type][0], sfTrue);
                            sfSprite_setTextureRect(enemy->sprite,
                                enemy->walk.mirrored_rect[enemy->walk.frame]);
                            enemy->walk.is_mirrored = 1;
                            break;
                        }
                    }
                    break;
                case 7:
                    for (int i = 0; i < objects->map.goal.total; i++) {
                        if (enemy->position.y == objects->map.goal.tiles[i].position.y) {
                            enemy->move.y = 0;
                            enemy->move.x = 1;
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            else if (enemy->move.y == 1) {
                switch (objects->map.tileset[i].type) {
                case 2:
                    sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][1], sfTrue);
                    sfSprite_setTextureRect(enemy->sprite, enemy->walk.rect[enemy->walk.frame]);
                    enemy->walk.is_mirrored = 0;
                    enemy->move.x = 1;
                    enemy->move.y = 0;
                    break;
                case 3:
                    enemy->move.x = -1;
                    enemy->move.y = 0;
                    sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][0], sfTrue);
                    sfSprite_setTextureRect(enemy->sprite, enemy->walk.mirrored_rect[enemy->walk.frame]);
                    enemy->walk.is_mirrored = 1;
                    break;
                case 5:
                    for (int i = 0; i < objects->map.goal.total; i++) {
                        if (enemy->position.y == objects->map.goal.tiles[i].position.y) {
                            enemy->move.y = 0;
                            enemy->move.x = -1;
                            sfSprite_setTexture(enemy->sprite,
                                objects->enemies.textures[enemy->type][0], sfTrue);
                            sfSprite_setTextureRect(enemy->sprite,
                                enemy->walk.mirrored_rect[enemy->walk.frame]);
                            enemy->walk.is_mirrored = 1;
                            break;
                        }
                    }
                    break;
                case 6:
                    randomly_move_left_or_right(enemy, objects);
                    break;
                case 7:
                    for (int i = 0; i < objects->map.goal.total; i++) {
                        if (enemy->position.y == objects->map.goal.tiles[i].position.y) {
                            enemy->move.y = 0;
                            enemy->move.x = 1;
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            else if (enemy->move.x == 1) {
                switch (objects->map.tileset[i].type) {
                case 1:
                    enemy->move.x = 0;
                    enemy->move.y = 1;
                    break;
                case 3:
                    enemy->move.x = 0;
                    enemy->move.y = -1;
                    break;
                case 4:
                    for (int i = 0; i < objects->map.goal.total; i++) {
                        if (enemy->position.x == objects->map.goal.tiles[i].position.x) {
                            enemy->move.y = 1;
                            enemy->move.x = 0;
                            break;
                        }
                    }
                    break;
                case 5:
                    randomly_move_up_or_down(enemy);
                    break;
                case 6:
                    for (int i = 0; i < objects->map.goal.total; i++) {
                        if (enemy->position.x == objects->map.goal.tiles[i].position.x) {
                            enemy->move.y = -1;
                            enemy->move.x = 0;
                            break;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            else if (enemy->move.x == -1) {
                switch (objects->map.tileset[i].type) {
                case 0:
                    enemy->move.y = 1;
                    enemy->move.x = 0;
                    break;
                case 2:
                    enemy->move.y = -1;
                    enemy->move.x = 0;
                    break;
                case 4:
                    for (int i = 0; i < objects->map.goal.total; i++) {
                        if (enemy->position.x == objects->map.goal.tiles[i].position.x) {
                            enemy->move.y = 1;
                            enemy->move.x = 0;
                            break;
                        }
                    }
                    break;
                case 6:
                    for (int i = 0; i < objects->map.goal.total; i++) {
                        if (enemy->position.x == objects->map.goal.tiles[i].position.x) {
                            enemy->move.y = -1;
                            enemy->move.x = 0;
                            break;
                        }
                    }
                    break;
                case 7:
                    randomly_move_up_or_down(enemy);
                    break;
                default:
                    break;

                }
            }
            /*switch (objects->map.tileset[i].type) {
            case 0: enemy->move.x = 1; enemy->move.y = 0;
                break;
            case 1: enemy->move.x = 0; enemy->move.y = 1;
                break;
            case 2: enemy->move.x = 1; enemy->move.y = 0;
                break;
            case 3: enemy->move.x = 0; enemy->move.y = -1;
                break;
            case 7: enemy->move.x = 0; enemy->move.y = 1;*/
        }
    }
    sfSprite_move(enemy->sprite, enemy->move);
    enemy->position.x += enemy->move.x;
    enemy->position.y += enemy->move.y;
    sfClock_restart(enemy->clock);
    enemy->health_bar.position = enemy->position;
    enemy->health_bar.position.y -= 5;
    enemy->health_bar.position.x -= 25;
    sfSprite_setPosition(enemy->health_bar.background_sprite, enemy->health_bar.position);
    sfSprite_setPosition(enemy->health_bar.foreground_sprite, enemy->health_bar.position);
        //printf("position k: y-> %f x->%f\n", enemy->position.y, enemy.position.x);
}

void randomly_move_left_or_right(enemy_t *enemy, objects_t *objects)
{
    int random = get_random_int_within_range(0, 1);

    if (random != 1)
        random = -1;
    enemy->move.x = random;
    enemy->move.y = 0;
    if (enemy->move.x < 0) {
        sfSprite_setTexture(enemy->sprite,
            objects->enemies.textures[enemy->type][0], sfTrue);
        sfSprite_setTextureRect(enemy->sprite,
            enemy->walk.mirrored_rect[enemy->walk.frame]);
        enemy->walk.is_mirrored = 1;
    } else {
        sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][1], sfTrue);
        sfSprite_setTextureRect(enemy->sprite, enemy->walk.rect[enemy->walk.frame]);
        enemy->walk.is_mirrored = 0;
    }
}

void randomly_move_up_or_down(enemy_t *enemy)
{
    int random = get_random_int_within_range(0, 1);

    if (random != 1)
        random = -1;
    enemy->move.y = random;
    enemy->move.x = 0;
}