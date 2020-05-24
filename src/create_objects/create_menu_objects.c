//
// Created by benedikt on 3/6/20.
//

#include "../../include/defender.h"
#include "../../include/my.h"

void create_menu_objects(menu_t *menu)
{
    sfVector2f position = {500, 20};
    sfVector2f position_2 = {330, -220};
    sfVector2f pos_level_1 = {375, 420};
    sfVector2f pos_quit = {1450, 170};
    sfVector2f victory_pos = {630, 50};
    sfVector2f back_pos = {700, 700};
    sfVector2f restart_pos = {1000, 700};
    sfVector2f star_pos = {775, 290};

    menu->logo = sfSprite_create();
    sfSprite_setTexture(menu->logo, sfTexture_createFromFile("resources/menu/logo.png", NULL), sfTrue);
    sfSprite_setPosition(menu->logo, position);
    position.y += 300;
    position.x += 320;
    menu->background = sfSprite_create();
    sfSprite_setTexture(menu->background, sfTexture_createFromFile("resources/menu/bg.png", NULL), sfTrue);
    menu->play.sprite = sfSprite_create();
    sfSprite_setTexture(menu->play.sprite, sfTexture_createFromFile("resources/menu/play.png", NULL), sfTrue);
    sfSprite_setPosition(menu->play.sprite, position);
    position.y += 300;
    position.x -= 20;
    menu->how_to_play.sprite = sfSprite_create();
    sfSprite_setTexture(menu->how_to_play.sprite, sfTexture_createFromFile("resources/menu/tutorial_button.png", NULL), sfTrue);
    sfSprite_setPosition(menu->how_to_play.sprite, position);
    menu->how_to_play.is_hovered = 0;
    position.y += 165;
    menu->level_select_background = sfSprite_create();
    sfSprite_setTexture(menu->level_select_background, sfTexture_createFromFile("resources/menu/level_table.png", NULL), sfTrue);
    sfSprite_setPosition(menu->level_select_background, position_2);
    menu->level_1.sprite = sfSprite_create();
    sfSprite_setTexture(menu->level_1.sprite, sfTexture_createFromFile("resources/menu/level_1_button.png", NULL), sfTrue);
    sfSprite_setPosition(menu->level_1.sprite, pos_level_1);
    menu->level_1.is_hovered = 0;
    menu->play.is_hovered = 0;
    menu->quit.sprite =sfSprite_create();
    sfSprite_setTexture(menu->quit.sprite, sfTexture_createFromFile("resources/menu/button_close.png", NULL), sfTrue);
    sfSprite_setPosition(menu->quit.sprite, pos_quit);
    menu->quit.is_hovered = 0;
    menu->state = 'm';
    menu->victory_screen = sfSprite_create();
    sfSprite_setTexture(menu->victory_screen, sfTexture_createFromFile("resources/menu/victory_screen.png", NULL), sfTrue);
    sfSprite_setPosition(menu->victory_screen, victory_pos);
    menu->back_to_menu.sprite = sfSprite_create();
    sfSprite_setTexture(menu->back_to_menu.sprite, sfTexture_createFromFile("resources/menu/button_menu.png", NULL), sfTrue);
    sfSprite_setPosition(menu->back_to_menu.sprite, back_pos);
    menu->back_to_menu.is_hovered = 0;
    menu->game_over_screen = sfSprite_create();
    sfSprite_setTexture(menu->game_over_screen, sfTexture_createFromFile("resources/menu/game_over_screen.png", NULL), sfTrue);
    sfSprite_setPosition(menu->game_over_screen, victory_pos);
    menu->restart.sprite = sfSprite_create();
    sfSprite_setTexture(menu->restart.sprite, sfTexture_createFromFile("resources/menu/button_restart.png", NULL), sfTrue);
    sfSprite_setPosition(menu->restart.sprite, restart_pos);
    menu->restart.is_hovered = 0;
    menu->quit_main_menu.sprite = sfSprite_create();
    sfSprite_setTexture(menu->quit_main_menu.sprite, sfTexture_createFromFile("resources/menu/quit_game_button.png", NULL), sfTrue);
    sfSprite_setPosition(menu->quit_main_menu.sprite, position);
    menu->quit_main_menu.is_hovered = 0;
    menu->star_texture = sfTexture_createFromFile("resources/menu/stars.png",NULL);
    menu->level_1_stars.sprite = sfSprite_create();
    menu->level_1_stars.count = 0;
    sfSprite_setTexture(menu->level_1_stars.sprite, menu->star_texture, sfTrue);
    menu->level_1_stars.rects = get_rect_arr(1, 4, 432, 238);
    sfSprite_setTextureRect(menu->level_1_stars.sprite, menu->level_1_stars.rects[0]);
    sfSprite_setPosition(menu->level_1_stars.sprite, star_pos);
    menu->menu_star.sprite = sfSprite_copy(menu->level_1_stars.sprite);
    sfVector2f scale = {0.25, 0.25};
    sfSprite_setScale(menu->menu_star.sprite, scale);
    pos_level_1.y += 80;
    pos_level_1.x += 34;
    sfSprite_setPosition(menu->menu_star.sprite, pos_level_1);
    menu->tutorial_sprite = sfSprite_create();
    sfSprite_setTexture(menu->tutorial_sprite, sfTexture_createFromFile("resources/menu/tutorial.png", NULL), sfTrue);
}

void create_setting_objects(settings_t *settings, game_interface_t *interface)
{
    sfVector2f position = {330, -220};
    sfVector2f setting_button_pos = {1830, 100};
    sfVector2f pos_close = {1450, 170};
    sfVector2f pos_restart = {375, 450};
    sfVector2f pos_back_to_menu = {765, 450};
    sfVector2f pos_quit = {1155, 450};
    sfVector2f pos_music = {1300, 720};
    sfVector2f pos_sound = {400, 720};

    settings->bg_sprite = sfSprite_create();
    sfSprite_setTexture(settings->bg_sprite, sfTexture_createFromFile("resources/menu/setting_table.png", NULL), sfTrue);
    sfSprite_setPosition(settings->bg_sprite, position);
    settings->close.sprite = sfSprite_create();
    sfSprite_setTexture(settings->close.sprite, sfTexture_createFromFile("resources/menu/button_close.png", NULL), sfTrue);
    sfSprite_setPosition(settings->close.sprite, pos_close);
    settings->close.is_hovered = 0;
    settings->restart.sprite = sfSprite_create();
    sfSprite_setTexture(settings->restart.sprite, sfTexture_createFromFile("resources/menu/restart_button.png", NULL), sfTrue);
    sfSprite_setPosition(settings->restart.sprite, pos_restart);
    settings->restart.is_hovered = 0;
    settings->back_to_menu.sprite = sfSprite_create();
    sfSprite_setTexture(settings->back_to_menu.sprite, sfTexture_createFromFile("resources/menu/quit_level_button.png", NULL), sfTrue);
    sfSprite_setPosition(settings->back_to_menu.sprite, pos_back_to_menu);
    settings->back_to_menu.is_hovered = 0;
    settings->quit.sprite = sfSprite_create();
    sfSprite_setTexture(settings->quit.sprite, sfTexture_createFromFile("resources/menu/quit_game_button.png", NULL), sfTrue);
    sfSprite_setPosition(settings->quit.sprite, pos_quit);
    settings->quit.is_hovered = 0;
    interface->settings_button.sprite = sfSprite_create();
    sfSprite_setTexture(interface->settings_button.sprite, sfTexture_createFromFile("resources/menu/button_settings.png", NULL), sfTrue);
    sfSprite_setPosition(interface->settings_button.sprite, setting_button_pos);
    interface->settings_button.is_hovered = 0;
    settings->is_active = 0;
    settings->music.sprite = sfSprite_create();
    sfSprite_setTexture(settings->music.sprite, sfTexture_createFromFile("resources/menu/button_music.png", NULL), sfTrue);
    settings->music.rects = get_rect_arr(1, 2, 175, 175);
    sfSprite_setTextureRect(settings->music.sprite, settings->music.rects[0]);
    sfSprite_setPosition(settings->music.sprite, pos_music);
    settings->sounds.sprite = sfSprite_create();
    sfSprite_setTexture(settings->sounds.sprite, sfTexture_createFromFile("resources/menu/button_sound.png", NULL), sfTrue);
    settings->sounds.is_hovered = 0;
    settings->sounds.rects = settings->music.rects;
    sfSprite_setTextureRect(settings->sounds.sprite, settings->sounds.rects[0]);
    sfSprite_setPosition(settings->sounds.sprite, pos_sound);
}