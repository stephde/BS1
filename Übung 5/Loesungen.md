#BS1 Übung 5


##5.1

### Erläutern Sie das Sicherheitsproblem und durch welche Techniken dieses in Betriebssystemen 
adressiert wird.

- wenn das Betriebsystem nichts tun würden, dann wären alle Nutzer in der Lage auf alle Daten außerhalb des Kernels zuzugreifen.
- Nutzer muss sich zuerst authentifizieren, dann weiß der Rechner ob er autorisiert ist
- rwx Bits, Gruppen in Linux
- acl (Acces Control List) in Windows : Wenn acl nicht enthalten ist, hat jeder Zugriff, wenn sie enthalten ist und leer, dann keiner.


##5.2

### Umsetzung unter Unix

Angestellten ist die Nutzergruppe, in der jeder Angestellte Mitglied ist.
 
`mkdir angestellten_ordner`  
`chown :angestellten angestellten_ordner`  
`chmod 070 angestellten_ordner`  

Kleines Problem ist, dass der Admin noch rechte auf den übergeordneten Ordner hat.

### Umsetzung unter Windows

1. allow: Angestellten
2. deny: Administratoren (nicht notwendig)

### Umsetzung bei zusätzlichen Nutzern

Bei beiden Varianten dürfen die neuen Nutzer nicht der Benutzergruppe Angestellten hinzugefügt werden.

##5.3

##5.4

### Nur Priviligierter User soll shutdown.exe ausführen

Die ACL muss ein ACL enthalten. Er muss es den anderen nicht verbieten, da alles expliziet verboten wird.

allow: privilegierterBenutzer
