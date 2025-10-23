# Systemkomponenten 
- Sensorik (Füllstand, Temperatur)
- Mikrocontroller (Auswertelogik + Steuerlogik)
- Benutzer Interface (Display, Summer)
- Stromversorgung
- Heizelement


| Schnittstelle | Quelle | Ziel | Art der Daten | Beschreibung |
|---------------|--------|-----|---------------|--------------|
| Füllstandssensor → Steuerlogik | Sensor | Steuerlogik | Analog/Digitalwert (0–100 %) | Überträgt aktuellen Füllstand in Echtzeit (≤200 ms) |
| Temperatursensor → Steuerlogik | Sensor | Steuerlogik | Temperaturwert in °C | Meldet Heizplattentemperatur mit 5 Hz Abtastrate |
| Zeitgeber → Steuerlogik | RTC/Timer | Steuerlogik | Zeitstempel | Liefert Zeit für Soll/Ist-Vergleiche, Plausibilitätstests |
| Steuerlogik → Heizung | Steuerlogik | Heizsystem | Schaltbefehl (Ein/Aus) | Aktiviert/Deaktiviert Heizung je nach Sensorwerten |
| Steuerlogik → Display | Steuerlogik | Display | Status, Füllstand, Warnungen | Anzeige von Betriebszustand, Warnungen, Fehlern |
| Steuerlogik → Summer | Steuerlogik | Akustische Signalgeber | Signaltyp (2× kurz / 3× lang) | Warnt Benutzer bei kritischen Zuständen |

### 2.2 Externe Schnittstellen
| Schnittstelle | Quelle | Ziel | Art der Daten | Beschreibung |
|---------------|--------|-----|---------------|--------------|
| Benutzer → UI | Benutzer | System | Eingaben, Quittierung, Warnschwellen | Benutzer kann Warnwerte einstellen und Fehler quittieren |
| Stromversorgung | Extern | System | Elektrische Energie | Versorgt Sensoren, Steuerung, Display und Heizung |
