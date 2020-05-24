//
// Created by benedikt on 2/22/20.
//

#include "../../include/defender.h"

void display_tower_stats(tower_t tower, stat_display_t *display, building_plots_t building_plots, sfTexture *texture)
{
    int pre_digits = 0;

    if (tower.level > 3)
        tower.level = 0;
    sfVector2f position = {360, 950};
    sfText_setPosition(display->cur_stats_text, position);
    sfVector2f position_2 = {10, 950};
    position_2.y += tower.gap.y;
    position_2.x += tower.gap.x;
    sfSprite_setPosition(display->icon, position_2);
    if (tower.type == 1) {
        sfSprite_setTexture(display->icons_sprite, display->tavern_icons, sfTrue);
    } else
        sfSprite_setTexture(display->icons_sprite, display->icons_texture, sfTrue);
    sfSprite_setTexture(display->icon, texture, sfTrue);
    sfSprite_setTextureRect(display->icon,
        building_plots.tower_rects[tower.type][tower.level]);
    for (int i = 0; i < 66; i++)
        display->cur_stats_str[i] = ' ';
    if (tower.stats_arr[tower.level].damage >= 10)
        display->cur_stats_str[1] = '0';
    if (tower.stats_arr[tower.level].damage >= 100)
        display->cur_stats_str[0] = '0';
    for (int i = 0; i < tower.stats_arr[tower.level].damage && i < 999; i++)
        add_points(display->cur_stats_str, 2);
    int cut_to_int = tower.stats_arr[tower.level].attacks_per_sec;
    display->cur_stats_str[21] = '0';
    for (int i = 0; i < cut_to_int && i < 9; i++)
        add_points(display->cur_stats_str, 21);
    display->cur_stats_str[22] = '.';
    pre_digits =
        (tower.stats_arr[tower.level].attacks_per_sec - cut_to_int) * 100;
    display->cur_stats_str[23] = '0';
    for (int i = 0; i < pre_digits && i < 99; i++)
        add_points(display->cur_stats_str, 24);
    cut_to_int = tower.stats_arr[tower.level].radius;
    if (cut_to_int >= 100)
        display->cur_stats_str[39] = '0';
    if (cut_to_int >= 10)
        display->cur_stats_str[40] = '0';
    if (cut_to_int == 0)
        display->cur_stats_str[41] = '0';
    for (int i = 0; i < cut_to_int && i < 999; i++)
        add_points(display->cur_stats_str, 41);
    pre_digits = (tower.stats_arr[tower.level].radius - cut_to_int) * 10;
    if (pre_digits == 0)
        display->cur_stats_str[43] = '0';
    display->cur_stats_str[42] = '.';
    for (int i = 0; i < pre_digits && i < 9; i++)
        add_points(display->cur_stats_str, 43);
    cut_to_int = tower.stats_arr[tower.level].splash_radius;
    if (cut_to_int >= 10)
        display->cur_stats_str[58] = '0';
    if (cut_to_int == 0)
        display->cur_stats_str[59] = '0';
    for (int i = 0; i < cut_to_int && i  < 99; i++)
        add_points(display->cur_stats_str, 59);
    pre_digits = (tower.stats_arr[tower.level].splash_radius - cut_to_int) * 10;
    display->cur_stats_str[60] = '.';
    if (pre_digits == 0)
        display->cur_stats_str[61] = '0';
    for (int i = 0; i < pre_digits && i < 9; i++)
        add_points(display->cur_stats_str, 61);
    if (tower.type == 1) {
        display->cur_stats_str[63] = 's';
        display->cur_stats_str[64] = 'e';
        display->cur_stats_str[65] = 'c';
    }
    sfText_setString(display->cur_stats_text, display->cur_stats_str);
    display->is_active = 1;
}

void display_tower_stats_preview(tower_t tower, stat_display_t *display, building_plots_t building_plots, sfTexture *texture)
{
    int pre_digits = 0;

    if (tower.level == 2)
        return;
    sfVector2f position = {360, 900};
    sfText_setPosition(display->cur_stats_text, position);
    //sfText_setCharacterSize(display->cur_stats_text, 30);
    //printf("level: %d damage: %d, atps: %f, range: %f\n", tower.level, tower.stats_arr[tower.level].damage, tower.stats_arr[tower.level].attacks_per_sec, tower.stats_arr[tower.level].radius);
    sfSprite_setTexture(display->icon, texture, sfTrue);
    sfSprite_setTextureRect(display->icon,
        building_plots.tower_rects[tower.type][tower.level]);
    for (int i = 0; i < 66; i++)
        display->cur_stats_str[i] = ' ';
    if (tower.stats_arr[tower.level + 1].damage >= 10)
        display->cur_stats_str[1] = '0';
    if (tower.stats_arr[tower.level + 1].damage >= 100)
        display->cur_stats_str[0] = '0';
    for (int i = 0; i < tower.stats_arr[tower.level + 1].damage && i < 999; i++)
        add_points(display->cur_stats_str, 2);
    int cut_to_int = tower.stats_arr[tower.level + 1].attacks_per_sec;
    display->cur_stats_str[21] = '0';
    for (int i = 0; i < cut_to_int && i < 9; i++)
        add_points(display->cur_stats_str, 21);
    display->cur_stats_str[22] = '.';
    pre_digits =
        (tower.stats_arr[tower.level + 1].attacks_per_sec - cut_to_int) * 100;
    display->cur_stats_str[23] = '0';
    for (int i = 0; i < pre_digits && i < 99; i++)
        add_points(display->cur_stats_str, 24);
    cut_to_int = tower.stats_arr[tower.level + 1].radius;
    if (cut_to_int >= 100)
        display->cur_stats_str[39] = '0';
    if (cut_to_int >= 10)
        display->cur_stats_str[40] = '0';
    if (cut_to_int == 0)
        display->cur_stats_str[41] = '0';
    for (int i = 0; i < cut_to_int && i < 999; i++)
        add_points(display->cur_stats_str, 41);
    pre_digits = (tower.stats_arr[tower.level + 1].radius - cut_to_int) * 10;
    if (pre_digits == 0)
        display->cur_stats_str[43] = '0';
    display->cur_stats_str[42] = '.';
    for (int i = 0; i < pre_digits && i < 9; i++)
        add_points(display->cur_stats_str, 43);
    cut_to_int = tower.stats_arr[tower.level + 1].splash_radius;
    if (cut_to_int >= 10)
        display->cur_stats_str[58] = '0';
    if (cut_to_int == 0)
        display->cur_stats_str[59] = '0';
    for (int i = 0; i < cut_to_int && i  < 99; i++)
        add_points(display->cur_stats_str, 59);
    pre_digits = (tower.stats_arr[tower.level + 1].splash_radius - cut_to_int) * 10;
    display->cur_stats_str[60] = '.';
    if (pre_digits == 0)
        display->cur_stats_str[61] = '0';
    for (int i = 0; i < pre_digits && i < 9; i++)
        add_points(display->cur_stats_str, 61);
    if (tower.type == 1) {
        display->cur_stats_str[63] = 's';
        display->cur_stats_str[64] = 'e';
        display->cur_stats_str[65] = 'c';
    }
    sfText_setString(display->preview_stats_text, display->cur_stats_str);
    display->is_preview = 1;
}

void display_money_count(game_interface_t *interface)
{
    static int prev_count = 0;
    sfVector2f position = {1630, 13};
    sfColor red = {139, 36, 15, 232};

    for (int i = 0; i < 5; i++)
        interface->money_count_str[i] = ' ';
    interface->money_count_str[5] = '0';
    for (int i = 9, j = 4; i < interface->money_count && j >= 0; i *= 10, i += 9, j--) {
        interface->money_count_str[j] = '0';
        position.x -= 15;
    }
    for (int i = 0; i < interface->money_count && i < 999999; i++)
        add_points(interface->money_count_str, 5);
    sfText_setString(interface->money_count_text, interface->money_count_str);
    //printf("%d->%d\n", prev_count, interface->money_count);
    if (prev_count < interface->money_count)
        sfText_setColor(interface->money_count_text, sfGreen);
    else if (prev_count > interface->money_count)
        sfText_setColor(interface->money_count_text, red);
    prev_count = interface->money_count;
    sfText_setPosition(interface->money_count_text, position);
}

void display_button_cost(button_t *button, tower_t *tower)
{
    sfVector2f position = sfSprite_getPosition(button->sprite);

    if (tower->level == 2) {
        sfText_setString(button->number_text, "max");
    } else {
        //printf("cost: %d", tower->stats_arr[tower->level + 1].cost);
        position.x += 25;
        for (int i = 0; i < 5; i++)
            button->number_str[i] = ' ';
        button->number_str[5] = '0';
        for (int i = 9, j = 4; i < tower->stats_arr[tower->level + 1].cost &&
            j >= 0; i *= 10, i += 9, j--) {
            button->number_str[j] = '0';
            position.x -= 18;
        }
        for (int i = 0; i < tower->stats_arr[tower->level + 1].cost; i++)
            add_points(button->number_str, 5);
        sfText_setString(button->number_text, button->number_str);
    }
    position.y += 15;
    sfText_setPosition(button->number_text, position);
}

void display_sell_button_value(button_t *button, tower_t *tower)
{
    sfVector2f position = sfSprite_getPosition(button->sprite);
    int total_value = 0;

    for (int i = 0; i <= tower->level; i++)
        total_value += tower->stats_arr[i].cost;
    total_value /= 3;
    position.x -= 10;
    for (int i = 0; i < 5; i++)
        button->number_str[i] = ' ';
    button->number_str[5] = '0';
   for (int i = 9, j = 4; i < total_value && j >= 0; i *= 10, i += 9, j--) {
        button->number_str[j] = '0';
    }
    for (int i = 0; i < total_value; i++)
        add_points(button->number_str, 5);
    sfText_setString(button->number_text, button->number_str);
    position.y += 25;
    sfText_setPosition(button->number_text, position);
}

int display_radius(tower_t tower, spots_t spot, sfSprite *sprite, int is_preview)
{
    sfVector2f position = spot.position;

    if ((tower.level == 2 && is_preview != 0) || tower.type == 0)
        return (0);
    position.x += 50;
    position.y += 50;
    position.x -= tower.stats_arr[tower.level + is_preview].radius * 10;
    position.y -= tower.stats_arr[tower.level + is_preview].radius * 10;
    sfSprite_setPosition(sprite, position);
    sfVector2f radius_scale = {(tower.stats_arr[tower.level + is_preview].radius * 10 * 2) / 400.0, (tower.stats_arr[tower.level + is_preview].radius * 10 * 2) / 400.0};
    sfSprite_setScale(sprite, radius_scale);
    return (1);
}