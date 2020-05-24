//
// Created by benedikt on 3/10/20.
//

#include "../../include/defender.h"

tower_t create_tavern(building_plots_t *plot)
{
    tower_t tavern;

    tavern.clock = sfClock_create();
    tavern.type = 1;
    tavern.level = 0;
    sfSprite_setTexture(plot->spots[plot->build_menu.spot_nb].tile,
        plot->tower_textures[1], sfTrue);
    tavern.stats_arr[0].cost = 100;
    tavern.stats_arr[0].damage = 7;
    tavern.stats_arr[0].attacks_per_sec = 1.0;
    tavern.stats_arr[0].radius = 15;
    tavern.stats_arr[0].splash_radius = 10.0;
    tavern.stats_arr[1].cost = 175;
    tavern.stats_arr[1].damage = 12;
    tavern.stats_arr[1].attacks_per_sec = 1.2;
    tavern.stats_arr[1].radius = 20;
    tavern.stats_arr[1].splash_radius = 9.5;
    tavern.stats_arr[2].cost = 400;
    tavern.stats_arr[2].damage = 40;
    tavern.stats_arr[2].attacks_per_sec = 1.4;
    tavern.stats_arr[2].radius = 22.4;
    tavern.stats_arr[2].splash_radius = 8.7;
    tavern.special_attributes.is_ability_locked = 1;
    tavern.gap.x = 0;
    tavern.gap.y = -25;
    tavern.projectile.sprite = sfSprite_create();
    tavern.projectile.is_active = -1;
    tavern.projectile.state = -1;
    tavern.projectile.animation.clock = sfClock_create();
    return (tavern);
}

sfVector2f get_positon_of_clicked_tile_if_possible(sfVector2i mouse_pos, objects_t *objects)
{
    sfVector2f failed_pos = {-1, -1};
    for (int i = 0; i < objects->map.total_tiles; i++) {
        sfVector2f tile_pos = sfSprite_getPosition(
            objects->map.tileset[i].tile);
        if (mouse_pos.y >= tile_pos.y && mouse_pos.y <= tile_pos.y + 100 \
 && mouse_pos.x >= tile_pos.x && mouse_pos.x <= tile_pos.x + 100) {
            return (tile_pos);
        }
    }
        for (int i = 0; i < objects->map.goal.total; i++) {
            sfVector2f tile_pos = sfSprite_getPosition(objects->map.goal.tiles[i].tile);
            if (mouse_pos.y >= tile_pos.y && mouse_pos.y <= tile_pos.y + 100 \
 && mouse_pos.x >= tile_pos.x && mouse_pos.x <= tile_pos.x + 100) {
                return (tile_pos);
            }
        }
        return (failed_pos);
}

void create_ally_if_possible(building_plots_t *plot, tower_t *tavern, sfVector2i mouse_pos, objects_t *objects)
{
            sfVector2f tile_pos;
    if (!sfMouse_isButtonPressed(sfMouseLeft) ||
        !(is_mouse_inside_radius(mouse_pos,
            tavern->stats_arr[tavern->level].radius + 2.5,
            (objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].position))))
        return;
    objects->interaction.mouse1_is_held = 1;
    if ((tile_pos = get_positon_of_clicked_tile_if_possible(mouse_pos, objects)).x != -1) {
        create_ally(tavern, objects, plot, tile_pos);
        plot->upgrade.button_2.is_confirm = 0;
        tavern->special_attributes.is_ability_locked = 1;
        sfSprite_setColor(plot->upgrade.button_2.sprite,
            plot->upgrade.button_2.def_color);
        sfSprite_setTextureRect(plot->upgrade.button_2.sprite,
            plot->upgrade.button_2.rects[2]);
        sfClock_restart(tavern->clock);
    }
     /*       create_ally(tavern, objects, plot, objects->map.goal.tiles[i]);
            plot->upgrade.button_2.is_confirm = 0;
            tavern->special_attributes.is_ability_locked = 1;
            sfSprite_setColor(plot->upgrade.button_2.sprite,
                plot->upgrade.button_2.def_color);
            sfSprite_setTextureRect(plot->upgrade.button_2.sprite,
                plot->upgrade.button_2.rects[2]);
            sfClock_restart(tavern->clock);
        }
    }*/
}

void create_ally(tower_t *tavern, objects_t *objects, building_plots_t *plot, sfVector2f tile_pos)
{
    enemy_t *enemy = malloc(sizeof(enemy_t));

    for (enemy_list_t *temp = objects->map.building_plots.allies->next;
        temp != NULL; temp = temp->next) {
        if (sfSprite_getPosition(temp->enemy->sprite).x ==
            tile_pos.x && \
sfSprite_getPosition(temp->enemy->sprite).y ==
            tile_pos.y) {
            temp->enemy->ally_stats.cur_hp = 0;
            refresh_enemy_health_bar(temp->enemy, objects,
                temp->enemy->ally_stats.cur_hp, temp->enemy->ally_stats.max_hp);
        }
    }
    enemy->is_ally = 1;
    enemy->type = tavern->level;
    enemy->target = NULL;
    enemy->ally_stats = plot->ally_stats[tavern->level];
    enemy->sprite = sfSprite_create();
    sfSprite_setTexture(enemy->sprite, plot->ally_textures[tavern->level][0],
        sfTrue);
    enemy->clock = sfClock_create();
    enemy->walk.is_mirrored = 1;
    enemy->walk.frame = 0;
    enemy->walk.max_frame = 20;
    enemy->walk.clock = sfClock_create();
    enemy->walk.delay = 35000;
    enemy->walk.rect = plot->ally_rects[tavern->level];
    enemy->walk.mirrored_rect = objects->map.building_plots.ally_rects_mirrored[tavern->level];
    sfSprite_setTextureRect(enemy->sprite, enemy->walk.mirrored_rect[0]);
    sfSprite_setPosition(enemy->sprite, tile_pos);
    enemy->health_bar.background_sprite = sfSprite_create();
    enemy->health_bar.foreground_sprite = sfSprite_create();
    sfSprite_setTexture(enemy->health_bar.background_sprite,
        objects->game_interface.health_bar_template.background_texture, sfTrue);
    sfSprite_setTexture(enemy->health_bar.foreground_sprite,
        objects->game_interface.ally_health_bar_foreground, sfTrue);
    enemy->health_bar.percentage = 100.0;
    sfIntRect rect = {0, 0, 100, 11};
    enemy->health_bar.foreground_rect = rect;
    enemy->health_bar.position = sfSprite_getPosition(enemy->sprite);
    enemy->health_bar.position.y += 5;
    enemy->health_bar.position.x -= 25;
    sfSprite_setPosition(enemy->health_bar.background_sprite,
        enemy->health_bar.position);
    sfSprite_setPosition(enemy->health_bar.foreground_sprite,
        enemy->health_bar.position);
    enemy->is_alive = 1;
    enemy->death.rect = enemy->walk.rect;
    enemy->death.frame = 0;
    enemy->is_targeted = 0;
    append_to_list(plot->allies, enemy);
}

void handle_tower_abilities(tower_t *tower, objects_t *objects)
{
    if (objects->map.building_plots.upgrade.is_active == 1) {
        if (objects->map.building_plots.upgrade.button_1.is_confirm == 2 && SELECTED_TOWER_U.stats_arr[SELECTED_TOWER_U.level + 1].cost <= objects->game_interface.money_count) {
            objects->map.building_plots.upgrade.button_1.is_confirm = 0;
            sfSprite_setTextureRect(objects->map.building_plots.upgrade.button_1.sprite, objects->map.building_plots.upgrade.button_1.rects[0]);
        } /*else if (objects->map.building_plots.upgrade.button_1.is_confirm == 0 || objects->map.building_plots.upgrade.button_1.is_confirm == 1) {
            objects->map.building_plots.upgrade.button_1.is_confirm = 2;
            sfSprite_setTextureRect(objects->map.building_plots.upgrade.button_1.sprite, objects->map.building_plots.upgrade.button_1.rects[2]);
        }*/
            if (SELECTED_TOWER_U.type == 1 &&
            sfClock_getElapsedTime(SELECTED_TOWER_U.clock).microseconds >
                SELECTED_TOWER_U.stats_arr[SELECTED_TOWER_U.level].splash_radius *
                    pow(10, 6) &&
            SELECTED_TOWER_U.special_attributes.is_ability_locked == 1)
            sfSprite_setTextureRect(
                objects->map.building_plots.upgrade.button_2.sprite,
                objects->map.building_plots.upgrade.button_2.rects[0]);
    }
    if (tower->type == 1) {
        if (sfClock_getElapsedTime(tower->clock).microseconds > tower->stats_arr[tower->level].splash_radius * pow(10, 6) && tower->special_attributes.is_ability_locked == 1) {
            sfClock_restart(tower->clock);
            tower->special_attributes.is_ability_locked = 0;
        }
    }
    if (objects->map.building_plots.build_menu.is_active == 1) {
        if (objects->map.building_plots.build_menu.button_2.is_confirm == 2 && objects->map.building_plots.tavern_template.stats_arr[0].cost <= objects->game_interface.money_count) {
            objects->map.building_plots.build_menu.button_2.is_confirm = 0;
            sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_2.sprite, objects->map.building_plots.build_menu.button_2.rects[0]);
        }/* else if (objects->map.building_plots.build_menu.button_2.is_confirm != 2 && objects->map.building_plots.tavern_template.stats_arr[0].cost > objects->game_interface.money_count) {
            objects->map.building_plots.build_menu.button_2.is_confirm = 2;
            sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_2.sprite, objects->map.building_plots.build_menu.button_2.rects[2]);
        }*/
        if (objects->map.building_plots.build_menu.button_3.is_confirm == 2 && objects->map.building_plots.fire_mage.stats_arr[0].cost <= objects->game_interface.money_count) {
            objects->map.building_plots.build_menu.button_3.is_confirm = 0;
            sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_3.sprite, objects->map.building_plots.build_menu.button_3.rects[0]);
        } /*else if (objects->map.building_plots.build_menu.button_3.is_confirm != 2 && objects->map.building_plots.fire_mage.stats_arr[0].cost > objects->game_interface.money_count) {
            objects->map.building_plots.build_menu.button_3.is_confirm = 2;
            sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_3.sprite, objects->map.building_plots.build_menu.button_3.rects[2]);
        }*/
        if (objects->map.building_plots.build_menu.button_4.is_confirm == 2 && objects->map.building_plots.stone_preview.stats_arr[0].cost <= objects->game_interface.money_count) {
            objects->map.building_plots.build_menu.button_4.is_confirm = 0;
            sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_4.sprite, objects->map.building_plots.build_menu.button_4.rects[0]);
        } /*else if (objects->map.building_plots.build_menu.button_4.is_confirm != 2 && objects->map.building_plots.stone_preview.stats_arr[0].cost > objects->game_interface.money_count) {
            objects->map.building_plots.build_menu.button_4.is_confirm = 2;
            sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_4.sprite, objects->map.building_plots.build_menu.button_4.rects[2]);
        }*/
    }
}