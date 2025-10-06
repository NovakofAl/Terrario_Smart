# Terrario_Smart

**Autore**: Vitali Riccardo

# Descrizione
Il Terrario Smart è in grado di mantenere temperatura e umidità constanti all'interno di un ecosistema artificiale chiuso, in questo caso, il terrario.

Utilizza un Arduino per controllare un Atomizzatore (che dispenserà l'acqua sotto forma di nebbia nell'ambiente) e un tappetino riscaldante operato tramite un interruttore elettronico.

Per controllare i valori di temperatura e umidità, nel terrario è installato un sensore DHT in grado di rilevare i dati necessari.

Sull'Arduino è presente uno Shield Oled che permetterà di controllare:
- Temperatura e Umidità, rispettivamente in Celsius e in percentuale
- Stato di attività, quali apparati sono attivi al momento (atomizer o tappetino)
- Specie e numero di individui


## Materiali 
- Arduino Uno
- Oled Shield con 5 pulsanti
- DHT11
- Tappetino Riscaldante
- Relay
- Atomizzatore
- Terrario
