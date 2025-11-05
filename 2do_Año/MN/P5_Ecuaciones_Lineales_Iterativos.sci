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

A1 = [1 -1 0; -1 2 -1; 0 -1 1.1]
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

A1 = [1 -1 0; -1 2 -1; 0 -1 1.1]
b1 = [0 1 0]'
necesidad_convergencia_gs(A1)

// jacobi
// xi^{k+1} = 1/aii (bi - sum_{j=1, j/=i}^{n} aij xj^{k})

function x = jacobi(A,b,x0,eps)
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

function x1 = jacobi2(A, b, x0, eps)
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

// c)

jacobi2(A1, b1, [0 0 0]', 1e-2)

gauss_seidel(A1, b1, [0 0 0]', 1e-2)

//---------------------------------------------------------------------------//

// 2)
