// 1)

function s = suficiencia_convergencia_jacobi(A)
    [m, n] = size(A)

    if n <> m then
        error("suficiencia_convergencia_jacobi - La matriz debe ser cuadrada")
        abort;
    end

    Dinv = diag(1 ./ diag(A))

    s = norm(eye(n, n) - Dinv * A)
    disp(s)

    s = s < 1
endfunction

A1 = [0 2 4; 1 -1 -1; 1 -1 2];

// Se intercambian filas para que D sea no singular
A1([1 2], :) = A1([2 1], :);

suficiencia_convergencia_jacobi(A1)

function s = necesidad_convergencia_jacobi(A)
    [m, n] = size(A)

    if n <> m then
        error("necesidad_convergencia_jacobi - La matriz debe ser cuadrada")
        abort;
    end

    Dinv = diag(1 ./ diag(A))

    s = max(abs(spec(eye(n, n) - Dinv * A)))
    disp(s)

    s = s < 1
endfunction

A1 = [0 2 4; 1 -1 -1; 1 -1 2];

// Se intercambian filas para que D sea no singular
A1([1 2], :) = A1([2 1], :);

necesidad_convergencia_jacobi(A1)

// a)
// 1er sistema: Como A(1,1) = 0. Luego no existe D^{-1} por lo que Jacobi no es aplicable.

// 2do sistema: Si ya que el radio espectral de la matriz de iteración es < 1

A1 = [1 -1 0; -1 2 -1; 0 -1 1.1];
necesidad_convergencia_jacobi(A1)


function s = necesidad_convergencia_gs(A)
    [m, n] = size(A)

    if n <> m then
        error("necesidad_convergencia_gs- La matriz debe ser cuadrada")
        abort;
    end

    Ninv = inv(tril(A))

    s = max(abs(spec(eye(n, n) - Ninv * A)))
    disp(s)

    s = s < 1
endfunction

// b)
// 1er sistema: Como A(1,1) = 0 luego det(tril(A)) = 0 por lo que no es inversible

// 2do sistema: Si ya que el radio espectral de la matriz de iteración es < 1

A1 = [1 -1 0; -1 2 -1; 0 -1 1.1];
b1 = [0 1 0]';
necesidad_convergencia_gs(A1)

function x = jacobi_rabs(A,b,x0,eps)
    n = size(A,1);
    x = x0;
    xk = x;
    suma = 0;
    cont = 0;
    
    for i=1:n
        suma = 0
            for j=1:n
                if (i<>j)
                    suma = suma + A(i,j) * xk(j)
                end
            end
        x(i) = 1/A(i,i) * (b(i) - suma)
    end
    cont = cont+1

    while (abs(norm(x-xk)) > eps)
        xk = x;
        for i=1:n
            suma = 0
            for j = 1:n
                if (i<>j)
                    suma = suma + A(i,j)*xk(j)
                end
            end
            x(i) = 1/A(i,i)*(b(i)-suma)
        end
     cont = cont+1
    end
    disp(cont);
endfunction

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

function x=gauss_seidel_rabs(A,b,x0,eps)
    n = size(A,1);
    x = x0;
    xk = x;
    cont = 0;
    for i=1:n 
        suma = 0
        for j = 1:n
            if (i<>j)
                suma = suma + A(i,j)*x(j);
            end
        end                
        x(i) = 1/A(i,i)*(b(i)-suma)
    end
    cont = cont+1;

    while (norm(x-xk)>eps)
        xk = x;
        for i=1:n 
            suma = 0
            for j = 1:n
                if (i<>j)
                    suma = suma + A(i,j)*x(j);
                end
            end                
            x(i) = 1/A(i,i)*(b(i)-suma)
        end
        cont = cont+1;
     end
     disp(cont) ;
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

// c)

jacobi(A1, b1, [0 0 0]', 1e-2)

gauss_seidel(A1, b1, [0 0 0]', 1e-2)

//---------------------------------------------------------------------------//

// 2)

A2 = [10 1 2 3 4; 1 9 -1 2 -3; 2 -1 7 3 -5; 3 2 3 12 -1; 4 -3 -5 -1 15];
b2 = [12 -27 14 -17 12]';

jacobi(A2, b2, [0 0 0 0 0]', 1e-6)
gauss_seidel(A2, b2, [0 0 0 0 0]', 1e-6)

//---------------------------------------------------------------------------//

// 3)

function B = encontrar_matriz(n)
    I = eye(n,n)
    A = I * 2 + diag(ones(n-1, 1), -1) * -1 + diag(ones(n-1, 1), 1) * -1
    
    N = tril(A)
    Ninv = inversa_n(N)

    B = I - Ninv * A
endfunction

function M = inversa_n(N)
    n = size(N,1)
    
    for k=1:n
        i = k
        j = 1
        pot2 = 2^(-k)
        while i <= n
            M(i,j) = pot2
            i = i + 1
            j = j + 1
        end
    end
endfunction

//---------------------------------------------------------------------------//

// 4)
N = 500;

A4 = 8 * eye(N,N) + 2 * diag(ones(N-1,1), 1) + 2 * diag(ones(N-1,1), -1) + diag(ones(N-3,1), 3) + diag(ones(N-3,1), -3);
b4 = ones(N,1);
x04 = zeros(N, 1);

tic(); gauss_seidel(A4, b4, x04, 1e-11); t=toc() // N = 100 -> ~0.037, N = 500 -> ~0.35

// gausselimPP: N = 100 -> ~0.039, N = 500 -> ~0.67

//---------------------------------------------------------------------------//

// 5)

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

// Omega óptimo
function w = omega_SOR(A)
    // Entrada: A matriz nxn tridiagonal y definida positiva
    // Salida: w óptimo del método de SOR
    
    [n,m] = size(A)
    T_j = eye(n,n) - diag(1./diag(A)) * A
    autovalores = spec(T_j)
    rho = max(abs(autovalores))
    w = 2/(1+sqrt(1-rho^2))
endfunction

A5 = [4 3 0; 3 4 -1; 0 -1 4];
b5 = [24 30 -24]';
x05 = [0 0 0]';
val = [3 4 -5]';

tic(); sor(A5, b5, x05, 1e-7, 1); toc() // 37 iteraciones
tic(); sor(A5, b5, x05, 1e-7, omega_SOR(A5)); toc() // 15 iteraciones



