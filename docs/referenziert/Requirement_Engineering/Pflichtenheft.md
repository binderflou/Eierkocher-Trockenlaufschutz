# Pflichtenheft – Trockenlaufschutz für Eierkocher

## 1. Ziel des Systems

Das Pflichtenheft beschreibt die technische Umsetzung der Anforderungen aus dem Lastenheft für den Trockenlaufschutz eines Eierkochers.  
Das System soll Wasserfüllstand, Temperatur und Zustand erfassen, Warnungen ausgeben, Fehlermeldungen anzeigen und im Ernstfall automatisch abschalten.  
Die Steuerung erfolgt über einen **Arduino Nano** mit angeschlossener Sensorik und Display-Peripherie.

---

## 2. Systemübersicht

| Komponente | Typ | Beschreibung |
|-------------|-----|--------------|
| Mikrocontroller | Arduino Nano | Zentrale Steuerung, Auswertung der Sensoren, Ansteuerung von Display, Summer, Relais |
| Füllstandsensor | Kapazitiver Sensor (0–3,3 V) | Misst Wasserstand zwischen 5 ml (0 %) und 250 ml (100 %) – **R1.1** |
| Temperatursensor | NTC / DS18B20 | Misst Temperatur an Heizplatte (30–150 °C) – **R1.2** |
| Timer / Echtzeituhr | Intern (Arduino) | Zeitstempel für Plausibilität und Verlaufsauswertung – **R1.3** |
| Display | LCD oder OLED (mind. 0,96") | Anzeige von Füllstand, Warnungen, Temperatur und Fehlern – **R5.1–R5.3** |
| Summer | Akustisches Warnsignal | Ton bei Warnungen und Fehlern – **R5.4** |
| Relais / MOSFET | Schaltelement | Steuerung der Heizleistung (An/Aus) – **R3.1** |
| Spannungsversorgung | 5 V DC | Versorgung von Arduino, Sensoren und Peripherie |

---

## 3. Funktionale Requirements

### 3.1 Anzeige des Füllstands (**R5.1, R5.2, R5.3**)

- **Darstellung:**  
  - Mehrfarbige Anzeige (Grün, Gelb, Rot) auf dem Display  
  - Zusätzlich numerische Anzeige in **ml**  
- **Aktualisierungsintervall:** 500 ms  
- **Genauigkeit:** ± 5 % des Messwerts  
- **Farbkodierung:**
  - **Grün:** Füllstand > 50 % (ausreichend Wasser, betriebsbereit)  
  - **Gelb:** Füllstand 10–50 % (Warnung 1)  
  - **Rot:** Füllstand < 10 % (kritisch, Trockenlauf droht)  
  - **Rot blinkend:** Trockenlaufschutz aktiv, Heizung abgeschaltet  
- **Ziel:** Anzeige bleibt schlicht, leicht lesbar und reagiert ohne wahrnehmbare Verzögerung (< 300 ms Anzeigewechsel).  

---

### 3.2 Warnfunktion bei niedrigem Füllstand (**R3.1, R3.2, R5.4, R5.5**)

- **Benutzerdefinierte Warnschwelle:** Einstellbar zwischen 10 % und 50 % über das Display-Menü (**R5.5**).  
- **Aktionen bei Unterschreitung der Warnschwelle:**  
  - **Visuell:** Rotes Segment blinkt (1 Hz Frequenz)  
  - **Akustisch:** Piepton (70 dB(A), 2× kurz) (**R5.4**)  
- **Automatische Abschaltung:**  
  - Bei Füllstand < 10 % oder Temperaturanstieg > 5 °C/s (**R3.1**)  
  - Heizung wird über Relais innerhalb von ≤ 1 s deaktiviert  
- **Anzeige:** Fehlermeldung „Trockenlauf erkannt“ bleibt aktiv, bis Benutzer durch Taste **OK** quittiert. (**R3.2**)  

---

### 3.3 Fehlermeldungen und Diagnose (**R4.1–R4.3**)

- **Ziel:** Klare und priorisierte Darstellung von Systemstörungen.  
- **Fehlertypen und Reaktionen:**

| Fehlerart | Auslöser | Anzeige | Reaktion |
|------------|-----------|----------|-----------|
| Trockenlauf | Füllstand < 10 % oder dT/dt > 5 °C/s | Rot blinkend, Meldung „Trockenlauf erkannt“ | Heizung aus, akustisch 3× Ton |
| Überhitzung | Temperatur > 120 °C | Meldung „Überhitzung / Sicherheitsabschaltung“ | Heizung aus |
| Sensorfehler | Sensorwert außerhalb plausibler Range | Meldung „Sensorfehler“ | Warnung, Heizung aus |
| Keine Sensoränderung | Keine Änderung > 10 s | Warnung „Sensorprüfung“ | Fehlermeldung Display |

- **Quittierung:**  
  - Alle Fehlermeldungen müssen manuell mit „OK“ bestätigt werden.  
  - Nach erfolgreicher Quittierung wird auf **Grün (bereit)** geschaltet.  

---

### 3.4 Sensordatenerfassung, Zustandsüberwachung und Steuerlogik  
(**R1.1–R1.3, R2.1–R2.3, R3.3**)

#### a. Füllstandsensorik (**R1.1**)
- Kapazitiver Sensor (0–3,3 V Analogausgang)  
- **Messbereich:** 5 ml = 0 %, 200 ml = 100 % (± 5 %)  
- **Abtastrate:** 5 Hz (200 ms)  
- **Filterung:** Gleitender Mittelwert (5 Messpunkte)  

#### b. Temperaturerfassung (**R1.2**)
- Messung über NTC oder DS18B20-Sensor an Heizplatte  
- **Messbereich:** 30–150 °C  
- **Abtastung:** 5 Hz  
- **Trockenlauf-Erkennung:** Temperaturanstieg > 5 °C/s über 500 ms  
- **Überhitzungsschutz:** Abschaltung > 120 °C  

#### c. Sensorüberwachung (**R2.3, R4.3**)
- Keine Änderung des Füllstandwertes > 10 s → Fehleranzeige  
- Plausibilitätsprüfung bei Boot (**R4.1**):  
  - Temperatur: 0–50 °C  
  - Füllstand: 0–100 %  
- Bei unplausiblen Werten → Warnung „Sensorfehler“ und Deaktivierung Heizung.  

#### d. Zustandslogik (**R2.1, R2.2, R3.1, R3.2**)

| Zustand | Bedingung | Anzeige | Aktion |
|----------|------------|----------|---------|
| Bereit | Wasser > 50 % | Grün | Heizung erlaubt |
| Warnung 1 | Wasser 10–50 % | Gelb | Warnanzeige |
| Warnung 2 | Wasser < 10 % | Rot | Warnsignal |
| Trockenlauf | Kein Wasser / ΔT > 5 °C/s | Rot blinkend | Heizung aus, Fehler |
| Überhitzung | T > 120 °C | Warnsymbol „Überhitzung“ | Heizung aus |
| Sensorfehler | Unplausible Werte | Fehlermeldung | Heizung aus |

#### e. Steuerung / Logik (**R2.1–R2.3, R3.3**)
- Steuerung erfolgt durch **Arduino Nano**.  
- **Programmlogik:**  
  1. Erfassung Sensorwerte  
  2. Vergleich Soll/Ist-Werte  
  3. Zustandserkennung  
  4. Ausgabe von Signalen an Display und Summer  
  5. Sicherheitsabschaltung bei Fehler  

---

### 3.5 Benutzerinterface (**R5.1–R5.5**)

- **Displayinhalte:**  
  - Füllstand in ml (**R5.1**)  
  - Füllstandsampel (Grün/Gelb/Rot) (**R5.2**)  
  - Temperatur (°C)  
  - Fehlermeldungen (priorisiert) (**R5.3**)  
- **Akustische Signale:**  
  - Warnung: 2× kurz (**R5.4**)  
  - Fehler: 3× lang (**R5.4**)  
- **Bedienung:**  
  - Eine Taste („OK“) zur Quittierung von Fehlern  
  - Menüsteuerung über Dreh-Encoder oder Taster optional (**R5.5**)  
- **Barrierefreiheit:**  
  - Farbcodes werden durch Symbole ergänzt  
  - Hoher Kontrast (min. 7:1 Verhältnis)  
- **Reaktionszeiten:**  
  - Anzeigeupdate: ≤ 300 ms  
  - Tonstart nach Ereignis: ≤ 200 ms  

---

## 4. Selbsttest und Fehlerdiagnose (**R4.1–R4.3**)

- **Automatischer Selbsttest beim Einschalten:**  
  - Prüft Sensoren auf plausible Wertebereiche  
  - Testet Display-Elemente (alle Farben kurz aktiv)  
  - Prüft Summer (1 kurzer Ton)  
- **Dauer:** ≤ 2 s  
- **Anzeige:**  
  - Erfolgreich → Grün  
  - Fehler → Fehlermeldung mit Symbol und Ton  
- **Laufende Prüfung:**  
  - Alle 30 s wird Sensorplausibilität erneut überprüft (**R4.3**)  

---

## 5. Nicht-funktionale Requirements

| Kriterium | Zielwert | Beschreibung |
|------------|-----------|--------------|
| Reaktionszeit Sensor → Anzeige | ≤ 300 ms | Anzeigeänderung nach Messwertänderung |
| Reaktionszeit Sensor → Abschaltung | ≤ 1 s | Trockenlaufschutz aktiv |
| Füllstandmessgenauigkeit | ± 5 % | Innerhalb des Messbereichs |
| Temperaturgenauigkeit | ± 1 °C | Im Bereich 30–120 °C |
| Fehlalarmrate | < 5 % | Anteil unnötiger Abschaltungen |
| Selbsttestdauer | ≤ 2 s | Einschaltprüfung |
| Lautstärke Warnsignal | 60–80 dB(A) | Wahrnehmbar, aber nicht störend |
| Betriebsspannung | 5 V ± 10 % | Versorgung aller Komponenten |
| Umgebungstemperatur | 0–45 °C | Betrieb unter Haushaltsbedingungen |
| Luftfeuchtigkeit | 20–90 % r. F. | Keine Fehlfunktionen durch Dampf |

---

## 6. Sicherheitsfunktionen (**R3.1–R3.3, R4.2**)

- Heizung deaktiviert bei:  
  - Füllstand < 10 % (**R3.1**)  
  - Temperatur > 120 °C (**R3.1**)  
  - Sensorfehler oder Kommunikationsfehler (**R4.2**)  
- Alle sicherheitsrelevanten Funktionen werden im **Fail-Safe-Modus** ausgeführt (Heizung aus).  
- Softwarefehler (Watchdog-Reset) führen zu sicherem Zustand (Abschaltung).  

---

## 7. Erweiterungen (optional)

- Serielle Schnittstelle (UART/I²C) für Diagnose und Firmwareupdate.  
- Datenlogging (Fehlerhistorie der letzten 10 Ereignisse).  
- Statistiken: Gesamtbetriebszeit, Anzahl Trockenlauf-Ereignisse.  
- Optionale Bluetooth-Verbindung für App-basierte Anzeige.

---

## 8. Abnahmekriterien

Das System gilt als erfolgreich umgesetzt, wenn:

1. Alle Sensoren zuverlässig arbeiten und Trockenlauf in 100 % der Tests erkannt wird (**R1.1–R1.2, R3.1**).  
2. Warnungen (akustisch und visuell) klar unterscheidbar sind (**R3.2, R5.1–R5.4**).  
3. Abschaltung bei kritischem Zustand < 1 s erfolgt (**R3.1**).  
4. Keine Fehlabschaltung (> 95 % Erfolgsrate) (**R2.1, R3.3**).  
5. Selbsttest beim Einschalten funktioniert fehlerfrei (**R4.1–R4.3**).  
6. Nach Quittierung eines Fehlers wechselt Anzeige auf Grün und Gerät ist betriebsbereit (**R5.3, R5.5**).

---

© 2025 – Projekt Trockenlaufschutz / Florian Binder
