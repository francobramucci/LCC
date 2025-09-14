// Ejercicio 1.
// Recibe un polinomio con discriminante positivo y devuelve un vector
// con sus raices calculadas de forma robusta.
// misraices: polinomio -> vector
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

function s = suma3()
    s = 0.9222 * 10**4 + 0.9123 * 10**3 + 0.3244 * 10**3 + 0.2849 * 10**3
endfunction

/* 
 * Se obtiene un resultado con menor error al sumar de menor a mayor ya que
 * no se pierde ninguna cifra significativa.
 */

 // Ejercicio 3
 // b)
 // Dado un polinomio y un valor, evalua dicho polinomio en ese valor
 // mihorner: polinomio, real -> real
function b0 = mihorner(p, x0)
    grado = degree(p)
    b0 = coeff(p, grado)

    for i = grado-1:-1:0
        b0 = coeff(p, i) + x0 * b0 
    end
endfunction

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







