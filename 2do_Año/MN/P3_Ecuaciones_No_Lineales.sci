function r = metodo_biseccion(f, a, b, e)
    k = ceil(log((b-a)/e)/(log(2)))

    fa = f(a)
    fb = f(b)
    c = (b+a)/2
    fc = f(c)

    while k > 0 
        if fa*fc < 0 then
            b = c 
            fb = fc
        else
            a = c 
            fa = fc
        end

        c = (b+a)/2
        fc = f(c)
        k = k-1
    end

    r = c
endfunction

function r = metodo_newton(f, x0, t)
    old = x0
    new = old - f(old)/numderivative(f, old, 1e-4, 4)
    
    while abs(new - old) > t 
        old = new
        new = old - f(old)/numderivative(f, old, 1e-4, 4)
    end
    
    r = new
endfunction

function salida = newton_rabs(f, x0, tol, iter)
    i = 0
    x1 = x0 - f(x0)/numderivative(f, x0)

    while abs(x1-x0) > tol && i < iter
        i = i+1
        x0 = x1
        x1 = x0 - f(x0)/numderivative(f, x0)
    end

    if abs(x1-x0) > tol then
        disp("Se alcanzo el maximo de iteraciones")
    end

    disp(i)

    salida = x1
endfunction

function y = F(x)
    f1 = x(1)^2 + x(2)^2 - 290
    f2 = x(1) + x(2) -24
    y = [f1;f2]
endfunction

function salida = metodo_newton_multi(f, x0, tol, iter)
    warning("off")
    i = 0
    x1 = x0 - inv(numderivative(f, x0)) * f(x0)

    while norm(x1-x0, 2) > tol && i < iter
        i = i+1
        x0 = x1
        x1 = x0 - inv(numderivative(f, x0)) * f(x0)
    end

    if norm(x1-x0, 2) > tol then
        disp("Se alcanzo el maximo de iteraciones")
    end

    disp(i)

    salida = x1
endfunction


function salida = metodo_secante(f, x0, x1, tol, iter)
    i = 0
    x2 = x1 - f(x1) * (x1-x0) / (f(x1) - f(x0))

    while abs(x2 - x1) > tol && i < iter
        x0 = x1
        x1 = x2
        x2 = x1 - f(x1) * (x1-x0) / (f(x1) - f(x0))
    end

    if abs(x2-x1) > tol then
        disp("Se alcanzo el maximo de iteraciones")
    end

    disp(i)

    salida = x2
endfunction


function salida = metodo_regula_falsi(f, a, b, tol, iter)
    i = 0
    c = a - f(a) * (a-b) / (f(a) - f(b))
    fa = f(a)
    fb = f(b)
    fc = f(c)

    while abs(b - c) > tol && i < iter
        if fa*fc < 0 then
            b = c
            fb = fc
            else
            a = c
            fa = fc
        end

        c = a - f(a) * (a-b) / (f(a) - f(b))
        fc = f(c)
        i = i+1
    end

    if abs(b-c) > tol then
        disp("Se alcanzo el maximo de iteraciones")
    end

    disp(i)

    salida = c
endfunction

function salida = metodo_punto_fijo(g, x0, tol, iter)
    i = 0
    x1 = g(x0)

    while abs(x1-x0) > tol && i < iter
        x0 = x1
        x1 = g(x0)
    end

    if abs(x1-x0) > tol then
        disp("Se alcanzo el maximo de iteraciones")
    end

    disp(i)

    salida = x1
endfunction


function y = cos_n(x0, n)
    y = x0

    for i = 1:n
        y = cos(y)
    end
endfunction

