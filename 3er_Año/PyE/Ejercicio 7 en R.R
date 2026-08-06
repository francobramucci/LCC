library(markovchain)

#Distribución inicial
pi <- c(2/5,1/5,2/5)
#Estados
states <- c("A","B","C")
#Matriz de transición
transition <- matrix(c(0,1/3,2/3,1/4,3/4,0,2/5,0,3/5),byrow=TRUE,nrow=3)
#Creo la cadena de markov. Chequea automáticamente las propiedades necesarias
mc <- new("markovchain",states = states,transitionMatrix = transition,name="Ejercicio5")

#Probabilidad de ir de un estado a otro
transitionProbability(mc,"A","B")
mc[1,2]

#Grafo asociado
plot(mc)

#¿Es irreducible?
is.irreducible(mc)
#Período de la cadena
period(mc)
#Estados transitorios
transientStates(mc)
#Distribución estacionaria
steadyStates(mc)
#Estados absorbentes
absorbingStates(mc)

#Matriz de transición en 1 paso
transition1 <- mc
#Matriz de transición en 2 pasos
transition2 <- mc * mc
#Matriz de transición en 3 pasos
transition3 <- mc ^ 3

eja <- transitionProbability(transition1,"A","B") * 
  transitionProbability(transition1,"B","B") * 
  transitionProbability(transition1,"B","B") *
  transitionProbability(transition1,"B","A") *
  transitionProbability(transition1,"A","C")

ejb <- transitionProbability(transition1,"A","B") * 
  transitionProbability(transition1,"A","C") *
  transitionProbability(transition2,"C","B") *
  transitionProbability(transition2,"B","A")

ejc <- (pi * transition2)[2] *
  transitionProbability(transition1,"B","A") *
  transitionProbability(transition3,"B","B")

#Otra forma de resolver el apartado c
ejc2 <- (pi[1] * 
  transitionProbability(transition2,"A","B") *
  transitionProbability(transition3,"B","B") *
  transitionProbability(transition1,"B","A")) +
  (pi[2] * 
  transitionProbability(transition2,"B","B") *
  transitionProbability(transition3,"B","B") *
  transitionProbability(transition1,"B","A")) +
  (pi[3] * 
  transitionProbability(transition2,"C","B") *
  transitionProbability(transition3,"B","B") *
  transitionProbability(transition1,"B","A"))

#Simula una trayectoria de 100 estados partiendo desde C
rmarkovchain(mc,n=100,t0="C")
