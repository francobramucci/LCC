// Diferencias divididas. Implementación bottom-up
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
                v(k) = y(j)
                c = c + 1
            end
        end
    end
endfunction

// Diferencias divididas. Implementación recursiva
function w=DD(x,y)
    n = length(x);
    if n==1 then
        w = y(1)
    else
        w = (DD(x(2:n),y(2:n))-DD(x(1:n-1),y(1:n-1)))/(x(n)-x(1))
    end;
endfunction


// Interpolación Lagrange
function y = Lk(x,k)
    [Xn,Xm] = size(x)
    r = [x(1:k-1) x(k+1:Xm)]
    p = poly(r,"x","roots")
    pk = horner(p,x(k))
    y = p / pk
endfunction

function z = interpolLagrange(x,y)
    [Xn,Xm] = size(x)
    pol = 0
    for k = 1:Xm
        pol = pol + (Lk(x,k)*y(k))
    end
    z = pol
endfunction
/*$(-2, 4), (-1, -1), (0, 0), (1, -1), (2, 4)$,
x1=[-2,-1,0,1,2]
y1=[4,-1,0,-1,4]
cuatro = interpolLagrange(x1,y1)
*/

// lineal
x1=[0,0.2]
y1=[1,1.2214]
// cubica
x2=[0,0.2,0.4,0.6]
y2=[1,1.2214,1.4918,1.8221]

lineal = interpolLagrange(x1,y1)
cubica = interpolLagrange(x2,y2)

rango = [-2:0.01:2]

plot(rango,horner(lineal,rango),"r")
plot(rango,horner(cubica,rango),"b")
plot(rango,exp(rango),"g")
a=gca();
a.x_location = "origin";
a.y_location = "origin";
h1 = legend("Lineal","Cubico","e^x")

/*
Error en el caso lineal es:
 er_lineal(x) = (x-0)*(x-0.2)/2*exp(c_x)''
 
 exp(x)'' = exp(x), tomo el extremo derecho 0.2
 er_lineal(1/3) =  ((1/3)-0)*((1/3)-0.2)/2*exp(0.2) 
                = 0.0271423
*/

/*Ejercicio 7.5*/
/*
    x = [0,1,2,3]
    y = [1,3,3,k]
    P_123(x) =L1(x)*3 + L2(x)*3 + L3(x)* k
    P_123(2.5) =L1(2.5)*3 + L2(2.5)*3 + L3(2.5)* k = 3
*/

/*
    x = [1,2,3]
    L1 = Lk(x,1)
    L2 = Lk(x,2)
    L3 = Lk(x,3)

    c1 = horner(L1,2.5)*3
    c2 = horner(L2,2.5)*3
    c3 = horner(L3,2.5)
    k = (3-c1-c2)/c3

    xx = [0,1,2,3]
    yy = [1,3,3,k]

    p = interpolLagrange(xx,yy)

    res = horner(p,2.5)
*/

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
function va =  minimos_cuadrados(x, y, vs)
    n = size(vs,2)
    m = size(x,2)
    A = zeros(m, n)
    for j = 1:n
        deff( "y = aux(x)", "y = " + vs(j) + "(x)")
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
    
    disp(sf)
endfunction

// lineal
x1=[4 4.2 4.5 4.7 5.1 5.5 5.9 6.3 6.8 7.1]
y1=[102.56 113.18 130.11 142.05 167.53 195.14 224.87 256.73 299.5 326.72]
// cubica
x2=[0,0.2,0.4,0.6]
y2=[1,1.2214,1.4918,1.8221]

deff("y = f1(x)", "y = 1")
deff("y = f2(x)", "y = x")
deff("y = f3(x)", "y = x^2")
deff("y = f4(x)", "y = x^3")
deff("y = f5(x)", "y = x^4")
deff("y = f6(x)", "y = x^5")
deff("y = f7(x)", "y = x^6")
deff("y = f8(x)", "y = x^7")
deff("y = f9(x)", "y = x^8")
deff("y = f10(x)", "y = x^9")

vs = ["f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10"]
va = minimos_cuadrados(x1, y1, vs(1:4))
g = funcion_aprox(va,vs(1:4))

x = 3:0.01:8 
plot(x,g)













