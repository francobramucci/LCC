// P4:

function [x,a] = gausselim2(A,b)
    [nA,mA] = size(A) 
    [nb,mb] = size(b)

    if nA<>mA then
        error('gausselim - La matriz A debe ser cuadrada');
        abort;
    elseif mA<>nb then
        error('gausselim - Dimensiones incompatibles entre A y b');
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


function [L, U, P] = lu_gauss_pivot(A)
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
        [_, i] = max(abs(U(k:n, k)))
        i = i + k-1
       	
		// Intercambio de filas 
        U([k i], k:n) = U([i k], k:n)
        L([k i], 1:k-1) = L([i k], 1:k-1)
        P([k i], :) = P([i k], :)
		
		L(k+1:n, k) = U(k+1:n, k) / U(k,k)
		U(k+1:n, k+1:n) = U(k+1:n, k+1:n) - L(k+1:n, k) * U(k, k+1:n)
		U(k+1:n, k) = 0
	end

endfunction


function [L, U] = lu_doolittle(A)
    [nA, mA] = size(A)

    if nA <> mA then
        error("lu_doolittle - La matriz debe ser cuadrada.")
        abort()
    end

    n = nA
    U = zeros(n,n)
    L = eye(n,n)
    
    // Inicialización de U y L
	U(1, 1:n) = A(1, 1:n)
    L(2:n, 1) = A(2:n, 1) / U(1,1)

	for i=2:n
        // Calculamos fila de U
		U(i, i:n) = A(i, i:n) - L(i, 1:i-1) * U(1:i-1, i:n)
        
        // Teniendo fila de U calculamos columna de L
        if i < n then
            L(i+1:n, i) = (A(i+1:n, i) - L(i+1:n, 1:i-1) * U(1:i-1, i)) / U(i,i)
        end
    end
endfunction


function [U, ind] = cholesky(A)
    eps = 1.0e-8
    n = size(A, 1)
    U = zeros(n, n)

    for k = 1:n
        if k == 1 then
            t = A(k, k)
        else 
            t = A(k, k) - U(1:k-1, k)' * U(1:k-1, k)
        end

        if t <= eps
            printf("Matriz no definida positiva.\n")
            ind = 0
            return
        end

        U(k, k) = sqrt(t)
        for j = k+1:n
            if k == 1 then 
                U(k, j) = A(k, j) / U(k, k)
            else 
                U(k, j) = (A(k, j) - U(1:k-1, k)' * U(1:k-1, j)) / U(k, k)
            end
        end
    end
    ind = 1
endfunction

//---------------------------------------------------------------------------//

// P5:

function x1 = jacobi(A, b, x0, eps)
    n = size(A, 1)
    cont = 0

    Dinv = diag(1 ./ diag(A))
    
    x1 = Dinv * b + (eye(n, n) - Dinv * A) * x0

    cont = cont + 1

    while abs(norm(x1-x0)) > eps
        x0 = x1
        x1 = Dinv * b + (eye(n, n) - Dinv * A) * x0
        cont = cont + 1
    end

    disp(cont)
endfunction


function x1 = gauss_seidel(A, b, x0, eps)
    n = size(A,1);
    err = %inf
    cont = 0;

    while err > eps
        x1(1) = 1/A(1,1) * (b(1) - A(1, 2:n) * x0(2:n))

        for i=2:n-1
           x1(i) = 1/A(i,i) * (b(i) - A(i, 1:i-1) * x1(1:i-1) - A(i, i+1:n) * x0(i+1:n))
        end

        x1(n) = 1/A(n,n) * (b(n) - A(n, 1:n-1) * x1(1:n-1))

        err = abs(norm(x1-x0))
        x0 = x1
        cont = cont + 1
    end

   disp(cont);
endfunction


function x1 = sor(A, b, x0, eps, w)
    n = size(A,1);
    err = %inf
    cont = 0;

    while err > eps
        x1(1) = (1-w) * x0(1) + w/A(1,1) * (b(1) - A(1, 2:n) * x0(2:n))

        for i=2:n-1
           x1(i) = (1-w) * x0(i) + w/A(i,i) * (b(i) - A(i, 1:i-1) * x1(1:i-1) - A(i, i+1:n) * x0(i+1:n))
        end

        x1(n) = (1-w) * x0(n) + w/A(n,n) * (b(n) - A(n, 1:n-1) * x1(1:n-1))

        err = abs(norm(x1-x0))
        x0 = x1
        cont = cont + 1
    end
    
    disp("Cantidad de iteraciones: " + string(cont))
endfunction


function w = omega_SOR(A)
    // Entrada: A matriz nxn tridiagonal y definida positiva
    // Salida: w óptimo del método de SOR
    
    [n,m] = size(A)
    T_j = eye(n,n) - diag(1./diag(A)) * A
    autovalores = spec(T_j)
    rho = max(abs(autovalores))
    w = 2/(1+sqrt(1-rho^2))
endfunction


//---------------------------------------------------------------------------//

// P6:

function c = circulos_greshgorin(A)
    n = size(A,2)
    for i=1:n
        c(i,1) = A(i,i)
        c(i,2) = sum(abs(A(i,:))) - abs(A(i,i))
        disp("|lambda - " + string(c(i,1)) + "| <= " + string(c(i,2)))
    end
endfunction


function [valor, z1] = metodo_potencia(A, z0, eps, maxiter)
    valor = 0
    iter = 1

    w = A * z0
    z1 = w / norm(w,%inf)

    [_, j] = max(abs(w));
    valor = w(j) / z0(j);
    z1 = w/valor;

    while (iter <= maxiter) & (norm(z0-z1,%inf)>eps)
        z0 = z1;
        w = A*z0;
        z1 = w / norm(w,%inf)
        [m,j] = max(abs(w));
        valor = w(j) / z0(j);
        z1 = w/valor;
        iter = iter +1;
    end

    disp("Iteraciones: " + string(iter));    
endfunction


