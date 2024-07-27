# FDF


https://github.com/glfw/glfw
https://github.com/codam-coding-college/MLX42

## Descripción
Este proyecto se trata de la creación de un simple
modelo de estructura alámbrica de un paisaje.
conceptos básicos de la programación gráfica, especialmente cómo colocar puntos en
el espacio, unirlos entre ellos y, lo más importante, cómo ver la escena desde un punto de
vista especifico.
Este proyecto se trata de la creación de un simple modelo de estructura alámbrica
con una representación en 3D de un paisaje uniendo varios puntos (x, y, z) gracias a
los segmentos de lineas (edge).
Wireframe es un algoritmo de renderización del que resulta una imagen semitransparente, de la cual solo se dibujan las aristas de la malla que constituye al objeto modelado.

## Funciones autorizadas
open, close, read, write,
malloc, free, perror,
strerror, exit
• Todas las funciones de la
librería math (-lm opción del
compilador, man 3 math)
• Todas las funciones de la
librería MiniLibX
• ft_printf y cualquier función
que TÚ hayas programado

## Restricciones
debes utilizar la MiniLibX
El uso de variables globales están prohibidas.
los mapas se pasarán como unico argumento mediante archivos .fdf
¡Ten en cuenta que el objetivo de este proyecto no es analizar mapas! Sin embargo, esto
no significa que tu programa deba tener algún tipo de crash cuando se ejecuta. Significa
que asumimos que el mapa contenido en el archivo tiene el formato correcto.
• Tu programa tiene que mostrar la imagen en una ventana.
• La gestión de su ventana debe permanecer fluida (cambiando de ventanas, mini-
mizando, etc).
• Al presionar ESC se debe cerrar la ventana y terminar el programa de forma limpia.
• Al hacer click en la x en el marco de la ventana se debe cerrar la ventana y terminar
el programa de forma limpia.
• El uso de las imágenes de la MiniLibX es obligatoria.

## Conceptos clave
Uno de los problemas al empezar este proyecto es que no sabes por donde empezar. Ahí van algunos conceptos a investigar:
wireframe
Proyección isométrica
segmentos de lineas
wireframe
Bresenham's line algorithm
interpolacion lineal
paralelaje
matriz de proyeccion

## Mapa FDF
Cada número representa un punto en el espacio:
• La posición horizontal corresponde a su eje.
• La posición vertical corresponde a su eje de coordenada Y.
• El valor corresponde a su altitud.

## BONUS
Obtendrás algunos puntos extras si puedes:
• Incluir una proyección extra (como paralela o cónica)
• Acercar y alejar.
• Trasladar tu modelo.
• Rotar tu modelo.
• Añade un bonus más de tu elección.


https://anzeljg.github.io/rin2/book2/2405/docs/tkinter/key-names.html
https://learnwebgl.brown37.net/08_projections/projections_ortho.html
https://www.cs.uic.edu/~jbell/CourseNotes/ComputerGraphics/3DTransforms.html
https://docs.hektorprofe.net/graficos-3d/17-matriz-de-proyeccion/

https://github.com/ailopez-o/42Barcelona-FdF
https://github.com/duarte3333

https://rgbcolorcode.com/color/008000
https://www.rgbtohex.net/

Map Generator
https://github.com/jgigault/42MapGenerator



https://www.youtube.com/results?search_query=bresenham

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fdf_bonus maps/42.fdf

https://es.wikipedia.org/wiki/Modelo_de_estructura_al%C3%A1mbrica
https://github.com/jgigault/42MapGenerator



Comparación algoritmo BRESENHAM-DDA-LINEA
https://graficacion2017.wordpress.com/2017/08/14/algoritmos-dda-y-bresenham/
https://es.wikipedia.org/wiki/Algoritmo_de_Bresenham

meter
https://harm-smits.github.io/42docs/libs/minilibx/colors.html me tu readme
https://medium.com/@alaricsaltzman913/fdf-42-a-detailed-walkthrough-7184cca317fc

https://github.com/caroldaniel/42sp-cursus-fdf



https://www.youtube.com/watch?v=FDxxs6ZFPJs
W, ⬆️ 	Arriba
A, ⬅️ 	Izquierda
S, ⬇️ 	Abajo
D, ➡️
ESC ❌



int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);

https://github.com/f-corvaro/FDF
https://pulgamecanica.herokuapp.com/posts/mlx-animations
https://github.com/codam-coding-college/MLX42/blob/master/include/MLX42/MLX42.h


https://stackoverflow.com/questions/72756900/color-gradient-in-c


BRESENHAM
Utiliza puntos fijos es decir artmetica de numeros enteros

emplea unicamente las operaciones de suma y resta

es una codigo que se ejecuta de forma rrapida, ya que  los resiultados que arroja son enteros


no redondea las coordenadas pero toma el valor incremental en su operacion



DDS

utiliza puntos flotantes, aritmetica real

emplea  las operaciones de multiplicacion y division

tarda mas en efectuarse ppuesto que los resultados que arroja son flotantes

redondea las cooordenadas al numero entero que es mas cercano a la linea


UMNG

utiliza puntos flotantes y arimetica real

emplea todas las operaciones basicas

tarda cierto tiempo en completarse ya que sus resultados son flotantes

toma las coordenadas ingresadas y a partir de ese punto traza la linea sin aproximacion


vease
Algoritmo de línea de Xiaolin Wu:
Algoritmo de recorte de línea de Cohen-Sutherland:
Algoritmo de recorte de línea de Liang-Barsky:

http://www.nosolounix.com/2010/05/algoritmo-bresenham-dibujar-linea.html

# FDF

Poner marco
mlx_sync
get_screensize
set intro image
cambiar mapa sin cerrar
estadisticas - show
auto move + color
full screen enter
enum key ???

negative color
click bom
hook -> keylistener
keyevent == --
fdfs -> this self
mlx-loop-hookauto
mlx_fdf_file_to imag
auto zumm con mouse

saltar 1 pixel hacer mas eficiente??

difuminado alrededor de lineas
estrella muerte
galaxia
mode pandemic
shadow rts
on click move
modo sin ft_bzero


CAMBIAR COLOR BACKG
ALTITUDE DOBLE
PONER NIVEL 0 A NEGRO




('alt', <Key.alt: <65513>>),
                                           ('alt_l', <Key.alt: <65513>>),
                                           ('alt_r', <Key.alt_r: <65514>>),
                                           ('alt_gr', <Key.alt_gr: <65406>>),
                                           ('backspace',
                                            <Key.backspace: <65288>>),
                                           ('caps_lock',
                                            <Key.caps_lock: <65509>>),
                                           ('cmd', <Key.cmd: <65515>>),
                                           ('cmd_l', <Key.cmd: <65515>>),
                                           ('cmd_r', <Key.cmd_r: <65516>>),
                                           ('ctrl', <Key.ctrl: <65507>>),
                                           ('ctrl_l', <Key.ctrl: <65507>>),
                                           ('ctrl_r', <Key.ctrl_r: <65508>>),
                                           ('delete', <Key.delete: <65535>>),
                                           ('down', <Key.down: <65364>>),
                                           ('end', <Key.end: <65367>>),
                                           ('enter', <Key.enter: <65293>>),
                                           ('esc', <Key.esc: <65307>>),
                                           ('f1', <Key.f1: <65470>>),
                                           ('f2', <Key.f2: <65471>>),
                                           ('f3', <Key.f3: <65472>>),
                                           ('f4', <Key.f4: <65473>>),
                                           ('f5', <Key.f5: <65474>>),
                                           ('f6', <Key.f6: <65475>>),
                                           ('f7', <Key.f7: <65476>>),
                                           ('f8', <Key.f8: <65477>>),
                                           ('f9', <Key.f9: <65478>>),
                                           ('f10', <Key.f10: <65479>>),
                                           ('f11', <Key.f11: <65480>>),
                                           ('f12', <Key.f12: <65481>>),
                                           ('f13', <Key.f13: <65482>>),
                                           ('f14', <Key.f14: <65483>>),
                                           ('f15', <Key.f15: <65484>>),
                                           ('f16', <Key.f16: <65485>>),
                                           ('f17', <Key.f17: <65486>>),
                                           ('f18', <Key.f18: <65487>>),
                                           ('f19', <Key.f19: <65488>>),
                                           ('f20', <Key.f20: <65489>>),
                                           ('home', <Key.home: <65360>>),
                                           ('left', <Key.left: <65361>>),
                                           ('page_down',
                                            <Key.page_down: <65366>>),
                                           ('page_up', <Key.page_up: <65365>>),
                                           ('right', <Key.right: <65363>>),
                                           ('step', <Key.step: <65505>>),
                                           ('step_l', <Key.step: <65505>>),
                                           ('step_r', <Key.step_r: <65506>>),
                                           ('space', <Key.space: ' '>),
                                           ('tab', <Key.tab: <65289>>),
                                           ('up', <Key.up: <65362>>),
                                           ('media_play_pause',
                                            <Key.media_play_pause: <0>>),
                                           ('media_volume_mute',
                                            <Key.media_play_pause: <0>>),
                                           ('media_volume_down',
                                            <Key.media_play_pause: <0>>),
                                           ('media_volume_up',
                                            <Key.media_play_pause: <0>>),
                                           ('media_previous',
                                            <Key.media_play_pause: <0>>),
                                           ('media_next',
                                            <Key.media_play_pause: <0>>),
                                           ('insert', <Key.insert: <65379>>),
                                           ('menu', <Key.menu: <65383>>),
                                           ('num_lock',
                                            <Key.num_lock: <65407>>),
                                           ('pause', <Key.pause: <65299>>),
                                           ('print_screen',
                                            <Key.print_screen: <65377>>),
                                           ('scroll_lock',
                                            <Key.scroll_lock: <65300>>)]),
