//
// Created by benedikt on 3/1/20.
//

#include "../../include/defender.h"
#include "../../include/my.h"

void get_waves_array(objects_t *objects, char *argv2)
{
    objects->enemies.cur_wave = 0;
    //char *test = NULL;
    size_t size = 0;
    FILE *stream = fopen(argv2, "r");

    objects->enemies.cur_wave = 0;
    objects->enemies.cur_column = 0;
    //objects->enemies.
    objects->enemies.waves = malloc(sizeof(char *) * 99 + 1); //todo: the maximal possible wave is 100, but mallocing for less if the file is smaller would be better
    if (stream == NULL) {
        my_printf("Error: wave file '%s' does not exist.\n", argv2);
        exit(cleanup(objects, 84));
    }
    for (objects->enemies.final_wave = 0; objects->enemies.final_wave < 99; objects->enemies.final_wave++) {
        objects->enemies.waves[objects->enemies.final_wave] = NULL;
        if (getline(&objects->enemies.waves[objects->enemies.final_wave], &size, stream) == -1)
            break;
    }
    objects->enemies.waves[objects->enemies.final_wave] = NULL;
    objects->map.cur_waves = malloc(sizeof(char) * my_strlen(argv2));
    my_strcpy(objects->map.cur_waves, argv2);
    //for (int i = 0; objects->enemies.waves[i] != NULL; i++)
    //    printf("%s", objects->enemies.waves[i]);
    fclose(stream);
    //printf("\n\n");
    for (int i = 0; i < objects->enemies.final_wave; i++)
        add_points(objects->enemies.wave_text_str, 10);
    sfText_setString(objects->enemies.wave_text, objects->enemies.wave_text_str);
}