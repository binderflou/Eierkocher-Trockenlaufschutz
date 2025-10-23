# Funktionale Requirements

# 1. Sensordatenerfassung

   ## 1.1 Füllstand

   - Messbereich: 0 % – 100 % des zulässigen Behältervolumens (250 ml)

   - Messauflösung: ≤ 5 % des Gesamtvolumens

   - Reaktionszeit (von Füllstandsänderung bis Messwertaktualisierung): ≤ 200 ms

   - Sensorfehlererkennung: Messwert außerhalb 0–110 % → Fehlermeldung „Sensorfehler“ 

   - Genauigkeit: ± 5 % des Messbereichs

   ## 1.2 Temperatur

   - Messbereich: 0 °C – 150 °C

   - Messgenauigkeit: ± 1 °C

   - Abtastrate: ≥ 5 Hz (alle 200 ms)

   - Überhitzungserkennung: Temperaturanstieg > 5 °C/s → Trockenlauf-Verdacht

   - Sicherheitsabschaltung bei > 110 °C

   ## 1.3 Zeit

   - Zeitbasis: interne Echtzeituhr oder Timer mit Genauigkeit ± 0,1 s

   - Erfassung der Zeitdifferenz zwischen Messungen zur Verlaufsauswertung

   - Messintervall zwischen Sensorwerten: ≤ 200 ms

# 2. Zustandsüberwachung

   ## 2.1 Auswertung Sensorwerte

   - Vergleich der gemessenen Sensorwerte mit definierten Sollwerten:

         Soll-Füllstand ≥ 20 % für sicheren Betrieb

         Soll-Temperatur < 100 °C während des Kochens

         Abweichung > 10 % vom Sollwert → Statuswarnung

         Berechnungszyklus: ≤ 500 ms

   ## 2.2 Vergleich Soll/Ist

   - Soll/Ist-Vergleich erfolgt kontinuierlich im laufenden Betrieb

   - Entscheidungslogik aktualisiert mindestens 2× pro Sekunde

   - Falscher oder fehlender Messwert → automatische Umschaltung in Sicherheitsmodus

# 3. Steuerlogik (Füllstand & Abschaltung)
   ## 3.1 Entscheidungsfindung Abschalten

   Heizung wird deaktiviert, wenn:

      Füllstand < 10 % oder

      Temperaturanstieg > 5 °C/s über Zeitraum von 500 ms

      Abschaltung erfolgt mit Reaktionszeit ≤ 1 s nach Erkennung

      Wiedereinschalten erst, wenn Füllstand > 20 % und Temperatur < 70 °C

   # 3.2 Warnungen an Display/Peripherie

   - Anzeigewechsel (Normal → Warnung → Fehler) innerhalb ≤ 300 ms nach Zustandsänderung

   - Akustisches Signal bei kritischem Zustand (z. B. 2 × kurz + Pause)

   - Warnsignal wiederholt sich alle 10 s, solange der Fehler aktiv ist

   # 3.3 Berechnung des tatsächlichen Füllstandes

   - Berechnungsalgorithmus auf Basis von Sensordaten + Temperaturkompensation

   - Berechnungszeit: ≤ 100 ms

   - Glättung: gleitender Mittelwert über 3 Messungen

# 4. Selbsttest und Fehlerdiagnose

   ## 4.1 Plausibilitätsprüfung

   Beim Einschalten wird geprüft:

      - Temperatur zwischen 0 °C und 50 °C

      - Füllstand zwischen 0 % und 100 %

      - Dauer des Selbsttests: ≤ 2 s

      Bei Abweichung → optische + akustische Fehlermeldung

   ## 4.2 Fehlermeldungen

   Fehler werden in drei Stufen klassifiziert:

      Warnung: niedriger Füllstand (< 20 %)

      Fehler: Trockenlauf erkannt

      Kritisch: Sensorfehler oder Überhitzung

      Fehleranzeige erfolgt < 300 ms nach Erkennung.

   ## 4.3 Selbsttest (zyklisch)

   Automatische Überprüfung der Sensorwerte alle 30 s

   Unveränderte Werte über > 10 s → Plausibilitätswarnung

# 5. Benutzerinterface

   ## 5.1 Füllstandsanzeige

      Anzeigeauflösung: 5 Stufen oder Prozentwert (z. B. 0–100 %)

      Aktualisierung: alle 500 ms

      Anzeigegenauigkeit: ± 5 %

   ## 5.2 Warnanzeige

      Farbcode (z. B. Grün = OK, Gelb = niedrig, Rot = Trockenlauf)

      Helligkeit: < 300 cd/m² (nicht blendend)

      Alternativanzeige über Symbole bei Farbfehlsichtigkeit

   ## 5.3 Fehlermeldung bei Trockenlauf

      Textmeldung („Trockenlauf erkannt“) oder Symbolanzeige

      Anzeige bleibt aktiv, bis Zustand behoben ist

   ## 5.4 Akustische Signalisierung

      Lautstärke: 60–80 dB(A) auf 0,5 m Abstand

      Signaltyp: 2 × kurz bei Warnung, 3 × lang bei Fehler

      Reaktionszeit: ≤ 300 ms nach Ereignis

#   Zusammenfassung Requirements

   - Sensordatenerfassung
   - Zustandsüberwachung
   - Steuerlogik
   - Selbsttest und Fehlerdiagnose
   - Benutzerinterface

## Teilfunktionalitäten

| **Nr.** | **Teilfunktion** | **Unterfunktion** | **Beschreibung** |
|----------|-------------------|------------------------|------------------|
| 1 | Sensordatenerfassung | Füllstandsmessung | Misst Wasserstand über kapazitiven Sensor |
|   |   | Temperaturmessung | Erfasst Heizplattentemperatur |
|   |   | Zeiterfassung | Zeitstempel für Plausibilitätsprüfungen |
| 2 | Zustandsüberwachung | Soll-Ist-Vergleich | Vergleich mit Warnschwellen |
|   |   | Zustandserkennung | Erkennung: Bereit, Warnung, Kritisch, Trockenlauf |
|   |   | Fehleranalyse | Sensorfehler, Überhitzung |
| 3 | Steuerlogik & Sicherheit | Heizungssteuerung | Heizung aktivieren/deaktivieren |
|   |   | Trockenlaufschutz | Verhindert Betrieb ohne Wasser |
|   |   | Fehlerbehandlung | Quittierung durch Benutzer |
| 4 | Fehlerdiagnose & Überwachung | Plausibilitätsprüfung | Prüft Sensorwerte auf Gültigkeit |
|   |   | Selbsttest | Funktionsprüfung beim Start |
|   |   | Watchdog | Reaktion auf Ausfälle |
| 5 | Benutzerinterface | Füllstandsanzeige | Darstellung ml/% mit Ampelsystem |
|   |   | Fehlermeldungen | Priorisierte Fehlerausgabe |
|   |   | Akustische Warnung | Summer bei Warnung |
|   |   | Schwelle einstellen | Benutzerdefinierbare Warnwerte |
|   |   | Quittierung | Freigabe nach Fehler |



