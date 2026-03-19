function y=fe(x)
    y = (x+2)^2-1;
endfunction

function salida = newton(f,x0,tol,iter)
    i = 0;
    x1 = x0 - f(x0)/numderivative(f,x0);
    while abs(x1-x0)>tol && i < iter
        i = i+1;
        x0 = x1;
        x1 = x0 - f(x0)/numderivative(f,x0);
    end
    if (abs(x1-x0)>tol) then disp('Se alcanzo el máximo de iteracciones');
    end
    disp(i);
    salida = x1;
endfunction

function y=F(x)
    f1 = x(1)^2+x(2)^2-290
    f2 = x(1)+x(2)-24
    y = [f1;f2]
endfunction

function salida = newton_sis(f,x0,tol,iter)
    warning("on");
    i = 0;
    x1 = x0 - inv(numderivative(f,x0))*f(x0);
    while (norm(x1-x0,2))>tol && i < iter
        i = i+1;
        x0 = x1;
        x1 = x0 - inv(numderivative(f,x0))*f(x0);
    end
    if (norm(x1-x0,2))>tol then disp('Se alcanzo el máximo de iteracciones');
    end
    disp(i);
    salida = x1;
endfunction
/*
--> newton_sis(F,[1;16],10^(-16),100)

   8.
 ans  =

   11.0000
   13.0000
*/


