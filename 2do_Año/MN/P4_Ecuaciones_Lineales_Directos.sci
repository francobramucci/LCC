// 1
function s = resolver_triangular_superior(A, b, n)
    x(n) = b(n) / A(n,n)

    for i = [n-1:-1:1]
        x(i) = b(i)

        for j = [i+1:n]
            x(i) = x(i) - A(i,j) * x(j)
        end

        // Preguntar que ocurre si A(i,i) = 0
        if A(i,i) <> 0 then
            x(i) = x(i) / A(i,i)
        else
            x(i) = 0
        end
    end

    s = x
endfunction


function s = resolver_triangular_inferior(A, b, n)
    x(1) = b(1) / A(1,1)

    for i = [2:n]
        x(i) = b(i)

        for j = [1:i-1]
           x(i) = x(i) - A(i,j) * x(j)
        end
        
        if A(i,i) <> 0 then
            x(i) = x(i) / A(i,i)
        else
            x(i) = 0
        end
    end

    s = x
endfunction

//2


// Esta función obtiene la solución del sistema de ecuaciones lineales A*x=b, 
// dada la matriz de coeficientes A y el vector b.
// La función implementa el método de Eliminación Gaussiana sin pivoteo.  
function [x,a] = gausselim(A,b)
    SR = 0 // Cantidad de sumas y restas realizadas
    MD = 0 // Cantidad de multiplicaciones y divisiones realizadas

    [nA,mA] = size(A) 
    [nb,mb] = size(b)

    if nA<>mA then
        error('gausselim - La matriz A debe ser cuadrada');
        abort;
    elseif mA<>nb then
        error('gausselim - dimensiones incompatibles entre A y b');
        abort;
    end;

    a = [A b]; // Matriz aumentada

    // Eliminación progresiva
    n = nA;
    for k=1:n-1
        for i=k+1:n
            M = a(i,k) / a(k,k)
            MD = MD + 1

            for j=k+1:n+1
                a(i,j) = a(i,j) - a(k,j) * M;
                SR = SR + 1
                MD = MD + 1
            end;
            for j=1:k        // no hace falta para calcular la solución x
                a(i,j) = 0;  // no hace falta para calcular la solución x
            end              // no hace falta para calcular la solución x
            disp("MD:"+ string(MD))
        end;

    end;

    // Sustitución regresiva
    x(n) = a(n,n+1)/a(n,n);
    for i = n-1:-1:1
        sumk = 0
        for k=i+1:n
            sumk = sumk + a(i,k) * x(k);
            SR = SR + 1
            MD = MD + 1
        end;
        x(i) = (a(i,n+1)-sumk) / a(i,i);
        MD = MD + 1
        SR = SR + 1
    end;
endfunction

disp("i)")
A = [1 1 0 3; 2 1 -1 1; 3 -1 -1 2; -1 2 3 -1]
b = [4 1 -3 4]'

[x,a] = gausselim(A,b)

disp("ii)")
A = [1 -1 2 -1; 2 -2 3 -3; 1 1 1 0; 1 -1 4 3]
b = [-8 -20 -2 4]'

[x,a] = gausselim(A,b)

disp("iii)")

A = [1 1 0 4; 2 1 -1 1; 4 -1 -2 2; 3 -1 -1 2]
b = [2 1 0 -3]'

[x,a] = gausselim(A,b)

// Ejemplos de aplicación
A = [3 -2 -1; 6 -2 2; -9 7 1]
b = [0 6 -1]'

A = [1 1 0 3; 2 1 -1 1; 3 -1 -1 2; -1 2 3 -1]
b = [4 1 -3 4]'

[x,a] = gausselim(A,b)
disp(x)
disp(a)

A2 = [0 2 3; 2 0 3; 8 16 -1]
b2 = [7 13 -3]'

A2 = [1 -1 2 -1; 2 -2 3 -3; 1 1 1 0; 1 -1 4 3]
b2 = [-8 -20 -2 4]'

[x2,a2] = gausselim(A2,b2)

// !--error 27 
//Division by zero...
//at line      24 of function gausselim called by :  
//[x2,a2] = gausselim(A2,b2)

