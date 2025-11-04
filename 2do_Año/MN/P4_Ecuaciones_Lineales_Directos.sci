// 1)

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
//---------------------------------------------------------------------------//

// 2)

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
            // for j=1:k        // no hace falta para calcular la solución x
            //     a(i,j) = 0;  // no hace falta para calcular la solución x
            // end              // no hace falta para calcular la solución x
            a(i,k) = 0
        end;

        disp("MD:"+ string(MD))
    end;

    // Sustitución regresiva
    x(n) = a(n,n+1)/a(n,n);
    MD = MD + 1
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

    disp("Cantidad de sumas y restas realizadas: " + string(SR))
    disp("Cantidad de multiplicaciones y divisiones realizadas: " + string(MD))

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


// Eliminación Gaussiana optimizada usando cálculos con submatrices
function [x,a] = gausselim2(A,b)
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
        // Calculo multiplicadores
        M = a(k+1:n, k) / a(k,k) 

        // Resto la fila pivote multiplicada por el respectivo multiplicador a 
        // cada fila debajo de la fila pivote en columnas distintas de la del pivote
        a(k+1:n, k+1:n+1) = a(k+1:n, k+1:n+1) - M * a(k, k+1:n+1)
        
        // Elementos debajo del pivote igualados a 0
        a(k+1:n, k) = 0
    end;

    // Sustitución regresiva
    x(n) = a(n,n+1) / a(n,n);
    for i = n-1:-1:1
        sumk = 0
        for k=i+1:n
            sumk = sumk + a(i,k) * x(k);
        end;
        x(i) = (a(i,n+1)-sumk) / a(i,i);
    end;
endfunction

//---------------------------------------------------------------------------//

// 3)

function [x,a] = gausselim_mult(A,B)
    [nA,mA] = size(A) 
    [nB,mB] = size(B)

    if nA<>mA then
        error('gausselim - La matriz A debe ser cuadrada');
        abort;
    elseif mA<>nB then
        error('gausselim - dimensiones incompatibles entre A y B');
        abort;
    end;

    a = [A B]; // Matriz aumentada

    // Eliminación progresiva
    n = nA;
    for k=1:n-1
        // Calculo multiplicadores
        M = a(k+1:n, k) / a(k,k) 

        // Resto la fila pivote multiplicada por el respectivo multiplicador a 
        // cada fila debajo de la fila pivote en columnas distintas de la del pivote
        a(k+1:n, k+1:n+nB) = a(k+1:n, k+1:n+nB) - M * a(k, k+1:n+nB)
        
        // Elementos debajo del pivote igualados a 0
        a(k+1:n, k) = 0
    end;

    // Sustitución regresiva
    x(n, :) = a(n, n+1:n+nB) / a(n,n)
    for i = n-1:-1:1
        sumk = 0
        for k=i+1:n
            sumk = sumk + a(i,k) * x(k, 1:n);
        end;
        x(i, :) = (a(i, n+1:n+nB)-sumk) / a(i,i);
    end;
endfunction

function Ainv = inv_gausselim(A)
    if nA<>mA then
        error('gausselim - La matriz A debe ser cuadrada');
        abort;
    end

    [n,m] = size(A)
    Ainv = gausselim_mult(A, eye(n,m))
endfunction

//---------------------------------------------------------------------------//

// 4)

function d = det_gausselim(A)
     [n,m] = size(A) 

    if n<>m then
        error('gausselim - La matriz A debe ser cuadrada');
        abort;
    end

    a = A
    // Eliminación progresiva
    for k=1:n-1
        // Calculo multiplicadores
        M = a(k+1:n, k) / a(k,k) 

        // Resto la fila pivote multiplicada por el respectivo multiplicador a 
        // cada fila debajo de la fila pivote en columnas distintas de la del pivote
        a(k+1:n, k+1:n) = a(k+1:n, k+1:n) - M * a(k, k+1:n)
        
        // Elementos debajo del pivote igualados a 0
        a(k+1:n, k) = 0
    end;
    
    d = prod(diag(a))
endfunction

//---------------------------------------------------------------------------//

// 5)

// Esta función obtiene la solución del sistema de ecuaciones lineales A*x=b, 
// dada la matriz de coeficientes A y el vector b.
// La función implementa el método de Eliminación Gaussiana con pivoteo parcial.
function [x,a] = gausselimPP(A,b)
    [nA,mA] = size(A) 
    [nb,mb] = size(b)

    if nA<>mA then
        error('gausselimPP - La matriz A debe ser cuadrada');
        abort;
    elseif mA<>nb then
        error('gausselimPP - dimensiones incompatibles entre A y b');
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
        disp("!!")
        disp(a)
        disp("!!")

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

// Ejemplo de aplicación
A2 = [0 2 3; 2 0 3; 8 16 -1]
b2 = [7 13 -3]'

[x2,a2] = gausselimPP(A2,b2)
disp(x2)
disp(a2)

//---------------------------------------------------------------------------//

// 6)

function [x,a] = gausselim_tridiag(A,b)
    SR = 0
    MD = 0

    [nA,mA] = size(A) 
    [nb,mb] = size(b)

    if nA<>mA then
        error('gausselimPP - La matriz A debe ser cuadrada');
        abort;
    elseif mA<>nb then
        error('gausselimPP - dimensiones incompatibles entre A y b');
        abort;
    end;
    
    a = [A b]
    n = nA

    // Eliminación progresiva
    for k=1:n-1
        // Calculo multiplicadores
        M = a(k+1, k) / a(k,k)
        MD = MD + 1
    
        // Resto el elemento de mi tridiagonal c_i por el multiplicador al b_{i+1}
        // y lo propio en la columna del vector solución
        a(k+1, [k+1 n+1]) = a(k+1, [k+1 n+1]) - M * a(k, [k+1 n+1])
        MD = MD + 2
        SR = SR + 2
        
        // Se elimina el elemento debajo del pivote
        a(k+1, k) = 0
    end

    // Sustitución regresiva
    
    x(n) = a(n, n+1) / a(n,n)
    MD = MD + 1

    for i=n-1:-1:1
        x(i) = (a(i, n+1) - a(i, i+1) * x(i+1)) / a(i,i)
        SR = SR + 1
        MD = MD + 2
    end

    disp("La cantidad de sumas y restas es: " + string(SR))
    disp("La cantidad de multiplicaciones y divisiones es: " + string(MD))
endfunction

//---------------------------------------------------------------------------//

// 7)

function [P, A, L, U] = lu_gauss_pivot(A)
    [nA, mA] = size(A)

    if nA<>mA then
        error('lu_gauss_pivot - La matriz A debe ser cuadrada');
        abort;
    end

    U = A
    L = eye(nA, mA)
    P = eye(nA, mA)
    
    n = nA
    for k=1:n-1
        [_, i] = max(abs(a(k:n, k)))
        i = i + k-1
        
        U([k i], k:n) = U([i k], k:n)
        L([k i], 1:k-1) = L([i k], 1:k-1)
        P([k i], :) = P([i k], :)

        for j=k+1:n
            L(j,k) = U(j,k)/U(k,k)
            U(j, k:n) = U(j, k:n) - L(j, k) * U(k, k:n)
        end
    end

endfunction

A = [2 1 1 0; 4 3 3 1; 8 7 9 5; 6 7 9 8]
[P, A, L, U] = lu_gauss_pivot(A)

//---------------------------------------------------------------------------//

// 8)

A = [1.012 -2.132 3.104; -2.132 4.096 -7.013; 3.104 -7.013 0.014]
[P, A, L, U] = lu_gauss_pivot(A)

A1 = [2.1756 4.0231 -2.1732 5.1967; -4.0231 6.0000 0 1.1973; -1.0000 5.2107 1.1111 0; 6.0235 7.0000 0 4.1561]
[P1, A1, L1, U1] = lu_gauss_pivot(A1)








