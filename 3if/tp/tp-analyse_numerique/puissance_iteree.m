function [v, V] = puissance_iteree(A, l)
% Initialisation
    [A_i, A_j] = size(A);
    Y0 = rand(A_j, 1);
    Y = Y0;
    
    while true
        % Passage � la prochaine it�ration.
        X = Y/norm(Y);
        Y = A*X;
        
        % V�rifier la colin�rarit�.
        [M, I] = max(abs(Y));
        k = Y(I)/X(I);
        if norm(Y - k*X) < l
            break
        end
    end
    
    v = k;
    V = Y;
end