/*
** EPITECH PROJECT, 2020
** main_gameplay.c
** File description:
** gameplay
*/


#include "../include/defender.h"

void handle_gameplay(objects_t *objects, sfRenderWindow **window)
{
    sfEvent event;
    enemy_list_t *temp_2;

    draw_ingame_objects(*window, objects);
    if (objects->game_interface.settings.is_active == 0) {
        check_if_enemy_can_attack(objects->enemies.enemy_list, objects->map.building_plots.allies, objects);
        for (enemy_list_t *temp = objects->enemies.enemy_list->next;
            temp != NULL; temp = temp->next) {
            if (animate_enemy(temp->enemy, objects, &temp->enemy->walk) == 1)
                break;
            if (temp->enemy->is_poisoned == 1)
                handle_poisoned_enemy(temp->enemy, objects);
            if (temp->enemy->target) {
                for (temp_2 = objects->map.building_plots.allies->next; temp_2 != NULL; temp_2 = temp_2->next) {
                    if (temp_2->enemy == temp->enemy->target)
                        break;
                }
                if (temp_2 == NULL) {
                    temp->enemy->target = NULL;
                    temp->enemy->walk.frame = 0;
                    if (temp->enemy->walk.is_mirrored == 0) {
                        sfSprite_setTexture(temp->enemy->sprite, objects->enemies.textures[temp->enemy->type][1], sfTrue);
                        sfSprite_setTextureRect(temp->enemy->sprite, temp->enemy->walk.rect[0]);
                    } else {
                        sfSprite_setTexture(temp->enemy->sprite, objects->enemies.textures[temp->enemy->type][0], sfTrue);
                        sfSprite_setTextureRect(temp->enemy->sprite, temp->enemy->walk.mirrored_rect[0]);
                    }
                }
                else
                    continue;
            }
            if (sfClock_getElapsedTime(temp->enemy->clock).microseconds >
                temp->enemy->stats.move_delay && temp->enemy->is_alive == 1) {
                move_enemy(temp->enemy, objects);
            }
        }
        for (enemy_list_t *temp = objects->map.building_plots.allies->next;
        temp != NULL; temp = temp->next) {
            if (temp->enemy->ally_stats.damage != 15 && temp->enemy->target == NULL && temp->enemy->is_alive != 0)
                continue; //temp :cur only knight_1 has a functional idle animation
             if (animate_enemy(temp->enemy, objects, &temp->enemy->walk) == 1)
                break;
            if (temp->enemy->target) {
                for (temp_2 = objects->enemies.enemy_list->next; temp_2 != NULL; temp_2 = temp_2->next) {
                    if (temp_2->enemy == temp->enemy->target)
                        break;
                }
                if (temp_2 == NULL) {
                    temp->enemy->target = NULL;
                    temp->enemy->walk.frame = 0;
                    temp->enemy->is_targeted = 0;
                    if (temp->enemy->walk.is_mirrored == 0) {
                        sfSprite_setTexture(temp->enemy->sprite, objects->map.building_plots.ally_textures[temp->enemy->type][1], sfTrue);
                        sfSprite_setTextureRect(temp->enemy->sprite, temp->enemy->walk.rect[0]);
                    } else {
                        sfSprite_setTexture(temp->enemy->sprite, objects->map.building_plots.ally_textures[temp->enemy->type][0], sfTrue);
                        sfSprite_setTextureRect(temp->enemy->sprite, temp->enemy->walk.mirrored_rect[0]);
                    }
                }
            }
        }
        for (int i = 0; i < objects->map.building_plots.total; i++) {
            if (objects->map.building_plots.spots[i].is_filled == 1) {
                if (objects->map.building_plots.spots[i].tower.type == 1)
                    handle_tower_abilities(&objects->map.building_plots.spots[i].tower,  objects);
                else {
                    for (enemy_list_t *temp = objects->enemies.enemy_list->next;
                        temp != NULL; temp = temp->next) {
                        handle_tower_attack(
                            objects->map.building_plots.spots[i],
                            &objects->map.building_plots.spots[i].tower,
                            temp->enemy);
                    }
                }
            }
            if (objects->map.building_plots.spots[i].tower.projectile.is_active == 1) {
                if (objects->map.building_plots.spots[i].tower.projectile.type == 1)
                    animate_rain_cloud( &objects->map.building_plots.spots[i].tower.projectile,
                        &objects->map.building_plots.spots[i].tower.projectile.animation,
                        objects->enemies.enemy_list, &objects->map.building_plots.spots[i].tower);
                if (objects->map.building_plots.spots[i].tower.projectile.state == 4 ||
                    objects->map.building_plots.spots[i].tower.projectile.type == 3 )
                    animate_projectile_impact(
                        &objects->map.building_plots.spots[i].tower.projectile,
                        &objects->map.building_plots.spots[i].tower.projectile.animation,
                        objects->enemies.enemy_list, objects);
                else if (
                    objects->map.building_plots.spots[i].tower.projectile.type ==
                        4 &&
                        objects->map.building_plots.spots[i].tower.projectile.state <
                            2)
                    animate_catapult_startup(
                        &objects->map.building_plots.spots[i].tower,
                        objects->map.building_plots.spots[i],
                        objects->enemies.enemy_list);
                else if (
                    objects->map.building_plots.spots[i].tower.projectile.type ==
                        4 &&
                        (objects->map.building_plots.spots[i].tower.projectile.state ==
                            2 ||
                            objects->map.building_plots.spots[i].tower.projectile.state ==
                                3))
                    animate_stone_flight(
                        &objects->map.building_plots.spots[i].tower,
                        objects->enemies.enemy_list);
            }
        }
        for (enemy_list_t *temp = objects->enemies.enemy_list->next;
            temp != NULL; temp = temp->next) {
            if (is_enemy_past_goal(temp->enemy, objects) == 1) {
                objects->game_interface.live_count -= temp->enemy->stats.threat;
                if (objects->game_interface.live_count <= 0) {
                    objects->game_state = 'm';
                    objects->menu.state = 'f';
                    cleanup_map(objects);
                    get_default_game_stats(objects);
                    return;
                }
                for (int i = 0; i < temp->enemy->stats.threat; i++) {
                    remove_points(objects->game_interface.lives_str, 1,
                        objects->game_interface.lives_text);
                }
                remove_enemy_from_list(objects->enemies.enemy_list,
                    temp->enemy);
                break;
            }
        }
        if (sfClock_getElapsedTime(objects->enemies.spawn_timer).microseconds >=
            objects->enemies.spawn_delay &&
            objects->enemies.cur_wave <= objects->enemies.final_wave &&
            (objects->enemies.is_new_wave == 0 ||
                is_new_wave_start(objects, &objects->enemies,
                    objects->enemies.enemy_list))) {
            sfClock_restart(objects->enemies.spawn_timer);
            determine_enemy(objects,
                objects->enemies.waves[objects->enemies.cur_wave][objects->enemies.cur_column]);
        }
    }
    while (sfRenderWindow_pollEvent(*window, &event))
        handle_events(*window, objects, event);
}

void handle_events(sfRenderWindow *window, objects_t *objects, sfEvent event)
{
    sfVector2f def = {1, 1};
    if (objects->game_interface.settings.is_active == 1) {
        handle_setting_menu(&objects->game_interface.settings, window, objects);
    }
    if (objects->game_interface.settings.is_active == 0) {
        if (sfMouse_isButtonPressed(sfMouseRight))
            set_all_buttons_to_default(objects);
        for (int i = 0; i < objects->map.building_plots.total; i++) {
            if (sfMouse_getPositionRenderWindow(window).y >=
                objects->map.building_plots.spots[i].position.y && \
        sfMouse_getPositionRenderWindow(window).y <=
                objects->map.building_plots.spots[i].position.y + 100 && \
        sfMouse_getPositionRenderWindow(window).x >=
                objects->map.building_plots.spots[i].position.x && \
        sfMouse_getPositionRenderWindow(window).x <=
                objects->map.building_plots.spots[i].position.x + 100) {
                //my_printf("%d->", i);
                if (objects->map.building_plots.spots[i].is_filled == 1 &&
                    !(objects->map.building_plots.upgrade.is_active == 1 &&
                        objects->map.building_plots.upgrade.spot_nb == i))
                    handle_tower_interaction(objects,
                        objects->map.building_plots.spots[i], i);
                else if (
                    !(objects->map.building_plots.build_menu.spot_nb == i &&
                        objects->map.building_plots.build_menu.is_active ==
                            1) &&
                        !(objects->map.building_plots.upgrade.is_active == 1 &&
                            objects->map.building_plots.upgrade.spot_nb == i))
                    handle_building_spots(objects,
                        objects->map.building_plots.spots[i], i);
                objects->map.building_plots.spots[i].is_hovered = 1;
                break;
            } else if (objects->map.building_plots.spots[i].is_hovered == 1) {
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    objects->interaction.mouse1_is_held = 1;
                    objects->map.building_plots.upgrade.is_active = 0;
                    objects->map.building_plots.build_menu.is_active = 0;
                }
                sfSprite_setScale(objects->map.building_plots.spots[i].tile,
                    def);
                objects->map.building_plots.spots[i].is_hovered = 0;
            }
            //my_printf("Cursor: x:%d y: %d Spot: x:%d y:%d\n", sfMouse_getPositionRenderWindow(window).x, sfMouse_getPositionRenderWindow(window).y, objects->map.building_plots.spots[i].position.x, objects->map.building_plots.spots[i].position.y);
        }
        handle_setting_button(&objects->game_interface, window,
            objects->interaction, objects->click);
        if (objects->map.building_plots.upgrade.is_active == 1)
            handle_upgrade_menu(window, objects);
        if (objects->map.building_plots.build_menu.is_active == 1)
            handle_building_menu(window, objects);
    }
    if (!(sfMouse_isButtonPressed(sfMouseLeft)))
        objects->interaction.mouse1_is_held = 0;
    else
        objects->interaction.mouse1_is_held = 1;
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
}