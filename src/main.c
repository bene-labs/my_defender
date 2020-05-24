/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** main function of my_defender
*/

#include "../include/defender.h"
#include "../include/my.h"

int main(int argc, char **argv)
{
    objects_t objects;
    sfVideoMode mode = {1920, 1080, 64};
    sfRenderWindow *window = sfRenderWindow_create(mode, "-My Defender-", \
sfClose, NULL);

    if (create_objects(&objects) == 84)
        return (84);
    if (argc == 3) {
        if (generate_map(&objects, get_map(argv[1], &objects)) == 84)
            return (84);
        get_waves_array(&objects, argv[2]);
        objects.game_state = 'i';
        if (objects.map.total_tiles == 0 || objects.map.spawn.total == 0 ||
            objects.map.goal.total == 0) {
            my_printf(
                "Error: maps must contain at least one goal and one spawn!\n");
            return (cleanup(&objects, 84));
        }
        sfMusic_play(objects.main_theme);
    } else if (argc != 1) {
        my_printf("Error: invalid arguments!\n");
        return (cleanup(&objects, 84));
    }
    handle_game_loop(&objects, window);
    return (cleanup(&objects, 0));
}

void handle_game_loop(objects_t *objects, sfRenderWindow *window)
{
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        switch (objects->game_state) {
        case 'm':
            handle_menu(objects, &window);
            break;
        case 'i':
            handle_gameplay(objects, &window);
            break;
        }
        //handle_gameplay(objects, window);
        sfRenderWindow_display(window);
    }
}

void draw_ingame_objects(sfRenderWindow *window, objects_t *objects)
{
    sfRenderWindow_drawSprite(window, objects->map.background, NULL);
    for (int i = 0; i < objects->map.total_tiles; i++)
        sfRenderWindow_drawSprite(window, objects->map.tileset[i].tile, NULL);
    for (int i = 0; i < objects->map.small_deco.total; i++)
        sfRenderWindow_drawSprite(window,
            objects->map.small_deco.sprites[i].sprite, NULL);
    for (int i = 0; i < objects->map.big_deco.total; i++)
        sfRenderWindow_drawSprite(window,
            objects->map.big_deco.sprites[i].sprite, NULL);
    for (int i = 0; i < objects->map.spawn.total; i++)
        sfRenderWindow_drawSprite(window, objects->map.spawn.tiles[i].tile,
            NULL);
    for (int i = 0; i < objects->map.goal.total; i++)
        sfRenderWindow_drawSprite(window, objects->map.goal.tiles[i].tile,
            NULL);
    for (enemy_list_t *temp = objects->enemies.enemy_list->next;
        temp != NULL; temp = temp->next)
        sfRenderWindow_drawSprite(window, temp->enemy->sprite, NULL);
    for (enemy_list_t *temp = objects->map.building_plots.allies->next; temp != NULL; temp = temp->next) {
        sfRenderWindow_drawSprite(window, temp->enemy->sprite, NULL);
        sfRenderWindow_drawSprite(window,
            temp->enemy->health_bar.background_sprite, NULL);
        sfRenderWindow_drawSprite(window,
            temp->enemy->health_bar.foreground_sprite, NULL);
    }
    for (int i = 0; i < objects->map.building_plots.total; i++) {
        if (objects->map.building_plots.spots[i].is_filled &&
            objects->map.building_plots.spots[i].tower.type == 3)
            sfRenderWindow_drawSprite(window,
                objects->map.building_plots.spots[i].tower.special_attributes.background_sprite,
                NULL);
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.spots[i].tile, NULL);
        if (objects->map.building_plots.spots[i].is_filled)
            if (objects->map.building_plots.spots[i].tower.projectile.is_active)
                sfRenderWindow_drawSprite(window,
                    objects->map.building_plots.spots[i].tower.projectile.sprite,
                    NULL);
        if (objects->map.building_plots.spots[i].is_filled &&
            objects->map.building_plots.spots[i].tower.type == 3) {
            sfRenderWindow_drawSprite(window,
                objects->map.building_plots.spots[i].tower.special_attributes.foreground_sprite,
                NULL);
        }
    }
    for (enemy_list_t *temp = objects->enemies.enemy_list->next;
        temp != NULL; temp = temp->next) {
        sfRenderWindow_drawSprite(window,
            temp->enemy->health_bar.background_sprite, NULL);
        sfRenderWindow_drawSprite(window,
            temp->enemy->health_bar.foreground_sprite, NULL);
    }
    for (enemy_list_t *temp = objects->map.building_plots.allies->next;
        temp != NULL; temp = temp->next) {
        sfRenderWindow_drawSprite(window,
            temp->enemy->health_bar.background_sprite, NULL);
        sfRenderWindow_drawSprite(window,
            temp->enemy->health_bar.foreground_sprite, NULL);
    }
    if (objects->game_interface.tower_stats.display_radius == 1) {
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.upgrade.radius_sprite, NULL);
        if (objects->map.building_plots.upgrade.button_1.is_confirm == 1 ||
            objects->map.building_plots.upgrade.button_1.is_confirm == 2) {
            sfRenderWindow_drawSprite(window,
                objects->map.building_plots.upgrade.radius_preview_sprite,
                NULL);
        }
    }
    sfRenderWindow_drawSprite(window, objects->game_interface.background_sprite,
        NULL);
    if (objects->game_interface.tower_stats.is_active == 1) {
        sfRenderWindow_drawSprite(window,
            objects->game_interface.tower_stats.icons_sprite, NULL);
        sfRenderWindow_drawText(window,
            objects->game_interface.tower_stats.cur_stats_text, NULL);
        sfRenderWindow_drawSprite(window,
            objects->game_interface.tower_stats.icon, NULL);
        if (objects->game_interface.tower_stats.is_preview == 1)
            sfRenderWindow_drawText(window,
                objects->game_interface.tower_stats.preview_stats_text, NULL);
    }
    sfRenderWindow_drawSprite(window, objects->game_interface.settings_button.sprite, NULL);
    sfRenderWindow_drawText(window, objects->game_interface.lives_text, NULL);
    sfRenderWindow_drawSprite(window, objects->game_interface.lives_icon, NULL);
    sfRenderWindow_drawText(window, objects->game_interface.money_count_text,
        NULL);
    sfRenderWindow_drawSprite(window, objects->game_interface.money_icon, NULL);
    sfRenderWindow_drawText(window, objects->enemies.wave_text, NULL);
    if (objects->map.building_plots.build_menu.is_active == 1) {
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.build_menu.sprite, NULL);
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.build_menu.quit.sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->map.building_plots.build_menu.button_1.sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->map.building_plots.build_menu.button_2.sprite, NULL);
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.build_menu.button_3.sprite, NULL);
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.build_menu.button_4.sprite, NULL);
    }
    if (objects->map.building_plots.upgrade.is_active == 1) {
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.upgrade.sprite, NULL);
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.upgrade.quit.sprite, NULL);
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.upgrade.button_1.sprite, NULL);
        sfRenderWindow_drawText(window,
            objects->map.building_plots.upgrade.button_1.number_text, NULL);
        if (SELECTED_TOWER_U.type == 1 || SELECTED_TOWER_U.type == 0)
            sfRenderWindow_drawSprite(window, objects->map.building_plots.upgrade.button_2.sprite, NULL);
        if (SELECTED_TOWER_U.type == 0)
            sfRenderWindow_drawSprite(window, objects->map.building_plots.druid_arrow_mark_sprite, NULL);
        sfRenderWindow_drawSprite(window,
            objects->map.building_plots.upgrade.sell.sprite, NULL);
        sfRenderWindow_drawText(window,
            objects->map.building_plots.upgrade.sell.number_text, NULL);
    }
    if (objects->game_interface.settings.is_active == 1) {
        sfRenderWindow_drawSprite(window, objects->game_interface.settings.bg_sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->game_interface.settings.close.sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->game_interface.settings.restart.sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->game_interface.settings.back_to_menu.sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->game_interface.settings.quit.sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->game_interface.settings.sounds.sprite, NULL);
        sfRenderWindow_drawSprite(window, objects->game_interface.settings.music.sprite, NULL);
    }
}