# Lastenheft – Trockenlaufschutz für Eierkocher

## 1. Ziel des Systems

Der Trockenlaufschutz soll den sicheren Betrieb des Eierkochers gewährleisten, indem er den Wasserstand kontinuierlich überwacht, den Nutzer rechtzeitig warnt und im Ernstfall das Gerät automatisch abschaltet, um Beschädigungen zu vermeiden.

Das System informiert den Benutzer visuell und akustisch über den aktuellen Füllstand, die Temperatur sowie mögliche Fehlerzustände. Es soll intuitiv bedienbar und wartungsfrei funktionieren.

---

## 2. Funktionsanforderungen

### 2.1 Füllstandserkennung
- **Ziel:** Kontinuierliche Messung des Wasserfüllstands im Eierkocher.  
- **Messbereich:** 0 ml – 250 ml  
- **Auflösung:** ≤ 10 ml  
- **Genauigkeit:** ± 5 % des Messwerts  
- **Abtastrate:** ≥ 5 Hz (alle 200 ms)
- **Anzeige:**  
  - Grün: Füllstand ≥ 50 %  
  - Gelb: 25 % ≤ Füllstand < 50 % (Warnung 1)  
  - Rot: 10 % ≤ Füllstand < 25 % (Warnung 2)  
  - Rot blinkend: Füllstand < 10 % (Trockenlaufschutz aktiv)
- **Benutzerdefinierte Warnschwelle:** Einstellbar zwischen 10 % und 50 % über Menü.  

---

### 2.2 Trockenlaufschutz (Abschaltlogik)
- **Ziel:** Schutz vor Überhitzung oder Schäden durch fehlendes Wasser.  
- **Abschaltkriterium:**  
  - Füllstand < 10 % **oder**  
  - Temperaturanstieg > 5 °C/s über Zeitraum von ≥ 500 ms  
- **Reaktionszeit:** ≤ 1 s nach Erkennung  
- **Abschaltverhalten:**  
  - Heizung wird sofort deaktiviert.  
  - Akustische und visuelle Warnung werden ausgelöst.  
  - Fehlermeldung bleibt aktiv, bis Quittierung erfolgt.  
- **Wiedereinschalten:** Erst möglich, wenn Füllstand > 20 % und Benutzer die Fehlermeldung quittiert.  

---

### 2.3 Restkochzeitberechnung
- **Ziel:** Benutzer erkennt, wie lange mit aktuellem Wasserstand gekocht werden kann.  
- **Berechnungsgrundlage:**  
  - Wasserfüllstand (ml)  
  - Aktuelle Heizleistung (W)  
  - Durchschnittlicher Verdampfungswert (≈ 5 ml/min bei 100 °C)  
- **Anzeige:** Restzeit in Minuten ± 10 % Genauigkeit  
- **Warnung:**  
  - Bei Restkochzeit < 2 min erfolgt Warnung (gelb blinkend + kurzer Ton).  

---

### 2.4 Selbsttest und Fehlerdiagnose
- **Ziel:** Automatische Funktionsprüfung ohne Benutzereingriff.  
- **Ablauf:**  
  - Startet beim Einschalten (Dauer ≤ 2 s).  
  - Prüft Sensoren auf plausible Werte:  
    - Temperatur: 0–50 °C  
    - Füllstand: 0–100 %  
  - LED-/Displaytest: Alle Symbole kurz aktiv.  
- **Ergebnis:**  
  - Bei Erfolg → Anzeige Grün (betriebsbereit).  
  - Bei Fehler → akustische + visuelle Fehlermeldung.  
- **Laufende Diagnose:** Alle 30 s Plausibilitätsprüfung.  

---

### 2.5 Benutzerinterface
- **Ziel:** Klare, intuitive Anzeige aller relevanten Zustände.  
- **Anzeigeelemente:**  
  - Füllstand in ml  
  - Füllstand als Ampel (Grün/Gelb/Rot/Rot blinkend)  
  - Temperatur (°C)  
  - Fehlermeldungen mit Priorität über allen anderen Meldungen  
- **Fehlermeldungen:**  
  - „Sensorfehler“ (Sensor liefert unplausible Werte)  
  - „Überhitzung“ (Temperatur > 110 °C)  
  - „Trockenlauf erkannt“ (Heizung abgeschaltet)  
- **Akustische Signale:**  
  - Warnung: 2× kurz (60–70 dB(A))  
  - Fehler: 3× lang (70–80 dB(A))  
- **Displayeigenschaften:**  
  - Max. Helligkeit: < 300 cd/m²  
  - Ablesbarkeit bei Raumlicht ≤ 500 lx und Dunkelheit ≤ 10 lx  
  - Reaktionszeit Anzeigewechsel: ≤ 300 ms  
  - Barrierefreie Symbole für farbfehlsichtige Nutzer.  
- **Intuitive Bedienung:**  
  - Quittierung über einzige Taste „OK“.  
  - Nach Quittierung → Anzeige wechselt auf Grün.  

---

## 3. Nicht-funktionale Requirements

| Kriterium | Zielwert | Beschreibung |
|------------|-----------|--------------|
| **Reaktionszeit Sensor → Anzeige** | ≤ 300 ms | Zeit zwischen Messwertänderung und Anzeigeaktualisierung |
| **Abschaltzeit bei Trockenlauf** | ≤ 1 s | Schutzzeit zur Vermeidung von Überhitzung |
| **Falschalarmrate** | < 5 % | Fehlabschaltungen pro 100 Zyklen |
| **Selbsttestdauer** | ≤ 2 s | Zeit vom Einschalten bis Betriebsbereitschaft |
| **Lautstärke Warnsignal** | 60–80 dB(A) | Wahrnehmbar, aber nicht störend |
| **Temperaturgenauigkeit** | ± 1 °C | |
| **Füllstandgenauigkeit** | ± 5 % | |
| **Umgebungstemperatur** | 0–45 °C | Betriebstauglichkeit |
| **Luftfeuchtigkeit** | 20–90 % r. F. | |

---

## 4. Benutzerinteraktion und Ablauf

1. **Einschalten:**  
   - Selbsttest läuft automatisch (ca. 2 s).  
   - Anzeige wechselt auf Grün (System bereit).  

2. **Betrieb:**  
   - Anzeige zeigt Füllstand, Temperatur, ggf. Restzeit.  
   - Bei Füllstand < 50 % → Gelb (1. Warnung).  
   - Bei Füllstand < 25 % → Rot (2. Warnung).  

3. **Kritischer Zustand:**  
   - Bei Füllstand < 10 % oder Temperaturanstieg > 5 °C/s → Abschaltung.  
   - Warnsignal + Fehlermeldung „Trockenlauf erkannt“.  

4. **Wiedereinfüllen:**  
   - Nach Wasserzugabe → Benutzer muss Fehlermeldung quittieren.  
   - Anzeige wechselt nach Quittierung auf Grün (bereit).  

---

## 5. Sicherheit und Zuverlässigkeit

- Heizung darf nur aktiv sein, wenn kein Fehlerzustand anliegt.  
- System muss auch nach längerer Nichtbenutzung (> 30 Tage) korrekt funktionieren.  
- Daten aus Sensoren werden auf Plausibilität geprüft (0–110 %).  
- Bei Kommunikationsfehlern → sofortige Abschaltung (Fail-Safe-Modus).  

---

## 6. Erweiterungsmöglichkeiten (optional)

- Schnittstelle (z. B. UART/I²C) für Diagnose und Firmware-Update.  
- Log-Funktion für Fehlerhistorie (max. 10 Einträge).  
- Optionale App-Anbindung zur Anzeige von Wasserstand und Status.

---

## 7. Akzeptanzkriterien

Das System gilt als erfolgreich umgesetzt, wenn:

1. Der Trockenlauf in 100 % der Testläufe zuverlässig erkannt und verhindert wird.  
2. Warnanzeigen und akustische Signale klar und verständlich sind.  
3. Keine Fehlabschaltung bei normalem Betrieb auftritt (> 95 % Erfolgsrate).  
4. Selbsttest alle Sensoren korrekt erkennt.  
5. Der Benutzer nach dem Quittieren eindeutig erkennen kann, dass das Gerät wieder betriebsbereit ist.

---

© 2025 – Projekt Trockenlaufschutz / Florian Binder
