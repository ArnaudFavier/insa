function application_4
    % Rectangle
    l = 2
    L = 3

    % Lecture des deux images
    [d, map1] = imread('PhotoTexte.png');
    [iR, map2] = imread('PhotoRef.png');
    D = fft2(d);
    IR = fft2(iR);
    
    % Cr�ation du filtre
    h = zeros(512, 512);
    for u=1:512
        for v=1:512
            if any(u == (257 - l:257 + l)) && any(v == (257 - L:257 + L))
                h(u, v) = 1/((2*l+1)*(2*L+1));
            end
        end
    end
    H = fft2(fftshift(h));
    
    % Calcul du bruit
    DR = IR .* H;
    dr = ifft2(DR);
    b = dr - round(dr);
    B = fft2(b);
    
    % Calcul de W
    W = (1./H) .* ((abs(H).*abs(H))./(abs(H).*abs(H) + (abs(B).*abs(B))./(abs(IR).*abs(IR)) ));
    
    % Calcul de I
    I = D .* W;
    i = ifft2(I);
    
    % Affichage de l'image de r�f�rence flout�e
    figure(1)
    image(real(dr))
    colormap(map2)
    figure(2)
    image(affIm(DR))
    colormap(map2)
    
    % Affichage de l'image id�ale
    figure(3)
    image(real(i))
    colormap(map1)
    figure(4)
    image(affIm(I))
    colormap(map1)
end

function affI = affIm(I)
    affI = abs(I) + 1;
    maxi = max(max(affI));
    mini = min(min(affI));
    affI = (log(affI)-log(mini))/(log(maxi)-log(mini))*255;
end