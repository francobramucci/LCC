// Apaga warning de redinifición de funciones
funcprot(0)

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
    h = (b-a)
    e = abs(((h^3)/12) * cot)
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
// Entrada: a,b = extremos del intervalo; cot = cota de la derivada cuarta de f
// Salida: e = cota del error de la aproximación
function e = error_regla_simspon(a, b, cot)
    h = (b-a)/2
    e = abs(h^5 * cot / 90)
endfunction

// a)
aproxTrapecioA = regla_trapecio(log, 1, 2)
aproxSimpsonA = regla_simspon(log, 1, 2)
valorRealA = integrate("log(x)", "x", 1, 2)

errorTrapecioA = error_regla_trapecio(1, 2, 1)
errorSimpsonA = error_regla_simspon(1, 2, 6)

errorTrapecioRealA = abs(valorRealA - aproxTrapecioA)
errorSimpsonRealA = abs(valorRealA - aproxSimpsonA)

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

// 2), 3)
disp("Ejercicios 2 y 3")

// Aproximación de la integral de f en el intervalo [a,b] por el método de 
// trapecio compuesto.
// Entrada: f = función; a,b = extremos del intervalo;
// n = cantidad de subintervalos;
// Salida: Tn = aproximación de la integral 
function Tn = trapecio_compuesto(fx, a, b, n)
    h = (b - a) / n;
    Tn = (1/2) * (fx(a) + fx(b));

    for i = 1:n-1
        xi = a+i*h;
        Tn = Tn + fx(xi);
    end
    
    Tn = h * Tn
endfunction

// Versión vectorizada de trapecio compuesto. f debe ser una función aplicable
// a vectores
function Tn = trapecio_compuesto_vectorizado(f, a, b, n)
    h = (b - a) / n;
    xi = linspace(a, b, n+1);
    fxi = f(xi);

    Tn = h * (sum(fxi) - (fxi(1) + fxi(n+1))/2);
endfunction

// Error de la aproximación de la integral en el intervalo [a,b] por el método
// del trapecio compuesto.
// Entrada: a,b = extremos del intervalo; n = cantidad de subintervalos;
// cot = cota de la derivada segunda de f
// Salida: ETn = cota del error de la aproximación
function ETn = error_trapecio_compuesto(a, b, n, cot)
    h = (b - a) / n;
    ETn = abs((1 / 12) * (h^2 * (b-a)) * cot)
endfunction

// Aproximación de la integral de f en el intervalo [a,b] por el método de 
// simpson compuesto.
// Entrada: f = función; a,b = extremos del intervalo; 
// n = cantidad de subintervalos, debe ser par;
// Salida: Sn = aproximación de la integral 
function Sn = simpson_compuesto(f, a, b, n)
    h = (b-a) / n;
    xi = linspace(a, b, n+1);
    fxi = f(xi);
    
    // Multiplicamos por 4 las posiciones pares
    // Multiplicamos por 2 las posiciones impares menos
    // en los extremos
    fxi([2:2:n]) = fxi([2:2:n]) * 4
    fxi([3:2:n]) = fxi([3:2:n]) * 2

    Sn = (h/3) * sum(fxi);
endfunction

// Error de la aproximación de la integral en el intervalo [a,b] por el método
// de simpson compuesto.
// Entrada: a,b = extremos del intervalo; n = cantidad de subintervalos, debe ser par;
// cot = cota de la derivada cuarta de f
// Salida: ESn = cota del error de la aproximación
function ESn = error_simpson_compuesto(a, b, n, cot)
    h = (b-a)/n;
    ESn = abs(h^4 * (b-a) * (1/180) * cot)
endfunction

// Regla del trapecio en dominio bidimensional.
// Entrada: f función de dos variables; a,b extremos del intervalo en el eje x
// c,d: extremos del intervalo en el eje y; 
// Salida: aproximación de la integral de la función f(x,y) para a <= x <= b, c <= y <= d

// a)
disp("a)")
deff("y = fa(x)", "y = 1./x");
aproxTrapecioA = trapecio_compuesto(fa, 1, 3, 4)
aproxSimpsonA = simpson_compuesto(fa, 1, 3, 4)
valoreRealA = integrate("1/x", "x", 1, 3)

// b)
disp("b)")
deff("y = fb(x)", "y = x.^3");
aproxTrapecioA = trapecio_compuesto(fb, 0, 2, 4)
aproxSimpsonA = simpson_compuesto(fb, 0, 2, 4)
valoreRealA = integrate("x^3", "x", 0, 2)

// c)
disp("c)")
deff("y = fc(x)", "y = x .* (1 + x.^2).^(1/2)");
aproxTrapecioA = trapecio_compuesto(fc, 0, 3, 6)
aproxSimpsonA = simpson_compuesto(fc, 0, 3, 6)
valoreRealA = integrate("x * (1 + x^2)^(1/2)", "x", 0, 3)

// d)
disp("d)")
deff("y = fd(x)", "y = sin(%pi .* x)");
aproxTrapecioA = trapecio_compuesto(fd, 0, 1, 8)
aproxSimpsonA = simpson_compuesto(fd, 0, 1, 8)
valoreRealA = integrate("sin(%pi .* x)", "x", 0, 1)

// e)
disp("e)")
deff("y = fe(x)", "y = x .* sin(x)");
aproxTrapecioA = trapecio_compuesto(fe, 0, 2*%pi, 8)
aproxSimpsonA = simpson_compuesto(fe, 0, 2*%pi, 8)
valoreRealA = integrate("x * sin(x)", "x", 0, 2*%pi)

// f)
disp("f)")
deff("y = ff(x)", "y = x.^2 .* exp(x)");
aproxTrapecioA = trapecio_compuesto(ff, 0, 1, 8)
aproxSimpsonA = simpson_compuesto(ff, 0, 1, 8)
valoreRealA = integrate("x^2 * exp(x)", "x", 0, 1)


// 4)
disp("Ejercicio 4")

deff("y = f(x)", "y = (x+1).^(-1)");
aproxTrapecio = trapecio_compuesto_vectorizado(f, 0, 1.5, 10)
aproxSimpson = simpson_compuesto(f, 0, 1.5, 10)
valorReal = integrate("(x+1)^(-1)", "x", 0, 1.5)

// 5)

function v = regla_trapecio_bidimensional(f, a, b, c, d)
    h = (b-a) * (d-c)/4
    v = h * (f(c,a) + f(c,b) + f(d,a) + f(d,b))
endfunction

disp("Ejercicio 5")
deff("y = f(x,y)", "y = sin(x + y)");
regla_trapecio_bidimensional(f, 0, 2, 0, 1)


// 6)

// Regla del trapecio compuesta en dominio bidimensional.
// Entrada: f función de dos variables; a,b extremos del intervalo en el eje x
// c,d: funciones delimitadoras de intervalos en el eje y; n: cantidad de subintervalos
// en el eje x; m = cantidad de subintervalos en el eje y
// Salida: aproximación de la integral de la función f(x,y) para a <= x <= b, c(x) <= y <= d(x)
function Tn = trapecio_compuesto_bidimensional(f, a, b, c, d, n, m)
    hx = (b - a) / n
    Tn = 0
    
    // Aplicamos regla del trapecio compuesta para cada subintervalo en
    // el eje y
    for i = 0:n
        xi = a + i*hx;
        limiteSuperiorY = d(xi);
        limiteInferiorY = c(xi);
        
        hy = (limiteSuperiorY - limiteInferiorY) / m;
        yi = linspace(limiteInferiorY, limiteSuperiorY, m+1);
        valoresY = f(xi, yi);

        Gxi = (sum(valoresY) - (valoresY(1) + valoresY(m+1)) / 2) * hy
        
        if i == 0 | i == n then
            peso = 1/2;
        else
            peso = 1;
        end

        Tn = Tn + peso * Gxi
    end

    Tn = Tn * hx
endfunction


// Otra versión de la regla del trapecio compuesto bidimensional muy poco
// óptima. Usar únicamente para fines didácticos.
function v = DobleTn(f, a, b, c, d, n, m)
    h = (b-a)/n
    deff("z = fxa(y)","z = f(" + string(a) + ",y)")
    deff("z = fxb(y)","z = f(" + string(b) + ",y)")
    v = trapecio_compuesto(fxa, c(a), d(a), m)/2 + trapecio_compuesto(fxb, c(b), d(b), m)/2
    for i = 1:n-1
        xi = a + i*h;
        deff("z=fxi(y)","z=f("+string(xi)+",y)");
        v = v + trapecio_compuesto(fxi, c(xi), d(xi), m);
    end
    v = h * v;
endfunction

// Método de Simpson compuesto en dominio bidimensional.
// Entrada: f función de dos variables; a,b extremos del intervalo en el eje x
// c,d: funciones delimitadoras de intervalos en el eje y; n: cantidad de subintervalos
// en el eje x; m = cantidad de subintervalos en el eje y. n y m deben ser pares.
// Salida: aproximación de la integral de la función f(x,y) para a <= x <= b, c(x) <= y <= d(x)
function Sn = simpson_compuesto_bidimensional(f, a, b, c, d, n, m)
    hx = (b - a) / n
    Sn = 0

    for i = 0:n
        xi = a + i*hx;
        limiteSuperiorY = d(xi);
        limiteInferiorY = c(xi);

        hy = (limiteSuperiorY - limiteInferiorY) / m;
        yi = linspace(limiteInferiorY, limiteSuperiorY, m+1);
        valoresY = f(xi, yi);

        valoresY([2:2:m]) = valoresY([2:2:m]) * 4;
        valoresY([3:2:m]) = valoresY([3:2:m]) * 2;

        Gxi = (hy / 3) * sum(valoresY);

        if i == 0 | i == n then
            peso = 1
        else 
            if modulo(i, 2) == 0 then
                peso = 2
            else
                peso = 4
            end
        end
        
        Sn = Sn + Gxi * peso;
    end

    Sn = Sn * hx/3
endfunction

disp("Ejercicio 6")

a = 0;
b = 2;
deff("y = c(x)", "y = - (2 * x - x^2)^(1/2)")
deff("y = d(x)", "y = (2 * x - x^2)^(1/2)")
deff("z = f(x,y)", "z = 0*x + 0*y + 1")

aproxTrapecioBid = trapecio_compuesto_bidimensional(f, a, b, c, d, 10000, 10000)
aproxSimpsonBid = simpson_compuesto_bidimensional(f, a, b, c, d, 10000, 10000)
//aproxTrapecioBid2 = DobleTn(f, a, b, c, d, 100, 100)


















