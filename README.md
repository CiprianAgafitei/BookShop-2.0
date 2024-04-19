*Introduzione*
Book Store è un’applicazione scritta in linguaggio C++ con framework Qt, che offre il controllo di un insieme di libri suddivisi in tre 
categorie diverse, simulandone la gestione da parte di un negozio-libreria, tenendo traccia dei nuovi prodotti arrivati, per essere 
iscritti nel catalogo dei libri, nella categoria opportuna, ed essere quindi disponibili per la visualizzazione da parte dei clienti, 
offrendo la possibilità di aggiungere o rimuovere libri, cercare un libro, modificare le informazioni di un libro, eliminare un libro 
(cancellazione definitiva). Ciascun libro è caratterizzato da varie proprietà, alcune comuni tra tutti i libri e altre più specifiche per 
ciascuna categoria.
L’applicazione simula solamente la parte che il venditore-bibliotecario può gestire riguardo ai libri, non implementa dunque 
funzionalità per i clienti, anche se l’idea è stata analizzata e non richiederebbe molto più lavoro di quanto già svolto. Nuove 
funzionalità sarebbero facilmente implementabili ma richiederebbero più ore di lavoro di quanto richiesto.
La scelta dell’idea è stata fatta su questo tema in quanto ho già lavorato su un’applicazione simile, in un altro linguaggio (Java), e 
mi è stato più facile pensare a questo modello, viste le richieste che si potrebbero avere da un’applicazione del genere, ma anche 
i requisiti che non mi sembravano molto difficili da affrontare, avendo già qualche esperienza in questo ambito di programmazione 
ad oggetti.

*Descrizione dell’applicazione*
L’applicazione prevede la gestione di tre categorie di libri: LETTURE, LIBRI DI TESTO ed ESERCIZIARI. Vi è una classe Libro, astratta, 
con le seguenti caratteristiche comuni per tutte le tre tipologie di libri:
  o ISBN: codice identificativo di ciascun libro, univoco (non esistono due libri diversi con stesso ISBN)
  o Titolo: titolo del libro
  o Prezzo: prezzo del libro €
  o Disponibilità: dato un isbn, è la quantità di libri disponibili nel negozio per la vendita
  
Oltre ai semplici metodi di set e update(metodi get) per ciascuna caratteristica dei libri, necessari per l’ottenimento delle singole 
informazioni, vi è un metodo virtuale puro per il calcolo totale del prezzo, dove vengono applicate delle politiche stabilite 
(personalmente, non da altre fonti) per questo Book Store.

Ciascuna classe, Letture, Libri_di_Testo ed Eserciziari, derivata dalla classe base Libro, ha ulteriori caratteristiche proprie:
*Letture*:
- Genere: genere del libro-lettura
- Nr. pagine: numero delle pagine del libro
- Copertina flessibile: proprietà del libro di essere in formato cartaceo, copertina flessibile, oppure digitale, copertina rigida

*Libri di Testo*:
- Materia: materia del libro di testo
- Nr. argomenti: numero di argomenti del libro di testo
- Livello apprendimento: livello di apprendimento suggerito per il libro di testo (da 1 a 3)
- Sconto: sconto previsto “da applicare” al libro al momento della vendita in caso il cliente sia uno studente/docente 
(questa idea è stata solamente implementata in parte in quanto non è stata creata la parte cliente, ma solamente la 
parte gestionale del negozio)

*Eserciziari*:
- Materia: materia dell’eserciziario
- Nr. Esercizi: numero di esercizi del libro
- Difficoltà: grado di difficoltà (da 1 a 3) dell’eserciziario

Dal menu principale, dopo aver selezionato il pulsante Entra, l’utente può scegliere una delle tre categorie di libri da visitare. Le 
finestre non sono modificabili in grandezza. Comprendono immagini inserite in Label o in QPushButton.
Ciascuna opzione ha un’immagine simbolica sul pulsante attraverso cui è possibile entrare nella categoria scelta, sopra il quale vi 
è un titolo indicante il nome della categoria a cui si fa riferimento.
La struttura di ciascuna delle tre finestre è quasi identica, se non per il nome, il numero delle colonne delle tabelle e il titolo della 
schermata. Ciascuna categoria di libri ha una colonna per ciascun attributo. 
È possibile, dalla barra di ricerca sottostante alla tabella, effettuare una ricerca sui campi delle informazioni di ciascun libro, 
visualizzando così solamente i libri (della categoria selezionata in precedenza), che contengono i caratteri digitati nei loro campiattributi.
Nella tabella è consentita la selezione di una sola riga alla volta, per cui sarà possibile effettuare alcune operazioni spiegate in 
seguito.
Dopo aver scelto una delle tre categorie di libri, ed essere dunque in una delle tre schermate con relativa tabella e opzioni, sulla 
destra sarà visibile un pulsante ‘+’ (se non è stata selezionata ancora nessuna riga della tabella, altrimenti sarà il primo pulsante 
della colonna laterale), corrispondente a “Nuovo libro”, suggerimento visibile quando si pone il puntatore sopra, senza 
selezionare. Attraverso questo pulsante sarà possibile inserire un nuovo libro (della categoria scelta prima), nella tabella.

1. **NUOVO LIBRO**: presenta una schermata con dei campi da completare, con le informazioni del nuovo libro da registrare 
sull’applicazione. È presente un controllo sui campi difficoltà e livello apprendimento che accettano valori solo compresi 
tra 1 e 3. Inoltre, è possibile proseguire, una volta compilati i campi, alla creazione del libro solamente se non vengono 
rilevati campi vuoti, altrimenti il pulsante per continuare sarà disabilitato. 
Controllo ulteriore: una volta inseriti tutti i dati del nuovo libro e premuto il pulsante di conferma, viene effettuato un 
controllo che verifica se il codice ISBN inserito appartiene già ad un libro nella tabella. Se così, viene mostrato un 
messaggio che invita a modificare semplicemente la quantità del libro già esistente o, se necessario, modificare il codice 
ISBN se è stato inserito in modo errato.
Selezionando invece una delle righe della tabella verranno visualizzate alte quattro opzioni, sotto al pulsante ‘+’, che faranno 
riferimento al libro selezionato nella tabella e per cui sarà visibile un suggerimento come per il pulsante spiegato 
precedentemente.

2. **ELIMINA LIBRO**: consente la rimozione definitiva del libro dal negozio (cancellazione dal vettore libri e dalla tabella), con 
l’unica condizione che il libro abbia la disponibilità pari a 0, altrimenti si avvisa che tale condizione deve essere prima 
soddisfatta. Inoltre, è presente anche un messaggio che avverte sull’operazione che si sta per eseguire e quindi, se si 
desidera continuare con l’eliminazione o meno. Il libro scomparirà dalla tabella, così come verrà rimosso dal contenitore.

3. **INSERISCI LIBRO**: consente l’aggiornamento della disponibilità del libro selezionato inserendone uno. Un messaggio di 
avvenuto inserimento verrà visualizzato e sarà disponibile vedere la disponibilità aggiornata nella tabella.

5. **RIMUOVI LIBRO**: consente l’aggiornamento della disponibilità del libro selezionato rimuovendo un libro. Un messaggio 
di avvenuta rimozione verrà visualizzato e sarà disponibile vederne la modifica della disponibilità nella tabella.

7. **MODIFICA LIBRO**: consente la modifica dei dati del libro selezionato, ad eccezione del codice ISBN, considerato chiave e 
dunque univoco. È stata rimossa questa possibilità in quanto richiederebbe un controllo ulteriore per verificare che il 
codice nuovo digitato non sia già presente nella tabella, quindi il libro non sarebbe più modificabile (perché non 
corrisponderebbe a quello selezionato), portando dunque ad operazioni inutili. Dopo aver modificato i dati desiderati, si 
potranno visualizzare le modifiche apportate nella tabella aggiornata, dopo aver confermato tramite il pulsante ”Salva”.

L’applicazione prevede il salvataggio dei dati su un documento JSON, garantendone la persistenza. È stato inserito un controllo, in 
questo caso, per far in modo che se il file dovesse essere vuoto, vi sarà un vettore libri presente, che verrà salvato su file e caricato 
nelle opportune tabelle.
Ogni operazione di creazione, inserimento, rimozione, modifica ed eliminazione dei libri presenta il relativo salvataggio su file per 
aggiornare le modifiche apportate.
Inoltre, per quanto riguarda la disponibilità dei libri, è stato posto un limite pari a 100, per ciascun libro.

(NOTA IMPORTANTE: eseguendo il programma ho notato che aprendo il file contenente i libri, libri.json, vengono visualizzati come 
vuoti, nonostante dopo la chiusura dell’applicazione e la riesecuzione i dati vengono mantenuti corrispondentemente a quelli dopo 
le modifiche. Non ho provato però a verificare se questo è dovuto alla mancanza di un’applicazione per l’apertura e visualizzazione 
dei file in formato JSON).

*Polimorfismo*
Il concetto del polimorfismo è stato implementato attraverso una funzione di calcolo totale del prezzo dei libri, una funzione 
virtuale pura dichiarata nella classe base Libro e opportunamente implementata in ciascuna delle tre classi delle categorie di libri.
Per ciascuna categoria vi sono dei criteri stabiliti per il calcolo del prezzo del libro. Tuttavia, questo prezzo verrà attribuito al libro 
solamente in caso di inserimento di un nuovo libro, non già presente, in modo da evitare che ad ogni chiamata di aggiornamento 
del prezzo venga applicato il calcolo della funzione.
I criteri sono i seguenti:
1. Lettura: si calcola lo 0.05€ per ciascuna pagina del libro, se in copertina flessibile, e si confronta il risultato con il prezzo 
impostato proposto al momento dell’inserimento. Verrà mantenuto quello con valore inferiore;
2. Libro di testo: viene applicato uno sconto del 50-30-20% in base alla quantità disponibile nel negozio:
a. disponibilità <= 15: applicato lo sconto del 20%
b. disponibilità <= 25: applicato lo sconto del 30%
c. disponibilità > 25: applicato lo sconto del 50%
Lo sconto viene applicato sul prezzo proposto.
3. Eserciziario: si calcola lo 0.01€ per il numero di esercizi dell’eserciziario e se il valore ottenuto sarà maggiore di quello 
proposto, allora si applicherà:
a. il 10% di sconto se il libro ha grado di difficoltà pari a 1;
b. il 20% di sconto se il grado di difficoltà è pari a 2;
c. il 30% di sconto se il grado di difficoltà è pari a 3.

*Persistenza dei dati*
Come già accennato, l’applicazione effettua il salvataggio dei dat su documento JSON garantendone la persistenza. Ciascuna delle 
tre classi derivate prevede un metodo book4print che crea e restituisce un QJsonObject, contenente tutte le informazioni relative 
al libro della categoria selezionata. Viene inoltre inserita un’informazione che indica il tipo di libro (categoria) utile al momento 
della lettura per la creazione degli oggetti e l’inserimento nel vettore dei libri.
In questo modo, all’avvio dell’applicazione verranno caricati i libri dal file, se presenti, all’interno del vettore libri, per poi essere 
visualizzati nelle varie tabelle (se non presenti, verranno inseriti dei libri di default, inizializzati, per poter visualizzare comunque il 
funzionamento del programma).
Successivamente vi è il salvataggio dei dati effettuato dopo ogni operazione che comporti la modifica dei libri, per non perdere 
aggiornamenti alle informazioni dei libri.

I libri vengono salvati del file „libri.json”.
Funzionalità implementate
Funzionalità codice C++:
✓ Gestione di una gerarchia di tre classi derivate da una classe madre astratta
✓ Creazione di un contenitore nativo contenente oggetti della gerarchia con relative operazioni di inserimento, rimozione, 
ricerca, lettura in base ad alcuni criteri, aggiornamento informazioni
✓ Creazione di vettori contenenti gli oggetti di ciascuna categoria di libri
✓ Salvataggio su file JSON con lettura all’avvio del programma e caricamento automatico di alcuni oggetti libro per 
consentire operazioni di prova in caso il programma venga eseguito per la prima volta
Funzionalità grafiche:
✓ Accesso all’applicazione tramite pulsante iniziale „Entra”
✓ Utilizzo di titoli e caratteri speciali ed immagine per la schermata principale
✓ Inserimento icona per l’applicazione e relativo nome dell’applicativo
✓ Ridimensionamento finestra disabilitato
✓ Opzione di selezione a scelta tra tre schermate relative alle tre categorie di libri disponibili
✓ Inserimento immagini all’interno di QPushButton
✓ Inserimento di titoli e descrizioni vicino agli elementi
✓ Inserimento suggerimento per i pulsanti con opzione „on hover”
✓ Pulsante di ritorno alla schermata principale di selezione categoria dei libri su ciascuna sezione delle categorie dei libri
✓ Tabelle contenenti le informazioni dei libri di ciascuna categoria
✓ Righe delle tabelle selezionabili singolarmente
✓ Barra di ricerca sottostante a ciascuna tabella nella propria schermata → ricerca in base a qualsiasi criterio
✓ Opzione di modifica informazioni di ciascuna riga disabilitata
✓ Colonna laterale sulla destra con pulsanti, con icone, per le varie operazioni da eseguire, ciascuno con suggerimento 
all’operazione a cui fa riferimento
✓ Pulsante „Nuovo libro” visibile anche singolarmente se non viene selezionata nessuna riga della tabella
✓ Possibilità di inserire un nuovo libro attraverso una schermata con i campi necessari per la creazione del nuovo libro
✓ Controlli disponibilità (valori tra 0 e 100 compresi) e confronto isbn con gli altri già esistenti per evitare di creare nuovi libri 
con codici isbn già esistenti
✓ Selezione singola delle righe delle tabelle e comparsa dei restanti pulsanti relativi alle operazioni da eseguire sui libri
✓ Rimozione di un libro selezionato con condizione che la sua disponibilità sia uguale a 0
✓ Aggiornamento della quantità di un libro aggiungendone/rimuovendone uno dal libro selezionato nella tabella con relativo 
messaggio di avvenuto/a inserimento/rimozione
✓ Opzione di modifica delle informazioni del libro selezionato
✓ Campi per la modifica delle informazioni apparte il campo isbn non modificabile (disabilitato)
✓ Pulsante „Salva” per il salvataggio delle modifiche apportate
✓ Aggiornamento immediato con le modifiche apportate (sia cancellazione, rimozione, inserimento e creazione) sia nelle tabelle 
sia nel file JSON
✓ Campi „difficoltà” della categoria „eserciziari” e „livello di apprendimento” della categoria „libri di testo” con valori accettati 
compresi tra 1 e 3 (1,2,3)
✓ Applicazione sconti ai libri di ciascuna categoria, sulla base dei rispettivi criteri, al momento della creazione del libro
✓ Messaggi di errore in caso di condizioni non rispettate per tutte le opzioni
