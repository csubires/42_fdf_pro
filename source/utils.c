/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/26 16:37:57 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#include <math.h>
#include <stdbool.h>

#include <stdlib.h>
#include <time.h>

#define WIDTH 1920
#define HEIGHT 1080
#define ALIVE_COLOR 0xFFFFFF  // Color blanco para las células vivas
#define DEAD_COLOR 0x000000   // Color negro para las células muertas

#define Z_CAMERA 1000 // Posición del observador en el eje Z


void	error_and_exit(const char *func, const char *msg)
{
	printf("Error in function \"%s\": %s", func, msg);
	exit(-1);
}

void	free_all(t_fdfs *fdfs)
{
	mlx_delete_image(fdfs->mlx, fdfs->img);
	mlx_delete_image(fdfs->mlx, fdfs->menu);
	free_map(fdfs->map);
	if (fdfs->img)
		free(fdfs->img);
	if (fdfs->menu)
		free(fdfs->menu);
	free(fdfs);
}

void	isometric(t_fdfs *fdfs, int *x, int *y, int z)
{
	int	tmp_x;
	int	tmp_y;

	if (!fdfs->state.zenith)
		return ;
	tmp_x = *x;
	tmp_y = *y;
	*x = (tmp_x - tmp_y) * cos(DEGREE_30);
	*y = -z + (tmp_x + tmp_y) * sin(DEGREE_30);
}

t_point	new_point(int x, int y, t_fdfs *fdfs)
{
	t_point	new;

	new.x = x;
	new.y = y;
	new.z = fdfs->map->z_gen[y][x];
	if (fdfs->map->has_color)
		new.color = fdfs->map->color_file[y][x];
	else
		new.color = gen_gradient(fdfs, new.z);
	return (new);
}

void	mode_strange(t_fdfs *fdfs, int *x, int *y, int z)
{
	// Coordenadas esféricas
	double theta = (*x / (double)(fdfs->map->width - 1)) * M_PI;
	double phi = (*y / (double)(fdfs->map->height - 1)) * 2 * M_PI;
	// Altura y radio
	double r = fdfs->zoom + z; // R es el radio base

	// Coordenadas en la esfera
	*x = (int)(r * sin(theta) * cos(phi));
	*y = (int)(r * sin(theta) * sin(phi));
	*x += WIN_W / 2;
	*y += WIN_H / 2;

}

void	mode_strange00(t_fdfs *fdfs, int *x, int *y, int *z)
{
	float r = 10.0;
	float x_norm = 2 * *x  / (fdfs->map->width - 1) - 1;
    float y_norm = 2 * *y / (fdfs->map->height - 1) - 1;
    float theta = x_norm * M_PI;
    float phi = y_norm * (M_PI / 2);

	*x = r * cos(phi) * cos(theta);
	*y = r * cos(phi) * sin(theta);
	*z = r * sin(phi);

}

void	sphere(t_fdfs *fdfs, int *x, int *y, int *z)
{
	/*
	double r = sqrt((pow((double)x, 2)) + pow((double)y, 2) + pow((double)z, 2));
	float x_norm = 2 * *x  / (fdfs->map->width - 1) - 1;
    float y_norm = 2 * *y / (fdfs->map->height - 1) - 1;
    float theta = x_norm * M_PI;
    float phi = y_norm * (M_PI / 2);
	*x = r * cos(phi) * cos(theta);
	*y = r * cos(phi) * sin(theta);
	*/
	double theta = (*x / (double)(fdfs->map->width - 1)) * M_PI;
	double phi = (*y / (double)(fdfs->map->height - 1)) * 2 * M_PI;
	//	(void)fdfs;
	//double theta = atan(*y / *x);
	//double phi = atan(*z / sqrt((*x^2) + (*y^2)));
	double r = RADIX + sqrt((*x^2) + (*y^2) + (*z^2));
	//double r = sqrt ((*x^2) + (*y^2) + (*z^2));
	//x_norm = r * cos (theta);
	//*y = r * sin (theta);
	*x = (int)(r * cos (phi) * cos (theta));
	*y = (int)(r * cos (phi) * sin (theta));
	//*z = (int)(r * sin (phi));
	*x += WIN_W / 2;
	*y += WIN_H / 2;
}

/*
void	cilindro(t_fdfs *fdfs, int *x, int *y, int *z)
{
	(void)z;
	double theta = (*x / (double)(fdfs->map->width - 1)) * M_PI;
	double phi = (*y / (double)(fdfs->map->height - 1)) * 2 * M_PI;
	double r = RADIX; // + sqrt((*x^2) + (*y^2));

	*x = (int)(r * cos (theta));
	*y = (int)(r * sin (phi));
	*z = (int)(r * sin (phi));
	*x += WIN_W / 2;
	*y += WIN_H / 2;
}
*/

bool es_visible(int x, int y, int z)
{
	(void)y;
    // Calcular la distancia desde el observador al punto en el cilindro
    double dist_x = x - WIN_W / 2;
    double dist_z = Z_CAMERA - z;
    double angulo = atan2(dist_x, dist_z);  // Ángulo del punto desde el observador

    // El cilindro visible estará entre -PI/2 y PI/2
    return (angulo > -M_PI / 2 && angulo < M_PI / 2);
}

void cilindro(t_fdfs *fdfs, int *x, int *y, int *z)
{
    double theta = (*x / (double)(fdfs->map->width - 1)) * 2 * M_PI; // Escalar x para obtener el ángulo alrededor del cilindro
    double r = RADIX;  // Usar un radio fijo para el cilindro

    // Convertir coordenadas cartesianas a coordenadas cilíndricas
   // int tempX = *x; // Guardamos x temporalmente si necesitamos su valor original para cálculos adicionales
    *x = (int)(r * cos(theta)); // Calculamos la posición x en el cilindro
    *z = (int)(r * sin(theta)); // Calculamos la posición z en el cilindro

    // Ajustar la posición y al centro de la ventana
    *x += WIN_W / 2;
    *y = *y; // `y` permanece igual ya que no estamos cambiando su valor
    *z += WIN_H / 2; // Dependiendo del marco de referencia, ajustar z podría ser necesario
}


void	mode_strange01(t_fdfs *fdfs, int *x, int *y, int *z)
{
	(void)z;
	double theta = (*x / (double)(fdfs->map->width - 1)) * M_PI;
	double phi = (*y / (double)(fdfs->map->height - 1)) * 2 * M_PI;
	double r = RADIX; // + sqrt((*x^2) + (*y^2));

	*x = (int)(r * cos (theta));
	*y = (int)(r * sin (phi));
	*z = (int)(r * sin (phi));
	*x += WIN_W / 2;
	*y += WIN_H / 2;
}

t_point	set_changes(t_fdfs *fdfs, t_point point)
{
	if (fdfs->state.mod_04)
		mode_strange00(fdfs, &point.x, &point.y, &point.z);

	point.x *= fdfs->zoom;
	point.y *= fdfs->zoom;
	point.z *= (fdfs->zoom / 10) * fdfs->flat;
	rotate_x(fdfs, &point.y, &point.z);
	rotate_y(fdfs, &point.x, &point.z);
	rotate_z(fdfs, &point.x, &point.y);
	if (!fdfs->state.mod_03)
		isometric(fdfs, &point.x, &point.y, point.z);
	point.x += fdfs->step_x;
	point.y += fdfs->step_y;
	if (fdfs->state.mod_00)
		sphere(fdfs, &point.x, &point.y, &point.z);
	if (fdfs->state.mod_01)
		cilindro(fdfs, &point.x, &point.y, &point.z);
	if (fdfs->state.mod_02)
		mode_strange(fdfs, &point.x, &point.y, point.z);
	if (fdfs->state.mod_03)
		mode_strange01(fdfs, &point.x, &point.y, &point.z);
	return (point);
}

void	reset_fdfs(t_fdfs *fdfs)
{
	fdfs->zoom = ft_maximum((WIN_W / fdfs->map->width / 2), (WIN_H / fdfs->map->height / 2));
	fdfs->step_x = WIN_W / 2;
	fdfs->step_y = (WIN_H - fdfs->map->height * fdfs->zoom) / 2;
	fdfs->flat = 1 + (fdfs->zoom / fdfs->map->max_z);
	fdfs->rotate_x = 0;
	fdfs->rotate_y = 0;
	fdfs->rotate_z = 0;
	fdfs->state.menu = 0;
	fdfs->state.zenith = 1;
	fdfs->state.bg_color = 0x000000FF;
	fdfs->state.dark_zero = 0;
	fdfs->state.disable_clean = 0;
	fdfs->state.extra_pixel = 0;
	fdfs->state.mirror = 0;
	fdfs->state.desplace = 0;

	fdfs->state.one_color = 0;
	fdfs->state.rnd_color = 0;
	fdfs->state.map_color = 0;
	fdfs->state.multi_color = 0;
	fdfs->state.live = 0;
	fdfs->state.clon = 0;

	fdfs->state.mod_00 = 0;
	fdfs->state.mod_01 = 0;
	fdfs->state.mod_02 = 0;
	fdfs->state.mod_03 = 0;
	fdfs->state.mod_04 = 0;
	set_palette(&fdfs->state.palette, 1);
}




// ------------------------------------------------


// Inicializa la cuadrícula con células vivas y muertas aleatoriamente
void initialize_grid(int grid[WIDTH][HEIGHT]) {
    for (int y = 1; y < HEIGHT; y++) {
        for (int x = 1; x < WIDTH; x++) {
            grid[x][y] = rand() % 2;  // 0 para muerto, 1 para vivo
        }
    }
}

// Cuenta los vecinos vivos alrededor de la celda en la posición (x, y)
int count_alive_neighbors(int grid[WIDTH][HEIGHT], int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;  // No contarse a sí mismo
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

// Calcula la siguiente generación del Juego de la Vida
void next_generation(int current[WIDTH][HEIGHT], int next[WIDTH][HEIGHT]) {
    for (int y = 1; y < HEIGHT; y++) {
        for (int x = 1; x < WIDTH; x++) {
            int alive_neighbors = count_alive_neighbors(current, x, y);
            if (current[x][y] == 1) {  // La celda está viva
                if (alive_neighbors < 2 || alive_neighbors > 3) {
                    next[x][y] = 0;  // Muere por soledad o sobrepoblación
                } else {
                    next[x][y] = 1;  // Sobrevive
                }
            } else {  // La celda está muerta
                if (alive_neighbors == 3) {
                    next[x][y] = 1;  // Nace una nueva celda
                } else {
                    next[x][y] = 0;  // Permanece muerta
                }
            }
        }
    }
}

// Dibuja la cuadrícula en la imagen usando mlx_put_pixel
void draw_grid(mlx_image_t *img, int grid[WIDTH][HEIGHT]) {
    for (int y = 1; y < HEIGHT; y++) {
        for (int x = 1; x < WIDTH; x++) {
            int color = (grid[x][y] == 1) ? ALIVE_COLOR : DEAD_COLOR;
			if (is_into_screen(img, x, y))
            	mlx_put_pixel(img, x, y, color);
        }
    }
}

// Función principal para ejecutar el Juego de la Vida
void game_of_life(mlx_image_t *img)
{
    int current[WIDTH][HEIGHT];
    int next[WIDTH][HEIGHT];

    srand(time(NULL));  // Inicializa la semilla aleatoria
    initialize_grid(current);  // Inicializa la cuadrícula

    while (1) {  // Bucle infinito para generar generaciones continuamente
        draw_grid(img, current);  // Dibuja la cuadrícula actual
        next_generation(current, next);  // Calcula la siguiente generación

        // Copia la siguiente generación a la generación actual
        for (int y = 1; y < HEIGHT; y++) {
            for (int x = 1; x < WIDTH; x++) {
                current[x][y] = next[x][y];
            }
        }

		sleep(1);
        // Aquí puedes agregar un retraso para ver la animación en tiempo real
        // Por ejemplo, usando usleep(100000) para 0.1 segundos de retraso
    }
}
