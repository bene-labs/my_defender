/*
** EPITECH PROJECT, 2020
** create_objects->c
** File description:
** temp
*/

#include "../../include/defender.h"
#include "../../include/my.h"

int create_objects(objects_t *objects)
{
    objects->enemies.spawn_delay = 500000;
    objects->game_interface.money_count = 500;
    objects->game_state = 'm';
    objects->interaction.mouse1_is_held = 0;
    objects->is_sound_mute = 0;
    objects->is_music_mute = 0;
    objects->click = sfMusic_createFromFile("resources/sounds/sound_click.ogg");
    objects->rock = sfMusic_createFromFile("resources/sounds/sound_rock.ogg");
    objects->main_theme = sfMusic_createFromFile("resources/sounds/main_theme.ogg");
    sfMusic_setLoop(objects->main_theme, sfTrue);
    create_game_interface_objects(objects);
    if (create_initial_objects_enemies(objects) == 84)
        return (84);
    create_upgrade_ui_sprites(objects);
    create_tower_sprites(objects);
    get_default_game_stats(objects);
    create_setting_objects(&objects->game_interface.settings, &objects->game_interface);
    create_menu_objects(&objects->menu);
    create_map_sprites(objects);
    if (create_initial_allies(&objects->map.building_plots) == 84)
        return (84);
    return (0);
}

int create_initial_objects_enemies(objects_t *objects)
{
    sfVector2f position = {800, 10};
    objects->enemies.wave_text = sfText_copy(objects->game_interface.money_count_text);
    sfText_setCharacterSize(objects->enemies.wave_text, 50);
    sfText_setColor(objects->enemies.wave_text, sfBlack);
    sfText_setPosition(objects->enemies.wave_text, position);
    objects->enemies.wave_text_str = malloc(sizeof(char) * 11 + 1);
    objects->enemies.spawn_timer = sfClock_create();
    objects->enemies.enemy_list = create_enemy_list();
    objects->game_interface.health_bar_template.background_texture = sfTexture_createFromFile("resources/enemies/health_bar_background.png", NULL);
    objects->game_interface.health_bar_template.foreground_texture = sfTexture_createFromFile("resources/enemies/health_bar_foreground.png", NULL);
    objects->game_interface.ally_health_bar_foreground = sfTexture_createFromFile("resources/towers/tavern/allies/ally_health_bar_foreground.png", NULL);
    char paths[10][6][51] = {{"resources/enemies/zombie/walk_mirrored.png", "resources/enemies/zombie/walk.png", "resources/enemies/zombie/die.png", "resources/enemies/zombie/die_mirrored.png", "resources/enemies/zombie/attack.png", "resources/enemies/zombie/attack_mirrored.png"}, \
{"resources/enemies/goblin/walk_mirrored.png", "resources/enemies/goblin/walk.png", "resources/enemies/goblin/die.png", "resources/enemies/goblin/die_mirrored.png", "resources/enemies/goblin/attack.png", "resources/enemies/goblin/attack_mirrored.png"}, \
{"resources/enemies/goblin_mage/walk_mirrored.png", "resources/enemies/goblin_mage/walk.png", "resources/enemies/goblin_mage/die.png", "resources/enemies/goblin_mage/die_mirrored.png", "resources/enemies/goblin_mage/attack.png", "resources/enemies/goblin_mage/attack_mirrored.png"}, \
{"resources/enemies/ogre/walk_mirrored.png", "resources/enemies/ogre/walk.png", "resources/enemies/ogre/die.png", "resources/enemies/ogre/die_mirrored.png", "resources/enemies/ogre/attack.png", "resources/enemies/ogre/attack_mirrored.png"}, \
{"resources/enemies/hollow/walk_mirrored.png", "resources/enemies/hollow/walk.png", "resources/enemies/hollow/die.png", "resources/enemies/hollow/die_mirrored.png", "resources/enemies/hollow/attack.png", "resources/enemies/hollow/attack_mirrored.png"}, \
{"resources/enemies/armored_goon/walk_mirrored.png", "resources/enemies/armored_goon/walk.png", "resources/enemies/armored_goon/die.png", "resources/enemies/armored_goon/die_mirrored.png", "resources/enemies/armored_goon/attack.png", "resources/enemies/armored_goon/attack_mirrored.png"}, \
{"resources/enemies/lizard/walk_mirrored.png", "resources/enemies/lizard/walk.png", "resources/enemies/lizard/die.png", "resources/enemies/lizard/die_mirrored.png", "resources/enemies/lizard/attack.png", "resources/enemies/lizard/attack_mirrored.png"}, \
{"resources/enemies/ghost/walk_mirrored.png", "resources/enemies/ghost/walk.png", "resources/enemies/ghost/die.png", "resources/enemies/ghost/die_mirrored.png", "resources/enemies/ghost/attack.png", "resources/enemies/ghost/attack_mirrored.png"}, \
{"resources/enemies/troll/walk_mirrored.png", "resources/enemies/troll/walk.png", "resources/enemies/troll/die.png", "resources/enemies/troll/die_mirrored.png", "resources/enemies/troll/attack.png", "resources/enemies/troll/attack_mirrored.png"}, \
{"resources/enemies/scorpion/walk_mirrored.png", "resources/enemies/scorpion/walk.png", "resources/enemies/scorpion/die.png", "resources/enemies/scorpion/die_mirrored.png", "resources/enemies/scorpion/attack.png", "resources/enemies/scorpion/attack_mirrored.png"}};
    objects->enemies.textures = malloc(sizeof(sfTexture **) * 10);
    for (int i = 0; i < 10; i++) {
        objects->enemies.textures[i] = malloc(sizeof(sfTexture *) * 6);
        for (int j = 0; j < 6; j++) {
            if (!(objects->enemies.textures[i][j] = sfTexture_createFromFile(paths[i][j], NULL))) {
                my_printf("Error: Csfml failed to create an Enemy texture.\n");
                return(84);
            }
        }
    }
    ally_stats_t ally_stats[3] = {{15, 100.0, 100.0, 1.0, {0, 0}}, \
{23, 165, 165, 1.3, {0, -10}}, \
{40, 250, 250, 1.4, {0, -5}}};

    for (int i = 0; i < 3; objects->map.building_plots.ally_stats[i] = ally_stats[i], i++);
    objects->map.building_plots.ally_rects = malloc(sizeof(sfIntRect *) * 3);
    objects->map.building_plots.ally_rects[0] = get_rect_arr(4, 5, 84, 70);
    objects->map.building_plots.ally_rects[1] = get_rect_arr(4, 5, 73, 78);
    objects->map.building_plots.ally_rects[2] = get_rect_arr(4, 5, 79, 84);
    objects->map.building_plots.ally_rects_mirrored = malloc(sizeof(sfIntRect *) * 3);
    objects->map.building_plots.ally_rects_mirrored[0] = get_rect_arr_mirrored(4, 5, 84, 70);
    objects->map.building_plots.ally_rects_mirrored[1] = get_rect_arr_mirrored(4, 5, 73, 78);
    objects->map.building_plots.ally_rects_mirrored[2] = get_rect_arr_mirrored(4, 5, 79, 84);
    return (0);
}

void create_game_interface_objects(objects_t *objects)
{
    sfVector2f position = {0, 900};
    objects->game_interface.background_sprite = sfSprite_create();
    objects->game_interface.background_texture = sfTexture_createFromFile("resources/towers/table_down.png", NULL);
    sfSprite_setTexture(objects->game_interface.background_sprite, objects->game_interface.background_texture, sfTrue);
    sfSprite_setPosition(objects->game_interface.background_sprite, position);
    objects->game_interface.lives_icon = sfSprite_create();
    objects->game_interface.lives_texture = sfTexture_createFromFile("resources/menu/lives.png", NULL);
    sfSprite_setTexture(objects->game_interface.lives_icon, objects->game_interface.lives_texture, sfTrue);
    objects->game_interface.lives_text = sfText_create();
    sfVector2f position_2 = {1800, 10};
    sfText_setPosition(objects->game_interface.lives_text, position_2);
    position_2.x += 60;
    position_2.y += 18;
    sfSprite_setPosition(objects->game_interface.lives_icon, position_2);
    sfText_setFont(objects->game_interface.lives_text, \
sfFont_createFromFile("resources/menu/Bebas-Regular.otf"));
    sfText_setCharacterSize(objects->game_interface.lives_text, 70);
    sfText_setColor(objects->game_interface.lives_text, sfRed);
    objects->game_interface.lives_str = malloc(sizeof(char*) *2 + 1);
    objects->game_interface.lives_str[0] = '2';
    objects->game_interface.lives_str[1] = '0';
    objects->game_interface.lives_str[2] = '\0';
    sfText_setString(objects->game_interface.lives_text, objects->game_interface.lives_str);
    objects->game_interface.live_count = 20;
    objects->game_interface.tower_stats.icons_sprite = sfSprite_create();
    objects->game_interface.tower_stats.icons_texture = sfTexture_createFromFile("resources/towers/tower_stats_overlay.png", NULL);
    objects->game_interface.tower_stats.tavern_icons = sfTexture_createFromFile("resources/towers/tavern_stats_overlay.png", NULL);
    sfSprite_setTexture(objects->game_interface.tower_stats.icons_sprite, objects->game_interface.tower_stats.icons_texture, sfTrue);
    position.y -= 20;
    sfSprite_setPosition(objects->game_interface.tower_stats.icons_sprite, position);
    objects->game_interface.tower_stats.cur_stats_text = sfText_create();
    objects->game_interface.tower_stats.icon = sfSprite_create();
    position.y -= 25;
    position.x += 20;
    position.x += 340;
    position.y += 95;
    sfText_setPosition(objects->game_interface.tower_stats.cur_stats_text, position);
    sfText_setFont(objects->game_interface.tower_stats.cur_stats_text, sfFont_createFromFile("resources/menu/Bebas-Regular.otf"));
    sfText_setColor(objects->game_interface.tower_stats.cur_stats_text, sfWhite);
    sfText_setCharacterSize(objects->game_interface.tower_stats.cur_stats_text, 60);
    objects->game_interface.tower_stats.cur_stats_str = malloc(sizeof(char) * 66 + 1);
    for (int i = 0; i < 66; i++)
        objects->game_interface.tower_stats.cur_stats_str[i] = ' ';
    objects->game_interface.tower_stats.cur_stats_str[66] = '\0';
    sfText_setString(objects->game_interface.tower_stats.cur_stats_text, objects->game_interface.tower_stats.cur_stats_str);
    objects->game_interface.tower_stats.preview_stats_text = sfText_copy(objects->game_interface.tower_stats.cur_stats_text);
    //sfText_setCharacterSize(objects->game_interface.tower_stats.preview_stats_text, 30);
    sfVector2f move = {0, 10};
    sfText_move(objects->game_interface.tower_stats.preview_stats_text, move);
    sfText_setColor(objects->game_interface.tower_stats.preview_stats_text, sfGreen);
    objects->game_interface.money_count_str = malloc(sizeof(char) * 6 + 1);
    for (int i = 0; i < 5; i++)
        objects->game_interface.money_count_str[i] = ' ';
    objects->game_interface.money_count_str[5] = '0';
    objects->game_interface.money_count_str[6] = '\0';
    objects->game_interface.money_count_text = sfText_copy(objects->game_interface.tower_stats.cur_stats_text);
    objects->game_interface.money_icon = sfSprite_create();
    sfSprite_setTexture(objects->game_interface.money_icon, sfTexture_createFromFile("resources/menu/dollar_sign.png", NULL), sfTrue);
    position_2.x -= 130;
    sfSprite_setPosition(objects->game_interface.money_icon, position_2);
    position_2.x -= 100;
    position_2.y -= 15;
    sfText_setCharacterSize(objects->game_interface.money_count_text, 70);
    sfText_setPosition(objects->game_interface.money_count_text, position_2);
    sfText_setString(objects->game_interface.money_count_text, objects->game_interface.money_count_str);
    objects->game_interface.tower_stats.display_radius = 0;
    //printf("x: %f y:%f\n", sfText_getPosition(objects->game_interface.money_count_text).x, sfText_getPosition(objects->game_interface.money_count_text).y);
}

void create_upgrade_ui_sprites(objects_t *objects)
{
    objects->map.building_plots.build_menu.sprite = sfSprite_create();
    objects->map.building_plots.build_menu.texture = sfTexture_createFromFile("resources/menu/build_menu.png", NULL);
    sfSprite_setTexture(objects->map.building_plots.build_menu.sprite, objects->map.building_plots.build_menu.texture, sfTrue);
    objects->map.building_plots.build_menu.button_1.sprite = sfSprite_create();
    objects->map.building_plots.build_menu.button_1.texture = sfTexture_createFromFile("resources/menu/druid_button.png", NULL);
    objects->map.building_plots.build_menu.button_1.rects = get_rect_arr(2, 2, 32, 32);
    sfSprite_setTexture(objects->map.building_plots.build_menu.button_1.sprite, objects->map.building_plots.build_menu.button_1.texture, sfTrue);
    sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_1.sprite, objects->map.building_plots.build_menu.button_1.rects[0]);
    objects->map.building_plots.build_menu.button_1.is_confirm = 0;
    objects->map.building_plots.build_menu.button_1.is_locked = 0;
    objects->map.building_plots.build_menu.button_1.type = 1;
    objects->map.building_plots.build_menu.button_1.is_hovered = 0;
    objects->map.building_plots.build_menu.button_2.sprite = sfSprite_create();
    objects->map.building_plots.build_menu.button_2.texture =  sfTexture_createFromFile("resources/menu/tavern_button.png", NULL);
    objects->map.building_plots.build_menu.button_2.rects = objects->map.building_plots.build_menu.button_1.rects;
    sfSprite_setTexture(objects->map.building_plots.build_menu.button_2.sprite, objects->map.building_plots.build_menu.button_2.texture, sfTrue);
    sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_2.sprite, objects->map.building_plots.build_menu.button_2.rects[0]);
    objects->map.building_plots.build_menu.button_2.is_hovered = 0;
    objects->map.building_plots.build_menu.button_2.type = 2;
    objects->map.building_plots.build_menu.button_2.is_confirm = 0;
    objects->map.building_plots.build_menu.button_3.sprite = sfSprite_create();
    objects->map.building_plots.build_menu.button_3.texture = sfTexture_createFromFile("resources/menu/mage_button_1.png", NULL);
    objects->map.building_plots.build_menu.button_3.rects = objects->map.building_plots.build_menu.button_2.rects;
    sfSprite_setTexture(objects->map.building_plots.build_menu.button_3.sprite, objects->map.building_plots.build_menu.button_3.texture, sfTrue);
    sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_3.sprite, objects->map.building_plots.build_menu.button_3.rects[0]);
    objects->map.building_plots.build_menu.button_3.is_hovered = 0;
    objects->map.building_plots.build_menu.button_3.is_confirm = 0;
    objects->map.building_plots.build_menu.button_3.is_locked = 0;
    objects->map.building_plots.build_menu.button_3.type = 3;
    objects->map.building_plots.build_menu.button_4.sprite = sfSprite_create();
    objects->map.building_plots.build_menu.button_4.texture = sfTexture_createFromFile("resources/menu/stone_button.png", NULL);
    objects->map.building_plots.build_menu.button_4.rects = objects->map.building_plots.build_menu.button_2.rects;
    objects->map.building_plots.build_menu.button_4.is_hovered = 0;
    objects->map.building_plots.build_menu.button_4.is_confirm = 0;
    objects->map.building_plots.build_menu.button_4.type = 4;
    sfSprite_setTexture(objects->map.building_plots.build_menu.button_4.sprite, objects->map.building_plots.build_menu.button_4.texture, sfTrue);
    sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_4.sprite, objects->map.building_plots.build_menu.button_4.rects[0]);
    objects->map.building_plots.build_menu.quit.sprite = sfSprite_create();
    objects->map.building_plots.build_menu.quit.texture = sfTexture_createFromFile("resources/menu/close.png", NULL);
    sfSprite_setTexture(objects->map.building_plots.build_menu.quit.sprite, objects->map.building_plots.build_menu.quit.texture, sfTrue);
    objects->map.building_plots.build_menu.quit.is_hovered = 0;
    objects->map.building_plots.build_menu.is_active = 0;
    objects->map.building_plots.upgrade.sprite = sfSprite_create();
    objects->map.building_plots.upgrade.texture = sfTexture_createFromFile("resources/menu/upgrade_menu.png", NULL);
    sfSprite_setTexture(objects->map.building_plots.upgrade.sprite, objects->map.building_plots.upgrade.texture, sfTrue);
    objects->map.building_plots.upgrade.is_active = 0;
    objects->map.building_plots.upgrade.quit.sprite = sfSprite_create();
    sfSprite_setTexture(objects->map.building_plots.upgrade.quit.sprite,  objects->map.building_plots.build_menu.quit.texture, sfTrue);
    objects->map.building_plots.upgrade.quit.is_hovered = 0;
    objects->map.building_plots.upgrade.button_1.texture = sfTexture_createFromFile("resources/menu/upgrade_button.png", NULL);
    objects->map.building_plots.upgrade.button_1.sprite = sfSprite_create();
    sfSprite_setTexture(objects->map.building_plots.upgrade.button_1.sprite, objects->map.building_plots.upgrade.button_1.texture, sfTrue);
    objects->map.building_plots.upgrade.button_1.rects =  get_rect_arr(2, 2, 32, 32);
    objects->map.building_plots.upgrade.button_1.is_locked = 0;
    sfSprite_setTextureRect(objects->map.building_plots.upgrade.button_1.sprite,  objects->map.building_plots.upgrade.button_1.rects[0]);
    objects->map.building_plots.upgrade.button_1.is_hovered = 0;
    objects->map.building_plots.upgrade.button_1.is_confirm = 0;
    objects->map.building_plots.upgrade.button_1.number_text = sfText_copy(objects->game_interface.money_count_text);
    sfText_setCharacterSize(objects->map.building_plots.upgrade.button_1.number_text, 20);
    sfText_setColor(objects->map.building_plots.upgrade.button_1.number_text, sfYellow);
    objects->map.building_plots.upgrade.button_1.number_str = malloc(sizeof(char) * 6 + 1);
    objects->map.building_plots.upgrade.button_1.number_str[5] = '0';
    objects->map.building_plots.upgrade.button_1.number_str[6] = '\0';
    objects->map.building_plots.upgrade.sell.sprite = sfSprite_create();
    objects->map.building_plots.upgrade.button_2.texture = sfTexture_createFromFile("resources/menu/position_button.png", NULL);
    objects->map.building_plots.upgrade.button_2.sprite = sfSprite_create();
    sfSprite_setTexture(objects->map.building_plots.upgrade.button_2.sprite, objects->map.building_plots.upgrade.button_2.texture, sfTrue);
    objects->map.building_plots.upgrade.button_2.rects = objects->map.building_plots.upgrade.button_1.rects;
    sfSprite_setTextureRect(objects->map.building_plots.upgrade.button_2.sprite, objects->map.building_plots.upgrade.button_2.rects[2]);
    objects->map.building_plots.upgrade.button_2.is_confirm = 0;
    objects->map.building_plots.upgrade.button_2.is_locked = 1;
    objects->map.building_plots.upgrade.button_2.is_hovered = 0;
    objects->map.building_plots.upgrade.button_2.def_color = sfSprite_getColor(objects->map.building_plots.upgrade.button_2.sprite);
    sfSprite_setTexture(objects->map.building_plots.upgrade.sell.sprite, sfTexture_createFromFile("resources/menu/remove.png", NULL), sfTrue);
    objects->map.building_plots.upgrade.sell.is_hovered = 0;
    objects->map.building_plots.upgrade.sell.is_confirm = 0;
    objects->map.building_plots.upgrade.sell.rects = get_rect_arr(1, 2, 32, 32);
    sfSprite_setTextureRect(objects->map.building_plots.upgrade.sell.sprite, objects->map.building_plots.upgrade.sell.rects[0]);
    objects->map.building_plots.upgrade.sell.number_text = sfText_copy(objects->map.building_plots.upgrade.button_1.number_text);
    //sfColor color = {75, 179, 43, 200};
    sfText_setColor(objects->map.building_plots.upgrade.sell.number_text, sfGreen);
    objects->map.building_plots.upgrade.sell.number_str = malloc(sizeof(char) * 6 + 1);
    objects->map.building_plots.upgrade.sell.number_str[5] = '0';
    objects->map.building_plots.upgrade.sell.number_str[6] = '\0';
    objects->map.building_plots.upgrade.radius_preview_sprite = sfSprite_create();
    sfSprite_setTexture(objects->map.building_plots.upgrade.radius_preview_sprite, sfTexture_createFromFile("resources/towers/radius.png", NULL), sfTrue);
}

void create_map_sprites(objects_t *objects)
{
    objects->map.texture = sfTexture_createFromFile(\
"resources/tiles/main_bg.png", NULL);
    objects->map.background = sfSprite_create();
    sfSprite_setTexture(objects->map.background, objects->map.texture, sfTrue);
    objects->map.rect = get_rect_arr(4, 4, 100, 100);
    objects->map.tile_texture = sfTexture_createFromFile(\
"resources/tiles/roads_sheet_1.png", NULL);
    objects->map.small_deco.texture = sfTexture_createFromFile(\
"resources/tiles/simple_decorations_1.png", NULL);
    objects->map.small_deco.rect = get_rect_arr(5, 5, 100, 100);
    objects->map.big_deco.texture = sfTexture_createFromFile("resources/tiles/big_decorations.png", NULL);
    objects->map.big_deco.rect = get_rect_arr(4, 2, 100, 100);
    objects->map.spawn.texture = sfTexture_createFromFile("resources/tiles/spawns.png", NULL);
    objects->map.spawn.rect = get_rect_arr(2, 2, 100, 100);
    objects->map.goal.texture = sfTexture_createFromFile("resources/tiles/goals.png", NULL);
    objects->map.goal.rect = get_rect_arr(2, 2, 100, 100);
    objects->map.building_plots.texture = sfTexture_createFromFile("resources/tiles/spot.png", NULL);
}

sfIntRect *get_rect_arr(int columns, int rows, int width, int height)
{
    sfIntRect *rect = malloc(sizeof(sfIntRect) * columns * rows);
    int d = 0;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++, d++) {
            rect[d].height = height;
            rect[d].width = width;
            rect[d].top = y * height;
            rect[d].left = x * width;
        }
    }
    return (rect);
}

sfIntRect *get_rect_arr_mirrored(int columns, int rows, int width, int height)
{
    sfIntRect *rect = malloc(sizeof(sfIntRect) * columns * rows);
    int d = 0;

    for (int y = 0; y < rows; y++) {
        for (int x = columns - 1; x >= 0; x--, d++) {
            rect[d].height = height;
            rect[d].width = width;
            rect[d].top = y * height;
            rect[d].left = x * width;
        }
    }
    return (rect);
}