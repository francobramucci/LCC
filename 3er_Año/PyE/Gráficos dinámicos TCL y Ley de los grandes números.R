library(lattice)
library(grid)
library(manipulate)

#############################################################
# 1 - DISTRIBUCIÓN MUESTRAL DEL TOTAL - POBLACIÓN NO NORMAL #
#############################################################

# Aunque la variable no tenga distribución normal, 
# la suma de n variables aleatorias sí la tendrá si n es grande.

# Ejemplo: distribución exponencial

# Definimos parámetros
alfa <- 0.3
cant <- 5000

# Vemos la forma de la distribución
hist(rexp(n = 1000, rate = alfa),
     xlab = "Valores de la variable exponencial simulada",
     ylab = "Frecuencia absoluta",
     main = paste0("Distribución de frecuencias de una muestra de n=",
                   cant," observaciones de una distribución exponencial"))

# Esperanza y error estándar de la variable
esperanza <- 1/alfa
EE <- 1/alfa

# Histogramas para variable no normal 
manipulate(
  histogram(colSums(matrix(data=rexp(cant * n, rate = alfa),nrow=n,ncol=cant)),
            type = "density",
            main = list(paste("Distribución del total muestral.\n", 
                              cant, " muestras de tamaño variante.",sep=""), 
                        cex = 1.3),
            xlab = list(paste0("Suma de ",n," v.a."), cex=1.1),
            ylab = list("Densidad", cex=1.1),
            col = "deepskyblue",
            nint = Intervalos,
            panel = function(x, ...) {
              panel.histogram(x, ...)
              panel.mathdensity(dmath = dnorm, col = "black",lwd = 1.7, 
                                args = list(mean=n*esperanza,sd=EE*sqrt(n)))
            })
  , n = slider(1,50), Intervalos = slider(10,30) )


##########################################################
# 2 - DISTRIBUCIÓN MUESTRAL DEL TOTAL - POBLACIÓN NORMAL #
##########################################################

# Si la variable tiene distribución normal, la suma de
# n variables aleatorias también, para cualquier n.

mu <- 0
sigma <- 1
cant <- 5000

# Esperanza y error estándar de la variable
esperanza <- mu
EE <- sigma

# Histogramas para variable normal
manipulate(
  histogram(colSums(matrix(data=rnorm(cant * n, mean = mu, sd = sigma),nrow=n,ncol=cant)),
            type = "density",
            main = list(paste("Distribución del total muestral.\n", 
                              cant, " muestras de tamaño variante.",sep=""), 
                        cex = 1.3),
            xlab = list(paste0("Suma de ",n," v.a."), cex=1.1),
            ylab = list("Densidad", cex=1.1),
            col = "deepskyblue",
            nint = Intervalos,
            panel = function(x, ...) {
              panel.histogram(x, ...)
              panel.mathdensity(dmath = dnorm, col = "black",lwd = 1.7, 
                                args = list(mean=n*esperanza,sd=EE*sqrt(n)))
            })
  , n = slider(1,50), Intervalos = slider(10,30) )




###############################################################
# 3 - DISTRIBUCIÓN MUESTRAL DE LA MEDIA - POBLACIÓN NO NORMAL #
###############################################################

# Aunque la variable no tenga distribución normal, 
# la media sí la tendrá si n es grande.

# Ejemplo: distribución exponencial

# Definimos parámetros
alfa <- 2
cant <- 5000

# Vemos la forma de la distribución
hist(rexp(n = 1000, rate = alfa),
     xlab = "Valores de la variable exponencial simulada",
     ylab = "Frecuencia absoluta",
     main = paste0("Distribución de frecuencias de una muestra de n=",
                   cant," observaciones de una distribución exponencial"))

# Esperanza y error estándar de la variable
esperanza <- 1/alfa
EE <- 1/alfa

# Histogramas para variable no normal 
manipulate(
  histogram(colMeans(matrix(data=rexp(cant * n, rate = alfa),nrow=n,ncol=cant)),
            type = "density",
            main = list(paste("Distribución de la media muestral.\n", 
                              cant, " muestras de tamaño variante.",sep=""), 
                        cex = 1.3),
            xlab = list("Media aritmética", cex=1.1),
            ylab = list("Densidad", cex=1.1),
            col = "deepskyblue",
            nint = Intervalos,
            panel = function(x, ...) {
              panel.histogram(x, ...)
              panel.mathdensity(dmath = dnorm, col = "black", lwd = 1.7, args = list(mean=esperanza,sd=EE/sqrt(n)))
            })
  , n = slider(1,200), Intervalos = slider(10,30) )


############################################################
# 4 - DISTRIBUCIÓN MUESTRAL DE LA MEDIA - POBLACIÓN NORMAL #
############################################################

# Si la variable tiene distribución normal, la media también, para cualquier n.

mu <- 0
sigma <- 1
cant <- 5000

# Esperanza y error estándar de la variable
esperanza <- mu
EE <- sigma

# Histogramas para variable normal
manipulate(
  histogram(colMeans(matrix(data=rnorm(cant * n, mean = mu, sd = sigma),nrow=n,ncol=cant)),
            type = "density",
            main = list(paste("Distribución de la media muestral.\n", cant, " muestras de tamaño variante.",sep=""), cex = 1.3),
            xlab = list("Media aritmética", cex=1.1),
            ylab = list("Densidad", cex=1.1),
            col = "deepskyblue",
            nint = Intervalos,
            panel = function(x, ...) {
              panel.histogram(x, ...)
              panel.mathdensity(dmath = dnorm, col = "black", lwd = 1.7, args = list(mean=esperanza,sd=EE/sqrt(n)))
            })
  , n = slider(1,100), Intervalos = slider(10,30) )


##############################################
# 5 - DISTRIBUCIÓN MUESTRAL DE LA PROPORCIÓN #
##############################################

# Por la Ley de los grandes números la proporción muestral
# tiende a la proporción teórica (parámetro) a medida que n crece.

# Por el TCL, la distribución de la proporción muestral
# tiende a la Normal a medida que n crece.

p <- 0.4

# Gráficos de línea para evaluar convergencia
par(mfrow = c(2, 2)) 
for (j in c(50,500,2000,5000)){
  n <- c()
  prop <- c()
  for (i in 1:j){
    prop <- c(prop,sum(rbinom(n = i, size = 1, prob = p))/i)
    n <- c(n,i)
  }
  plot(n,prop,type="l",
       ylim=c(0,1), 
       main = paste0("Proporción muestral para ",j," simulaciones"))
}


# Histograma para la proporción muestral
cant = 5000

esperanza <- p
EE <- sqrt(p*(1-p))

manipulate(
  histogram(colMeans(matrix(data=rbinom(cant * n, size = 1, prob = p),
                            nrow=n,ncol=cant)),
            type = "density",
            main = list(paste("Distribución de la proporción muestral.\n", cant, " muestras de tamaño variante.",sep=""), cex = 1.3),
            xlab = list("Proporción muestral", cex=1.1),
            ylab = list("Densidad", cex=1.1),
            col = "deepskyblue",
            nint = Intervalos,
            panel = function(x, ...) {
              panel.histogram(x, ...)
              panel.mathdensity(dmath = dnorm, col = "black", lwd = 1.7, args = list(mean=esperanza,sd=EE/sqrt(n)))
            })
  , n = slider(1,200), Intervalos = slider(10,30) )
