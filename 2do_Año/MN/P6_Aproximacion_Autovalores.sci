// a)
function c = circulos_greshgorin(A)
    n = size(A,2)
    for i=1:n
        c(i,1) = A(i,i)
        c(i,2) = sum(abs(A(i,:))) - abs(A(i,i))
        disp("|lambda - " + string(c(i,1)) + "| <= " + string(c(i,2)))
    end
endfunction

Aa = [1 0 0; -1 0 1; -1 -1 2];
Ab = [1 0 0; -0.1 0 0.1; -0.1 -0.1 2];
Ac = [1 0 0; -0.25 0 0.25; -0.25 -0.25 2];
Ad = [4 -1 0; -1 4 -1; -1 -1 4];
Ae = [3 2 1; 2 3 0; 1 0 3];
Af = [4.75 2.25 -0.25; 2.25 4.75 1.25; -0.25 1.25 4.75]

//---------------------------------------------------------------------------//

// 2)

function cotas_raices(p)
    n = size(p,2)
    disp("|r| <= 1 o |r + " + string(p(n-1)) + "| <= " + string(sum(abs(p(1:n-2)))) )
endfunction

cotas_raices([1 -1 1 -1 1 -4 1])
cotas_raices([1 0 0 0 0 0 0 0 0 8 1])

//---------------------------------------------------------------------------//

// 3)
eps = 1e-2

A = [1 -1 0; -2 4 -2; 0 -1 1+eps]

// i)
p = poly(A, "x")
r = roots(p)

// ii)

eigens = spec(A)

//---------------------------------------------------------------------------//

// 4)
function circ(r,x,y)
    xarc(x-r,y+r,2*r,2*r,0,360*64)
endfunction

function gres(A)
    [n,m] = size(A);
    centros = diag(A);
    radios = sum(abs(A),'c') - abs(centros) ;
    
    // buscamos calcular un rectángulo que contenga a todos los circulos
    // esquina inferiro izquierda
    
    mx = round (min(centros - radios)-1);
    my = round (min(-radios)-1);
    
    // esquina superior derecha
    
    Mx = round(max(centros+radios)+1);
    My = round(max(radios)+1);
    
    rectangulo = [mx my Mx My];
    
    // dibujamos los autovalores
    plot2d(real(spec(A)),imag(spec(A)),-1,"031","",rectangulo)
    replot(rectangulo); // reeplaza al rect
    xgrid();
    
    for i=1:n
        circ(radios(i),centros(i),0)
    end
    
endfunction

//---------------------------------------------------------------------------//

// 5)
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

A1 = [6 4 4 1; 4 6 1 4; 4 1 6 4; 1 4 4 6];
A2 = [12 1 3 4; 1 -3 1 5; 3 1 6 -2; 4 5 -2 -1];

metodo_potencia(A1, [1 1 1 1]', 1e-2, 100)
metodo_potencia(A2, [1 1 1 1]', 1e-2, 100)

function comparacion_mpotencia(A, z0, maxiter)
    iter = 1

    autovalores = spec(A)
    [_, j] = max(abs(autovalores))
    rval = autovalores(j)
    valor = 0

    w = A * z0
    z1 = w / norm(w, %inf)

    [_, j] = max(abs(w));
    valor = w(j) / z0(j);
    z1 = w/valor;

    while (iter <= maxiter - 1)
        disp("Diferencia: " + string(valor - rval) + " (it " + string(iter) + ")")
        z0 = z1;
        w = A * z0;
        z1 = w / norm(w, %inf)
        [_, j] = max(abs(w));
        valor = w(j) / z0(j);
        z1 = w / valor;

        iter = iter + 1;
    end

    disp("Iteraciones: " + string(iter));    
endfunction



