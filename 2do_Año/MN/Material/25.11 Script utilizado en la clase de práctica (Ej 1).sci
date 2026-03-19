// Ejercicio 1 de la Práctica 8
clc()
clear()

// Regla del Trapecio
function w = Trapecio(a,b,f)
    // Entrada: a,b = extremos de integración; f = función de Scilab
    // Salida: w = aproximación de la integral de f en [a,b] por la Regla del Trapecio
    w = ((b-a)/2)*(f(a)+f(b))
endfunction

// Regla de Simpson
function w = Simpson(a,b,f)
    // Entrada: a,b = extremos de integración; f = función de Scilab
    // Salida: w = aproximación de la integral de f en [a,b] por la Regla de Simpson
    h = (b-a)/2
    w = (h/3)*(f(a)+4*f(a+h)+f(b))
endfunction

// - Ejercicio i) y ii) - //

disp("a) f(x) = ln(x) y [a,b] = [1,2].")

int_trap = Trapecio(1,2,log)
int_simp = Simpson(1,2,log)
int_real = intg(1,2,log)

disp("Utilizando la Regla del Trapecio se tiene: "+string(int_trap))
disp("Utilizando la Regla de Simpson se tiene: "+string(int_simp))
disp("El valor real (calculado con la función intg) es: "+string(int_real))

// Ejercicio: Calcular el error absoluto y/o relativo.
