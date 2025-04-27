# Library Management System

Un'applicazione Qt/C++ per la gestione di una biblioteca multimediale che consente di catalogare diversi tipi di media.

## Caratteristiche

- Gestione di diverse tipologie di media (Libri, Film, Riviste, E-book)
- Interfaccia grafica intuitiva per la gestione della collezione
- Ricerca avanzata per titolo, autore, data, e altri attributi
- Salvataggio/caricamento della collezione in formato JSON
- Visualizzazione dettagli specifici per ogni tipo di media
- Editor dedicati per ogni tipo di media

## Istruzioni per la compilazione

1. Assicurarsi di avere Qt 5.15+ e qmake installati
2. Clonare il repository
3. Eseguire i seguenti comandi:

`qmake Library.pro`
`make`

4. Eseguire l'applicazione: `./LibraryManager`

## Struttura del progetto

- `model/`: Contiene le classi del modello dati
- `view/`: Contiene le classi dell'interfaccia utente
- `visitor/`: Implementazione del pattern Visitor
- `strategy/`: Implementazione del pattern Strategy
- `factory/`: Implementazione del pattern Factory Method
- `persistence/`: Gestione della persistenza dei dati

## Demo

Il progetto include un file di esempio `example_library.json` che può essere caricato per testare le funzionalità.