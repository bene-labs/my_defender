//
// Created by benedikt on 2/19/20.
//
#include "../../include/defender.h"

int is_collision_cursor_button(sfVector2i pos_cursor, sfVector2f pos_button, int height, int width)
{
    if (pos_cursor.y >= pos_button.y && \
        pos_cursor.y <= pos_button.y + height && \
        pos_cursor.x >= pos_button.x &&
        pos_cursor.x <= pos_button.x + width)
        return (1);
    return (0);
}

int is_enemy_inside_radius(enemy_t enemy, double radius, int origin_x, int origin_y)
{
    if (sqrt(pow(((enemy.position.x + 50) - (origin_x)), 2) +
        pow(((enemy.position.y + 50) - (origin_y)), 2)) <=
        radius * 10) {
        //printf("Abstand: %fpx\t", sqrt(pow(((enemy.position.x + 50) - (spot.position.x + 50)), 2) +
        //    pow(((enemy.position.y + 50) - (spot.position.y + 50)), 2)));
        return (1);
    }
    return (0);
}

int is_mouse_inside_radius(sfVector2i mouse_pos, double radius, sfVector2f position)
{
    if (sqrt(pow(((mouse_pos.x + 50) - (position.x + 50)), 2) +
        pow(((mouse_pos.y + 50) - (position.y + 50)), 2)) <=
        radius * 10) {
        //printf("Abstand: %fpx\t", sqrt(pow(((enemy.position.x + 50) - (spot.position.x + 50)), 2) +
        //    pow(((enemy.position.y + 50) - (spot.position.y + 50)), 2)));
        return (1);
    }
    return (0);
}