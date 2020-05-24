//
// Created by benedikt on 2/13/20.
//

#ifndef UNTITLED_DEFENDER_H
#define UNTITLED_DEFENDER_H

#define SELECTED_TOWER_U (objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower)
#define SELECTED_TOWER_B (objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tower)

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Config.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "defender_structs.h"

void handle_game_loop(objects_t *, sfRenderWindow *);
void handle_events(sfRenderWindow *, objects_t *, sfEvent);
void draw_ingame_objects(sfRenderWindow *, objects_t *);
int create_objects(objects_t *);
void create_map_sprites(objects_t *);
void create_game_interface_objects(objects_t *objects);
void create_upgrade_ui_sprites(objects_t *);
int create_initial_objects_enemies(objects_t *);
int generate_map(objects_t *, char **);
void create_tower_sprites (objects_t *objects);
sfIntRect *get_rect_arr(int columns, int rows, int width, int height);
sfIntRect *get_rect_arr_mirrored(int, int, int, int);
char **get_map(char *, objects_t *objects);
int test_map(objects_t *, char *, char **);
int get_tile_count(char **, objects_t *, char, char);
void determine_enemy(objects_t *objects, int type);
void create_enemy(objects_t *objects, int type, enemy_stats_t stats, sfIntRect *rects, sfIntRect *mirrored);
void move_enemy(enemy_t *, objects_t *);
int animate_enemy(enemy_t *, objects_t *, animation_t *);
int cleanup(objects_t *, int);
int get_random_int_within_range(int, int);
void handle_building_spots(objects_t *, spots_t, int);
void handle_building_menu(sfRenderWindow *, objects_t *);
void create_new_tower(objects_t *objects, tower_t);
void handle_tower_interaction(objects_t *objects, spots_t spot, int nb);
void handle_upgrade_menu(sfRenderWindow *window, objects_t *objects);
void handle_menu_quit_button(sfRenderWindow *,objects_t *, upgrade_menu_t *);
int is_collision_cursor_button(sfVector2i, sfVector2f, int, int);
void handle_upgrade_button(objects_t*, tower_t *, upgrade_menu_t, game_interface_t *);
int display_radius(tower_t, spots_t spot, sfSprite *sprite, int);
int is_enemy_inside_radius(enemy_t enemy, double radius, int, int);
void handle_tower_attack(spots_t spot, tower_t *tower, enemy_t *enemy);
void animate_projectile_impact(projectile_t *projectile, animation_t *animation, enemy_list_t *enemy_list, objects_t *objects);
void refresh_enemy_health_bar(enemy_t *, objects_t *objects, double cur_hp, double max_hp);
enemy_list_t *create_enemy_list(void);
void append_to_list(enemy_list_t *, enemy_t *);
void remove_enemy_from_list(enemy_list_t *, enemy_t *);
void add_points(char *score, int i);
void remove_points(char *score, int i, sfText *text);
int is_enemy_past_goal(enemy_t *enemy, objects_t *objects);
void display_tower_stats(tower_t tower, stat_display_t *display, building_plots_t, sfTexture *texture);
tower_t create_fire_mage(objects_t *objects);
void display_tower_stats_preview(tower_t tower, stat_display_t *display, building_plots_t building_plots, sfTexture *texture);
void display_money_count(game_interface_t *);
void display_button_cost(button_t *button, tower_t *tower);
void randomly_move_left_or_right(enemy_t *enemy, objects_t *objects);
void randomly_move_up_or_down(enemy_t *enemy);
void handle_tower_remove_button(objects_t *objects, button_t *remove, sfRenderWindow *window);
void remove_tower(spots_t *spot, game_interface_t *interface, tower_t *tower, building_plots_t * plots);
void display_sell_button_value(button_t *button, tower_t *tower);
tower_t create_basic_stone_tower(spots_t, objects_t *objects);
void handle_buy_button(button_t *button, sfRenderWindow *window, tower_t *tower, objects_t *objects);
void animate_catapult_startup(tower_t *tower, spots_t spot, enemy_list_t *enemy_list);
void animate_stone_flight(tower_t *tower, enemy_list_t *enemy_list);
int search_for_seed(void);
int set_seed_if_file_is_valid(FILE *file);
void determine_enemy_start(enemy_t *enemy, objects_t *objects);
char *concat_strings(char *str1, char *str2);
void get_waves_array(objects_t *objects, char *argv2);
void my_strcpy(char *dest, char const *str);
int is_new_wave_start(objects_t *objects, enemies_t *enemies, enemy_list_t *list);
void handle_gameplay(objects_t *objects, sfRenderWindow **window);
void create_menu_objects(menu_t *menu);
void handle_menu(objects_t *objects, sfRenderWindow **window);
void handle_main_menu_events(objects_t *objects, sfRenderWindow *window, sfEvent *event);
void handle_level_select(objects_t *objects, sfRenderWindow *window, sfEvent *event);
void victory_screen_events(objects_t *objects, sfRenderWindow *window, sfEvent *event);
void cleanup_map(objects_t *objects);
void get_default_game_stats(objects_t *objects);
void create_setting_objects(settings_t *settings, game_interface_t *interface);
void handle_setting_button(game_interface_t *interface, sfRenderWindow *window, interaction_t interaction, sfMusic *click);
void handle_setting_menu(settings_t *settings, sfRenderWindow *window, objects_t *objects);
int check_button_interaction(button_t *button, sfRenderWindow *window, int height, int width);
void game_over_screen_events(objects_t *objects, sfRenderWindow *window, sfEvent *event);
tower_t create_tavern(building_plots_t *plot);
int create_initial_allies(building_plots_t *plots);
void create_tavern_allies(objects_t *objects, tower_t *tavern);
void set_all_buttons_to_default(objects_t *objects);
void create_ally(tower_t *tavern, objects_t *objects, building_plots_t *plot, sfVector2f tile_pos);
void create_ally_if_possible(building_plots_t *plot, tower_t *tavern, sfVector2i mouse_pos, objects_t *objects);
void handle_tower_abilities(tower_t *tower, objects_t *objects);
void check_if_enemy_can_attack(enemy_list_t *enemy_list, enemy_list_t *ally_list, objects_t *objects);
int is_mouse_inside_radius(sfVector2i mouse_pos, double radius, sfVector2f position);
tower_t create_druid_tower(objects_t *objects);
sfVector2f get_positon_of_clicked_tile_if_possible(sfVector2i mouse_pos, objects_t *objects);
void animate_rain_cloud(projectile_t *projectile, animation_t *animation, enemy_list_t *enemy_list, tower_t *tower);
void handle_poisoned_enemy(enemy_t *enemy, objects_t *objects);
#endif //UNTITLED_DEFENDER_H