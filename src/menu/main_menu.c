/*
** EPITECH PROJECT, 2020
** main_menu
** File description:
** menu
*/

#include "../../include/defender.h"

void handle_menu(objects_t *objects, sfRenderWindow **window)
{
    sfEvent event;

    sfRenderWindow_drawSprite(*window, objects->menu.background, NULL);
    switch (objects->menu.state) {
    case 'm':
        sfRenderWindow_drawSprite(*window, objects->menu.logo, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.how_to_play.sprite, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.quit_main_menu.sprite, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.play.sprite, NULL);
        break;
    case 'l':
        sfRenderWindow_drawSprite(*window, objects->menu.level_select_background, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.quit.sprite, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.level_1.sprite, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.menu_star.sprite, NULL);
        break;
    case 'f':
        sfRenderWindow_drawSprite(*window, objects->menu.game_over_screen, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.back_to_menu.sprite, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.restart.sprite, NULL);
        break;
    case 't':
        sfRenderWindow_drawSprite(*window, objects->menu.tutorial_sprite, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.quit.sprite, NULL);
        break;
    default:
        sfRenderWindow_drawSprite(*window, objects->menu.victory_screen, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.level_1_stars.sprite, NULL);
        sfRenderWindow_drawSprite(*window, objects->menu.back_to_menu.sprite, NULL);
        break;
    }
    while (sfRenderWindow_pollEvent(*window, &event)) {
        if (objects->menu.state == 'm')
        handle_main_menu_events(objects, *window, &event);
        else if (objects->menu.state == 'l')
            handle_level_select(objects, *window, &event);
        else if (objects->menu.state == 'f')
            game_over_screen_events(objects, *window, &event);
        else if (objects->menu.state == 't') {
            if (check_button_interaction(&objects->menu.quit, *window, 100, 100)) {
                sfMusic_stop(objects->click);
                sfMusic_play(objects->click);
                objects->menu.state = 'm';
            }
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(*window);
        }
        else
            victory_screen_events(objects, *window, &event);
        if (!(sfMouse_isButtonPressed(sfMouseLeft)))
            objects->interaction.mouse1_is_held = 0;
        else
            objects->interaction.mouse1_is_held = 1;
    }
}

void handle_main_menu_events(objects_t *objects, sfRenderWindow *window, sfEvent *event)
{
    sfVector2f up = {1.1,1.1};
    sfVector2f def = {1.0, 1.0};
    sfVector2f pos_close = {1450, 170};
    sfVector2f pos_quit_2 = {1810, 90};

    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), sfSprite_getPosition(objects->menu.play.sprite), 330, 330) && !objects->interaction.mouse1_is_held) {
        if (objects->menu.play.is_hovered == 0) {
            sfSprite_setScale(objects->menu.play.sprite, up);
            objects->menu.play.is_hovered = 1;
        }
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            sfMusic_stop(objects->click);
            sfMusic_play(objects->click);
            sfSprite_setPosition(objects->menu.quit.sprite, pos_close);
            objects->menu.state = 'l';
        }
    } else if (objects->menu.play.is_hovered == 1) {
        sfSprite_setScale(objects->menu.play.sprite, def);
        objects->menu.play.is_hovered = 0;
    }
    if (check_button_interaction(&objects->menu.how_to_play, window, 175, 326)) {
        sfMusic_stop(objects->click);
        sfMusic_play(objects->click);
        objects->menu.state = 't';
        sfSprite_setPosition(objects->menu.quit.sprite, pos_quit_2);
    }
    if (event->type == sfEvtClosed || check_button_interaction(&objects->menu.quit_main_menu, window, 220, 334))
        sfRenderWindow_close(window);
}

void handle_level_select(objects_t *objects, sfRenderWindow *window, sfEvent *event)
{
    sfVector2f up = {1.1,1.1};
    sfVector2f def = {1.0, 1.0};

    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), sfSprite_getPosition(objects->menu.level_1.sprite), 175, 175) && !objects->interaction.mouse1_is_held) {
        if (objects->menu.level_1.is_hovered == 0) {
            sfSprite_setScale(objects->menu.level_1.sprite, up);
            objects->menu.level_1.is_hovered = 1;
        }
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            sfMusic_stop(objects->click);
            sfMusic_play(objects->click);
            objects->game_state = 'i';
            if (objects->is_music_mute == 0)
                sfMusic_play(objects->main_theme);
            generate_map(objects, get_map("bonus/maps/map_1", objects));
            get_waves_array(objects, "bonus/waves/map_1_waves");
            objects->game_interface.money_count = 500;
            display_money_count(&objects->game_interface);
        }
    } else if (objects->menu.level_1.is_hovered == 1) {
        sfSprite_setScale(objects->menu.level_1.sprite, def);
        objects->menu.level_1.is_hovered = 0;
    }
    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), sfSprite_getPosition(objects->menu.quit.sprite), 110, 110) && !objects->interaction.mouse1_is_held) {
        if (objects->menu.quit.is_hovered == 0) {
            sfSprite_setScale(objects->menu.quit.sprite, up);
            objects->menu.quit.is_hovered = 1;
        }
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            sfMusic_stop(objects->click);
            sfMusic_play(objects->click);
            objects->menu.state = 'm';
        }
    } else if (objects->menu.play.is_hovered == 1) {
        sfSprite_setScale(objects->menu.quit.sprite, def);
        objects->menu.quit.is_hovered = 0;
    } else
        victory_screen_events(objects, window, event);
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window);
}

void victory_screen_events(objects_t *objects, sfRenderWindow *window, sfEvent *event)
{
    sfVector2f up = {1.1,1.1};
    sfVector2f def = {1.0, 1.0};

    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), sfSprite_getPosition(objects->menu.back_to_menu.sprite), 175, 175) && !objects->interaction.mouse1_is_held) {
        if (objects->menu.back_to_menu.is_hovered == 0) {
            sfSprite_setScale(objects->menu.back_to_menu.sprite, up);
            objects->menu.back_to_menu.is_hovered = 1;
        }
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            sfMusic_stop(objects->click);
            sfMusic_play(objects->click);
            objects->menu.state = 'l';
        }
    } else if (objects->menu.back_to_menu.is_hovered == 1) {
        sfSprite_setScale(objects->menu.back_to_menu.sprite, def);
        objects->menu.back_to_menu.is_hovered = 0;
    }
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window);
}

void game_over_screen_events(objects_t *objects, sfRenderWindow *window, sfEvent *event)
{
    if (check_button_interaction(&objects->menu.back_to_menu, window, 175, 175) == 1)
        objects->menu.state = 'm';
    if (check_button_interaction(&objects->menu.restart, window, 175, 175) == 1) {
        objects->game_state = 'i';
        generate_map(objects, get_map(objects->map.cur_level, objects));
        get_waves_array(objects, objects->map.cur_waves);
        objects->game_interface.money_count = 500;
        display_money_count(&objects->game_interface);
    }
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window);
}