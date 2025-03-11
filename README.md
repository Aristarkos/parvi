# Parallel Zip - Käyttöjärjestelmät ja Systeemiohjelmointi kurssi

Tämä on LUT-yliopiston kurssin *Käyttöjärjestelmät ja Systeemiohjelmointi* harjoitustyö, jossa toteutettiin rinnakkainen pakkausohjelma **pzip**.

**Tiedostot**
Projektissa on seuraavat tiedostot:

- `wzip.c` – Perinteinen yksisäikeinen pakkausohjelma  
- `wunzip.c` – Pakatun tiedoston purkuohjelma  
- `pzip.c` – Rinnakkainen pakkausohjelma, joka hyödyntää useita säikeitä  
- `test.txt` – Testitiedosto, jota voi käyttää ohjelmien testaamiseen  

**Ohjelman kääntäminen**
Jokainen ohjelma täytyy kääntää ennen käyttöä. Käänsin näillä seuraavilla komennoilla:

gcc -o wzip wzip.c -Wall -Werror
gcc -o wunzip wunzip.c -Wall -Werror
gcc -o pzip pzip.c -Wall -Werror -pthread
