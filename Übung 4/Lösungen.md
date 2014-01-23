#BS1 Übung 4


##4.1 

###Erläutern Sie Ihrem Tutor folgende Begriffe und deren Verwendung im Kontext eines Betriebssystems!

##### Virtueller Speicher
Der virtuelle Speicher bezeichnet den vom tatsächlich vorhandenen Arbeitsspeicher unabhängigen Adressraum, der einem Prozess vom Betriebssystem zur Verfügung gestellt wird. Durch dieses System hat jeder Prozess den Eindruck er könne auf den gesamten Hauptspeicher zugreifen, obwohl er eigentlich nur zugriff auf einen Teil davon hat. Dieser greift sowohl auf den RAM als auch auf die Festplatte zu.

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

### FIFO

![] (https://github.com/stephde/BS2/blob/master/U%CC%88bung%204/FIFO.png?raw=true "")

### LRU

![] (https://github.com/stephde/BS2/blob/master/U%CC%88bung%204/LRU.png?raw=true "")


##4.4

##### Wie viele Einträge enthält eine Page-Table?
64 GiB / 16 KiB = 2^6 * 2^30  Byte / 2^4 * 2^10 = 2^22 = 4.194.304

##### Wie viel physikalischer Speicher wird von einer Seitentabelle belegt? Jeder Seitentabelleneintrag soll die Page- Frame Nummer und 10 Kontroll-Bits enthalten?
(22 Bit + 10 Bit) * 2^22 = 2^5 Bit * 2^22 = 2^27 Bit = 2^3 * 2^4 * 2^10 Bit = 16 MiB

#####Wenn drei Prozesse in diesem System laufen, wie groß kann das Working-Set eines Prozesses maximal sein?
1 GiB  – (3  * 16 MiByte )
– 128 MiByte  = 848 MiByte

##4.5

##### Bis zu einem bestimmten Punkt wird der Wert Mem Usage des Prozesses Leaky App größer, 
danach wird er erheblich kleiner um danach wieder anzuwachsen. Welcher Effekt im 
Windows Kern bewirkt das beobachtete Verhalten? 

Der Effekt der dies verursacht heißt WorkingSet Trimming.

##### Mem Usage, Peak Mem Usage, Virtual Mem Size
Working-Set, Maximaler Working Set, "benutzte Pagefiles"

##### Standby Liste
Alle Seiten der Liste gehören zu einem Workingset, deren Daten sind jedoch unverändert. Die  Seiteneinträge verweisen auf
physikalische Seiten, sind allerdings mit "invalid“ und "transition“ gekennzeichnet.

##### Modified Liste
Alle Seiten der Liste gehören zu einem Workingset, deren Daten wurden jedoch unverändert und sind noch nicht auf die Platte/ins Pagefile geschrieben worden. Die Seiteneinträge verweisen weiterhin auf physikalische Seiten, sind aber mit „invalid“ und „transition“ gekennzeichnet. Die Seiten müssen vor der Wiederverwendung wieder auf die Platte geschrieben werden.

##### Free Liste
Hier sind die Seiten nicht mehrt in Verwendung und enthalten Daten, welche nicht gebraucht werden. Aus Sicherheit werden die Seitenen vor der nächsten Verwendung mit 0 gefüllt.

##### Zero Liste
Hier sind die Seite
Seiten sind frei und mit ‚0’ gefüllt wie auf der Zeropage.





Quelle: Wikipedia :D

