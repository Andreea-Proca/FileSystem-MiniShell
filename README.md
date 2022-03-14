# FileSystem-MiniShell
 C, Linux

  Directorul principal este "home" si este declarat si alocat la inceput; acesta este si directorul curent initial.
    Citirea se face pe cate o linie care este retinuta inr-un buffer, iar comanda citita este impartita in mai multe
siriuri de caractere, in functie de numarul de spatii gasite, aceste fiind delimitatorii dintre cuvinte.
    Se apleleaza functia corespunzatoare primului cuvant, care reprezinta comanda data.   
****    
    Functia "touch" creeaza un fisier nou cu numele dat in directorul curent, daca acest nu exista deja.
    Functia "mkdir" creeaza un director nou cu numele dat in directorul curent, daca acest nu exista deja.
    Functia "ls" parcurge si afiseaza toate directoarele si apoi fisierele din directorul curent.
    Functia "rm" cauta in directorul curent fisierul cu numele dat si daca acesta exista, il sterge.
    Functia "rmdir"  cauta in directorul curent directorul cu numele dat pe care il parcurge si il sterge,daca acesta exista, in mod recursiv, coborand in ierarhia acestuia pentru a sterge toti fii si fii acestora si fisierele lor, samd.
    Functia "cd" cauta in directorul curent directorul cu numele dat si daca exista, acesta devine directorul
curent. In cazul in care directorul cautat este "..", atunci se urca in ierarhia diretoarelor, parintele
devenind noul director curent.
    Functia "pwd" afiseaza calea completa catre directorul cu numele dat, care este retinuta intr-un sir de 
caractere, urcand in ierarhia diretoarelor accesand parintele directorului si adaugand la inceputul sirului
numele acestuia pana se ajunge la directorul principal, "home"; "/" este folosit ca delimitator de cale.
    Functia "tree" parcurge recursiv ierarhia diretoarelor pornind de la directorul dat si afiseaza toate
directoarele si fisierele continute sub forma de arbore. Functia "print_sp" afiseaza spatii in functie de
nivelul in care ne aflam in ierarhie pentru un fisier sau director, raportat la nivelul directorului dat care este 0.
    Functia "mv" modifica numele unui fisier sau director dat. Mai intai cauta daca exista fisierul/directorul 
cu numele dat si daca nu exista niciun fisier/director cu noul nume. Daca conditiile sunt indeplinite, numele este
schimbat in cel nou si fisierul/directorul este mutat la sfarsitul listei de fisiere/directoare a parintelui sau.
****  
   La final, se elibereaza bufferul care retine ultima comanda data si apoi se apleleaza functia "stop" 
care elibereaza toata memoria alocata printr-o parcurgere recursiva si opreste programul.
