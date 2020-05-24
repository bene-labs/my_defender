//
// Created by benedikt on 3/12/20.
//

#include "../../include/defender.h"
#include "../../include/my.h"

void check_if_enemy_can_attack(enemy_list_t *enemy_list, enemy_list_t *ally_list, objects_t *objects)
{
    for (enemy_list_t *temp = enemy_list->next; temp != NULL; temp = temp->next) {
        if (temp->enemy->target)
            continue;
        sfIntRect rect_e= sfSprite_getTextureRect(temp->enemy->sprite);
        //rect_e.width -= rect_e.width / 100 * 20;
        for (enemy_list_t *temp_2 = ally_list->next; temp_2 != NULL; temp_2 = temp_2->next) {
            if (temp_2->enemy->is_targeted == 1)
                continue;
            sfIntRect rect_a = sfSprite_getTextureRect(temp_2->enemy->sprite);
            //printf("e: x->%f y->%f a : x->%f y-> %f")
            if (sfSprite_getPosition(temp_2->enemy->sprite).y == sfSprite_getPosition(temp->enemy->sprite).y /*&& sfSprite_getPosition(temp_2->enemy->sprite).y <= sfSprite_getPosition(temp->enemy->sprite).y + rect_e.height */\
&& sfSprite_getPosition(temp_2->enemy->sprite).x >= sfSprite_getPosition(temp->enemy->sprite).x && sfSprite_getPosition(temp_2->enemy->sprite).x <= sfSprite_getPosition(temp->enemy->sprite).x + rect_e.width / 100 * 65) {
                temp_2->enemy->walk.is_mirrored = 1;
                sfSprite_setTexture(temp->enemy->sprite, objects->enemies.textures[temp->enemy->type][4], sfTrue);
                sfSprite_setTexture(temp_2->enemy->sprite, objects->map.building_plots.ally_textures[temp_2->enemy->type][5], sfTrue);
                sfSprite_setTextureRect(temp_2->enemy->sprite, objects->map.building_plots.ally_rects_mirrored[temp_2->enemy->type][temp_2->enemy->walk.frame]);
                temp->enemy->walk.frame = 0;
                temp_2->enemy->is_targeted = 1;
                sfSprite_setTextureRect(temp->enemy->sprite, temp->enemy->walk.rect[0]);
                //printf("enemy type %d: target (to right) acquired!\n", temp->enemy->type);
                temp->enemy->target = temp_2->enemy;
                temp_2->enemy->target = temp->enemy;
            }
            else if (sfSprite_getPosition(temp_2->enemy->sprite).y == sfSprite_getPosition(temp->enemy->sprite).y /*&& sfSprite_getPosition(temp_2->enemy->sprite).y <= sfSprite_getPosition(temp->enemy->sprite).y + rect_e.height*/ \
&& sfSprite_getPosition(temp_2->enemy->sprite).x + rect_a.width / 4 == sfSprite_getPosition(temp->enemy->sprite).x /*/ 100 * 50 >= sfSprite_getPosition(temp->enemy->sprite).x -rect_e.width / 100 * 50 && sfSprite_getPosition(temp_2->enemy->sprite).x <= sfSprite_getPosition(temp->enemy->sprite).x + rect_a.width*/) {
                sfSprite_setTexture(temp->enemy->sprite, objects->enemies.textures[temp->enemy->type][5], sfTrue);
                //printf("enemy type %d: target (to left) acquired!\n", temp->enemy->type);
                //temp->enemy->walk.is_mirrored = 0;
                temp_2->enemy->walk.is_mirrored = 0;
                temp_2->enemy->is_targeted = 1;
                //sfSprite_setTexture(temp_2->enemy->sprite, objects->map.building_plots.ally_textures[temp_2->type][1], sfTrue);
                sfSprite_setTextureRect(temp_2->enemy->sprite, objects->map.building_plots.ally_rects[temp_2->enemy->type][temp_2->enemy->walk.frame]);
                sfSprite_setTexture(temp_2->enemy->sprite, objects->map.building_plots.ally_textures[temp_2->enemy->type][4], sfTrue);
                sfSprite_setTextureRect(temp_2->enemy->sprite, objects->map.building_plots.ally_rects_mirrored[temp_2->enemy->type][temp_2->enemy->walk.frame]);
                temp->enemy->walk.frame = 0;
                sfSprite_setTextureRect(temp->enemy->sprite, temp->enemy->walk.rect[0]);
                temp->enemy->walk.is_mirrored = 1;
                temp->enemy->target = temp_2->enemy;
                temp_2->enemy->target = temp->enemy;
            }
        }
    }
}