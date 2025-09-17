// Ejercicio 1.
// Recibe un polinomio con discriminante positivo y devuelve un vector
// con sus raices calculadas de forma robusta.
// misraices: polinomio -> [real, real]
function r = misraices(p)
    a = coeff(p, 2)
    b = coeff(p, 1)
    c = coeff(p, 0)
    
    if b >= 0 then 
        r(1) = (-b - sqrt(b**2 - 4*a*c)) / (2*a)
        r(2) = (2*c) /(-b - sqrt(b**2 - 4*a*c))
    else 
        r(1) = (2*c) /(-b + sqrt(b**2 - 4*a*c))
        r(2) = (-b + sqrt(b**2 - 4*a*c)) / (2*a)
    end
endfunction

// Ejercicio 2
// Suma de mayor a menor
function s = suma1()
    s = 0.9222 * 10**4 + 0.0912 * 10**4 + 0.0324 * 10**4 + 0.0284 * 10**4
endfunction

// Suma de menor a mayor
function s = suma2()
    s = 0.2849 * 10**3 + 0.3244 * 10**3 + 0.9123 * 10**3 + 9.222 * 10**3
endfunction

// Suma normal
function s = suma3()
    s = 0.9222 * 10**4 + 0.9123 * 10**3 + 0.3244 * 10**3 + 0.2849 * 10**3
endfunction

/* 
 * Se obtiene un resultado con menor error al sumar de menor a mayor ya que
 * no se pierde ninguna cifra significativa.
 */

 // Ejercicio 3
 // b)
 // Dado un polinomio p y un valor x0 retorna p(x0)
 // mihorner: polinomio, real -> real
function b0 = mihorner(p, x0)
    grado = degree(p)
    b0 = coeff(p, grado)

    for i = grado-1:-1:0
        b0 = coeff(p, i) + x0 * b0 
    end
endfunction

//d)
// Dado un polinomio p y un valor x0. Devuelve un vector con primera componente
// igual a p(x0) y segunda componente p'(x0)
// horner_derivat: polinomio, real -> [real, real]
function v = horner_derivat(p, x0)
    grado = degree(p)
    bi = coeff(p, grado)
    Dp0 = bi 

    for k = grado-1:-1:0
        bi = coeff(p, k) + x0 * bi
        if k > 0 then
            Dp0 = bi + x0 * Dp0
        end
    end

    v(1) = bi
    v(2) = Dp0
endfunction

// Ejercicio 4

function Df = derivar(f, v, n, h)
    if n == 0 then
        Df = f(v)
    else
        Df = (derivar(f, v+h, n-1, h) - derivar(f, v, n-1, h)) / h
    end
endfunction

function valor = derivar2(f, v, n, h)
    deff("y=DF0(x)", "y=f(x)")
    if n == 0 then 
        valor = DF0(v)
    else
        for i = 1:(n-1)
            deff("y = DF"+string(i)+"(x)","y = numderivative(DF"+string(i-1) + ", x, " + string(h) + ", 4)")
        end

        deff("y = DFn(x)", "y = numderivative(DF"+string(n-1)+", x, " + string(h) + ", 4)")
        valor = DFn(v)
    end
endfunction

function Df = derivar_gpt(f, v, n, h)
    Df = 0
    for k = 0:n
        coef = (-1)^k * nchoosek(n, k)
        Df = Df + coef * f(v + (n-k)*h)
    end
    Df = Df / (h^n)
endfunction

// Ejercicio 5

function T = taylor(f, a, n)
    x = poly(0,"x")
    p = f(a)

    for i = 1:n
        p = p + (1/factorial(i)) * derivar2(f, a, i, 0.001) * (x-a)^i
    end

    T = p
endfunction









