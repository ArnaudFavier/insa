function [] = x6_periodique(a, b, N, o)
    Te = (b-a)/N;
    Fe = 1/Te;
    t = a:Te:b-Te;
    f = -Fe/2:Fe/N:Fe/2-Fe/N;

    x = zeros(N, 1);
    for k=1:N
        if cos(2*pi*o*t(k)) > 0
            x(k) = 1;
        end
    end
    
    plot(t, x);
    pause();
    
    X = tfour(transpose(x));
    plot(f, X);
    pause();
    
    xinv = tfourinv(X);
    plot(t, xinv);
    pause();
end