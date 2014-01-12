#BS1 Übung 4


##4.1 

###Erläutern Sie Ihrem Tutor folgende Begriffe und deren Verwendung im Kontext eines Betriebssystems!

##### Virtueller Speicher
Der virtuelle Speicher bezeichnet den vom tatsächlich vorhandenen Arbeitsspeicher unabhängigen Adressraum, der einem Prozess vom Betriebssystem zur Verfügung gestellt wird. Dieser greift sowohl auf den RAM als auch auf die Festplatte zu.

##### Paging
Als Paging bezeichnet man die Methode der Speicherverwaltung per Seitenadressierung durch Betriebssysteme. Es wird zwischen logischen und physischen Adressen unterschieden. Der logische Adresseraum wird in gleich große "Pages" aufgeteilt. Diese verweisen dann auf die Adressen im phsikalischen Adressraum.

#####  Page-Fault
Ein Page-Fault tritt auf wenn ein Programm auf einen Speicherbereich zugreift, welcher nicht auf dem Arbeitsspeicher liegt.

##### Page-Replacement Algorithmus
Dieser Algorythmus entscheidet, welcher "Page" herausgeworfen wird, wenn neuer Speicher alloziert wird.

##### Swapping
Swapping beschreibt das auslagern von Datein von einer höhren in einer tiefere Ebene.

##### Interne Fragmentierung
Als interne Fragmentierung bezeichnet man den Effekt, dass bei einer Verteilung von Daten auf Speicherblöcke diese nur zum Teil gefüllt werden können.

##### Externe Fragmentierung
Wenn das größte frei Fragment kleiner ist als der angeforderte Speicher kann der Speicher nicht freigegeben werden auch wenn insgesamt genug Platz wäre.


##4.2

Code

##4.3

![] (https://github.com/stephde/BS2/blob/uebung3/BS%203.2.png?raw=true "")

##4.4

##### Wie viele Einträge enthält eine Page-Table?
64 GiB / 16 KiB = 2^6 * 2^30  Byte / 2^4 * 2^10 = 2^22 = 4.194.304

##### Wie viel physikalischer Speicher wird von einer Seitentabelle belegt? Jeder Seitentabelleneintrag soll die Page- Frame Nummer und 10 Kontroll-Bits enthalten?
(22 Bit + 10 Bit) * 2^22 = 2^5 Bit * 2^22 = 2^27 Bit = 2^3 * 2^4 * 2^10 Bit = 16 MiB

#####Wenn drei Prozesse in diesem System laufen, wie groß kann das Working-Set eines Prozesses maximal sein?
1 GiB  – (3  * 16 MiByte )
– 128 MiByte  = 848 MiByte

##4.5




Quelle: Wikipedia :D

