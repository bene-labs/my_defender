//
// Created by benedikt on 3/10/20.
//

#ifndef UNTITLED_DEFENDER_STRUCTS_H
#define UNTITLED_DEFENDER_STRUCTS_H

typedef struct text
{
    sfText *text;
    sfFont *font;
    sfColor *color;
    char *str;
    int size;
    sfVector2f position;
} text_t;

typedef struct sprite {
    sfSprite *sprite;
    sfVector2f position;
    int type;
} sprite_t;

typedef struct ally_stats
{
    int damage;
    double cur_hp;
    double max_hp;
    double attack_speed;
    sfVector2f gap;
} ally_stats_t;

typedef struct animation {
    sfIntRect *rect;
    sfIntRect *mirrored_rect;
    sfClock *clock;
    int delay;
    int frame;
    int max_frame;
    int is_mirrored;
    int type;
} animation_t;

typedef struct health_bar {
    sfVector2f position;
    sfSprite *background_sprite;
    sfTexture *background_texture;
    sfSprite *foreground_sprite;
    sfTexture *foreground_texture;
    sfIntRect foreground_rect;
    double percentage;
} health_bar_t;

typedef struct enemy_stats {
    int damage;
    int move_delay;
    double cur_hp;
    double max_hp;
    int value;
    double shield;
    double magic_shield;
    int threat;
} enemy_stats_t;

typedef struct enemy {
    sfSprite *sprite;
    sfColor def_color;
    animation_t walk;
    animation_t death;
    sfVector2f position;
    sfVector2f move;
    int posion_damage;
    int is_alive;
    int is_poisoned;
    int poison_limit;
    int poison_count;
    sfClock *poisoned_duration_clock;
    sfClock *poison_tick_clock;
    sfClock *clock;
    health_bar_t health_bar;
    enemy_stats_t stats;
    int is_targeted;
    int type;
    struct enemy *target;
    int is_ally;
    ally_stats_t ally_stats;
} enemy_t;

typedef struct enemy_list {
    struct enemy_list *next;
    enemy_t *enemy;
    int type;
} enemy_list_t;

typedef struct enemies {
    enemy_list_t *enemy_list;
    sfClock *spawn_timer;
    int spawn_delay;
    char **waves;
    int cur_wave;
    int final_wave;
    sfText *wave_text;
    char *wave_text_str;
    int cur_column;
    int is_new_wave;
    sfTexture ***textures;
} enemies_t;

typedef struct tile {
    sfSprite *tile;
    int type;
    sfVector2f position;
} tile_t;

typedef struct decoration {
    sprite_t *sprites;
    sfIntRect *rect;
    sfTexture *texture;
    int total;
} decoration_t;

typedef struct spawn
{
    tile_t *tiles;
    sfTexture *texture;
    sfIntRect *rect;
    int total;
} spawn_t;

typedef struct button
{
    sfIntRect *rects;
    sfTexture *texture;
    sfText *number_text;
    sfColor def_color;
    char *number_str;
    int is_hovered;
    sfSprite *sprite;
    int is_confirm;
    int type;
    int is_locked;
    sfVector2f position;
} button_t;

typedef struct projectile
{
    sfSprite *sprite;
    animation_t animation;
    int is_active;
    int type;
    int damage;
    int state;
    double radius;
    enemy_t *target;
    sfVector2f destination;
} projectile_t;

typedef struct tower_stats
{
    double radius;
    int damage;
    double attacks_per_sec;
    double splash_radius;
    int cost;
} tower_stats_t;

typedef struct special_tower
{
    sfSprite *background_sprite;
    sfTexture *background_texture;
    sfSprite *foreground_sprite;
    sfTexture *foreground_texture;
    sfClock *movement_timer;
    int movement_delay;
    int is_ability_locked;
} special_tower_t;

typedef struct tower
{
    int type;
    int level;
    tower_stats_t stats_arr[3];
    sfVector2f gap;
    projectile_t projectile;
    sfClock *clock;
    special_tower_t special_attributes;
} tower_t;

typedef struct spots
{
    sfSprite *tile;
    int type;
    int is_hovered;
    sfVector2f position;
    int is_filled;
    tower_t tower;
} spots_t;

typedef struct upgrade_menu
{
    tower_t tower;
    sfTexture *texture;
    sfSprite *sprite;
    button_t button_1;
    button_t button_2;
    button_t button_3;
    button_t button_4;
    button_t sell;
    button_t quit;
    sfVector2f gap;
    int is_active;
    int state;
    int spot_nb;
    sfTexture *radius_texture;
    sfSprite *radius_sprite;
    sfSprite *radius_preview_sprite;
} upgrade_menu_t;

typedef struct building_plots
{
    sfIntRect **tower_rects;
    sfIntRect **ally_rects;
    sfIntRect **ally_rects_mirrored;
    ally_stats_t ally_stats[3];
    tower_t druid_tower;
    tower_t fire_mage;
    tower_t stone_preview;
    tower_t tavern_template;
    spots_t *spots;
    sfTexture *texture;
    sfVector2f position;
    upgrade_menu_t build_menu;
    upgrade_menu_t upgrade;
    sfTexture **tower_textures;
    sfTexture **tower_projectiles_textures;
    sfTexture *ally_textures[3][6];
    sfTexture *druid_arrow_mark_texture;
    sfSprite *druid_arrow_mark_sprite;
    enemy_list_t *allies;
    int total;
} building_plots_t;

typedef struct map {
    int total_tiles;
    int lines;
    int columns;
    tile_t *tileset;
    decoration_t small_deco;
    decoration_t big_deco;
    building_plots_t building_plots;
    sfSprite *background;
    sfTexture *texture;
    sfIntRect *rect;
    sfTexture *tile_texture;
    spawn_t spawn;
    spawn_t goal;
    char *cur_level;
    char *cur_waves;
} map_t;

typedef struct stat_display {
    sfSprite *icon;
    sfSprite *icons_sprite;
    sfTexture *icons_texture;
    sfTexture *tavern_icons;
    sfText *cur_stats_text;
    char *cur_stats_str;
    sfText *preview_stats_text;
    char *prev_stats_str;
    int is_active;
    int is_preview;
    int display_radius;
} stat_display_t;

typedef struct settings {
    sfSprite *bg_sprite;
    button_t music;
    button_t sounds;
    button_t close;
    button_t restart;
    button_t quit;
    button_t back_to_menu;
    int is_active;
} settings_t;

typedef struct game_interface {
    stat_display_t tower_stats;
    sfSprite *background_sprite;
    sfTexture *background_texture;
    health_bar_t health_bar_template;
    sfSprite *lives_icon;
    sfTexture *lives_texture;
    sfTexture *ally_health_bar_foreground;
    sfText *lives_text;
    button_t settings_button;
    int live_count;
    char *lives_str;
    sfText *money_count_text;
    int money_count;
    char *money_count_str;
    sfSprite *money_icon;
    settings_t settings;
} game_interface_t;

typedef struct interaction
{
    int mouse1_is_held;
} interaction_t;

typedef struct stars
{
    sfIntRect *rects;
    char *info_path;
    sfSprite *sprite;
    int count;
    sfVector2f gap;
} stars_t;

typedef struct menu
{
    sfSprite *tutorial_sprite;
    stars_t menu_star;
    sfTexture *star_texture;
    sfSprite *background;
    sfSprite *victory_screen;
    sfSprite *game_over_screen;
    button_t how_to_play;
    button_t play;
    button_t quit_main_menu;
    button_t quit;
    button_t level_1;
    button_t back_to_menu;
    button_t restart;
    sfSprite *level_select_background;
    sfSprite *logo;
    stars_t level_1_stars;
    char state;
} menu_t;

typedef struct object {
    sfRenderWindow *window;
    char game_state;
    menu_t menu;
    map_t map;
    enemies_t enemies;
    interaction_t interaction;
    game_interface_t game_interface;
    sfMusic *click;
    sfMusic *main_theme;
    sfMusic *rock;
    int is_music_mute;
    int is_sound_mute;
} objects_t;


#endif //UNTITLED_DEFENDER_STRUCTS_H