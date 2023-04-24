#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
    char    *north_path;
    char    *south_path;
    char    *west_path;
    char    *east_path;
    int     f_colors[3];
    int     c_colors[3];

    int     map_width;
    int     map_height;
    char    **map;

    int     player_pos[2];
    char    player_dir;
}   t_map;

#endif