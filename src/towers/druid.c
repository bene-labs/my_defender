//
// Created by benedikt on 3/12/20.
//

#include "../../include/defender.h"

tower_t create_druid_tower(objects_t *objects)
{
    tower_t druid;

    sfSprite_setTexture(
        objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tile,
        objects->map.building_plots.tower_textures[0], sfTrue);
    druid.stats_arr[0] =  objects->map.building_plots.druid_tower.stats_arr[0];
    druid.stats_arr[1].cost = 150;
    druid.stats_arr[1].radius = 999.9;
    druid.stats_arr[1].attacks_per_sec = 0.2;
    druid.stats_arr[1].damage = 2;
    druid.stats_arr[1].splash_radius = 10.5;
    druid.stats_arr[2].cost = 225;
    druid.stats_arr[2].radius = 999.9;
    druid.stats_arr[2].attacks_per_sec = 0.3;
    druid.stats_arr[2].damage = 3;
    druid.stats_arr[2].cost = 350;
    druid.stats_arr[2].splash_radius = 12.8;
    druid.gap.y = -40;
    druid.type = 0;
    druid.level = 0;
    druid.clock = sfClock_create();
    druid.projectile.damage = druid.stats_arr[0].damage;
    druid.projectile.type = 1;
    druid.projectile.state = 0;
    druid.projectile.sprite = sfSprite_create();
    sfSprite_setTexture(druid.projectile.sprite, objects->map.building_plots.tower_projectiles_textures[0], sfTrue);
    druid.projectile.is_active = 0;
    druid.projectile.animation.rect = get_rect_arr(11, 4, 100, 263);
    druid.projectile.animation.delay = 100000;
    druid.projectile.radius = druid.stats_arr[0].splash_radius;
    druid.projectile.animation.max_frame = 43;
    druid.projectile.animation.frame = 0;
    druid.projectile.animation.clock = sfClock_create();
    druid.projectile.destination.x = -1;
    druid.projectile.destination.y = 0;
    druid.special_attributes.is_ability_locked = 0;
    return (druid);
}

void animate_rain_cloud(projectile_t *projectile, animation_t *animation, enemy_list_t *enemy_list, tower_t *tower)
{
    if (sfClock_getElapsedTime(animation->clock).microseconds > animation->delay) {
        sfClock_restart(animation->clock);
        animation->frame++;
        for (enemy_list_t *temp = enemy_list->next; temp != NULL; temp = temp->next) {
                if (temp->enemy->position.x >= projectile->destination.x && temp->enemy->position.x <= projectile->destination.x + 90 \
&& temp->enemy->position.y >= projectile->destination.y + 100 && temp->enemy->position.y <= projectile->destination.y + 260) {
                    sfSprite_setColor(temp->enemy->sprite, sfGreen);
                    temp->enemy->is_poisoned = 1;
                    sfClock_restart(temp->enemy->poison_tick_clock);
                    sfClock_restart(temp->enemy->poisoned_duration_clock);
                    temp->enemy->poison_limit = get_random_int_within_range(10, 80);
                    temp->enemy->posion_damage = projectile->damage;
                    /*temp->enemy->stats.cur_hp -= projectile->damage / 2;
                    refresh_enemy_health_bar(temp->enemy, objects, projectile->target->stats.cur_hp, projectile->target->stats.max_hp);*/
                }
            }
        }
    if (animation->frame == animation->max_frame) {
        animation->frame = 0;
        projectile->is_active = 0;
        projectile->state = 0;
        sfSprite_setTextureRect(projectile->sprite, animation->rect[0]);
        sfClock_restart(tower->clock);
        //printf("reload!\n");
        return;
    }
    //sfSprite_setPosition(projectile->sprite, projectile->destination);
    sfSprite_setTextureRect(projectile->sprite, animation->rect[animation->frame]);
}

void handle_poisoned_enemy(enemy_t *enemy, objects_t *objects)
{
    if (sfClock_getElapsedTime(enemy->poison_tick_clock).microseconds > 1000000 * 0.2) {
        sfClock_restart(enemy->poison_tick_clock);
        enemy->stats.cur_hp -= enemy->posion_damage;
        refresh_enemy_health_bar(enemy, objects, enemy->stats.cur_hp, enemy->stats.max_hp);
        enemy->poison_count++;
    }
    if (enemy->poison_count >= enemy->poison_limit || enemy->is_alive == 0) {
        sfSprite_setColor(enemy->sprite, enemy->def_color);
        enemy->is_poisoned = 0;
    }
}