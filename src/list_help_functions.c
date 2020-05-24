#include "../include/defender.h"

enemy_list_t *create_enemy_list(void)
{
    enemy_list_t *res = malloc(sizeof(enemy_list_t));
    res->enemy = NULL;
    res->type = 0;
    res->next = NULL;
    return (res);
}

void append_to_list(enemy_list_t *list, enemy_t *enemy)
{
    enemy_list_t *new_list_point = malloc(sizeof(enemy_list_t));
    new_list_point->next = NULL;
    new_list_point->enemy = enemy;
    new_list_point->type = enemy->type;
    for (; list->next != NULL; list = list->next);
    list->next = new_list_point;
}

void remove_enemy_from_list(enemy_list_t *list, enemy_t *to_remove)
{
    enemy_list_t *tmp;

    for (; list->next != NULL && list->next->enemy != to_remove; \
list = list->next);
    if (list->next == NULL)
        return;
    if (list->next->enemy == NULL)
        return;
    sfSprite_destroy(list->next->enemy->sprite);
    free(list->next->enemy);
    list->next->enemy = NULL;
    tmp = list->next->next;
    free(list->next);
    list->next = NULL;
    list->next = tmp;
}


