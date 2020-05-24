//
// Created by benedikt on 2/26/20.
//

#include "../../include/defender.h"

tower_t create_basic_stone_tower(spots_t spot, objects_t *objects)
{
    sfVector2f position = spot.position;
    tower_t tower;

    sfSprite_setTexture(spot.tile, objects->map.building_plots.tower_textures[3], sfTrue);
    tower.special_attributes.background_sprite = sfSprite_create();
    tower.special_attributes.foreground_sprite = sfSprite_create();
    sfSprite_setTexture(tower.special_attributes.background_sprite, objects->map.building_plots.stone_preview.special_attributes.background_texture, sfTrue);
    sfSprite_setTexture(tower.special_attributes.foreground_sprite, objects->map.building_plots.stone_preview.special_attributes.foreground_texture, sfTrue);
    position.x -= 3;
    position.y -= 34;
    sfSprite_setPosition(tower.special_attributes.background_sprite, position);
    position.y += 18.5;
    sfSprite_setPosition(tower.special_attributes.foreground_sprite, position);
    tower.special_attributes.movement_timer = sfClock_create();
    tower.special_attributes.movement_delay = 40000;
    tower.level = 0;
    //tower.texture = sfTexture_createFromFile("resources/towers/stone/3.png", NULL);
    tower.projectile.sprite = sfSprite_create();
    position.y -= 92;
    position.x += 3;
    sfSprite_setTexture(tower.projectile.sprite, objects->map.building_plots.tower_projectiles_textures[3], sfTrue);
    sfSprite_setPosition(tower.projectile.sprite, position);
    tower.projectile.animation.rect = get_rect_arr(3, 2, 100, 98);
    sfSprite_setTextureRect(tower.projectile.sprite, tower.projectile.animation.rect[0]);
    tower.projectile.animation.frame = 0;
    tower.projectile.animation.clock = sfClock_create();
    tower.projectile.animation.max_frame = 4;
    tower.projectile.animation.delay = 50000;
    tower.projectile.animation.is_mirrored = 0;
    tower.projectile.is_active = 0;
    tower.projectile.type = 4;
    tower.projectile.state = 0;
    tower.clock = sfClock_create();
    tower.gap.x = 0;
    tower.gap.y = -45;
    tower.stats_arr[0].cost = 160;
    tower.stats_arr[0].splash_radius = 12.5;
    tower.stats_arr[0].damage = 40;
    tower.stats_arr[0].radius = 14.0;
    tower.stats_arr[0].attacks_per_sec = 0.45;
    tower.stats_arr[1].cost = 280;
    tower.stats_arr[1].splash_radius = 17.8;
    tower.stats_arr[1].attacks_per_sec = 0.5;
    tower.stats_arr[1].damage = 70;
    tower.stats_arr[1].radius = 19.0;
    tower.stats_arr[2].cost = 450;
    tower.stats_arr[2].radius = 24.5;
    tower.stats_arr[2].damage = 100;
    tower.stats_arr[2].attacks_per_sec = 0.6;
    tower.stats_arr[2].splash_radius = 22.2;
    tower.projectile.radius = tower.stats_arr[0].splash_radius;
    tower.projectile.damage = tower.stats_arr[0].damage;
    tower.type = 3;
    return (tower);
}

void animate_catapult_startup(tower_t *tower, spots_t spot, enemy_list_t *enemy_list)
{
    sfVector2f down = {0, 1};
    sfVector2f up = {0, -1};
    sfVector2f position = spot.position;
    sfVector2f position_2;
    position.x -= 3;
    position.y -= 34;

    for (enemy_list_t *temp = enemy_list->next;
        temp != NULL; temp = temp->next) {
        if (temp->enemy == tower->projectile.target)
            break;
        else if (temp->next == NULL) {
            tower->projectile.is_active = 0;
            tower->projectile.state = 0;
            return;
        }
    }
    if (sfClock_getElapsedTime(tower->special_attributes.movement_timer).microseconds >= tower->special_attributes.movement_delay / ((tower->projectile.state * 7) + 1)) {
       sfClock_restart(tower->special_attributes.movement_timer);
        if (tower->projectile.state == 0) {
            sfSprite_move(tower->special_attributes.background_sprite, down);
            sfSprite_move(tower->special_attributes.foreground_sprite, down);
            sfSprite_move(tower->projectile.sprite, down);
        } else {
            sfSprite_move(tower->special_attributes.background_sprite, up);
            sfSprite_move(tower->special_attributes.foreground_sprite, up);
            sfSprite_move(tower->projectile.sprite, up);
        }
    }
    position_2 = sfSprite_getPosition(tower->special_attributes.background_sprite);
    if (position.y + 40 == position_2.y)
        tower->projectile.state = 1;
    else if (position.y == position_2.y)
        tower->projectile.state = 2;
}

void animate_stone_flight(tower_t *tower, enemy_list_t *enemy_list)
{
    sfVector2f down = {0, 1};
    sfVector2f up = {0, -1};

    for (enemy_list_t *temp = enemy_list->next;
        temp != NULL; temp = temp->next) {
        if (temp->enemy == tower->projectile.target)
            break;
        else if (temp->next == NULL) {
            tower->projectile.is_active = 0;
            tower->projectile.state = 0;
            return;
        }
    }
    if (sfClock_getElapsedTime(tower->special_attributes.movement_timer).microseconds >= tower->special_attributes.movement_delay / 10) {
        sfClock_restart(tower->special_attributes.movement_timer);
        if (tower->projectile.state == 2) {
            sfSprite_move(tower->projectile.sprite, up);
        } else {
            sfSprite_move(tower->projectile.sprite, down);
        }
    }
    sfVector2f position = sfSprite_getPosition(tower->projectile.sprite);
    if (position.y <= -100) {
        position.x = tower->projectile.target->position.x;
        sfSprite_setPosition(tower->projectile.sprite, position);
        tower->projectile.state = 3;
    }
    if (tower->projectile.state == 3) {
        position.x = tower->projectile.target->position.x;
        sfSprite_setPosition(tower->projectile.sprite, position);
     if (position.y >= tower->projectile.target->position.y) {
            tower->projectile.state = 4;
        }
    }
}