# Traceability Matrix 

| **Requirement ID** | **Requirement Beschreibung** | **Teilfunktion** | **Systemkomponente** | **Verfolgbarkeit / Kommentar** |
|-------------------|-----------------------------|-----------------|-------------------|-------------------------------|
| R1.1 | Füllstandsmessung: 0-250 ml, Auflösung ≤5 %, Reaktionszeit ≤500 ms, Sensorfehlererkennung, Genauigkeit ±5 % | Sensordatenerfassung | Füllstandssensor | Misst Wasserstand über kapazitiven Sensor |
| R1.2 | Temperaturmessung: 0–150 °C, Genauigkeit ±1 °C, Abtastrate ≥5 Hz, Überhitzungserkennung, Sicherheitsabschaltung >110 °C | Sensordatenerfassung | Temperatursensor | Erfasst Heizplattentemperatur und schützt vor Überhitzung |
| R1.3 | Zeitmessung: interne Echtzeituhr ±0,1 s, Messintervall ≤200 ms | Sensordatenerfassung | Timer | Liefert Zeitstempel für Plausibilitätsprüfungen und Verlaufsauswertung |
| R2.1 | Auswertung Sensorwerte: Sollwertvergleich, Statuswarnung bei Abweichung >10 %, Berechnungszyklus ≤500 ms | Zustandsüberwachung | Steuerlogik | Vergleicht Sensorwerte kontinuierlich mit Sollwerten |
| R2.2 | Vergleich Soll/Ist kontinuierlich, Update ≥2×/s, Sicherheitsmodus bei fehlendem Messwert | Zustandsüberwachung | Steuerlogik | Entscheidet Betriebszustand: Bereit, Warnung, Kritisch, Trockenlauf |
| R2.3 | Fehleranalyse: Sensorfehler, Überhitzung | Zustandsüberwachung | Steuerlogik | Erkennung und Klassifizierung von Fehlern |
| R3.1 | Heizungssteuerung: Abschalten bei Füllstand <10 % oder Temperaturanstieg >5 °C/s, Reaktionszeit ≤1 s | Steuerlogik & Sicherheit | Heizsystem | Automatisches Ausschalten der Heizung |
| R3.2 | Warnungen: Anzeigewechsel ≤300 ms, akustisches Signal bei kritischem Zustand, Wiederholung alle 10 s | Steuerlogik & Sicherheit | Display & Summer | Informiert Benutzer über kritische Zustände |
| R3.3 | Berechnung tatsächlicher Füllstand: Sensordaten + Temperaturkompensation, Berechnungszeit ≤100 ms, gleitender Mittelwert | Steuerlogik & Sicherheit | Steuerlogik | Genauigkeitsverbesserung und Schutz vor Trockenlauf |
| R4.1 | Plausibilitätsprüfung beim Einschalten: Temperatur 0–50 °C, Füllstand 0–100 %, Dauer ≤2 s | Fehlerdiagnose & Überwachung | Steuerlogik | Prüft Sensorwerte beim Systemstart |
| R4.2 | Fehlerklassifizierung: Warnung (Füllstand <20 %), Fehler (Trockenlauf), Kritisch (Sensorfehler/Überhitzung), Anzeige <300 ms | Fehlerdiagnose & Überwachung | Steuerlogik | Zeigt Fehlerprioritäten und sorgt für schnelle Meldung |
| R4.3 | Zyklischer Selbsttest: alle 30 s, unveränderte Werte >10 s → Plausibilitätswarnung | Fehlerdiagnose & Überwachung | Steuerlogik | Überwacht laufend Sensorfunktionen |
| R5.1 | Füllstandsanzeige: 0–100 %, Aktualisierung alle 500 ms, Genauigkeit ±5 % | Benutzerinterface | Display | Visualisiert Wasserstand für Benutzer |
| R5.2 | Warnanzeige: Farbcode (Grün/Gelb/Rot), Helligkeit <300 cd/m², Symbole bei Farbfehlsichtigkeit | Benutzerinterface | Display | Anzeige von Warnungen und Fehlern |
| R5.3 | Fehlermeldung bei Trockenlauf: Text, Anzeige aktiv bis quittiert | Benutzerinterface | Display | Zeigt kritische Zustände persistent an |
| R5.4 | Akustische Signalisierung: 60–80 dB(A), Signaltyp 2× kurz bei Warnung, 3× lang bei Fehler, Reaktionszeit ≤500 ms | Benutzerinterface | Summer | Akustische Benutzerwarnung bei kritischen Zuständen |
| R5.5 | Schwelle einstellen: benutzerdefinierbare Warnwerte | Benutzerinterface | Display & Eingabefeld | Benutzer kann Warnschwellen definieren und Fehler freigeben |
