cmake_minimum_required(VERSION 3.15)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(Defender src/main.c include/defender.h src/create_objects/create_objects.c src/map/generate_map.c src/create_objects/create_enemies.c src/movement/animate_enemies.c src/movement/move_enemies.c src/handle_randomness.c src/my_printf/disp_stdarg.c src/my_printf/disp_stdarg2.c src/my_printf/disp_stdarg3.c src/my_printf/disp_stdarg4.c src/my_printf/my_getnbr.c src/my_printf/my_printf.c src/my_printf/my_put_nbr.c src/my_printf/my_putchar.c src/my_printf/my_putstr.c src/my_printf/my_strlen.c src/my_printf/sum_stdarg.c src/my_printf/my_put_nbr_base.c src/cleanup.c src/towers/mage_tower.c src/towers/build_menus.c src/collision/handle_collision.c src/list_help_functions.c src/player_stats.c src/score.c src/towers/additional_tower_ui.c src/create_objects/create_towers.c src/towers/stone_tower.c src/str_functions.c src/create_objects/handle_enemy_waves.c src/main_gameplay.c src/menu/main_menu.c src/create_objects/create_menu_objects.c src/menu/settings.c src/towers/druid.c src/towers/tavern.c src/menu/buttons.c src/movement/enemy_attack.c)

target_link_libraries(Defender csfml-window csfml-graphics csfml-audio csfml-system m)