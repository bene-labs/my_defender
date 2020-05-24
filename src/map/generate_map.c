#include "../../include/defender.h"
#include "../../include/my.h"
/*
** EPITECH PROJECT, 2020
** generate_map.c
** File description:
** generates a map based on a text file
*/

int generate_map(objects_t *objects, char **map)
{
    int line = 0;

    if (map == NULL)
        return (84);
    objects->map.building_plots.total = 0;
    objects->map.total_tiles = 0;
    objects->map.small_deco.total = 0;
    objects->map.big_deco.total = 0;
    objects->map.spawn.total = 0;
    objects->map.goal.total = 0;

    display_money_count(&objects->game_interface);
    objects->map.tileset = malloc(sizeof(tile_t) * (get_tile_count(map, objects, '0', '9') + get_tile_count(map, objects, '|', '|') + get_tile_count(map, objects, '-', '-') + get_tile_count(map, objects, 'I', 'I') + get_tile_count(map, objects, '_', '_')));
    objects->map.small_deco.sprites = malloc(sizeof(sprite_t) * get_tile_count(map, objects, 'a', 'y'));
    objects->map.big_deco.sprites = malloc(sizeof(sprite_t) * get_tile_count(map, objects, 'A', 'H'));
    objects->map.spawn.tiles = malloc(sizeof(sprite_t) * get_tile_count(map, objects, '*', '*'));
    objects->map.goal.tiles = malloc(sizeof(sprite_t) * get_tile_count(map, objects, '#', '#'));
    objects->map.building_plots.spots = malloc(sizeof(spots_t) * get_tile_count(map, objects, '+', '+'));
    for (; line < objects->map.lines; line++) {
        for (int column = 0; column < objects->map.columns; column++) {
            //printf("%c", map[line][column]);
            if (map[line][column] == '*') {
                if (line == 0 && column > 0 && column < objects->map.columns - 1)
                    objects->map.spawn.tiles[objects->map.spawn.total].type = 0;
                else if (column == 0)
                    objects->map.spawn.tiles[objects->map.spawn.total].type = 1;
                else if (column == objects->map.columns - 2)
                    objects->map.spawn.tiles[objects->map.spawn.total].type = 2;
                else if (line == objects->map.lines - 1) {
                    objects->map.spawn.tiles[objects->map.spawn.total].type = 3;
                }
                else {
                    my_printf("Error: spawn %d is invalid (must be on the border of the map).\n", objects->map.spawn.total + 1);
                    return(cleanup(objects, 84));
                }
                sfVector2f position = {column * 100, (line) * 100};
                objects->map.spawn.tiles[objects->map.spawn.total].position = position;
                objects->map.spawn.tiles[objects->map.spawn.total].tile = sfSprite_create();
                sfSprite_setTexture(objects->map.spawn.tiles[objects->map.spawn.total].tile, objects->map.spawn.texture, sfTrue);
                sfSprite_setPosition(objects->map.spawn.tiles[objects->map.spawn.total].tile, position);
                sfSprite_setTextureRect(objects->map.spawn.tiles[objects->map.spawn.total].tile, objects->map.spawn.rect[objects->map.spawn.tiles[objects->map.spawn.total].type]);
                objects->map.spawn.total++;
            } else if (map[line][column] == '#') {
                if (line == 0 && column > 0 && column < objects->map.columns - 1)
                    objects->map.goal.tiles[objects->map.goal.total].type = 0;
                else if (column == 0)
                    objects->map.goal.tiles[objects->map.goal.total].type = 1;
                else if (column == objects->map.columns - 2)
                    objects->map.goal.tiles[objects->map.goal.total].type = 2;
                else if (line == objects->map.lines - 1) {
                    objects->map.goal.tiles[objects->map.goal.total].type = 3;
                }
                else {
                    my_printf("Error: goal %d is invalid (must be on the border of the map).\n", objects->map.goal.total + 1);
                    return(cleanup(objects, 84));
                }
                sfVector2f position = {column * 100, (line) * 100};
                objects->map.goal.tiles[objects->map.goal.total].position = position;
                objects->map.goal.tiles[objects->map.goal.total].tile = sfSprite_create();
                sfSprite_setTexture(objects->map.goal.tiles[objects->map.goal.total].tile, objects->map.goal.texture, sfTrue);
                sfSprite_setPosition(objects->map.goal.tiles[objects->map.goal.total].tile, position);
                sfSprite_setTextureRect(objects->map.goal.tiles[objects->map.goal.total].tile, objects->map.goal.rect[objects->map.goal.tiles[objects->map.goal.total].type]);
                objects->map.goal.total++;
            }
            else if ((map[line][column] >= '0' && map[line][column] <= '9') || map[line][column] == '|' || map[line][column] == '-' || map[line][column] == 'I' || map[line][column] == '_') {
                //  printf("%d", map[line][column] - 48);
                sfVector2f position = {column * 100, (line) * 100};
                objects->map.tileset[objects->map.total_tiles].position = position;
                //printf("type: %d position: x->%f y->%f\n", map[line][column] - 48, objects->map.tileset[objects->map.total_tiles].position.x, objects->map.tileset[objects->map.total_tiles].position.y);
                objects->map.tileset[objects->map.total_tiles].tile = sfSprite_create();
                sfSprite_setTexture(objects->map.tileset[objects->map.total_tiles].tile,
                    objects->map.tile_texture, sfTrue);
                switch (map[line][column]) {
                case '|':
                    sfSprite_setTextureRect(
                        objects->map.tileset[objects->map.total_tiles].tile,
                        objects->map.rect[9]);
                    break;
                case '-':
                    sfSprite_setTextureRect(
                        objects->map.tileset[objects->map.total_tiles].tile,
                        objects->map.rect[10]);
                    break;
                case '_':
                    sfSprite_setTextureRect(
                        objects->map.tileset[objects->map.total_tiles].tile,
                        objects->map.rect[11]);
                    break;
                case 'I':
                    sfSprite_setTextureRect(
                        objects->map.tileset[objects->map.total_tiles].tile,
                        objects->map.rect[12]);
                    break;
                default:
                    sfSprite_setTextureRect(
                        objects->map.tileset[objects->map.total_tiles].tile,
                        objects->map.rect
                            /*temp*/[map[line][column] - 48]);
                    break;
                }
                sfSprite_setPosition(objects->map.tileset[objects->map.total_tiles].tile, position);
                objects->map.tileset[objects->map.total_tiles].type = map[line][column] - 48;
                objects->map.total_tiles++;
                //printf("%d", objects->map.tileset[line].type);
            } else if (map[line][column] >= 'a' && map[line][column] <= 'y') {
                sfVector2f position = {column * 100, (line) * 100};
                objects->map.small_deco.sprites[objects->map.small_deco.total].sprite = sfSprite_create();
                sfSprite_setTexture(objects->map.small_deco.sprites[objects->map.small_deco.total].sprite,
                    objects->map.small_deco.texture, sfTrue);
                sfSprite_setTextureRect(
                    objects->map.small_deco.sprites[objects->map.small_deco.total].sprite,
                    objects->map.small_deco.rect[map[line][column] - 97]);
                sfSprite_setPosition(objects->map.small_deco.sprites[objects->map.small_deco.total].sprite,
                    position);
                objects->map.small_deco.total++;
            } else if (map[line][column] >= 'A' && map[line][column] <= 'H') {
                sfVector2f position = {column * 100, (line) * 100};
                objects->map.big_deco.sprites[objects->map.big_deco.total].sprite = sfSprite_create();
                sfSprite_setTexture(objects->map.big_deco.sprites[objects->map.big_deco.total].sprite,
                    objects->map.big_deco.texture, sfTrue);
                sfSprite_setTextureRect(
                    objects->map.big_deco.sprites[objects->map.big_deco.total].sprite,
                    objects->map.big_deco.rect[map[line][column] - 65]);
                sfSprite_setPosition(objects->map.big_deco.sprites[objects->map.big_deco.total].sprite,
                    position);
                objects->map.big_deco.total++;
            } else if (map[line][column] == '+')
            {
                sfVector2f position = {column * 100, (line) * 100 + 30};
                objects->map.building_plots.spots[objects->map.building_plots.total].tile = sfSprite_create();
                sfSprite_setTexture(objects->map.building_plots.spots[objects->map.building_plots.total].tile,
                    objects->map.building_plots.texture, sfTrue);
                sfSprite_setPosition(objects->map.building_plots.spots[objects->map.building_plots.total].tile,
                    position);
                objects->map.building_plots.spots[objects->map.building_plots.total].type = 0;
                objects->map.building_plots.spots[objects->map.building_plots.total].is_hovered = 0;
                objects->map.building_plots.spots[objects->map.building_plots.total].position = position;
                objects->map.building_plots.spots[objects->map.building_plots.total].is_filled = 0;
                objects->map.building_plots.total++;
            }
        }
    }
    return (0);
}

int get_tile_count(char **map, objects_t *objects, char min, char max)
{
    int result = 0;

    for (int line = 0; line < objects->map.lines; line++) {
        for (int column = 0; column < objects->map.columns; column++) {
            if (map[line][column] >= min && map[line][column] <= max)
                result++;
        }
    }
    return (result);
}

char **get_map(char *argv0, objects_t *objects)
{
    char **map = malloc(sizeof(char *) * 10 + 1);
    size_t size = 0;
    FILE *stream = fopen(argv0, "r");
    int line = 0;

    if (stream == NULL) {
        my_printf("Error: map '%s' does not exist.\n", argv0);
        cleanup(objects, 84);
        return (NULL);
    }
    for (; ; line++) {
        map[line] = NULL;
        if (getline(&map[line], &size, stream) == -1)
            break;
        if (line >= 9) {
            my_printf("Error: maps must not contain more than 9 lines!\n");
            cleanup(objects, 84);
            return (NULL);
        }
    }
    objects->map.cur_level = malloc(sizeof(char) * my_strlen(argv0));
    my_strcpy(objects->map.cur_level, argv0);
    fclose(stream);
    objects->map.lines = line;
    map[line] = NULL;
    if (test_map(objects, argv0, map) == 84)
        return (NULL);
    return (map);
}

int test_map(objects_t *objects, char *argv0, char **map)
{
    int size = 0;
    int prev_size = 0;

    for (int line = 1; line < objects->map.lines; line++) {
        for (prev_size = 0; map[line - 1][prev_size] != '\n'; prev_size++);
        for (size = 0;
            map[line][size] != '\n' && map[line][size] != '\0'; size++);
        //printf("%d : %d vs %d : %d\n", line, prev_size, line+1, size);
        if (prev_size != size && line != 0) {
            my_printf(
                "Error in line %d: map '%s'  is invalid.\n->all lines must have "
                "the same number of columns\n", line, argv0);
            return(cleanup(objects, 84));
        }
    }
    objects->map.columns = prev_size;
    return (0);
}