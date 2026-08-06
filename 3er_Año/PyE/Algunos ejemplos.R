#########################
#      EJEMPLO 1        #
#########################

P <- matrix(c(0.7,0.3,0.2,0.8), nrow=2, byrow = TRUE)
P

P2 <- P%*%P
P2

P3 <- P2%*%P
P3

P4 <- P2%*%P2
P4

P16 <- P4%*%P4
P16

P256 <- P16%*%P16
P256

# Podemos ver que hay un comportamiento límite



#########################
#     EJEMPLO 2         #
#########################

P <- matrix(c(0,1,1,0), nrow = 2, byrow = TRUE)
P

P2 <- P%*%P
P2

P3 <- P2%*%P
P3

P4 <- P2%*%P2
P4

# Nunca converge esta matriz de transición



#########################
#      EJEMPLO 3        #
#########################

P <- matrix(c(1/2, 1/2, 0,
              1/2, 1/4, 1/4,
              0, 1/3, 2/3), nrow = 3, byrow = TRUE)
P

P2 <- P%*%P
P2

# Por más que en el primer paso no es posible pasar del
#  estado A al C, en 2 pasos sí es posible

# Luego, A -> C
# y como además C <- A entonces decimos que 
# están comunicados  A <-> C

# Vemos también que todos los estados están comunicados
# entre sí. Cuando esto ocurre, decimos que la cadena
# es IRREDUCIBLE




#########################
#     EJEMPLO 4         #
#########################

P <- matrix(c(1/2, 1/2, 0, 0,
              1/2, 1/2, 0, 0,
              1/4, 1/4, 1/4, 1/4,
              0, 0, 0, 1), nrow = 4, byrow = TRUE)
P

P2 <- P%*%P
P2

P3 <- P2%*%P
P3

P4 <- P2%*%P2
P4

P5 <- P3%*%P2
P5

P6 <- P3%*%P3
P6

# Existen tres clases (grupos) de estados en función 
# de su comunicación: {1,2}, {3} y {4}
# Mientras que los estados 1 y 2 son accesibles
# desde el estado 3, no ocurre a la inversa.
# El estado 4, por su parte, es ABSORBENTE.

# Si todos los estados de una cadena de Markov comunican 
# entre sí, es decir si la cadena consta de una sola clase,
# se dice que es IRREDUCIBLE




######################################################
# Otras matrices de transición que vimos en la clase #
######################################################

P <- matrix( c(0.9, 0.1,
               0.2, 0.8), byrow = TRUE, nrow = 2)

P <- matrix( c(0.6, 0.3, 0.1,
               0.3, 0.5, 0.2,
               0.4, 0.3, 0.3), byrow = TRUE, nrow = 3)
