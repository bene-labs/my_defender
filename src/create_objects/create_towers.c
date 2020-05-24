//
// Created by benedikt on 3/10/20.
//

#include "../../include/defender.h"

void create_new_tower(objects_t *objects, tower_t tower)
{
    switch (tower.type) {
    case 0:
        objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tower = create_druid_tower(objects);
        break;
    case 1:
        objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tower = create_tavern(
            &objects->map.building_plots);
        break;
     case 2:
        objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tower = create_fire_mage(objects);
        break;
    case 3:
        objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tower = create_basic_stone_tower(objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb], objects);
        break;
    default:
        return;
    }
    sfVector2f position = objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].position;
    position.x += objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tower.gap.x;
    position.y += objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tower.gap.y;
    //my_printf("nb: %d\n", objects->map.building_plots.build_menu.spot_nb);
    objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].is_filled = 1;
    sfSprite_setTextureRect(
        objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tile,
        objects->map.building_plots.tower_rects[tower.type][0]);
    sfSprite_setPosition(
        objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tile,
        position);
    //objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].type = 3;
    objects->map.building_plots.build_menu.is_active = 0;
    objects->game_interface.money_count -= tower.stats_arr[0].cost;
    display_money_count(&objects->game_interface);
}

void create_tower_sprites (objects_t *objects)
{
    objects->map.building_plots.tower_rects = malloc(sizeof(sfIntRect *) * 4);
    objects->map.building_plots.tower_textures = malloc(sizeof(sfTexture *) * 4);
    objects->map.building_plots.tower_textures[0] = sfTexture_createFromFile("resources/towers/druid/druid.png", NULL);
    objects->map.building_plots.tower_textures[1] = sfTexture_createFromFile("resources/towers/tavern/tavern.png", NULL);
    objects->map.building_plots.tower_textures[2] = sfTexture_createFromFile("resources/towers/fire.png", NULL);
    objects->map.building_plots.tower_textures[3] = sfTexture_createFromFile("resources/towers/stone/3.png", NULL);
    objects->map.building_plots.tower_projectiles_textures = malloc(sizeof(sfTexture *) * 4);
    objects->map.building_plots.tower_projectiles_textures[0] = sfTexture_createFromFile("resources/towers/druid/rain.png", NULL);
    objects->map.building_plots.tower_projectiles_textures[2] = sfTexture_createFromFile("resources/towers/zip/zip.png", NULL);
    objects->map.building_plots.tower_projectiles_textures[3] = sfTexture_createFromFile("resources/towers/stone/stone_explosion_1.png", NULL);
    objects->map.building_plots.tower_rects[0] = get_rect_arr(3, 1, 100, 110);
    objects->map.building_plots.tower_rects[1] = get_rect_arr(2, 2, 100, 95);
    objects->map.building_plots.tower_rects[2] = get_rect_arr(3, 1, 100, 170);
    objects->map.building_plots.tower_rects[3] = get_rect_arr(3, 1, 100, 134);
    objects->map.building_plots.druid_tower.gap.y = -40;
    objects->map.building_plots.druid_tower.gap.x = 0;
    objects->map.building_plots.druid_tower.stats_arr[0].radius = 999.9;
    objects->map.building_plots.druid_tower.stats_arr[0].attacks_per_sec = 0.1;
    objects->map.building_plots.druid_tower.stats_arr[0].damage = 1;
    objects->map.building_plots.druid_tower.stats_arr[0].splash_radius = 7.5;
    objects->map.building_plots.druid_tower.stats_arr[0].cost = 75;
    objects->map.building_plots.druid_tower.type = 0;
    objects->map.building_plots.druid_arrow_mark_texture = sfTexture_createFromFile("resources/towers/druid/arrow.png", NULL);
    objects->map.building_plots.druid_arrow_mark_sprite = sfSprite_create();
    sfSprite_setTexture(objects->map.building_plots.druid_arrow_mark_sprite, objects->map.building_plots.druid_arrow_mark_texture, sfTrue);
    objects->map.building_plots.fire_mage.gap.y = -100;
    objects->map.building_plots.fire_mage.gap.x = 0;
    objects->map.building_plots.fire_mage.level = 0;
    objects->map.building_plots.fire_mage.stats_arr[0].radius = 12.5;
    objects->map.building_plots.fire_mage.stats_arr[0].attacks_per_sec = 1.0;
    objects->map.building_plots.fire_mage.stats_arr[0].damage = 20;
    objects->map.building_plots.fire_mage.stats_arr[0].cost = 125;
    objects->map.building_plots.fire_mage.stats_arr[0].splash_radius = 1.0;
    objects->map.building_plots.fire_mage.type = 2;
    objects->map.building_plots.stone_preview.special_attributes.background_texture = sfTexture_createFromFile("resources/towers/stone/4.png", NULL);
    objects->map.building_plots.stone_preview.special_attributes.foreground_texture = sfTexture_createFromFile("resources/towers/stone/5.png", NULL);
    objects->map.building_plots.stone_preview.level = 0;
    objects->map.building_plots.stone_preview.stats_arr[0].cost = 160;
    objects->map.building_plots.stone_preview.stats_arr[0].splash_radius = 12.5;
    objects->map.building_plots.stone_preview.stats_arr[0].damage = 40;
    objects->map.building_plots.stone_preview.stats_arr[0].radius = 14.0;
    objects->map.building_plots.stone_preview.stats_arr[0].attacks_per_sec = 0.45;
    objects->map.building_plots.stone_preview.gap.y = -45;
    objects->map.building_plots.stone_preview.gap.x = 0;
    objects->map.building_plots.stone_preview.type = 3;
    objects->map.building_plots.upgrade.radius_texture = sfTexture_createFromFile("resources/towers/radius.png", NULL);
    objects->map.building_plots.upgrade.radius_sprite = sfSprite_create();
    sfSprite_setTexture(objects->map.building_plots.upgrade.radius_sprite, objects->map.building_plots.upgrade.radius_texture, sfTrue);
    objects->map.building_plots.tavern_template.level = 0;
    objects->map.building_plots.tavern_template.gap.y = -25;
    objects->map.building_plots.tavern_template.gap.x = 0;
    objects->map.building_plots.tavern_template.stats_arr[0].cost = 100;
    objects->map.building_plots.tavern_template.stats_arr[0].damage = 7;
    objects->map.building_plots.tavern_template.stats_arr[0].attacks_per_sec = 1.0;
    objects->map.building_plots.tavern_template.stats_arr[0].radius = 15;
    objects->map.building_plots.tavern_template.stats_arr[0].splash_radius = 10.0;
    objects->map.building_plots.tavern_template.type = 1;
}

int create_initial_allies(building_plots_t *plots)
{
    char paths[3][6][60] = {{"resources/towers/tavern/allies/knight_1/idle_mirrored.png", "resources/towers/tavern/allies/knight_1/idle.png", "resources/towers/tavern/allies/knight_1/die.png", "resources/towers/tavern/allies/knight_1/die_mirrored.png", "resources/towers/tavern/allies/knight_1/attack.png", "resources/towers/tavern/allies/knight_1/attack_mirrored.png"}, \
{"resources/towers/tavern/allies/knight_2/die_mirrored.png", "resources/towers/tavern/allies/knight_2/die.png", "resources/towers/tavern/allies/knight_2/die.png", "resources/towers/tavern/allies/knight_2/die_mirrored.png", "resources/towers/tavern/allies/knight_2/attack.png",  "resources/towers/tavern/allies/knight_2/attack_mirrored.png"}, \
{"resources/towers/tavern/allies/knight_3/walk_mirrored.png", "resources/towers/tavern/allies/knight_3/walk.png", "resources/towers/tavern/allies/knight_3/die.png", "resources/towers/tavern/allies/knight_3/die_mirrored.png", "resources/towers/tavern/allies/knight_3/attack.png", "resources/towers/tavern/allies/knight_3/attack_mirrored.png"}};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            if (!(plots->ally_textures[i][j] = sfTexture_createFromFile(paths[i][j], NULL)))
                return (84);
        }
    }
    plots->allies = create_enemy_list();
    return (0);
}