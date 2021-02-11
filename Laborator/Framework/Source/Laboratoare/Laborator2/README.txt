Cristian Cotovanu 336CA
Laborator 2 EGC

2. Am creat cubul conform
3. Am incarcat geometria pe GPU prin VAO, VBO si IBO cu comenzile din laborator. 
Se testeaza prin afisarea celor 2 cuburi identice, unul ("cube") fiind afisat cu functia de pe GPU, 
iar celalat ("testCube") cu functia standard din framework.
4. Am desenat tetraedrul dupa cum se poate vedea - "pyramid"
5. F2 schimba perspectiva culling-ului din front in back si invers.
6. Am creat patratul prin 2 triunghiuri, fiecare avand normala intr-un sens opus fata de cealalta, 
astfel incat schimbarea culling-ului sa faca unul dintre triunghiuri sa dispara.

Bonus: 
360 de grade sunt impartite in LINES_COUNT parti astfel incat punctele asociate varfurilor 
sa aiba coordonate de forma (sin(degree.ToRadians), cos(degree.ToRadians))
Incep de la 0 grade, crescand apoi cu 360 / Lines_Count, pana ajung la 360.
Numarul de linii din care se face cercul poate fi modificat prin constanta LINES_COUNT din Laborator2.h 
Raza cercului poate fi de asemenea modificata prin constanta CIRCLE_RADIUS din Laborator2.h