#include "../../include/defender.h"
#include "../../include/my.h"

void handle_building_spots(objects_t *objects, spots_t spot, int nb)
{
    sfVector2f position = spot.position;
    sfVector2f up = {1.1, 1.1};

    if (sfMouse_isButtonPressed(sfMouseLeft) &&
        objects->interaction.mouse1_is_held == 0) {
        sfMusic_stop(objects->click);
        sfMusic_play(objects->click);
        objects->map.building_plots.upgrade.is_active = 0;
        objects->game_interface.tower_stats.is_active = 0;
        objects->game_interface.tower_stats.is_preview = 0;
        set_all_buttons_to_default(objects);
        objects->interaction.mouse1_is_held = 1;
        objects->map.building_plots.build_menu.is_active = 1;
        position.x -= 10;
        sfSprite_setPosition(objects->map.building_plots.build_menu.sprite,
            position);
        position = spot.position;
        position.x += 32;
        position.y -= 20;
        sfSprite_setPosition(objects->map.building_plots.build_menu.quit.sprite,
            position);
        objects->map.building_plots.build_menu.quit.position = position;
        sfVector2f position = spot.position;
        position.y += 7;
        position.x += 77;
        sfSprite_setPosition(objects->map.building_plots.build_menu.button_2.sprite, position);
        objects->map.building_plots.build_menu.button_2.position = position;
        position.x -= 77;
        position.y += 63;
        //position.x += 10;
        sfSprite_setPosition(
            objects->map.building_plots.build_menu.button_3.sprite, position);
        objects->map.building_plots.build_menu.button_3.position = position;
        objects->map.building_plots.build_menu.spot_nb = nb;
        objects->map.building_plots.build_menu.button_1.position = sfSprite_getPosition(objects->map.building_plots.build_menu.button_3.sprite);
        objects->map.building_plots.build_menu.button_1.position.y -= 63;
        sfSprite_setPosition(objects->map.building_plots.build_menu.button_1.sprite, objects->map.building_plots.build_menu.button_1.position);
        position.x += 77;
        sfSprite_setPosition(objects->map.building_plots.build_menu.button_4.sprite, position);
        objects->map.building_plots.build_menu.button_4.position = position;
        //printf("position: x->%f y->%f\n", objects->map.building_plots.total, spot.position.x, spot.position.y);
        objects->interaction.mouse1_is_held = 1;
    } else if (spot.is_hovered == 0) {
        sfSprite_setScale(spot.tile, up);
        spot.is_hovered = 1;
    }
}

void handle_tower_interaction(objects_t *objects, spots_t spot, int nb)
{
    sfVector2f position = spot.position;

    if (spot.is_hovered == 0) {
        sfVector2f up = {1.1, 1.1};
        sfSprite_setScale(spot.tile, up);
    }
    if (sfMouse_isButtonPressed(sfMouseLeft) &&
        objects->interaction.mouse1_is_held == 0) {
        sfMusic_stop(objects->click);
        sfMusic_play(objects->click);
        objects->interaction.mouse1_is_held = 1;
        set_all_buttons_to_default(objects);
        objects->map.building_plots.build_menu.is_active = 0;
        objects->map.building_plots.upgrade.is_active = 1;
        position.x -= 20;
        position.y -= 30;
        sfSprite_setPosition(objects->map.building_plots.upgrade.sprite,
            position);
        position = spot.position;
        position.x += 32;
        position.y -= 32;
        sfSprite_setPosition(objects->map.building_plots.upgrade.quit.sprite,
            position);
        objects->map.building_plots.upgrade.quit.position = position;
        position.x += 2;
        position.y += 105;
        sfSprite_setPosition(objects->map.building_plots.upgrade.sell.sprite, position);
        sfVector2f position = spot.position;
        position.y -= 2;
        position.x += 2;
        sfSprite_setPosition(objects->map.building_plots.upgrade.button_1.sprite,
            position);
        objects->map.building_plots.upgrade.button_1.position = position;
        objects->map.building_plots.upgrade.spot_nb = nb;
        if (SELECTED_TOWER_U.type == 1 || SELECTED_TOWER_U.type == 0) {
            position.x += 75;
            sfSprite_setPosition(
                objects->map.building_plots.upgrade.button_2.sprite, position);
            if (SELECTED_TOWER_U.special_attributes.is_ability_locked == 0)
                sfSprite_setTextureRect(objects->map.building_plots.upgrade.button_2.sprite, objects->map.building_plots.upgrade.button_2.rects[0]);
        }
        if (SELECTED_TOWER_U.type == 0)
            sfSprite_setPosition(objects->map.building_plots.druid_arrow_mark_sprite, SELECTED_TOWER_U.projectile.destination);
        display_button_cost(&objects->map.building_plots.upgrade.button_1, &objects->map.building_plots.spots[nb].tower);
        display_sell_button_value(&objects->map.building_plots.upgrade.sell, &objects->map.building_plots.spots[nb].tower);
        objects->game_interface.tower_stats.display_radius = display_radius(spot.tower, spot, objects->map.building_plots.upgrade.radius_sprite, 0);
        objects->game_interface.tower_stats.is_active = 1;
        objects->game_interface.tower_stats.is_preview = 0;
        display_tower_stats(objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower, &objects->game_interface.tower_stats, objects->map.building_plots, objects->map.building_plots.tower_textures[objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower.type]);
    }
}

void handle_upgrade_menu(sfRenderWindow *window, objects_t *objects)
{
    sfVector2f up = {1.1, 1.1};
    sfVector2f def = {1.0, 1.0};
    handle_menu_quit_button(window, objects, &objects->map.building_plots.upgrade);
    handle_tower_remove_button(objects, &objects->map.building_plots.upgrade.sell, window);
    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), objects->map.building_plots.upgrade.button_1.position, 30, 30)) {
        if (objects->map.building_plots.upgrade.button_1.is_hovered == 0) {
            sfSprite_setScale(
                objects->map.building_plots.upgrade.button_1.sprite, up);
            objects->map.building_plots.upgrade.button_1.is_hovered = 1;
        }
        if (objects->interaction.mouse1_is_held == 0 &&
            sfMouse_isButtonPressed(sfMouseLeft)) {
            sfMusic_stop(objects->click);
            sfMusic_play(objects->click);
            objects->interaction.mouse1_is_held = 1;
            if (objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower.level >= 2 || objects->game_interface.money_count < objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower.stats_arr[objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower.level + 1].cost) {
                objects->map.building_plots.upgrade.button_1.is_confirm = 2;//sfSprite_setTextureRect(objects->map.building_plots.upgrade.button_1.sprite, objects->map.building_plots.upgrade.button_1.rects[2]);
                display_tower_stats_preview(objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower, &objects->game_interface.tower_stats, objects->map.building_plots, objects->map.building_plots.tower_textures[objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower.type]);
                objects->game_interface.tower_stats.display_radius = display_radius(objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower, objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb], objects->map.building_plots.upgrade.radius_preview_sprite, 1);
            }
            else if (objects->map.building_plots.upgrade.button_1.is_confirm == 0) {
                objects->map.building_plots.upgrade.button_1.is_confirm = 1;
                display_tower_stats_preview(objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower, &objects->game_interface.tower_stats, objects->map.building_plots, objects->map.building_plots.tower_textures[objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower.type]);
                objects->game_interface.tower_stats.display_radius = display_radius(objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower, objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb], objects->map.building_plots.upgrade.radius_preview_sprite, 1);
            }
            else {
               handle_upgrade_button (objects, &objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower, objects->map.building_plots.upgrade, &objects->game_interface);
                objects->game_interface.tower_stats.display_radius = display_radius(objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower, objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb], objects->map.building_plots.upgrade.radius_sprite, 0);
                objects->map.building_plots.upgrade.button_1.is_confirm = 0;
            }
            sfSprite_setTextureRect(
                objects->map.building_plots.upgrade.button_1.sprite,
                objects->map.building_plots.upgrade.button_1.rects[objects->map.building_plots.upgrade.button_1.is_confirm]);
        }
    } else if (objects->map.building_plots.upgrade.button_1.is_hovered == 1) {
        sfSprite_setScale(objects->map.building_plots.upgrade.button_1.sprite,
            def);
        objects->map.building_plots.upgrade.button_1.is_hovered = 0;
    }
    if (objects->map.building_plots.upgrade.button_2.is_confirm == 1 && SELECTED_TOWER_U.special_attributes.is_ability_locked == 0) {
        if (SELECTED_TOWER_U.type == 1)
        create_ally_if_possible(&objects->map.building_plots, &SELECTED_TOWER_U,
            sfMouse_getPositionRenderWindow(window), objects);
        if (SELECTED_TOWER_U.type == 0 && sfMouse_isButtonPressed(sfMouseLeft) && SELECTED_TOWER_U.projectile.is_active == 0) {
            SELECTED_TOWER_U.projectile.destination = get_positon_of_clicked_tile_if_possible(sfMouse_getPositionRenderWindow(window), objects);
            SELECTED_TOWER_U.projectile.destination.y -= 175;
            sfSprite_setPosition(SELECTED_TOWER_U.projectile.sprite, SELECTED_TOWER_U.projectile.destination);
            sfSprite_setPosition(objects->map.building_plots.druid_arrow_mark_sprite, SELECTED_TOWER_U.projectile.destination);
        }
    }
    else if ((SELECTED_TOWER_U.type == 1 || SELECTED_TOWER_U.type == 0) && SELECTED_TOWER_U.special_attributes.is_ability_locked == 0 && check_button_interaction(&objects->map.building_plots.upgrade.button_2, window, 30, 30) && objects->interaction.mouse1_is_held == 0) {
        objects->interaction.mouse1_is_held = 1;
        sfSprite_setColor(objects->map.building_plots.upgrade.button_2.sprite, sfGreen);
        objects->map.building_plots.upgrade.button_2.is_confirm = 1;
    }
}

void handle_tower_remove_button(objects_t *objects, button_t *remove, sfRenderWindow *window)
{
    sfVector2f up = {1.1, 1.1};
    sfVector2f def = {1.0, 1.0};

    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), sfSprite_getPosition(remove->sprite), 32, 32)) {
        if (remove->is_hovered == 0) {
            sfSprite_setScale(remove->sprite, up);
            remove->is_hovered = 1;
        }
        if (sfMouse_isButtonPressed(sfMouseLeft) && objects->interaction.mouse1_is_held == 0) {
            sfMusic_stop(objects->click);
            sfMusic_play(objects->click);
            objects->interaction.mouse1_is_held = 1;
            if (remove->is_confirm == 0) {
                remove->is_confirm = 1;
            } else {
                remove_tower(&objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb], \
&objects->game_interface, &objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower, &objects->map.building_plots);
                remove->is_confirm = 0;
            }
        }
        sfSprite_setTextureRect(remove->sprite, remove->rects[remove->is_confirm]);
    } else if (remove->is_hovered == 1) {
        sfSprite_setScale(remove->sprite, def);
        remove->is_hovered = 0;
    }
}

void remove_tower(spots_t *spot, game_interface_t *interface, tower_t *tower, building_plots_t * plots)
{
    int total_value = 0;

    for (int i = 0; i <= tower->level; i++)
        total_value += tower->stats_arr[i].cost;
    interface->money_count += total_value / 3;
    spot->is_filled = 0;
    sfSprite_setTexture(spot->tile, plots->texture, sfTrue);
    sfSprite_setPosition(spot->tile, spot->position);
    display_money_count(interface);
    plots->upgrade.is_active = 0;
}

void handle_upgrade_button(objects_t *objects, tower_t *tower, upgrade_menu_t menu, game_interface_t *interface)
{
    if (tower->level < 2)
    {
        tower->level++;
        sfSprite_setTextureRect(objects->map.building_plots.spots[menu.spot_nb].tile, objects->map.building_plots.tower_rects[tower->type][tower->level]);
        objects->game_interface.tower_stats.is_preview = 0;
        display_tower_stats(objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower, &objects->game_interface.tower_stats, objects->map.building_plots, objects->map.building_plots.tower_textures[objects->map.building_plots.spots[objects->map.building_plots.upgrade.spot_nb].tower.type]);
        tower->projectile.damage = tower->stats_arr[tower->level].damage;
        tower->projectile.radius = tower->stats_arr[tower->level].splash_radius;
        interface->money_count -= tower->stats_arr[tower->level].cost;
        display_money_count(interface);
        display_button_cost(&objects->map.building_plots.upgrade.button_1, tower);
        display_sell_button_value(&objects->map.building_plots.upgrade.sell, tower);
        //printf("upgrade cost: %d\n", tower->stats_arr[tower->level].cost);
    }
    //else
    //    sfSprite_setTextureRect(menu.button_1.sprite, menu.button_1.rects[2]);
}

void handle_building_menu(sfRenderWindow *window, objects_t *objects)
{
    handle_menu_quit_button(window, objects, &objects->map.building_plots.build_menu);
    handle_buy_button(&objects->map.building_plots.build_menu.button_1, window, &objects->map.building_plots.druid_tower, objects);
    handle_buy_button(&objects->map.building_plots.build_menu.button_2, window, &objects->map.building_plots.tavern_template, objects);
    handle_buy_button(&objects->map.building_plots.build_menu.button_3, window, &objects->map.building_plots.fire_mage, objects);
    handle_buy_button(&objects->map.building_plots.build_menu.button_4, window, &objects->map.building_plots.stone_preview, objects);
}

void handle_buy_button(button_t *button, sfRenderWindow *window, tower_t *tower, objects_t *objects)
{

    sfVector2f up = {1.1, 1.1};
    sfVector2f def = {1.0, 1.0};
    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), button->position, 30, 30)) {
        sfSprite_setScale(
            button->sprite, up);
        button->is_hovered = 1;
        if (objects->interaction.mouse1_is_held == 0 &&
            sfMouse_isButtonPressed(sfMouseLeft)) {
            sfMusic_stop(objects->click);
            sfMusic_play(objects->click);
            objects->interaction.mouse1_is_held = 1;
            if (button->type != 1) {
                objects->map.building_plots.build_menu.button_1.is_confirm = 0;
                sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_1.sprite, objects->map.building_plots.build_menu.button_1.rects[0]);
            }
            if (button->type != 2) {
                objects->map.building_plots.build_menu.button_2.is_confirm = 0;
                sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_2.sprite, objects->map.building_plots.build_menu.button_2.rects[0]);
            }
            if (button->type != 3) {
                objects->map.building_plots.build_menu.button_3.is_confirm = 0;
                sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_3.sprite, objects->map.building_plots.build_menu.button_3.rects[0]);
            }
            if (button->type != 4) {
                objects->map.building_plots.build_menu.button_4.is_confirm = 0;
                sfSprite_setTextureRect(objects->map.building_plots.build_menu.button_4.sprite, objects->map.building_plots.build_menu.button_4.rects[0]);
            }
            if ((button->type == 1 && objects->game_interface.money_count < 75) || (button->type == 2 && objects->game_interface.money_count < 100) || (button->type == 3 && objects->game_interface.money_count < 125) || (button->type == 4 && objects->game_interface.money_count < 160)) {
                button->is_confirm = 2;
                display_tower_stats(*tower, &objects->game_interface.tower_stats, objects->map.building_plots, objects->map.building_plots.tower_textures[tower->type]);
                objects->game_interface.tower_stats.display_radius = display_radius(*tower, objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb], objects->map.building_plots.upgrade.radius_sprite, 0);
            }
            else if (button->is_confirm == 0) {
                button->is_confirm = 1;
                display_tower_stats(*tower, &objects->game_interface.tower_stats, objects->map.building_plots, objects->map.building_plots.tower_textures[tower->type]);
                objects->game_interface.tower_stats.display_radius = display_radius(*tower, objects->map.building_plots.spots[objects->map.building_plots.build_menu.spot_nb], objects->map.building_plots.upgrade.radius_sprite, 0);
            }
            else {
                create_new_tower(objects, *tower);
                button->is_confirm = 0;
            }
            sfSprite_setTextureRect(button->sprite, button->rects[button->is_confirm]);
        }
    } else if (button->is_hovered == 1) {
        sfSprite_setScale(button->sprite,
            def);
        button->is_hovered = 0;
    }
}

void handle_menu_quit_button(sfRenderWindow *window, objects_t *objects, upgrade_menu_t *menu)
{
    sfVector2f up = {1.1, 1.1};
    sfVector2f def = {1.0, 1.0};
    if (is_collision_cursor_button(sfMouse_getPositionRenderWindow(window), menu->quit.position, 30, 30)) {
        if (menu->quit.is_hovered == 0) {
            sfSprite_setScale(
                menu->quit.sprite, up);
            menu->quit.is_hovered = 1;
        }
        if (objects->interaction.mouse1_is_held == 0 &&
            sfMouse_isButtonPressed(sfMouseLeft)) {
            sfMusic_stop(objects->click);
            sfMusic_play(objects->click);
            objects->interaction.mouse1_is_held = 1;
            menu->is_active = 0;
            objects->game_interface.tower_stats.is_active = 0;
            objects->game_interface.tower_stats.is_preview = 0;
            set_all_buttons_to_default(objects);
        }
    } else if (menu->quit.is_hovered == 1) {
        sfSprite_setScale(menu->quit.sprite,
            def);
        menu->quit.is_hovered = 0;
    }
}