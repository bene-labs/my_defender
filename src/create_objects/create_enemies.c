//
// Created by benedikt on 2/14/20.
//

#include "../../include/defender.h"
#include "../../include/my.h"

int is_new_wave_start(objects_t *objects, enemies_t *enemies, enemy_list_t *list)
{
    sfVector2f pos_level_1 = {375, 420};

    if (list->next == NULL) {
        //printf("wave start: %d/%d\n", enemies->cur_wave + 1, enemies->final_wave);
        if (enemies->cur_wave == enemies->final_wave) {
            objects->game_state = 'm';
            objects->menu.state = 'v';
            if (objects->game_interface.live_count >= 15)
                objects->menu.level_1_stars.count = 3;
            else if (objects->game_interface.live_count >= 5)
                objects->menu.level_1_stars.count = 2;
            else
                objects->menu.level_1_stars.count = 1;
            sfSprite_setTextureRect(objects->menu.level_1_stars.sprite, objects->menu.level_1_stars.rects[objects->menu.level_1_stars.count]);
            objects->menu.menu_star.sprite = sfSprite_copy(objects->menu.level_1_stars.sprite);
            sfVector2f scale = {0.25, 0.25};
            sfSprite_setScale(objects->menu.menu_star.sprite, scale);
            pos_level_1.y += 80;
            pos_level_1.x += 34;
            sfSprite_setPosition(objects->menu.menu_star.sprite, pos_level_1);
            cleanup_map(objects);
            get_default_game_stats(objects);
            return (0);
        }
        add_points(objects->enemies.wave_text_str, 7);
        sfText_setString(objects->enemies.wave_text, objects->enemies.wave_text_str);
        enemies->is_new_wave = 0;
        objects->game_interface.money_count += objects->enemies.cur_wave * 50;
        display_money_count(&objects->game_interface);
        return (1);
    }
    return (0);
}

void determine_enemy(objects_t *objects, int type)
{
    enemy_stats_t stats[10] = {{10, 20000, 100.0, 100.0, 10, 30.0, 0.0, 1}, \
{7, 10000, 60.0, 60.0, 5, 0.0, 12.0, 1},\
{20, 35000, 250, 250, 25, 2.5, 75.0, 3}, \
{25, 40000, 333, 333, 30, 0.0, 0.0, 3}, \
{11,18000, 88, 88, 7, 0.0, 5.0, 1}, \
{15, 22000, 125, 125, 15, 80.0, 0.0, 2},\
{22, 25000, 175, 175, 20, 0.0, 50.0, 2}, \
{13, 33333, 333, 333, 33, 100.0, 0.0, 3}, \
{18, 12345, 125, 125, 15, 0.0, 34.5, 2},
{5,22000, 50, 50, 5, 5.0, 0.0, 1}};

    //1.Zombie 2.goblin 3.goblin mage 4.ogre 5.hollow 6.armored goon 7.lizard 8.ghost 9.troll 10.scorpion
    //printf("l: %d c: %d -> '%c'\n", objects->enemies.cur_wave, objects->enemies.cur_column, type);
    switch (type) {
    case '0':
        create_enemy(objects, 0, stats[0], get_rect_arr(4, 5, 83, 70),  get_rect_arr_mirrored(4, 5, 83, 70));
        break;
    case '1':
        create_enemy(objects, 1, stats[1], get_rect_arr(4, 5, 87, 70), get_rect_arr_mirrored(4, 5, 87, 70));
        break;
    case '2':
        create_enemy(objects, 2, stats[2], get_rect_arr(4, 5, 91, 80), get_rect_arr_mirrored(4, 5, 91, 80));
        break;
    case '3':
        create_enemy(objects, 3, stats[3], get_rect_arr(4, 5, 98, 82), get_rect_arr_mirrored(4, 5, 98, 82));
        break;
    case '4':
        create_enemy(objects, 4, stats[4], get_rect_arr(4, 5, 77, 72), get_rect_arr_mirrored(4, 5, 77, 72));
        break;
    case '5':
        create_enemy(objects, 5, stats[5], get_rect_arr(4, 5, 82, 70), get_rect_arr_mirrored(4, 5, 83, 70));
        break;
    case '6':
        create_enemy(objects, 6, stats[6], get_rect_arr(4, 5, 74, 75), get_rect_arr_mirrored(4, 5, 74, 75));
        break;
    case '7':
        create_enemy(objects, 7, stats[7], get_rect_arr(4, 5, 118, 70), get_rect_arr_mirrored(4, 5, 118, 70));
        break;
    case '8':
        create_enemy(objects, 8, stats[8], get_rect_arr(4, 5, 85, 72), get_rect_arr_mirrored(4, 5, 85, 72));
        break;
    case '9':
        create_enemy(objects, 9, stats[9], get_rect_arr(4, 5, 42, 50), get_rect_arr_mirrored(4, 5, 42, 50));
        break;
    case '\n':
        objects->enemies.cur_wave++;
        objects->enemies.cur_column = 0;
        objects->enemies.is_new_wave = 1;
        break;
    case '|':
        objects->enemies.is_new_wave = 1;
        objects->enemies.cur_wave++;
        break;
    default:
        break;
    }
    objects->enemies.cur_column++;
}

void create_enemy(objects_t *objects, int type, enemy_stats_t stats, sfIntRect *rects, sfIntRect *mirrored)
{
    enemy_t *enemy = malloc(sizeof(enemy_t));

    enemy->poison_count = 0;
    enemy->poison_tick_clock = sfClock_create();
    enemy->poison_limit = 0;
    enemy->poisoned_duration_clock = sfClock_create();
    enemy->is_ally = 0;
    enemy->type = type;
    enemy->stats = stats;
    enemy->target = NULL;
    enemy->sprite = sfSprite_create();
    determine_enemy_start(enemy, objects);
    sfSprite_setPosition(enemy->sprite, enemy->position);
    enemy->clock = sfClock_create();
    enemy->walk.frame = 0;
    enemy->walk.max_frame = 20;
    enemy->walk.clock = sfClock_create();
    enemy->walk.delay = stats.move_delay * 2;
    enemy->walk.rect = rects;
    sfSprite_setTextureRect(enemy->sprite, enemy->walk.rect[0]);
    enemy->walk.mirrored_rect = mirrored;
    enemy->health_bar.background_sprite = sfSprite_create();
    enemy->health_bar.foreground_sprite = sfSprite_create();
    sfSprite_setTexture(enemy->health_bar.background_sprite, objects->game_interface.health_bar_template.background_texture, sfTrue);
    sfSprite_setTexture(enemy->health_bar.foreground_sprite, objects->game_interface.health_bar_template.foreground_texture, sfTrue);
    enemy->health_bar.percentage = 100.0;
    sfIntRect rect = {0, 0, 100, 11};
    enemy->health_bar.foreground_rect = rect;
    enemy->health_bar.position = enemy->position;
    enemy->health_bar.position.y -= 5;
    enemy->health_bar.position.x -= 25;
    sfSprite_setPosition(enemy->health_bar.background_sprite, enemy->health_bar.position);
    sfSprite_setPosition(enemy->health_bar.foreground_sprite, enemy->health_bar.position);
    enemy->is_alive = 1;
    enemy->death.rect = enemy->walk.rect;
    enemy->death.frame = 0;
    enemy->is_targeted = 0;
    enemy->def_color = sfSprite_getColor(enemy->sprite);
    append_to_list(objects->enemies.enemy_list, enemy);
    //printf("created enemy from '%s'\n", name);
}

void determine_enemy_start(enemy_t *enemy, objects_t *objects)
{
    int random = get_random_int_within_range(0, objects->map.spawn.total-1);
    sfVector2f gap = {0, 0};
    sfVector2f move = {0, 0};

    switch (objects->map.spawn.tiles[random].type) {
    case 0:
        move.y = 1;
        gap.y = - 100;
        enemy->walk.is_mirrored = 1;
        sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][0], sfTrue);
        break;
    case 1:
        move.x = 1;
        gap.x = - 100;
        enemy->walk.is_mirrored = 0;
        sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][1], sfTrue);
        break;
    case 2:
        move.x = -1;
        gap.x = 100;
        enemy->walk.is_mirrored = 1;
        sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][0], sfTrue);
        break;
    case 3:
        move.y = -1;
        gap.y = 200;
        enemy->walk.is_mirrored = 0;
        sfSprite_setTexture(enemy->sprite, objects->enemies.textures[enemy->type][1], sfTrue);
        break;
    default:
        my_printf("error creating enemy: chosen spawn has undefined type\n");
        return;
    }
    enemy->position = objects->map.spawn.tiles[random].position;
    enemy->position.x += gap.x;
    enemy->position.y += gap.y;
    enemy->move = move;
}