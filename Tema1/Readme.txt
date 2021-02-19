Micut Andrei-Ion
Grupa 331CB



										Bow and arrow
										  ~Tema1~


	Tema este structurata astfel:
		- Object2D.cpp - mi-am creat formele cerute in enuntul temei, desenarea scenei(fisier bazat pe Laboratorul 3)
		- Tema1.cpp - am realizat functionalitatile obligatorii(animatia obiectelor tinta, stabilirea pozitiei arcului cu tastele, stabilirea directiei de tragere si deplasarea sagetii, coliziunea shuriken-personaj, sistemul de tragere, animatie tinte doborate si actualizarea scorului), iar pe langa acestea am creat un punct ce se misca in cadrul ferestrei dupa mouse, 3 inimi ce reprezinta vietile player-ului si mesaje friendly inainte de a incepe jocul si dupa ce jucatorul si-a epuizat vietile.
		- Object2D.h - in acest fisier se afla antetele functiilor de crearea a mesh-urilor din object2D.cpp.
		- Tema1.h - acest fisier contine functiile folosite in Tema1.cpp, variabilele pentru translatiile obiectelor din scena, unghiul dintre mouse si arc, dimensiunile laturii fiecarui obiect in parte, coordonatele centrelor obiectelor, precum si variabilele boolene pentru inceperea jocului, terminarea jocului, prezentarea mesajelor friendly pentru a incepe jocul/termina jocul impreuna cu scorul aferent, variabile pentru apasarea mouse-ului, coliziunea cu player-ul, cu baloanele, unghiul dintre mouse,scorul si vitezele obiectelor.
		- Transform2D.h - contine functiile pentru translatie, scalare, rotatie preluate din Laboratorul 3.
		- Main.cpp - fisier preluat din arhiva Laboratorului 3.

	Object2D.cpp:

		- Crearea powerbar-ului am realizat-o prin crearea unui patrat, unde mi-am pozitionat vertecsii si indicii, umplandu-l cu ajutorul functiei GL_LINE_LOOP
		- Crearea arcului a fost realizat dintr-un dreptunghi la capatul caruia se regaseste un triunghi. Acestea 2 au fost realizate din 3 triunghiuri si cu ajutorul functiei GL_TRIANGLES.
		- Crearea poliliniei de la capatul balonului am realizat-o prin intersectia mai multor linii si cu ajutorul functiei GL_LINES.
		- Crearea vietilor player-ului am realizat-o din mai multe tringhiuri, mai exact 4 triunghiuri, prin umplerea acestora cu functia GL_TRIANGLE_FAN.
		- Crearea shuriken-ului a fost realizata din 4 triunghiuri unite intr-un punct si cu ajutorul functiei GL_TRIANGLES.
		- Pentru a crea baloanele, mai intai am creat un cerc cu ajutorul functiilor trigonometrice sin, cos si cu ajutorul variabilei TAU  ce reprinza o bucata din lungimea cercului(2 * PI). In cele din urma, am realizat cercul din mai multe triunghiuri umplute care, ulterior, au avut parte de o scalare neuniforma pentru un aspect cat mai realistic.
		- Crearea punctului ce ne ajuta pentru a fixa mai bine locul unde dorim sa tragem(punctul corespunzator mouse-ului) l-am realizat cu ajutorul functiei de creare a baloanelor, doar ca acesta a suferit, ulterior, o scalare uniforma.
		- Crearea arcului ce reprezinta si player-ul jocului a fost creat pe baza functiei de creare a unui arc de cerc, la fel ca si crearea baloanelor si a punctului, doar ca a trebuit ca plecarea pentru constructia arcului de cerc sa fie facuta mai tarziu(acest lucru explica si initializarea varibilei i cu valoarea 12.95). Nu ne dorim ca arcul de cerc sa fie umplut si din acest motiv am folosit functia GL_LINE_STRIP.


	Tema1.cpp:
		
		- In functia Init am realizat initializarea centrelor obiectelor in functie de latura lor, initilizarea factorilor de translatie, respectiv scalare. Apoi mi-am definit obiectele ce urmeaza sa fie puse in scena.
		- Functia FrameStart a fost pastrata din laborator, doar culoarea acesteia a fost modificata
		- In functia Update se afla "bucataria" temei. Inainte de inceperea jocului se va afisa un mesaj friendly, arcul(rotit pentru a se afla de-a lungul axei OY) si sageata ce sunt plasate corespunzator pentru inceperea jocului. Dupa ce jocul a inceput (dupa apasarea tastei P), baloanele se vor translata pe axa OY+ in functie de deltaTimeSeconds, shuriken-ul se va roti in jurul propriului centru si se va translata de la resolution.x(la noi, 1280) la 0, apoi va reveni la resolution.x, arcul impreuna cu sageata se vor roti in functie de coordonatele unde se afla mouse-ul. Arcul a trebuit sa fie translatat in functie de factorii specificati in Init pentru o mai buna observare, iar apoi am calculat unghiul dintre coordonatele mouse-ului si factorii de translatie ai arcului pentru a face ca arcul sa se roteasca dupa mouse. Daca mouse-ul nu este actionat, atunci sageata se va roti impreuna cu arc in jurul centrului sau. Daca mouse-ul este actionat, powerbar-ul va realiza o scalare pe OX+, iar in functie de cat timp este apasat mouse-ul, scalarea va creste si viteza in functie de scalare. Daca se va depasi o anumita valoare, dupa ce am terminat apasarea mouse-ului, powerbar-ul va reveni la scalarea initiala. In continuare, dupa ce am eliberat mouse-ul, atunci sageata se va translata pe o directie data de coordonatele mouse-ului la finalizarea apasarii si unghiul pe care il face translatia arcului si mouse-ul.  In cazul in care baloanele au fost atinse de varful sagetii, atunci se va realiza o scalare uniforma descrescatoare pana cand factorii de scalare ajung la 0, atat pentru balon, cat si pentru polilinie, iar scorul va creste cu 100, daca balonule este rosu sau va scadea cu 100, daca este galben, altfel acestea se vor deplasa cu o viteza constanta pe OY. Daca shuriken-ul atinge player-ul, atunci acestuia ii vor scadea vietile (inimile se vor scala tot ca in cazul in care baloanele sunt atinse de varful sagetii; am folosit anumite valori, deoarece contactul dintre shuriken si player dureaza un timp), iar daca acesta ramane fara vieti va aparea ecranul negru alaturi de un mesaj friendly cu privire la faptul ca jocul s-a terminat si ni se va afisa si scorul aferent. La finalul acestei functii se afla modalitatea de calculare a coliziunii player-ului cu shuriken-ul (cerc la cerc).
		- In functia OnInputUpdate am realizat miscarea arcului si a sagetii impreuna cu powerbar-ul in functie de tastele W si S. Am avut in vedere ca deplasarea sa se faca astfel incat powerbar-ul sa raman in cadrul ecranului, la fel si arcul sau sageata si sa se produca aceeasi miscare pentru toate 3. Doar daca sageata porneste deplasarea, aceasta nu se va mai deplasa alaturi de arc si powerbar.
		- In functiile CollisionRedBallon si ColissionYellowBallon am calculat distanta dintre baloane si varful sagetii.
		- In functia OnMouseMove am calculat coordonata pe OY a mouse-ului (am realizat o scadere, deoarece mouse-ul se deplasa in sens opus directiei date)si am retinut coordonata pe OX si, de asemenea, am calculat si unghiul pe care-l formeaza translatia arcului si mouse-ul.
		- In functia OnMouseBtnPress am verificat daca mouse-ul este apasat, iar, in acest caz, voi retine unghiul translatiei arcului cu mouse-ul.
		- In OnMouseBtnRelease, daca depasesc scalarea powerbar-ului, atunci ma asigur sa fie transmis acest lucru si in functia Update. Daca mouse-ul nu mai este apasast, atunci vom trage cu sageata.(shoot = true)
		- Functia GameEnd imi va realiza terminarea jocului printr-o variabila booleana.


	Transform2D.h:
		- In acest fisier am scris matricile de translatie, scalare si rotatie precum sunt prezentate in laborator.

	Main.cpp:
		- Preluat din laborator.(nemodificat)



	
	Noutati aduse pe langa functionalitatile obligatorii:
		- Mesaj friendly
		- Inceperea jocului se va face prin apasarea tastei P.
		- Am adaugat un obiect nou, fireball care ii va lua arcasului 2 vieti daca este lovit din plin.
		- 3 inimi ce reprezinta vietile player-ului
		- Am mai adaugat baloane in scena 
		- Baloanele rosii au viteza de deplasare cu 1/2 mai mare decat a celor galbene
		- Dupa ce player-ul si-a pierdut vietile, ecranul se va face negru, ni se va afisa un mesaj friendly in consola si, de asemenea, scorul
		



