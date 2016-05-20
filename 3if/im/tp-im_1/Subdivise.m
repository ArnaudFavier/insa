function [ subterrain ] = Subdivise(terrain, alpha)

    [m, n] = size(terrain);
    subterrain = zeros(2*m - 1, 2*n - 1);
    [sm, sn] = size(subterrain);
    
    % 1. Diamond
    subterrain(1:2:sm, 1:2:sn) = terrain;
    
    subterrain(2:2:sm, 2:2:sn) = (terrain(1:m-1, 1:n-1) + ...
        terrain(2:m, 1:n-1) + terrain(1:m-1, 2:n) + ...
        terrain(2:m, 2:n))/4 + randrange(-alpha, alpha, subterrain(2:2:sm, 2:2:sn));
    
    % 2. Square
    
    % 2.1 Colonnes paires
    subterrain(3:2:sm-1, 2:2:sn-1) = (subterrain(3:2:sm-2, 1:2:sn-2) ... % Gauche
                                   + subterrain(3:2:sm-2, 3:2:sn)    ... % Droite
                                   + subterrain(2:2:sm-2, 2:2:sn)    ... % Haut
                                   + subterrain(4:2:sm, 2:2:sn))/4;  ... % Bas
                                   + randrange(-alpha, alpha, subterrain(3:2:sm-1, 2:2:sn-1));
    % 2.2 Colonnes impaires
    subterrain(2:2:sm-1, 3:2:sn-1) = (subterrain(2:2:sm, 2:2:sn-2)   ... % Gauche
                                   + subterrain(2:2:sm, 4:2:sn)      ... % Droite
                                   + subterrain(1:2:sm-2, 3:2:sn-2)  ... % Haut
                                   + subterrain(3:2:sm, 3:2:sn-2))/4 ... % Bas
                                   + randrange(-alpha, alpha, subterrain(2:2:sm-1, 3:2:sn-1));
    
    % 2.3 Limites
    subterrain(1:sm-1:sm, 2:2:sn-1) = (subterrain(1:sm-1:sm, 1:2:sn-1) ...
                                    + subterrain(1:sm-1:sm, 3:2:sn))/2 ...
                                    + randrange(-alpha, alpha, subterrain(1:sm-1:sm, 2:2:sn-1));
    subterrain(2:2:sm-1, 1:sn-1:sn) = (subterrain(1:2:sm-1, 1:sn-1:sn) ...
                                    + subterrain(3:2:sm, 1:sn-1:sn))/2 ...
                                    + randrange(-alpha, alpha, subterrain(2:2:sm-1, 1:sn-1:sn));

end

function [ v ] = randrange(lower, upper, m)
    v = rand(size(m)) * (upper-lower) + lower;
end
