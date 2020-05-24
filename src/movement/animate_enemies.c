//
// Created by benedikt on 2/14/20.
//

#include "../../include/defender.h"

int animate_enemy(enemy_t *enemy, objects_t *objects, animation_t *animation)
{
    if (sfClock_getElapsedTime(animation->clock).microseconds > animation->delay) {
        sfClock_restart(animation->clock);
            animation->frame++;
        if (animation->frame >= animation->max_frame) {
            if (enemy->is_alive == 0) {
                if (enemy->is_ally == 0) {
                    objects->game_interface.money_count += enemy->stats.value;
                    //printf("money: %d\n", objects->game_interface.money_count);
                    display_money_count(&objects->game_interface);
                    remove_enemy_from_list(objects->enemies.enemy_list, enemy);
                } else
                    remove_enemy_from_list(objects->map.building_plots.allies, enemy);
                return (1);
            }
            else
                animation->frame = 0;
        }
        if (animation->is_mirrored == 1) {
            sfSprite_setTextureRect(enemy->sprite, animation->mirrored_rect[animation->frame]);
        } else
            sfSprite_setTextureRect(enemy->sprite, animation->rect[animation->frame]);
        if (enemy->target && animation->frame == animation->max_frame / 2 && enemy->target->is_alive) {
            if (enemy->target->is_ally == 1) {
                enemy->target->ally_stats.cur_hp -= enemy->stats.damage;
                refresh_enemy_health_bar(enemy->target, objects,
                    enemy->target->ally_stats.cur_hp,
                    enemy->target->ally_stats.max_hp);
            }
            else {
                enemy->target->stats.cur_hp -= enemy->ally_stats.damage;
                refresh_enemy_health_bar(enemy->target, objects,
                    enemy->target->stats.cur_hp, enemy->target->stats.max_hp);
            }
        }
    }
    return (0);
}

void refresh_enemy_health_bar(enemy_t *enemy, objects_t *objects, double cur_hp, double max_hp)
{
    if (cur_hp <= 0) {
        enemy->health_bar.foreground_rect.width = 0;
        enemy->is_alive = 0;
        if (enemy->walk.is_mirrored == 1) {
            if (enemy->is_ally == 0)
                sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][3], sfTrue);
            else
                sfSprite_setTexture(enemy->sprite, objects->map.building_plots.ally_textures[enemy->type][3], sfTrue);
            sfSprite_setTextureRect(enemy->sprite, enemy->walk.mirrored_rect[0]);
        } else {
            if (enemy->is_ally == 0)
                sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][2], sfTrue);
            else
                sfSprite_setTexture(enemy->sprite, objects->map.building_plots.ally_textures[enemy->type][2], sfTrue);
            sfSprite_setTextureRect(enemy->sprite, enemy->walk.rect[0]);
        }
        enemy->walk.frame = 0;
    } else {
        enemy->health_bar.percentage = cur_hp / max_hp * 100;
        enemy->health_bar.foreground_rect.width = enemy->health_bar.percentage;
    }
        //printf("%f / %f * 100= %f%%\n", enemy->cur_hp, enemy->max_hp,
        //    enemy->health_bar.percentage);
    sfSprite_setTextureRect(enemy->health_bar.foreground_sprite,
        enemy->health_bar.foreground_rect);
}

void animate_projectile_impact(projectile_t *projectile, animation_t *animation, enemy_list_t *enemy_list, objects_t *objects)
{
    for (enemy_list_t *temp = enemy_list->next;
        temp != NULL; temp = temp->next) {
        if (temp->enemy == projectile->target)
            break;
        else if (temp->next == NULL) {
            animation->frame = 0;
            projectile->is_active = 0;
            projectile->state = 0;
            sfSprite_setTextureRect(projectile->sprite, animation->rect[0]);
            return;
        }
    }
    if (sfClock_getElapsedTime(animation->clock).microseconds > animation->delay) {
        sfClock_restart(animation->clock);
        animation->frame++;
        if (projectile->target->is_alive != 0 && animation->frame == animation->max_frame / 2 + 1) {
            if (projectile->type == 4) {
                sfMusic_stop(objects->rock);
                sfMusic_play(objects->rock);
            }
            projectile->target->stats.cur_hp -= projectile->damage / 2;
            if (projectile->damage % 2 != 0)
                projectile->target->stats.cur_hp--;
            refresh_enemy_health_bar(projectile->target, objects, projectile->target->stats.cur_hp, projectile->target->stats.max_hp);
            for (enemy_list_t *temp = enemy_list->next; temp != NULL; temp = temp->next) {
                if (is_enemy_inside_radius(*projectile->target, projectile->radius, temp->enemy->position.x + 50, temp->enemy->position.y + 50)) {
                    temp->enemy->stats.cur_hp -= projectile->damage / 2;
                    refresh_enemy_health_bar(temp->enemy, objects, projectile->target->stats.cur_hp, projectile->target->stats.max_hp);
                }
            }
        }
        if (animation->frame == animation->max_frame) {
            animation->frame = 0;
            projectile->is_active = 0;
            projectile->state = 0;
            projectile->target->is_targeted = 0;
            sfSprite_setTextureRect(projectile->sprite, animation->rect[0]);
            //printf("reload!\n");
            return;
        }
        sfVector2f position = sfSprite_getPosition(projectile->sprite);
        position.x = projectile->target->position.x;
        if (projectile->target->walk.is_mirrored)
            position.x += 20;
        //position.y -= 160;
        sfSprite_setPosition(projectile->sprite, position);
        sfSprite_setTextureRect(projectile->sprite, animation->rect[animation->frame]);
    }
}