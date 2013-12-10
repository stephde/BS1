BS1 �bung 3


1.1 

Erläutern Sie Ihrem Tutor den Unterschied zwischen preemptiven und nicht-preemptiven 
Scheduling.

Bei preemptive Sceduling wird ein Prozess unterbrochen, falls ein Prozess, mit einer höhren Priorität, bereit ist. Dieser wird dann zuerst abgearbeitet (Interrupt).
Beim nicht-preemptiven Sceduling muss ein Prozess warten, bis der andere Prozess fertig ist unabhängig ob seine Prioriät höher ist.

Welcher Ansatz ist zu bevorzugen, wenn der Systemdurchsatz maximiert werden 
soll?

Der nicht-preemptiven ist in dieser Hinsicht besser, da Prozesse nur einmal abgearbeitet werden müssen. Beim preemptiven Sceduling kann es vorkommen, dass ein Prozess kurz vor dem Ende unterbrochen wird und er dann danach wieder von neuem starten muss.

Wie versuchen Windows-Serversysteme den Durchsatz zu maximieren? 

3.3

KiComputeNewPriority

{
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


1524{
1525
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
1550}
238}


3.4

pspCreateThread / kestartthread


liste loggen
eintrag in die prozesssturktur
564 thread gestartet
359 Quantum wird gesetzt
373 BasePriority and actuall priority
466 insert tail list


_KPRCB
1083 currenthread, idle thread, next thread
1277 liste maxium priority
1274 wait list

sceudular bearbeiten

