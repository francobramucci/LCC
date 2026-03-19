// Jacobi
// xi^(k+1) = 1/aii (bi - sum_{j=1, j/=i}^{n} aij xj^{k})

function x=jacobi(A,b,x0,eps)
    n = size(A,1);
    x = x0;
    xk = x;
    cont = 0;
    for i=1:n 
        suma = 0
        for j = 1:n
            if (i<>j)
                suma = suma + A(i,j)*xk(j);
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
                    suma = suma + A(i,j)*xk(j);
                end
            end                
            x(i) = 1/A(i,i)*(b(i)-suma)
        end
        cont = cont+1;
     end
     disp(cont) ;
endfunction

// Gauss-Seidel
// xi^(k+1) = 1/aii (bi - sum_{j=1}^{i-1} aij xj^{k+1}
//                      - sum_{j=i+1}^{n} aij xj^{k})

function x=gauss(A,b,x0,eps)
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


function x=sor(A,b,x0,w,eps)
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
        x(i) =(1-w)*x(i) + w/A(i,i)*(b(i)-suma)
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
            x(i) =(1-w)*x(i) + w/A(i,i)*(b(i)-suma)
        end
        cont = cont+1;
     end
     disp(cont) ;
endfunction

// Omega óptimo
function w = omega_SOR(A)
    // Entrada: A matriz nxn tridiagonal y definida positiva
    // Salida: w óptimo del método de SOR
    
    [n,m] = size(A)
    T_j = eye(n,n)-diag(1./diag(A))*A
    autovalores = spec(T_j)
    rho = max(abs(autovalores))
    w = 2/(1+sqrt(1-rho^2))
    
endfunction

A = [4,3,0;3,4,-1;0,-1,4]
b = [24;30;-24]
x0 = [1;0;0] // Condición inicial
