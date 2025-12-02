// ------------------------ Interpolación polinómica --------------------------

// Diferencias divididas. Implementación recursiva
// Entrada: x,y = vectores de puntos de interpolación (x,y)
// Salida: w = valor de la diferencia dividida f[x0, ..., xn] 
function w = DD(x, y)
    n = length(x)
    if n == 1 then
        w = y(1)
    else
        w = (DD(x(2:n), y(2:n)) - DD(x(1:n-1), y(1:n-1))) / (x(n) - x(1))
    end;
endfunction

// Diferencias divididas. Implementación bottom-up.
// Entrada: x,y = vectores de puntos de interpolación (x,y)
// Salida: v = vector con las diferencias divididas f[x0, ..., xi] para i = 1, ..., n
function v = DD2(x, y)
    n = size(x,2)
    v(1) = y(1)
    c = 2
    k = 0
    for i=n-1:-1:1
        k = k + 1
        for j=1:i
            y(j) = (y(j+1) - y(j)) / (x(j+k) - x(j))
            if j == 1 then
                v(k+1) = y(j)
                c = c + 1
            end
        end
    end
endfunction

// Interpolación, método de diferencias divididas de Newton
// Entrada: xv,yv = vectores de puntos de interpolación (x,y)
// Salida: p = polinomio de diferencias divididas de Newton
function p = interpol_newton(xv, yv)
    D = DD2(xv, yv)
    n = size(xv, 2)
    x = poly(0, "x")
    p = D(n)
    
    for i=n-1:-1:1
        p = D(i) + (x - xv(i)) * p
    end
endfunction
    
// Polinomio Lk
// Entrada: xv = vector de abcisas de puntos de interpolación (x, y) 
// k = valor entero
// Salida: p = polinomio Lk
function p = Lk(xv, k)
    n = size(xv, 2)
    r = [xv(1:k - 1) xv(k + 1:n)]
    p = poly(r, "x", "roots")
    pk = horner(p, xv(k))
    p = p / pk
endfunction

// Interpolación, método de Lagrange
// Entrada: xv,yv = vectores de puntos de interpolación (x,y)
// Salida: p = polinomio de diferencias divididas de Newton
function p = interpol_lagrange(xv, yv)
    n = size(xv, 2)
    pol = 0
    for k=1:n
        pol = pol + (Lk(xv, k) * yv(k))
    end
    p = pol
endfunction

// Calcula el polinomio de error por interpolación polinómica.
// Entrada: xv = vector de abcisas de puntos de interpolación (x, y),
// cot = cota de f^(n) siendo f la función que está siendo aproximada
// Salida: polyError = polinomio del error cometido.
function polyError = interpol_error(xv, cot)
    n = size(xv, 2)
    polyError = poly(xv, "x", "roots")
    polyError = (polyError / factorial(n)) * cot
endfunction

// ------------------------ Aproximación de funciones -------------------------

// Resuelve el sistema Ax = b mediante eliminación gaussiana con pivoteo parcial
// Entrada: A = matriz de coeficientes cuadrada; b = términos independientes del sistema
// Salida: x = solución; a = sistema expandido
function [x,a] = gausselimPP(A,b)
    [nA,mA] = size(A) 
    [nb,mb] = size(b)

    if nA<>mA then
        error('gausselimPP - La matriz A debe ser cuadrada');
        abort;
    elseif mA<>nb then
        error('gausselimPP - Dimensiones incompatibles entre A y b');
        abort;
    end;

    a = [A b]; // Matriz aumentada
    n = nA;    // Tamaño de la matriz

    // Eliminación progresiva con pivoteo parcial
    for k=1:n-1
        // Obtener la posición del mayor elemento en valor absoluto para evitar 
        // errores de redondeo
        [_, kpivot] = max(abs(a(k:n, k)))
        kpivot = kpivot + k-1

        // Intercambiar la fila pivot elegida por la fila pivot original 
        a([kpivot k], :) = a([k kpivot], :)

        // Calculo multiplicadores
        M = a(k+1:n, k) / a(k,k) 

        // Resto la fila pivote multiplicada por el respectivo multiplicador a 
        // cada fila debajo de la fila pivote en columnas distintas de la del pivote
        a(k+1:n, k+1:n+1) = a(k+1:n, k+1:n+1) - M * a(k, k+1:n+1)
        
        // Elementos debajo del pivote igualados a 0
        a(k+1:n, k) = 0
    end;

    // Sustitución regresiva
    x(n) = a(n,n+1)/a(n,n);
    for i = n-1:-1:1
        sumk = 0
        for k=i+1:n
            sumk = sumk + a(i,k)*x(k);
        end;
        x(i) = (a(i,n+1)-sumk)/a(i,i);
    end;
endfunction

// Calcula los coeficientes para aproximar una función mediante mínimos 
// cuadrados dada una familia de funciones.
// Entrada: x,y = vectores de puntos de la función; vs = vector con cadenas
// correspondientes a los nombres de la familia de funciones definidas por el usuario
// Salida: va = vector de coeficientes
function va =  minimos_cuadrados_generalizado(x, y, vs)
    n = size(vs, 2)
    m = size(x, 2)
    A = zeros(m, n)

    // Calculo de la matriz A
    for j = 1:n
        deff("y = aux(x)", "y = " + vs(j) + "(x)")
        for i = 1:m
            A(i,j) = aux(x(i))
        end
    end
    
    // Resolvemos el sistema A' * A * x = A' * y
    
    va = gausselimPP(A' * A, A' * y');
endfunction

// Calcula la función aproximación por mínimimos cuadrados de una función.
// Entrada: va = vector de coeficientes; vs = nombres de las funciones de 
// la familia
// Salida: func = función aproximación
function func = funcion_aprox(va, vs)
    sf = "y = "
    n = size(vs,2)
    
    for i = 1:n
        a = va(i)
        s = vs(i)
        sf = sf + string(a) + "*" + string(s)+ "(x)"
        if i <> n then
            sf = sf + "+"
        end
    end
    
    deff("y = func(x)", sf)
endfunction

// Método de mínimos cuadrados polinomial
// Entrada: xv,yv = vectores 1xn+1 de los puntos de aproximación;
// n = grado del polinomio aproximante
// Salida: q = polinomio aproximante; e = error calculado con norma 2
function [q, e] = minimos_cuadrados_poly(xv, yv, n)
    m = size(xv, 2)

    A = zeros(m, n + 1)
    A(1:m, 1) = 1
    x = poly(0, "x")
    p = x
    
    // Calculamos A e R^(m x n+1)
    for i = 2:n+1
        A(1:m, i) = horner(p, xv)'
        p = p * x
    end

    // Resolvemos el sistema At * A * xv = At * yv
    va = gausselimPP(A' * A, A' * yv');

    // Polinomio aproximante
    q = poly(va, "x", "coeff")

    // Error norma 2
    e = norm(A * va - yv', 2)
endfunction

// Calcula las raices del polinomio de chebyshev T_n
// Entrada: n = grado T_n
// Salida: r = vector de 1xn con las raíces de T_n
function r = raices_chebyshev(n)
    // Valores para los que se anula T_n = cos(n*t)
    theta = (%pi/(2*n)) * [1:2:2*n-1]

    // x = cos(theta)
    r = cos(theta)
endfunction

// Dado una abcisa del intervalo [-1,1] lo escala al intervalo [a,b]
// Entrada: xv = vector de abcisas; a,b = extremos del intervalo
// Salida: yv = vector de abcisas escaladas a [a,b]
function yv = cambio_de_variable(xv, a, b)
    yv = ((b+a) + xv * (b-a))/2
endfunction

// Ejemplo para graficar
/*
 *   plot(rango, horner(P3Cheby, rango), "r")
 *
 *   plot(rango, horner(P3Eq, rango), "b")
 *
 *   a = gca();
 *   a.x_location = "origin";
 *   a.y_location = "origin";
 *   legend("Chebyshev", "Equidistante");
 */


// ------------------------ Integración Numérica --------------------------

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
function v = regla_trapecio_bidimensional(f, a, b, c, d)
    h = (b-a) * (d-c)/4
    v = h * (f(c,a) + f(c,b) + f(d,a) + f(d,b))
endfunction

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






