Textures de demonstration (carte de la Terre)
=============================================

Format : PPM binaire, magic P6, maxval 255, trois octets par pixel dans
l'ordre rouge, vert, bleu. Aucun commentaire dans l'en-tete.

    en-tete  "P6\n1024 512\n255\n"        15 octets
    pixels   1024 x 512 x 3               1 572 864 octets
    total                                 1 572 880 octets

Un pixel (x, y) commence a l'octet 15 + (y * 1024 + x) * 3.

Les trois cartes sont equirectangulaires : la colonne 0 est la longitude
-180 degres, la ligne 0 le pole nord. C'est exactement ce que produit le
mapping latitude / longitude du damier de sphere, donc les coordonnees
u et v de la sphere servent directement d'indices de texel.


earth_atmos_2048.ppm   couleur, avec les nuages
    Source : depot three.js (licence MIT), examples/textures/planets/
    earth_atmos_2048.jpg, redimensionne en 1024x512 et converti en PPM.
    L'image d'origine vient des cartographies NASA Visible Earth, domaine
    public.

earth_normal_2048.ppm  carte de normales, tangente a la surface
    Source : meme dossier du depot three.js (MIT), earth_normal_2048.jpg,
    meme conversion. Chaque texel encode une normale dans le repere
    tangent : rouge = direction u, vert = direction v, bleu = normale.
    Permet un relief sans gradient ni epsilon.

earth_height.ppm       relief en niveaux de gris
    Source : depot turban/webgl-earth, images/elev_bump_4k.jpg, meme
    conversion. Oceans noirs, continents clairs, les plus hauts sommets
    en blanc. C'est la carte a utiliser si le relief est calcule par
    differences finies sur la hauteur.
