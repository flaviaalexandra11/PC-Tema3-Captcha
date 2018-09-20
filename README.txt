README

citire:
Citim cu ajutorul functiilor readInput() si readCaptcha() culorile in B, G si R si elemtele ce trebuie sterse in vectorul toDel. 
Detaliile despre imagine sunt pastrate in fileheader si infoheader si bitmap-ului ii asociem o matrice structura a in care tinem minte culorile (prin campurile B, M, P). 
Functia name() stabileste numele fiserelor rezultate in urma rularii.

task1:
In functia newColor modificam in matricea a locurile unde nu este culoarea alb, cu culoarea ceruta; cream noul fisier bmp care va avea headerul la fel ca si cel initial si ne vom folosi de matricea a si variabilele B, G si R pentru a scrie informatiile in bitmap.
Padding-ul se calucleaza tinand cont de faptul ca fiecare linie din bitmap incepe la un nr divizibil cu 4 si ca fiecare pixel are 3 biti pentru culori. 

task2:
In functia templates() ne vom folosi de un vector de matrice 5X5 (templ) unde vom tine minte toate cifrele iar in pixelMatrix() vom crea o matrice mat in care vom simula continutul astfel: cifrele vor fi scrie cu 'X' si culoarea alb cu '.'.
Cautam in matrice cu functia checkDigit() cifrele din templ si le tinem minte pe cele gasite in vectorul v. Totodata, tinem minte in vectorul poz(de tip number) detaliile despre fiecare element ce apare in captcha. 
In cele din urma, scriem elemntele din vector in noul fisier txt.

task3:
In functia delDigit() deschidem noul fisier si completam header-ul la fel ca la task1. Cum la taskul trecut cautarea in matricea mat cu 'X' si '.' s-a facut de la dreapta la stanga si de jos in sus, trebuie sa reordonam vectorii in care sunt pastrate valorile din captcha. In vectorul rpoz de tip number tinem minte pentru fiecare element: cifra, coordonatele unde incepe (intr-o cautare dreapta-stanga, jos-sus), si culorile (B, G, R). 
Ne vom folosi de acest vector pentru a rescrie matricea mat si a, apoi, vom folosi matricea a ca sa completam bitmap-ul noii imagini(ca la task1). 

Popescu Flavia-Alexandra 311CD
  