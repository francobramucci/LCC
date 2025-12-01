// 1)

// Aproximación de la integral de f en el intervalo [a,b] por la regla del
// trapecio.
// Entrada: a,b = extremos del intervalo; f = función 
// Salida: y = aproximación de la integral 
function y = regla_trapecio(f, a, b)
    y = (b-a) * (f(a) + f(b)) / 2
endfunction

// Error de la aproximación de la integral en el intervalo [a,b] por la regla 
// del trapecio.
// Entrada: a,b = extremos del intervalo; cot = cota de la derivada segunda de f
// Salida: e = cota del error de la aproximación
function e = error_regla_trapecio(a, b, cot)
    e = abs(1/12 * (b-a)^3 * cot)
endfunction


// Aproximación de la integral de f en el intervalo [a,b] por la regla de
// Simpson.
// Entrada: a,b = extremos del intervalo; f = función 
// Salida: y = aproximación de la integral 
function y = regla_simspon(f, a, b)
    h = (b-a)/2
    y = h * (f(a) + 4*f(a + h) + f(b)) / 3
endfunction

// Error de la aproximación de la integral en el intervalo [a,b] por la regla 
// de Simpson.
// Entrada: a,b = extremos del intervalo; cot = cota de la derivada segunda de f
// Salida: e = cota del error de la aproximación
function e = error_regla_simspon(a, b, cot)
    h = (b-a)/2
    e = abs(h^5 * cot / 90)
endfunction

// a)
aproxTrapecioA = regla_trapecio(log, 1, 2)
aproxSimpsonA = regla_simspon(log, 1, 2)

valorRealA = integrate("log(x)", "x", 1, 2)

// b)
deff("y = fb(x)", "y = x^(1/3)");
aproxTrapecioB = regla_trapecio(fb, 0, 0.1)
aproxSimpsonB = regla_simspon(fb, 0, 0.1)

valorRealB = integrate("x^(1/3)", "x", 0, 0.1)

// c)
deff("y = fc(x)", "y = (sin(x))^2")
aproxTrapecioC = regla_trapecio(fc, 0, %pi/3)
aproxSimpsonC = regla_simspon(fc, 0, %pi/3)

valorRealC = integrate("(sin(x))^2", "x", 0, %pi/3)

// Aproximación de la integral de f en el intervalo [a,b] por el método de 
// trapecio compuesto.
// Entrada: a,b = extremos del intervalo; n = cantidad de subintervalos;
// f = función 
// Salida: Tn = aproximación de la integral 
function Tn = trapecio_compuesto(f, a, b, n)
    h = (b - a) / n;
    Tn = (1/2) * (f(a) + f(b));

    for i = 1:n-1
        xi = a+i*h;
        Tn = Tn + f(xi);
    end
    
    Tn = h * Tn
endfunction

// Versión vectorizada de trapecio compuesto. f debe ser una función aplicable
// a vectores
function Tn = trapecio_compuesto_vectorizado(f, a, b, n)
    h = (b - a) / n;
    xi = linspace(a,b,n+1)
    xi = f(xi)
    xi(1) = xi(1) / 2
    xi(n+1) = xi(n+1) / 2

    Tn = h * sum(xi)
endfunction

// Error de la aproximación de la integral en el intervalo [a,b] por el método
// del trapecio compuesto.
// Entrada: a,b = extremos del intervalo; n = cantidad de subintervalos;
// cot = cota de la derivada segunda de f
// Salida: ETn = cota del error de la aproximación
function ETn = error_trapecio_comp(a, b, n, cot)
    h = (b - a) / n;
    ETn = abs((1 / 12) * (h^2 * (b-a)) * cot)
endfunction





/*

Polinomio Lagrange
f(x) = p(x) + Error


*/
