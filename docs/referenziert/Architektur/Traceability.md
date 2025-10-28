# Traceability Matrix 

| **Requirement ID** | **Requirement Beschreibung** | **Systemkomponente** | **Bearbeitung in Sprint** |
|-------------------|-----------------------------|-------------------|--------|
| R1.1 | Füllstandsmessung: 0–250 ml, Auflösung ≤5 %, Reaktionszeit ≤500 ms, Sensorfehlererkennung, Genauigkeit ±5 % | Füllstandssensor | 1 | 
| R1.2 | Temperaturmessung: 0–150 °C, Genauigkeit ±1 °C, Abtastrate ≥5 Hz, Überhitzungserkennung, Sicherheitsabschaltung >110 °C | Temperatursensor | 1 |
| R1.3 | Zeitmessung: interne Echtzeituhr ±0,1 s, Messintervall ≤200 ms | Timer | 1 |
| R2.1 | Auswertung Sensorwerte: Sollwertvergleich, Statuswarnung bei Abweichung >10 %, Berechnungszyklus ≤500 ms | Steuerlogik | 1 |
| R2.2 | Vergleich Soll/Ist kontinuierlich, Update ≥2×/s, Sicherheitsmodus bei fehlendem Messwert | Steuerlogik |
| R2.3 | Fehleranalyse: Sensorfehler, Überhitzung | Steuerlogik | 
| R3.1 | Heizungssteuerung: Abschalten bei Füllstand <10 % oder Temperaturanstieg >5 °C/s, Reaktionszeit ≤1 s | Heizsystem | 1 |
| R3.2 | Warnungen: Anzeigewechsel ≤300 ms, akustisches Signal bei kritischem Zustand, Wiederholung alle 10 s | Display & Summer |
| R3.3 | Berechnung tatsächlicher Füllstand: Sensordaten + Temperaturkompensation, Berechnungszeit ≤100 ms, | Steuerlogik | 1 |
| R4.1 | Plausibilitätsprüfung beim Einschalten: Temperatur 0–50 °C, Füllstand 0–100 %, Dauer ≤2 s | Steuerlogik |
| R4.2 | Fehlerklassifizierung: Warnung (Füllstand <20 %), Fehler (Trockenlauf), Kritisch (Sensorfehler/Überhitzung), Anzeige <300 ms | Steuerlogik |
| R4.3 | Zyklischer Selbsttest: alle 30 s, unveränderte Werte >10 s → Plausibilitätswarnung | Steuerlogik |
| R5.1 | Füllstandsanzeige: 0–100 %, Aktualisierung alle 500 ms, Genauigkeit ±5 % | Display |
| R5.2 | Warnanzeige: Farbcode (Grün/Gelb/Rot), Helligkeit <300 cd/m², Symbole bei Farbfehlsichtigkeit | Display |
| R5.3 | Fehlermeldung bei Trockenlauf: Text, Anzeige aktiv bis quittiert | Display |
| R5.4 | Akustische Signalisierung: 60–80 dB(A), Signaltyp 2× kurz bei Warnung, 3× lang bei Fehler, Reaktionszeit ≤500 ms | Summer |
| R5.5 | Schwelle einstellen: benutzerdefinierbare Warnwerte | Display & Eingabefeld |

