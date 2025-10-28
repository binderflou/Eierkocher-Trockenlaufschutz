# Systemkomponenten 

- Sensorik (Füllstand, Temperatur, Timer)
- Mikrocontroller (Auswertelogik + Steuerlogik)
- Benutzer Interface (Display, Summer)
- Stromversorgung
- Heizelement


### 2.1 Interne Systemschnittstellen

| Schnittstelle | Quelle | Ziel | Art der Daten | Beschreibung | Kommunikationsart |
|---------------|--------|------|---------------|---------------|-------------------|
| Füllstandssensor → Auswertelogik | Sensor | Auswertelogik | Analog/Digitalwert (0–100 %) | Überträgt aktuellen Füllstand in Echtzeit (≤200 ms) | Asynchron (Sensor liefert Messwerte per Interrupt) |
| Temperatursensor → Auswertelogik | Sensor | Auswertelogik | Temperaturwert in °C | Meldet Heizplattentemperatur mit 5 Hz Abtastrate | Asynchron (periodisch getriggert durch Abtasttimer) |
| Zeitgeber → Steuerlogik | RTC/Timer | Steuerlogik | Zeitstempel | Liefert Zeit für Soll/Ist-Vergleiche, Plausibilitätstests | Synchron (Abfrage durch Steuerlogik bei Bedarf) |
| Auswertelogik → Steuerlogik | Auswertelogik | Steuerlogik | Sensorwerte | Meldet geglättete Sensorwerte zur Auswertung an Steuerlogik | Interprozesskommunikation (z. B. Message Queue oder Shared Memory zwischen Tasks) |
| Steuerlogik → Heizung | Steuerlogik | Heizsystem | Schaltbefehl (Ein/Aus) | Aktiviert/Deaktiviert Heizung je nach Sensorwerten | Synchron (direktes Steuersignal, digitaler Ausgang) |
| Steuerlogik → Display | Steuerlogik | Display | Status, Füllstand, Warnungen | Anzeige von Betriebszustand, Warnungen, Fehlern | Asynchron (Display-Update-Task per Event oder Timer) |
| Steuerlogik → Summer | Steuerlogik | Akustische Signalgeber | Signaltyp (2× kurz / 3× lang) | Warnt Benutzer bei kritischen Zuständen | Asynchron (Ereignisgesteuert durch Fehlerstatus) |
| Display → Steuerlogik | Display | Steuerlogik | Taster Input | Meldet Steuerlogik Quittierung des Trockenlaufes | Asynchron (Interrupt oder Event bei Benutzereingabe) |

---

### 2.2 Externe Schnittstellen

| Schnittstelle | Quelle | Ziel | Art der Daten | Beschreibung | Kommunikationsart |
|---------------|--------|------|---------------|---------------|-------------------|
| Benutzer → UI | Benutzer | System | Eingaben, Quittierung, Warnschwellen | Benutzer kann Warnwerte einstellen und Fehler quittieren | Asynchron (Ereignisgesteuerte Benutzereingabe) |
| Stromversorgung | Extern | System | Elektrische Energie | Versorgt Sensoren, Steuerung, Display und Heizung | Synchron (physikalisch kontinuierlich) |

