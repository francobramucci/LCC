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

function r = metodo_secante(f, x0, x1)


endfunction

