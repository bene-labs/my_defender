#include "../include/defender.h"

int cleanup(objects_t *objects, int return_value)
{
    if (objects->game_state == 'i')
        cleanup_map(objects);
    for (; objects->enemies.enemy_list->next != NULL; remove_enemy_from_list(
        objects->enemies.enemy_list, objects->enemies.enemy_list->next->enemy)) {
        if (objects->enemies.enemy_list->next->enemy == NULL)
            break;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++)
            sfTexture_destroy(objects->enemies.textures[i][j]);
    }
    sfMusic_destroy(objects->main_theme);
    sfMusic_destroy(objects->rock);
    sfMusic_destroy(objects->click);
    sfTexture_destroy(objects->map.tile_texture);
    sfTexture_destroy(objects->map.big_deco.texture);
    sfTexture_destroy(objects->map.small_deco.texture);
    sfTexture_destroy(objects->map.goal.texture);
    sfTexture_destroy(objects->map.building_plots.texture);
    sfSprite_destroy(objects->map.background);
    sfTexture_destroy(objects->map.texture);
    return (return_value);
}

void cleanup_map(objects_t *objects)
{
    for (int i = 0; i < objects->map.total_tiles; i++)
        sfSprite_destroy(objects->map.tileset[i].tile);
    free(objects->map.tileset);
    for (int i = 0; i < objects->map.small_deco.total; i++)
        sfSprite_destroy(objects->map.small_deco.sprites[i].sprite);
    free(objects->map.small_deco.sprites);
    for (int i = 0; i < objects->map.big_deco.total; i++)
        sfSprite_destroy(objects->map.big_deco.sprites[i].sprite);
    free(objects->map.big_deco.sprites);
    for (int i = 0; i < objects->map.spawn.total; i++)
        sfSprite_destroy(objects->map.spawn.tiles[i].tile);
    free(objects->map.spawn.tiles);
    for (int i = 0; i < objects->map.goal.total; i++)
        sfSprite_destroy(objects->map.goal.tiles[i].tile);
    free(objects->map.goal.tiles);
    for (int i = 0; i < objects->enemies.final_wave; i++)
        free(objects->enemies.waves[i]);
    for ( ; objects->enemies.enemy_list->next != NULL; remove_enemy_from_list(objects->enemies.enemy_list, objects->enemies.enemy_list->next->enemy))
        if (objects->enemies.enemy_list->next->enemy == NULL)
            break;
    for ( ;  objects->map.building_plots.allies->next != NULL; remove_enemy_from_list( objects->map.building_plots.allies,  objects->map.building_plots.allies->next->enemy))
        if ( objects->map.building_plots.allies->next->enemy == NULL)
            break;
    free(objects->enemies.waves);
}

void get_default_game_stats(objects_t *objects)
{
    my_strcpy(objects->enemies.wave_text_str, "Wave: 01/00");
    objects->enemies.is_new_wave = 0;
    objects->game_interface.live_count = 20;
    objects->game_interface.tower_stats.is_active = 0;
    objects->game_interface.tower_stats.is_preview = 0;
    objects->game_interface.settings.is_active = 0;
    objects->map.building_plots.build_menu.is_active = 0;
    objects->map.building_plots.upgrade.is_active = 0;
    objects->map.building_plots.build_menu.button_3.is_confirm = 0;
    objects->map.building_plots.build_menu.button_4.is_confirm = 0;
    objects->map.building_plots.upgrade.button_1.is_confirm = 0;
    objects->map.building_plots.upgrade.sell.is_confirm = 0;
    objects->game_interface.lives_str[0] = '2';
    objects->game_interface.lives_str[1] = '0';
    sfText_setString(objects->game_interface.lives_text, objects->game_interface.lives_str);
}