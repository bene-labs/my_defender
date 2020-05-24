#include "../../include/defender.h"

tower_t create_fire_mage (objects_t *objects)
{
    tower_t fire_mage;

    fire_mage.type = 2;
    //if (!(fire_mage.texture = sfTexture_createFromFile("resources/towers/fire.png", NULL)))
    //    printf("ERROR");
    sfSprite_setTexture(
        objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb].tile,
        objects->map.building_plots.tower_textures[2], sfTrue);
    fire_mage.stats_arr[0].radius = 12.5;
    fire_mage.stats_arr[0].attacks_per_sec = 1.0;
    fire_mage.stats_arr[0].damage = 25;
    fire_mage.stats_arr[0].cost = 125;
    fire_mage.stats_arr[0].splash_radius = 1.0;
    fire_mage.stats_arr[1].cost = 220;
    fire_mage.stats_arr[1].radius = 18.0;
    fire_mage.stats_arr[1].attacks_per_sec = 1.35;
    fire_mage.stats_arr[1].damage = 28;
    fire_mage.stats_arr[1].splash_radius = 1.5;
    fire_mage.stats_arr[2].cost = 200;
    fire_mage.stats_arr[2].radius = 25.0;
    fire_mage.stats_arr[2].attacks_per_sec = 1.77;
    fire_mage.stats_arr[2].damage = 33;
    fire_mage.stats_arr[2].cost = 350;
    fire_mage.stats_arr[2].splash_radius = 2.0;
    fire_mage.gap.y = -100;
    fire_mage.gap.x = 0;
    fire_mage.level = 0;
    fire_mage.projectile.state = 0;
    fire_mage.projectile.is_active = 0;
    fire_mage.projectile.type = 3;
    fire_mage.projectile.damage = fire_mage.stats_arr[fire_mage.level].damage;
    fire_mage.clock = sfClock_create();
    fire_mage.projectile.sprite = sfSprite_create();
    //fire_mage.projectile.animation.texture = sfTexture_createFromFile("resources/towers/zip/zip.png", NULL);
    sfSprite_setTexture(fire_mage.projectile.sprite, objects->map.building_plots.tower_projectiles_textures[2], sfTrue);
    fire_mage.projectile.animation.rect = get_rect_arr(6, 3, 100, 263);
    fire_mage.projectile.animation.clock = sfClock_create();
    fire_mage.projectile.animation.max_frame = 14;
    fire_mage.projectile.animation.frame = 0;
    fire_mage.projectile.animation.delay = 50000;
    fire_mage.projectile.radius = fire_mage.stats_arr[0].splash_radius;
    return (fire_mage);
}

void handle_tower_attack(spots_t spot, tower_t *tower, enemy_t *enemy)
{
    if (tower->type == 1 || (tower->projectile.type == 1 && tower->projectile.destination.x == -1 && tower->projectile.destination.y == -1))
        return;
    if (sfClock_getElapsedTime(tower->clock).microseconds >= 1 * pow(10, 6) / tower->stats_arr[tower->level].attacks_per_sec && tower->projectile.is_active == 0 && tower->projectile.state == 0) {
        if (is_enemy_inside_radius(*enemy, tower->stats_arr[tower->level].radius, spot.position.x + 50, spot.position.y + 50)) {
            if (tower->projectile.type == 4 && enemy->is_targeted == 1)
                return;
            sfClock_restart(tower->clock);
            tower->projectile.is_active = 1;
            //if (spot.type == 3)
           //     tower->projectile.type = 3;
            //printf("pew!\n");
            //temp
            if (tower->projectile.type == 1) {
                /*sfVector2f position = spot.pos
                position.y -= 107.5;*/
                //sfSprite_setPosition(tower->projectile.sprite, tower->projectile.destination);
                return;
            }
            sfVector2f position = enemy->position;
            if (tower->projectile.type == 3) {
                tower->projectile.state = 4;
                position.y -= 160;
                sfSprite_setPosition(tower->projectile.sprite, position);
            }
            if (tower->projectile.type == 4) {
                sfVector2f position = spot.position;
                position.y -= 107.5;
                sfSprite_setPosition(tower->projectile.sprite, position);
            }
            tower->projectile.target = enemy;
            enemy->is_targeted = 1;
        }
    }
}

