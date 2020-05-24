//
// Created by benedikt on 3/11/20.
//

#include "../../include/defender.h"

int check_button_interaction(button_t *button, sfRenderWindow *window, int height, int width)
{
    sfVector2f up = {1.1, 1.1};
    sfVector2f def = {1.0, 1.0};

    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window),
        sfSprite_getPosition(button->sprite), height, width)) {
        if (button->is_hovered == 0) {
            button->is_hovered = 1;
            sfSprite_setScale(button->sprite, up);
        } if (sfMouse_isButtonPressed(sfMouseLeft))
            return (1);
    } else if (button->is_hovered == 1) {
        button->is_hovered = 0;
        sfSprite_setScale(button->sprite, def);
    }
    return (0);
}


void set_all_buttons_to_default(objects_t *objects)
{
    objects->map.building_plots.build_menu.button_2.is_confirm = 0;
    objects->map.building_plots.build_menu.button_3.is_confirm = 0;
    objects->map.building_plots.build_menu.button_4.is_confirm = 0;
    objects->map.building_plots.upgrade.button_1.is_confirm = 0;
    objects->map.building_plots.upgrade.button_1.is_locked = 0;
    objects->map.building_plots.upgrade.button_2.is_confirm = 0;
    objects->map.building_plots.upgrade.sell.is_confirm = 0;
    sfSprite_setColor(objects->map.building_plots.upgrade.button_2.sprite, objects->map.building_plots.upgrade.button_2.def_color);
    sfSprite_setTextureRect(objects->map.building_plots.upgrade.button_1.sprite, objects->map.building_plots.upgrade.button_1.rects[0]);
    sfSprite_setTextureRect(objects->map.building_plots.upgrade.button_2.sprite, objects->map.building_plots.upgrade.button_2.rects[2]);
    sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_2.sprite, objects->map.building_plots.build_menu.button_2.rects[0]);
    sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_4.sprite, objects->map.building_plots.build_menu.button_4.rects[0]);
    sfSprite_setTextureRect(objects->map.building_plots.upgrade.sell.sprite, objects->map.building_plots.upgrade.sell.rects[0]);
    sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_3.sprite, objects->map.building_plots.build_menu.button_3.rects[0]);
    objects->game_interface.tower_stats.display_radius = 0;
}