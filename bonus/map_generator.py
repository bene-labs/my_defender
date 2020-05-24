#!/usr/bin/python3

from math import *
from sys import *
from random import *
import time

seed()


def print_map(my_map, nb_of_map, prefix):
    filename = prefix + "_" + str(nb_of_map)
    my_file = open("maps/" + filename, 'w')
    # print(filename)
    for i in range(len(my_map)):
        for j in range(len(my_map[i])):
            my_file.write(my_map[i][j])
        my_file.write("\n")
    my_file.close()


def keep_in_range(x, lowest, highest):
    if x < lowest:
        return lowest
    if x > highest:
        return highest
    return x


def rec_pathfinder(my_map, last_x, last_y, goal_x, goal_y, path):
    seed()
    if last_x == goal_x and last_y == goal_y:
        return
    okay = False
    old_x = last_x
    old_y = last_y
    while not okay:
        last_x = old_x
        last_y = old_y
        if randint(0, 1) > 0:
            delta = -1
        else:
            delta = 1
        if randint(0, 1) > 0:
            last_x += delta
        else:
            last_y += delta
        last_x = keep_in_range(last_x, 1, 7)
        last_y = keep_in_range(last_y, 1, 18)
        if sqrt((last_x - goal_x)**2 + (last_y - goal_y)**2) < sqrt((old_x - goal_x)**2 + (old_y - goal_y)**2):
            okay = True
    my_map[last_x][last_y] = path
    rec_pathfinder(my_map, last_x, last_y, goal_x, goal_y, path)
    return


def set_path(my_map):
    seed()
    start_left = randint(1, 7)
    end_right = 8 - start_left
    if end_right == 4:
        end_right += 1
    start_right = randint(1, 4)
    while abs(end_right - start_right) <= 1:
        end_right = randint(4, 7)
    end_bot = randint(1, 14)
    start_top2 = randint(7, 16)
    end_left = randint(3, 7)
    while abs(end_left - start_left) <= 1:
        end_left = randint(3, 7)
    my_map[start_left][0] = '*'
    my_map[start_left][1] = 'X'
    my_map[end_right][18] = '#'
    my_map[end_right][19] = '-'
    my_map[start_right][18] = '*'
    my_map[start_right][19] = '-'
    my_map[start_right][17] = 'X'
    my_map[8][end_bot] = '#'
    my_map[0][start_top2] = '*'
    my_map[1][start_top2] = 'X'
    my_map[end_left][0] = '#'
    rec_pathfinder(my_map, 0 + 1, start_top2, end_left, 0 + 1, 'X')
    rec_pathfinder(my_map, start_left, 0 + 1, end_right, 18 - 1, 'X')
    rec_pathfinder(my_map, start_right, 18 - 1, 8 - 1, end_bot, 'X')


def is_tile(up, down, left, right, i, j, my_map):
    if (my_map[i - 1][j] != ' ') == up and (my_map[i + 1][j] != ' ') == down and (my_map[i][j - 1] != ' ') == left and (my_map[i][j + 1] != ' ') == right:
        return True
    return False

def mapify(my_map):
    for i in range(1, len(my_map) - 1):
        for j in range(1, len(my_map[i]) - 2):
            if my_map[i][j] != ' ':
                if is_tile(True, True, False, False, i, j, my_map):
                    my_map[i][j] = '|'    # | way
                elif is_tile(False, False, True, True, i, j, my_map):
                    my_map[i][j] = '-'    # - way
                elif is_tile(False, True, False, True, i, j, my_map):
                    my_map[i][j] = '0'
                elif is_tile(False, True, True, False, i, j, my_map):
                    my_map[i][j] = '1'
                elif is_tile(True, False, False, True, i, j, my_map):
                    my_map[i][j] = '2'
                elif is_tile(True, False, True, False, i, j, my_map):
                    my_map[i][j] = '3'
                elif is_tile(False, True, True, True, i, j, my_map):
                    my_map[i][j] = '4'
                elif is_tile(True, True, True, False, i, j, my_map):
                    my_map[i][j] = '5'
                elif is_tile(True, False, True, True, i, j, my_map):
                    my_map[i][j] = '6'
                elif is_tile(True, True, False, True, i, j, my_map):
                    my_map[i][j] = '7'
                elif is_tile(True, True, True, True, i, j, my_map):
                    my_map[i][j] = '8'
                else:
                    my_map[i][j] = ' '  # should never be reached!


def count_T(my_map):
    res = 0
    for i in range(len(my_map)):
        for j in range(len(my_map[i])):
            if my_map[i][j] == '4' or my_map[i][j] == '5' or my_map[i][j] == '6' or my_map[i][j] == '7':
                res += 1
    return res


def is_adjacent(i, j, my_map):
    for k in range(i - 1, i + 1):
        for l in range(j - 1, j + 1):
            try:
                if not (k == i and l == j) and 0 <= int(my_map[k][l]) <= 8:
                    return True
            except ValueError:
                if not (k == i and l == j) and (my_map[k][l] == '-' or my_map[k][l] == '|'):
                    return True
    return False


def surround_house(my_map, i, j):
    for k in range(i - 1, i + 2):
        for l in range(j - 1, j + 2):
            if my_map[k][l] == ' ':
                switch_2 = randint(0, 4)
                if switch_2 == 0:
                    my_map[k][l] = 'l'
                if switch_2 == 1:
                    my_map[k][l] = 't'
                if switch_2 == 2:
                    my_map[k][l] = 'x'
                if switch_2 == 3:
                    my_map[k][l] = 'y'
                if switch_2 == 4:
                    my_map[k][l] = 'v'


def add_decorations(my_map):
    for i in range(1, len(my_map) - 1):
        for j in range(1, len(my_map[i]) - 2):
            if my_map[i][j] == ' ' and is_adjacent(i, j, my_map):
                if randint(0, 10) > 3:
                    my_map[i][j] = '+'
            elif my_map[i][j] == ' ' and randint(0, 10) > 5:
                switch = randint(0, 13)
                if switch == 0:
                    my_map[i][j] = 'i'
                elif switch == 1:
                    my_map[i][j] = 'j'
                elif switch == 2:
                    my_map[i][j] = 'k'
                elif switch == 3:
                    my_map[i][j] = 'm'
                elif switch == 4:
                    my_map[i][j] = 'n'
                elif switch == 5:
                    my_map[i][j] = 'p'
                    surround_house(my_map, i, j)
                elif switch == 6:
                    my_map[i][j] = 'r'
                elif switch == 7:
                    my_map[i][j] = 's'
                elif switch == 8:
                    my_map[i][j] = 't'
                elif switch == 9:
                    my_map[i][j] = 'u'
                elif switch == 10:
                    my_map[i][j] = 'v'
                elif switch == 11:
                    my_map[i][j] = 'w'
                elif switch == 12:
                    my_map[i][j] = 'x'
                elif switch == 13:
                    my_map[i][j] = 'p'
                    surround_house(my_map, i, j)
            if randint(0, 6) == 0 and my_map[i][j] == ' ' and my_map[i + 1][j] == ' ' and my_map[i][j - 1] == ' ' and my_map[i + 1][j - 1] == ' ':
                my_map[i][j] = 'B'
                my_map[i + 1][j] = 'D'
                my_map[i][j - 1] = 'A'
                my_map[i + 1][j - 1] = 'C'
            if randint(0, 2) == 0 and my_map[i][j] == ' ' and my_map[i + 1][j] == ' ' and my_map[i][j - 1] == ' ' and my_map[i + 1][j - 1] == ' ':
                my_map[i][j] = 'F'
                my_map[i + 1][j] = 'H'
                my_map[i][j - 1] = 'E'
                my_map[i + 1][j - 1] = 'G'


def gen_wave(wave):
    enemies = []
    for i in range(10):
        enemies.append(randint(0, 9))
    for i in range(round(len(wave) / 2 - 35)):
        wave[randint(0, len(wave) - 1)] = enemies[randint(0, len(enemies) - 1)]


def gen_waves():
    nb_waves = randint(4,7)
    my_file = open("waves/rand_waves", 'w')
    wave_len = randint(90, 100)
    for i in range(nb_waves):
        wave = []
        for j in range(wave_len):
            wave.append('.')
        gen_wave(wave)
        for j in range(wave_len - 1):
            my_file.write(str(wave[j]))
        my_file.write("\n")
        wave_len = round(wave_len * 1.2)
    my_file.close()


def main():
    rows = 9
    cols = 20
    if len(argv) > 2:
        nb_of_maps = int(argv[1])
        prefix = argv[2]
    else:
        nb_of_maps = 1
        prefix = "map"
    for i in range(nb_of_maps):
        map_okay = False
        while not map_okay:
            my_map = [list(' ' * cols) for i in range(rows)]
            set_path(my_map)
            mapify(my_map)
            add_decorations(my_map)
            if count_T(my_map) <= 3:
                print_map(my_map, i, prefix)
                map_okay = True
    gen_waves()

main()
