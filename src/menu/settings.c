//
// Created by benedikt on 3/6/20.
//

#include "../../include/defender.h"

void handle_setting_button(game_interface_t *interface, sfRenderWindow *window, interaction_t interaction, sfMusic *click)
{
    sfVector2f up = {1.1, 1.1};
    sfVector2f def = {1.0, 1.0};

    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), \
sfSprite_getPosition(interface->settings_button.sprite), 80, 80)) {
    if (interface->settings_button.is_hovered == 0) {
        interface->settings_button.is_hovered = 1;
        sfSprite_setScale(interface->settings_button.sprite, up);
    }
    if (sfMouse_isButtonPressed(sfMouseLeft) && interaction.mouse1_is_held == 0) {
        sfMusic_stop(click);
        sfMusic_play(click);
        interface->settings.is_active = 1;
    }
    } else if (interface->settings_button.is_hovered == 1) {
        interface->settings_button.is_hovered = 0;
        sfSprite_setScale(interface->settings_button.sprite, def);
    }
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        interface->settings.is_active = 1;
}

void handle_setting_menu(settings_t *settings, sfRenderWindow *window, objects_t *objects)
{
    if (check_button_interaction(&settings->close, window, 110, 110) == 1 && objects->interaction.mouse1_is_held == 0) {
        sfMusic_stop(objects->click);
        sfMusic_play(objects->click);
        settings->is_active = 0;
    }
    if (check_button_interaction(&settings->restart, window, 220, 334) == 1 && objects->interaction.mouse1_is_held == 0) {
        sfMusic_stop(objects->click);
        sfMusic_play(objects->click);
        sfMusic_stop(objects->main_theme);
        sfMusic_play(objects->main_theme);
        objects->game_state = 'i';
        cleanup_map(objects);
        get_default_game_stats(objects);
        generate_map(objects, get_map(objects->map.cur_level, objects));
        get_waves_array(objects, objects->map.cur_waves);
        objects->game_interface.money_count = 500;
        display_money_count(&objects->game_interface);
    }
    if (check_button_interaction(&settings->back_to_menu, window, 220, 334) == 1 && objects->interaction.mouse1_is_held == 0) {
        sfMusic_stop(objects->click);
        sfMusic_play(objects->click);
        sfMusic_stop(objects->main_theme);
        objects->game_state = 'm';
        objects->menu.state = 'l';
        cleanup_map(objects);
        get_default_game_stats(objects);
    }
    if (check_button_interaction(&settings->music, window, 175, 175) && objects->interaction.mouse1_is_held == 0) {
        sfMusic_stop(objects->click);
        sfMusic_play(objects->click);
        if (objects->is_music_mute == 0) {
            objects->is_music_mute = 1;
            sfMusic_pause(objects->main_theme);
        }
        else {
            objects->is_music_mute = 0;
            sfMusic_play(objects->main_theme);
        }
        sfSprite_setTextureRect(settings->music.sprite, settings->music.rects[objects->is_music_mute]);
    }
    if (check_button_interaction(&settings->sounds, window, 175, 175) && objects->interaction.mouse1_is_held == 0) {
        sfMusic_stop(objects->click);
        sfMusic_play(objects->click);
        if (objects->is_sound_mute == 0) {
            sfMusic_setVolume(objects->click, 0);
            sfMusic_setVolume(objects->rock, 0);
            objects->is_sound_mute = 1;
        }
        else {
            objects->is_sound_mute = 0;
            sfMusic_setVolume(objects->click, 100);
            sfMusic_setVolume(objects->rock, 100);
        }
        sfSprite_setTextureRect(settings->sounds.sprite, settings->sounds.rects[objects->is_sound_mute]);
    }
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        settings->is_active = 0;
    if (check_button_interaction(&settings->quit, window, 220, 334) == 1 && objects->interaction.mouse1_is_held == 0)
        sfRenderWindow_close(window);
}