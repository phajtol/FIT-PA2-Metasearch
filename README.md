# FIT-PA2-Metasearch


This is a project created as a semester work for subject Programming and algorithmic 2 (BI-PA2 - Programování a algoritmizace 2
) at FIT CTU.

Full assignment in Czech language is below.

Summary of the assignment: Create a program based on given specification: metadata search.

# Assignment

```
Meta vyhledavač

Uložené fotografie, videa a textové dokumenty na pevných discích jdou vyhledávat pouze podle názvů a datumů, ale mohlo by být výhodné je hledat podle jiných informací, například podle GPS

Implementujte následující funkcionalitu:
Načítání různých souborů (obrázky, videa, textové dokumenty)
Ukládání metadat pro potřeby vyhledávání
Vyhledávání podle zaznamenaných metadat

Nástroj musí dále splňovat následující funkcionality:
Import a export databáze
Načítání metadat dle podporovaných formátů
```

Semestrální práce by svým rozsahem a náročností měla odpovídat probíranému učivu (OO návrh, využití OO technik, polymorfismus…​). Předpokládaný rozsah práce je 1000-3000 zdrojových řádek (limity počtu řádek nejsou striktní, zejména horní limit lze v odůvodněných případech překročit).

Práce bude hodnocena automaticky Progtestem a následně cvičícím. Progtest pouze zkontroluje formální náležitosti práce a provede kompilaci a sestavení. Pokud odevzdávaná práce neprojde tímto testem, nebude hodnocena. Progtest nehodnotí funkcionalitu ani kvalitu zpracování práce (styl, návrh, OO techniky, …​).

## Náležitosti semestrální práce

Vypracovaná semestrální práce musí obsahovat tyto náležitosti:

- detailní zadání řešeného tématu (tedy přesná specifikace, která vychází z rámcového zadání),
- zdrojové kódy. Program musí být rozumně členěn do více modulů, které postihují logickou strukturu tříd,
- Makefile s popisem sestavení,
- dokumentaci (buď staticky vygenerovanou, nebo generovanou ze zdrojových kódů pomocí nástroje doxygen),
- sadu testovacích dat.

## Překlad a spuštění semestrální práce

Překlad semestrální práce bude prováděn pomocí příkazu make compile (pracovní adresář je adresáře kde je umístěn soubor Makefile). Spuštění práce bude prováděno příkazem make run. Pokud jeden z těchto příkazů skončí chybou, bude práce hodnocena stupněm F. Veškeré C/C++ soubory musí být překládány s následujícími volbami překladače:

`-Wall -pedantic -Wno-long-long -O0 -ggdb`
Použití dalších voleb je povolené, uvedené volby jsou však *povinné*.

Velmi doporučuji si před odevzdáním práce vyzkoušet následující sekvenci příkazů (předpokládejme, že chcete odevzdat semestrální práci v souboru vranyj1.zip):
```
unzip vranyj1.zip
cd vranyj1
make compile
make run
```
V této sekvenci příkazů by neměla nastat chyba.

## Požadavky na zdrojový kód

Krom toho, že kód se musí chovat správně a být „slušně“ napsaný, musí splňovat následující požadavky:

- zdrojový kód musí být rozdělen do souborů po logických celcích,
- musí být přehledně zarovnán,
- musí být smysluplně komentován,
- veškeré identifikátory stejně jako komentáře musí být v v anglickém jazyce,
- rozsah semestrální práce je 1000-3000 řádek, jakákoliv semestrální práce mající méně než 1000 řádek BUDE ZAMÍTNUTA. 1000 řádků opravdu není mnoho. Horní limit počtu řádků je orientační, může být ve zdůvodněných případech překročen. Počet řádků se počítá pomocí příkazu `wc -l <soubory>`, tzn. počítají se do toho i komentáře. Komentáře musí být v rozumném množství. Předem upozorňuji, že semestrální práce obsahující hodně řádků s komentářem může být zamítnuta.
- Požadavky na kód, respektive na minimální „technologii“ kterou bude kód používat: objektově orientované rysy C++ a velmi jednoduchý polymorfismus. Příklad: ve hře máte dvě postavy a) hráč; b) příšera. Vytvořím třídu moving_object a od ní podědí dva potomci: a) hráč; b) příšera. moving_object pochopitelně má metody typu: posun, zobrazení, …​ Pokud si nejste jisti, jak polymorfismus využít, včas kontaktujte svého cvičícího.

Přidělené zadání semestrální práce je pouze rámcové. To znamená: text zadání má vymezit téma. Primární je napsat program v požadovaném rozsahu 1000-3000 řádek jehož minimální funkcionalita je daná zadáním.
