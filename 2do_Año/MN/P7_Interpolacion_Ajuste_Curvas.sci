// Comando para evitar warnings por redefinición de funciones
funcprot(0)

// Interpolación polinómica

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

// 1)

// a)
// Aproximación de e^(1/3) lineal
x1=[0, 0.2];
y1=[1, 1.2214];

newtonLineal = interpol_newton(x1, y1)
lagrangeLineal = interpol_lagrange(x1, y1)

aproxNewtonLineal = horner(newtonLineal, 1/3)
aproxLagrangeLineal = horner(lagrangeLineal, 1/3)

// Aproximación de e^(1/3) cúbica
x2 = [0, 0.2, 0.4, 0.6];
y2 = [1, 1.2214, 1.4918, 1.8221];

lagrangeCubica = interpol_lagrange(x2, y2)
newtonCubica = interpol_newton(x2, y2)

aproxNewtonCubica = horner(newtonCubica, 1/3)
aproxLagrangeCubica = horner(lagrangeCubica, 1/3)

rango = [-2:0.01:2];

plot(rango, horner(newtonLineal, rango), "r")
plot(rango, horner(newtonCubica, rango), "b")
plot(rango, exp(rango), "g")
a = gca();
a.x_location = "origin";
a.y_location = "origin";
legend("Lineal", "Cubico", "e^x");


// b)
/*
 *   El error en el caso lineal es:
 *
 *   er_lineal(x) = ((x - 0) * (x - 0.2) / 2) * exp(c_x)''
 *   con c_x perteneciente a [0, 0.2]
 *
 *   exp(x)'' = exp(x)
 *
 *   exp(c_x)'' <= exp(0.2), pues exp es creciente
 *
 *   er_lineal(1/3) <= ((1/3 - 0) * (1/3 - 0.2) / 2) * exp(0.2) = 0.0271423
 *
 *   El error exacto es %e^(1/3) - aprox_nl = 0.0266124
 */

/*
 *   El error en el caso cubico es:
 *   er_cubico(x) = ((x - 0) * (x - 0.2) * (x - 0.4) * (x - 0.6) / 4!) * exp^(4)(c_x)
 *   con c_x perteneciente a [0, 0.6]
 *
 *   exp(x)(4) = exp(x)
 *
 *   exp^(4)(c_x) <= exp(0.6), pues exp es creciente
 *
 *   er_cubico(1/3) <= ((1/3 - 0) * (1/3 - 0.2) * (1/3 - 0.4) * (1/3 - 0.6)/ 4!) * exp(0.6) = 0.00006
 *
 *   Sin embargo vemos que el error exacto es %e^(1/3) - aprox_nc = 0.0000630
 *   Esto ocurre debido a los errores de redondeo en los valores de y2
 */

// 2)

/*
 *   Si f(x) es un polinomio con gr(f) <= n entonces f^(n+1)(x) = 0. 
 *   Luego el error de interpolación se anula y resulta f(x) = p(x) siendo p(x) polinomio interpolante
 *   con n+1 nodos de interpolación.
 */


// 4)

x1 = [2.0, 2.1, 2.2, 2.3, 2.4, 2.5];
y1 = [0.2239, 0.1666, 0.1104, 0.0555, 0.0025, -0.0484];

polyNewton = interpol_newton(x1, y1)

aprox1 = horner(polyNewton, 2.15)
aprox2 = horner(polyNewton, 2.35)

// Calculamos las cotas de los errores
/*
 *   error(x) = ((x - 2.0) * (x - 2.1) * (x - 2.2) * (x - 2.3) * (x - 2.4) * (x - 2.5) / factorial(6)) * f^(6)(c_x)
 *   
 *   Como f^(6)(x) <= 1
 *
 *   error(x) <= (x - 2.0) * (x - 2.1) * (x - 2.2) * (x - 2.3) * (x - 2.4) * (x - 2.5) / factorial(6)
 */

polyError = interpol_error(x1, 1)

error1 = horner(polyError, 2.15)
error2 = horner(polyError, 2.35)

// Calculamos el error real
function y = J0(x)
    y = (1 / %pi) * integrate("cos(" + string(x) + " * sin(t))", "t", 0, %pi)
endfunction

errorReal1 = J0(2.15) - aprox1
errorReal2 = J0(2.35) - aprox2

// Observamos que el error real es mayor debido a los errores de redondeo en y1

// 5)

// Sabemos que f(0) = P_01(0) = 1, f(1) = P_01(1) = 3 y f(2) = P_02(2) = 3
// ya que los polinomios coinciden con la función en dichos puntos
/*
 *   x = [0, 1, 2, 3]
 *   y = [1, 3, 3, k]
 *   P_123(x) = L1(x) * 3 + L2(x) * 3 + L3(x) * k
 *   P_123(2.5) = L1(2.5) * 3 + L2(2.5) * 3 + L3(2.5) * k = 3
 */

// Obtenemos f(3) = k despejando
x = [1, 2, 3];
L1 = Lk(x, 1)
L2 = Lk(x, 2)
L3 = Lk(x, 3)

c1 = horner(L1, 2.5) * 3
c2 = horner(L2, 2.5) * 3
c3 = horner(L3, 2.5)
k = (3 - c1 - c2) / c3

xx = [0, 1, 2, 3];
yy = [1, 3, 3, k];

// Calculamos P_0123
p = interpol_lagrange(xx, yy)

res = horner(p, 2.5)

// 6)
xv = [-1, 1, 2, 4]
Dv = [2, 1, -2, 2]

// a)
x = poly(0, "x")
P3 = 2 + (x + 1) * (1 + (x - 1) * (-2 + (x - 2) * 2))

// b)
aprox_f0 = horner(P3, 0)

// c)
polyError = interpol_error(xv, 33.6)
error = horner(polyError, 0)

// error <= -11.2

// Aproximación de funciones

// Resolver sistema
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

// Calcular coeficientes
function va =  minimos_cuadrados_generalizado(x, y, vs)
    n = size(vs, 2)
    m = size(x, 2)
    A = zeros(m, n)
    for j = 1:n
        deff("y = aux(x)", "y = " + vs(j) + "(x)")
        for i = 1:m
            A(i,j) = aux(x(i))
        end
    end
    
    // A' * A * x = A' * y
    
    va = gausselimPP(A' * A, A' * y');
endfunction

// Calcular función aproximación
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

x1 = [4 4.2 4.5 4.7 5.1 5.5 5.9 6.3 6.8 7.1];
y1 = [102.56 113.18 130.11 142.05 167.53 195.14 224.87 256.73 299.5 326.72];

x2=[0,0.2,0.4,0.6];
y2=[1,1.2214,1.4918,1.8221];

deff("y = f1(x)", "y = 1");
deff("y = f2(x)", "y = x");
deff("y = f3(x)", "y = x^2");
deff("y = f4(x)", "y = x^3");
deff("y = f5(x)", "y = x^4");
deff("y = f6(x)", "y = x^5");
deff("y = f7(x)", "y = x^6");
deff("y = f8(x)", "y = x^7");
deff("y = f9(x)", "y = x^8");
deff("y = f10(x)", "y = x^9");

vs = ["f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10"];
va = minimos_cuadrados(x1, y1, vs(1:4));
g = funcion_aprox(va, vs(1:4));

x = 3:0.01:8;
plot(x, g)

// 7)

// Método de mínimos cuadrados polinomial
// Entrada: xv,yv = vectores 1xn+1 de los puntos de aproximación,
// n = grado del polinomio aproximante
// Salida: q = polinomio aproximante, e = error calculado con norma 2
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

xv = [0, 0.15, 0.31, 0.5, 0.6, 0.75];
yv = [1, 1.004, 1.031, 1.117, 1.223, 1.422];

[poly1, error1] = minimos_cuadrados_poly(xv, yv, 1)
[poly2, error2] = minimos_cuadrados_poly(xv, yv, 2)
[poly3, error3] = minimos_cuadrados_poly(xv, yv, 3)

// error1 = 0.1567356 >= error2 = 0.0307449 >= error3 = 0.0105469
// Vemos que el error con polinomios de grado 3 es la menor

rango = 0:0.01:1;

// Limpia la figura anterior
clf;
plot(rango, horner(poly1, rango), "r")
h1 = gce();

plot(rango, horner(poly2, rango), "b")
h2 = gce();

plot(rango, horner(poly3, rango), "g")
h3 = gce();

plot(xv, yv, "k.")
a = gca();
a.x_location = "origin";
a.y_location = "origin";
h1 = legend([h1, h2, h3].children, "Lineal", "Cuadrático", "Cúbico");

// Se puede apreciar en la gráfica que el polinomio que mejor aproxima
// los puntos es poly3, de grado 3

// 8)

// a)
xv = [4, 4.2, 4.5, 4.7, 5.1, 5.5, 5.9, 6.3, 6.8, 7.1];
yv = [102.56, 113.18, 130.11, 142.05, 167.53, 195.14, 224.87, 256.73, 299.5, 326.72];

[poly1, error1] = minimos_cuadrados_poly(xv, yv, 1)
[poly2, error2] = minimos_cuadrados_poly(xv, yv, 2)
[poly3, error3] = minimos_cuadrados_poly(xv, yv, 3)

// error1 = 18.138721 <= error2 = 0.0379857 <= error3 = 0.0229639

// b)

// Crea y selecciona otra ventana
scf(1);

rango = 3:0.01:8;
plot(rango, horner(poly1, rango), "r")
h1 = gce();

plot(rango, horner(poly2, rango), "b")
h2 = gce();

plot(rango, horner(poly3, rango), "g")
h3 = gce();

plot(xv, yv, "k.")
a = gca();
a.x_location = "origin";
a.y_location = "origin";
legend([h1, h2, h3].children, "Lineal", "Cuadrático", "Cúbico");

// 9)
// Definimos f
deff("y = f(x)", "y = 1./(1 + x.^2)");


rango = -5:0.01:5;
scf(2);
colores = ["r", "g", "b", "k", "m"];
c = 1;
h = [];
textosLeyenda = [];
for n = [2, 4, 6, 10, 14]
    xv = linspace(-5, 5, n);
    yv = f(xv);
    Pn = interpol_newton(xv, yv);

    error_vals = f(rango) - horner(Pn, rango);
    plot(rango, error_vals, colores(c));

    temp = gce();
    h(c) = temp.children;
    textosLeyenda(c) = "n=" + string(n);

    c = c + 1;
end

a = gca();
a.x_location = "origin";
a.y_location = "origin";
legend(h, textosLeyenda)

// Se puede apreciar que a medida que aumenta n, el error cometido cerca de los
// extremos es mucho mayor que en el medio del intervalo

// 10)

// Calcula las raices del polinomio de chebyshev T_n
// Entrada: n = grado de T_n
// Salida: r = vector de 1xn con las raíces de T_n
function r = raices_chebyshev(n)
    // Valores para los que se anula T_n = cos(n*t)
    r = (%pi/(2*n)) * [1:2:2*n-1]

    // x = cos(t)
    r = cos(r)
endfunction

// a)
// Como queremos calcular un polinomio de grado 3 necesitamos 4 nodos
// de interpolación en [-1,1], en este caso, las raíces de T_4

xv = raices_chebyshev(4)
yv = exp(xv)

P3 = interpol_newton(xv, yv)

// b)
rango = -1:0.01:1;
scf(3);

error_vals = exp(rango) - horner(P3, rango);
plot(rango, error_vals);

a = gca();
a.x_location = "origin";
a.y_location = "origin";

// 11)

function yv = cambio_de_variable(xv, a, b)
    yv = ((b+a) + xv * (b-a))/2
endfunction

g = cos
a = 0;
b = %pi/2;

// Usando nodos de Chebyshev
xv = raices_chebyshev(11)
xv = cambio_de_variable(xv)
yv = g(xv)

P3Cheby = interpol_newton(xv, yv)

// Usando nodos equidistantes
xv = linspace(a, b, 11)
yv = g(xv)

P3Eq = interpol_newton(xv, yv)

// Graficamos el error en cada caso
rango = a:0.01:b;
scf(4);

plot(rango, cos(rango) - horner(P3Cheby, rango), "r")

plot(rango, cos(rango) - horner(P3Eq, rango), "b")

a = gca();
a.x_location = "origin";
a.y_location = "origin";
legend("Chebyshev", "Equidistante");














