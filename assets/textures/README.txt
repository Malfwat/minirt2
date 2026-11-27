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


Materiaux pour plan, cylindre et cone
=====================================

Dix cartes supplementaires, en paires couleur / normales, 1024 x 1024
chacune (en-tete "P6\n1024 1024\n255\n", 9 437 199 octets par fichier).
Les cartes de normales sont en convention OpenGL : le vert pointe vers le
haut de l'image, le bleu vers l'exterieur de la surface, et z vaut 255 sur
les texels plats.

Les cinq materiaux sont raccordables sans couture, ce qui compte pour un
cylindre ou un cone enroules.

    paving_color.ppm / paving_normal.ppm              paves gris, mousse dans les joints
    bricks_color.ppm / bricks_normal.ppm              briques irregulieres, mortier creux
    metalplates_color.ppm / metalplates_normal.ppm    tole diamantee sombre
    rock_color.ppm / rock_normal.ppm                  roche brute, relief le plus marque
    rust_color.ppm / rust_normal.ppm                  metal rouille

    Source : ambientCG (https://ambientcg.com), licence CC0, domaine public :
    aucune attribution requise. Fichiers d'origine en JPEG 1K, convertis en
    PPM binaire sans autre traitement que le redimensionnement.

    Relief mesure sur la carte de normales (ecart-type des composantes x et y,
    sur 255) : rock 25,0 / 31,5 ; paving 21,9 / 23,2 ; metalplates 17,0 / 11,5 ;
    rust 10,0 / 7,8 ; bricks tres marque visuellement.
