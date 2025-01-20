# Generador y resolvedor de laberintos en C y Python
El programa en python ejecuta un código en C para generar un laberinto en un
archivo llamado SalidaLaberinto.txt a partir de un archivo EntradaLaberinto.txt.
El archivo de entrada cuenta con el siguiente formato:

dimension
n
obstaculos fijos
(x1,y1)
(x2,y2)
...
(x3,y3)
obstaculos aleatorios
m
posicion inicial
(i1,i2)
objetivo
(o1,o2)

En caso de no respetar el formato el programa no funcionará y devolverá error.
Si no se quieren incluír obstaculos fijos los mismos pueden ser obviados.

En caso de que el laberinto generado no admita solución, python ejecutará
nuevamente al código en c. Eventualmente la disposición aleatoria de los
obstaculos deberá permitir una solución. De otra forma el programa se ejecutará
de forma infinita. Sin embargo, si la probabilidad de generar un camino es
demasiado baja, como la generación es aleatoria, el programa probablemente nunca
termine.

# Ejecución del programa
$ make
$ python3 main.py

"make" generará el ejecutable del archivo en el directorio build.
"make clean" limpiará todos los archivos objeto y el ejecutable main en el
directorio build/.

