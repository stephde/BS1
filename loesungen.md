#BS1 Übung 3


##1.1 

###Erläutern Sie Ihrem Tutor den Unterschied zwischen preemptiven und nicht-preemptiven Scheduling.

Bei preemptive Sceduling wird ein Prozess unterbrochen, falls ein Prozess, mit einer höhren Priorität, bereit ist. Dieser wird dann zuerst abgearbeitet (Interrupt).
Beim nicht-preemptiven Sceduling muss ein Prozess warten, bis der andere Prozess fertig ist unabhängig ob seine Prioriät höher ist.

###Welcher Ansatz ist zu bevorzugen, wenn der Systemdurchsatz maximiert werden soll?

Der nicht-preemptiven ist in dieser Hinsicht besser, da Prozesse nur einmal abgearbeitet werden müssen. Beim preemptiven Sceduling kann es vorkommen, dass ein Prozess kurz vor dem Ende unterbrochen wird und er dann danach wieder von neuem starten muss. Problem sind allerdings Endlosschleifen.

###Wie versuchen Windows-Serversysteme den Durchsatz zu maximieren? 

Ein Quantum ist deutlich länger als im Dekstop-Bereich. Dadurch kann der Server komplexere Rechnungen schneller durchführen, allerdings reagiert er nicht so schnell auf I/O.

##3.2

Gegeben sei ein Einprozessor-System welches Round-Robin-Scheduling mit 16 Prioritäts- stufen verwendet (0-15, 0 = niedrigste, 15 = höchste Priorität). Die Quantumslänge beträgt 20ms. Die Zeit für einen Kontextwechsel sei vernachlässigbar. Der Scheduler verwaltet laufende Threads und entscheidet ausschließlich nach dem Ablauf eines Quantums welcher Thread als nächstes laufen soll. Das Einfügen in die Warteliste erfolgt nach FIFO-Ordnung.
Es sollen drei Threads mit den folgenden Eigenschaften ausgeführt werden:

Zeichnen Sie ein Gantt-Diagramm unter der Annahme, dass alle drei Threads mit einer (statischen) Priorität von 8 ausgeführt werden.

Jetzt soll Th3 mit einer Priorität von 9 ausgeführt werden. Weiterhin erhält Th1 eine Priorität von 7 und tritt nach 16ms in einen I/O-Wartezustand. Die Priorität von Th1 soll nach Beendigung der I/O-Operation um drei erhöht werden („Boost“). Th1 verlässt den Wartezustand bei t=45ms. Die Priorität von Th1 wird um eine Stufe am Quantumsende reduziert, bis wieder die Basispriorität erreicht ist. Zeichnen Sie ein Gantt-Diagramm für den beschriebenen Vorgang!



![] (https://github.com/stephde/BS2/blob/uebung3/BS%203.2.png?raw=true "")


##3.3

###Eine neue Priorität wird für einen Thread mit Hilfe der Funktion KiComputeNewPriority berechnet. Erläutern sie zeilenweise genau den Ablauf der Funktion

```
214
215    SCHAR Priority; // Priorität wird deklariert
216
217    //
218    // Compute the new thread priority.
219    //
220
221    ASSERT((Thread->PriorityDecrement >= 0) && (Thread->PriorityDecrement <= Thread->Priority)); 
222   // Priorität decrementiert darf nicht kleiner null sein und muss kleiner als die ThreadPriority sein.
223    ASSERT((Thread->Priority < LOW_REALTIME_PRIORITY) ? TRUE : (Thread->PriorityDecrement == 0));
224 // falls die priorität kkleiner als low real time priority ist und decrement gräßer null gibt er false zurück
225    Priority = Thread->Priority;
226    if (Priority < LOW_REALTIME_PRIORITY) {
227        Priority = Priority - Thread->PriorityDecrement - Adjustment;
228        if (Priority < Thread->BasePriority) {
229            Priority = Thread->BasePriority;
230        }
231    
232        Thread->PriorityDecrement = 0;
233    }
234
235    ASSERT((Thread->BasePriority == 0) || (Priority != 0));
236
237    return Priority;
```

###Ein Boost der Threadpriorität kann beispielsweise mit der Funktion KiBoostPriorityThread erzeugt werden. Erläutern sie zeilenweise genau den Ablauf der Funktion!

```
1526    KPRIORITY NewPriority;                                    
1527
1528    //
1529    // If the thread is not a real time thread and does not already
1530    // have an unusual boost, then boost the priority as specified.
1531    //
1532
1533    KiAcquireThreadLock(Thread);                                
1534    if ((Thread->Priority < LOW_REALTIME_PRIORITY) &&
1535        (Thread->PriorityDecrement == 0)) {
1536
1537        NewPriority = Thread->BasePriority + Increment; 
1538        if (NewPriority > Thread->Priority) {             
1539            if (NewPriority >= LOW_REALTIME_PRIORITY) {     
1540                NewPriority = LOW_REALTIME_PRIORITY - 1;    
1541            }                                               
1542                                                            
1543            Thread->Quantum = Thread->QuantumReset;     
1544            KiSetPriorityThread(Thread, NewPriority);     
1545        }                                                   
1546    }
1547
1548    KiReleaseThreadLock(Thread);
1549    return;
1550
```

##3.4

### Erläutern Sie Ihrem Tutor den Unterschied zwischen Scheduler und Dispatcher!

Der Dispatcher dient dazu, bei einem Kontextwechsel dem derzeit aktiven Prozess die CPU zu entziehen und anschließend dem nächsten Prozess die CPU zuzuteilen. Der Sceduler trifft die Entscheidung im Rahmen der Warteschlangenorganisation , welcher Prozess der nächste ist.

### Vergleichen Sie das Verhalten Ihrer Implementierung mit der Theorie (zum Beispiel mit Hilfe eines Gantt-Diagramms)!

### Bewerten Sie die Laufzeitkomplexität Ihres Verfahrens!



