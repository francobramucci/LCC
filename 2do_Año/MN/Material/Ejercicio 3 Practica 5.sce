// Ejercicio 3
function x= tridiagonal(n)
    // Entrada: n= dimensión de la matriz tridiagonal
    // Salida: x = matriz tridiagonal
    infsupD=-1*ones(1,n-1)
    D= 2*ones(1,n)
    x=diag(infsupD,-1)+ diag(D)+diag(infsupD,1)
endfunction


function x= Ninv(n)
    // Entrada: n= dimensión de la matriz tridiagonal
    // Salida: x = inversa de la matriz tridiagonal del ejercicio 3
   for j=1:n
       for i=1:n
           //if i<j then
               //N_inv(i,j)=0
           //end
           if i>=j then
              N_inv(i,j)=1/2**(i-j+1)
           end
       end
   end
   x=N_inv
endfunction


function x= MatrizGauss(n)
    I=eye(n,n)
    A=tridiagonal(n)
    N_inv=Ninv(n)
    x=I-N_inv*A //Matriz de Gauss-Seidel
endfunction



function x= MatrizGauss2(A)
    [nA,mA]=size(A)
    I=eye(nA,nA)
    //N=diag(diag(A,-1),-1)+diag(diag(A))
    N=tril(A)
    invN=inv(N)
    x=I-invN*A //Matriz de Gauss-Seidel
endfunction

function x= M_G(n)
   zero=zeros(n,n)
   col=(0.5)^[1:n]'
   for k=1:n-1
       zero(k:n,k+1)=col(1:(n-k+1))
   end
   x=zero
endfunction


