# Design
## Klassendiagramm

![Klassendiagramm](../referenziert/Design/KlassendiagrammSoftwareEngineering.png)

## 1. Zweck des Klassendiagramms
Das Klassendiagramm beschreibt die objektorientierte Struktur der Software für den **Trockenlaufschutz eines Eierkochers**.  
Es dient der logischen Modellierung aller wesentlichen Systemkomponenten und stellt deren **Verantwortlichkeiten, Attribute, Methoden und Beziehungen** dar.  
Die Architektur folgt dem **Schichtenmodell** aus:

- **UserInterface** (Anzeige, Ton, Eingabe)  
- **Steuerungslogik** (Systemsteuerung, Zustandsmanagement, Sicherheit)  
- **HardwareAbstraction** (Sensor- und Aktorsteuerung)  
- **PersistenceManager** (Datenspeicherung und Kalibrierung)

Dieses Diagramm bildet die Grundlage für die Implementierung auf einem **Arduino Nano** mit C++.

---

## 2. Überblick über die Struktur
Die Software besteht aus vier Hauptschichten mit den zugehörigen Klassen:

| **Schicht** | **Klassen** | **Beschreibung** |
|--------------|-------------|------------------|
| **UserInterface** | `DisplayController`, `BuzzerController`, `InputHandler` | Verwaltung von Anzeige, akustischer Signalisierung und Benutzereingaben |
| **Steuerungslogik** | `SystemController`, `StateDetector`, `SafetyManager`, `ThresholdManager` | Zentrale Steuerung, Zustandsüberwachung und Sicherheitslogik |
| **HardwareAbstraction** | `FillLevelSensor`, `TemperatureSensor`, `HeaterControl`, `TimerService` | Ansteuerung und Abstraktion der Sensoren und Aktoren |
| **PersistenceManager** | `CalibrationData`, `SettingsStorage` | Verwaltung von Kalibrierungsdaten und Persistenzspeicherung |

---

## 3. Klassendokumentation

### 3.1 `SystemController`
**Rolle:** Hauptsteuerung der Anwendung  
**Schicht:** Steuerungslogik  

**Aufgaben:**
- Führt den Hauptzyklus (`loop`) aus  
- Liest Sensordaten ein  
- Prüft Zustände und Sicherheitsbedingungen  
- Steuert Anzeige, Summer und Heizung  

**Attribute:**
- `fillSensor : FillLevelSensor`  
- `tempSensor : TemperatureSensor`  
- `heater : HeaterControl`  
- `ui : DisplayController`  
- `buzzer : BuzzerController`  

**Methoden:**
- `setup()` – Initialisierung von Komponenten  
- `executeCycle()` – Ablaufsteuerung  
- `handleError(errorCode : int)` – Fehlerbehandlung  
- `updateSystemState()` – Zustandslogik aktualisieren  

---

### 3.2 `StateDetector`
**Rolle:** Erkennung des aktuellen Systemzustands (Bereit, Warnung, Trockenlauf, Fehler)  
**Schicht:** Steuerungslogik  

**Aufgaben:**
- Auswertung von Füllstand und Temperatur  
- Rückgabe eines logischen Zustands zur Anzeige und Steuerung  

**Attribute:**
- `currentState : string`  
- `fillLevel : int`  
- `temperature : float`  

**Methoden:**
- `detectState(fillLevel : int, temperature : float) : string`  
- `getState() : string`

---

### 3.3 `SafetyManager`
**Rolle:** Überwachung und Schutzfunktionen  
**Schicht:** Steuerungslogik  

**Aufgaben:**
- Prüft Trockenlaufbedingungen  
- Löst Sicherheitsabschaltung aus  
- Verwaltet Fail-Safe-Verhalten  

**Attribute:**
- `dryRunDetected : bool`  

**Methoden:**
- `checkDryRun(fillLevel : int, tempRise : float) : bool`  
- `emergencyShutdown()` – Heizung abschalten  

---

### 3.4 `DisplayController`
**Rolle:** Anzeige der Systemzustände  
**Schicht:** UserInterface  

**Aufgaben:**
- Aktualisiert die Displayanzeige (Füllstand, Temperatur, Warnungen, Fehler)  
- Steuert farbliche und symbolische Darstellung  

**Attribute:**
- `fillLevelDisplay : int`  
- `temperatureDisplay : int`  
- `warningMessage : string`  

**Methoden:**
- `updateDisplay(fillLevel : int, temperature : int, status : string)`  
- `showWarning(message : string)`  
- `clearDisplay()`  

---

### 3.5 `BuzzerController`
**Rolle:** Akustische Signalisierung  
**Schicht:** UserInterface  

**Aufgaben:**
- Ausgabe von Warn- und Fehlertönen  
- Steuerung der Signalarten (kurz/lang)  

**Attribute:**
- `buzzerPin : int`  

**Methoden:**
- `playWarningTone()`  
- `playErrorTone()`  
- `stopTone()`  

---

### 3.6 `InputHandler`
**Rolle:** Benutzerinteraktion (Taster/Encoder)  
**Schicht:** UserInterface  

**Aufgaben:**
- Liest Eingaben ein  
- Übermittelt Benutzeraktionen an die Steuerlogik  

**Attribute:**
- `buttonPin : int`  
- `buttonState : bool`  

**Methoden:**
- `readInput() : bool`  
- `isButtonPressed() : bool`

---

### 3.7 `FillLevelSensor`
**Rolle:** Erfassung des Wasserstands  
**Schicht:** HardwareAbstraction  

**Aufgaben:**
- Liest analogen Sensorwert  
- Berechnet Prozentfüllstand  
- Prüft Messwert auf Plausibilität  

**Attribute:**
- `analogPin : int`  
- `fillLevelPercent : int`  

**Methoden:**
- `readLevel() : int`  
- `isValid() : bool`

---

### 3.8 `TemperatureSensor`
**Rolle:** Messung der Temperatur  
**Schicht:** HardwareAbstraction  

**Aufgaben:**
- Liest Temperaturwert (NTC oder DS18B20)  
- Berechnet Temperaturänderungsrate  

**Attribute:**
- `tempPin : int`  
- `temperature : float`  

**Methoden:**
- `readTemperature() : float`  
- `getDeltaT() : float`

---

### 3.9 `HeaterControl`
**Rolle:** Steuerung der Heizleistung  
**Schicht:** HardwareAbstraction  

**Aufgaben:**
- Schaltet Heizelement über Relais oder MOSFET  
- Prüft Zustand der Heizung  

**Attribute:**
- `relayPin : int`  
- `isOn : bool`  

**Methoden:**
- `switchOn()`  
- `switchOff()`  
- `getStatus() : bool`

---

### 3.10 `SettingsStorage`
**Rolle:** Verwaltung persistenter Parameter  
**Schicht:** PersistenceManager  

**Aufgaben:**
- Laden und Speichern von Grenzwerten und Kalibrierungsdaten  
- Zugriff auf Fehlerhistorie  

**Attribute:**
- `warningThreshold : int`  
- `criticalThreshold : int`  

**Methoden:**
- `loadSettings()`  
- `saveSettings()`  
- `getCalibrationData() : CalibrationData`

---

### 3.11 `CalibrationData`
**Rolle:** Speicherung der Kalibrierungsdaten  
**Schicht:** PersistenceManager  

**Aufgaben:**
- Verwaltung der Füllstands- und Temperaturkennlinien  
- Bereitstellung von Korrekturwerten für Sensorik  

**Attribute:**
- `fillCalibValues : int[]`  
- `tempCalibValues : float[]`  

**Methoden:**
- `getFillCalib() : int[]`  
- `getTempCalib() : float[]`

---

## 4. Beziehungen zwischen den Klassen

| **Beziehung** | **Beteiligte Klassen** | **Beschreibung** |
|----------------|------------------------|------------------|
| Aggregation | `SystemController` → `FillLevelSensor`, `TemperatureSensor`, `HeaterControl`, `DisplayController` | Zentrale Steuerung besitzt und verwendet diese Komponenten |
| Assoziation | `SystemController` ↔ `SafetyManager`, `StateDetector` | Logische Zusammenarbeit bei Zustandsprüfung |
| Komposition | `UserInterface` ↔ `DisplayController`, `BuzzerController`, `InputHandler` | UI besteht aus diesen Subkomponenten |
| Abhängigkeit | `Steuerungslogik` → `PersistenceManager` | Steuerlogik nutzt gespeicherte Parameter |
| Aggregation | `SettingsStorage` → `CalibrationData` | Persistenzmodul enthält Kalibrierdatenobjekt |

---

## 5. Zusammenhang mit Anforderungen

| **Requirement-ID** | **Betroffene Klassen** | **Beschreibung** |
|---------------------|------------------------|------------------|
| R1.1, R1.2 | `FillLevelSensor`, `TemperatureSensor` | Erfassen und Filtern von Messwerten |
| R2.1–R3.3 | `SystemController`, `StateDetector`, `SafetyManager` | Zustandslogik und Sicherheitsüberwachung |
| R4.1–R4.3 | `SettingsStorage`, `CalibrationData` | Selbsttest, Fehlerdiagnose, Datenspeicherung |
| R5.1–R5.5 | `DisplayController`, `BuzzerController`, `InputHandler` | Anzeige, Warnungen und Benutzerinteraktion |

---

## 6. Fazit

Das Klassendiagramm gewährleistet eine **klare Trennung der Verantwortlichkeiten** und eine **testbare modulare Struktur**.  
Durch die Schichtenarchitektur ist das System:
- **erweiterbar** (z. B. Bluetooth-Diagnose, Logging),
- **fehlertolerant** (Sicherheitsabschaltung über SafetyManager),
- **wartbar** (klare Schnittstellen),
- und **hardwareunabhängig** (dank Abstraktionsschicht).

Damit erfüllt die Architektur die funktionalen und nicht-funktionalen Anforderungen aus dem Pflichtenheft vollständig.


## Sequenzdiagramm

![Sequenzdiagramm](../referenziert/Design/SequenzdiagrammSoftwareEngineering.png)

## Kommunikationsdiagramm

![Kommunikationsdiagramm](../referenziert/Design/Kommunikationsdiagramm1.png)


# Softwarearchitektur – Design-Komponenten

```mermaid
graph TD
    %% Schicht 1: Sensordatenerfassung
    subgraph Sensordatenerfassung
        FILL[Füllstandsmessung]
        TEMP[Temperaturmessung]
        TIME[Zeitgeber]
    end

    %% Schicht 2: Datenverarbeitung & Zustandsüberwachung
    subgraph Auswerte-Steuerlogik
        DAT[Sensor-Datenverarbeitung]
        SIV[Soll/Ist-Vergleich]
        STATUS[Statusverwaltung]
    end

    %% Schicht 3: Steuerlogik & Sicherheit
    subgraph Steuerung
        HEAT[Heizungssteuerung]
        SAFETY[Trockenlaufschutz/Sicherheitsmodus]
    end

    %% Schicht 4: Benutzerinterface
    subgraph UI
        DISPLAY_FILL[Füllstandsanzeige]
        DISPLAY_TEMP[Temperaturanzeige]
        WARN[Warn- & Fehlermeldung]
    end

    %% Schicht 5: Test & Diagnose
    subgraph Test_und_Diagnose
        SELFTEST[Selbsttest & Plausibilitätsprüfung]
        ERROR[Fehleranalyse]
    end

    %% Datenflüsse zwischen den Komponenten
    FILL --> DAT
    TEMP --> DAT
    TIME --> DAT
    DAT --> SIV
    SIV --> STATUS
    STATUS --> HEAT
    STATUS --> SAFETY
    STATUS --> DISPLAY_FILL
    STATUS --> DISPLAY_TEMP
    STATUS --> WARN
    SELFTEST --> DAT
    SELFTEST --> SIV
    SELFTEST --> WARN
    ERROR --> STATUS
    ERROR --> WARN
````

# Software-Design-Komponenten

Die folgende Tabelle zeigt die Zerlegung der Architektur-Ebenen (Sensorik, Auswertelogik, Steuerlogik, Benutzerinterface)  
in kleinere Software-Design-Komponenten.  
Diese Beschreibung erfolgt **ohne objektorientierte Modellierung** (also nur Funktionsblöcke).

| **Architektur-Ebene** | **Software-Design-Komponente** | **Aufgabe / Beschreibung** | **Eingabe** | **Ausgabe** |
|------------------------|--------------------------------|-----------------------------|--------------|--------------|
| **Sensorik** | `FillLevelReader` | Erfasst den analogen Füllstandswert, normiert auf 0–100 %, filtert Messrauschen. | Analoge Spannung (0–3,3 V) | Prozentwert (0–100 %), gefiltert |
|  | `TemperatureReader` | Liest Temperatur über NTC oder DS18B20, berechnet Temperaturdifferenz ΔT/Δt. | Digitalwert / Widerstand | Temperaturwert in °C, Änderungsrate |
|  | `SensorValidator` | Prüft Sensordaten auf Plausibilität (0–100 %, 0–150 °C). | Messwerte | Status: OK / Fehlercode |
| **Auswertelogik** | `DataFilter` | Gleitender Mittelwert über letzte n Messpunkte, um Schwankungen zu glätten. | Rohdaten | Gefilterte Werte |
|  | `StateDetector` | Erkennt Systemzustand (Bereit, Warnung, Trockenlauf, Überhitzung). | Sensordaten | Zustandskennung |
|  | `ThresholdManager` | Verarbeitet benutzerdefinierte Warnschwelle (10–50 %). | Eingabewert | Grenzwert |
|  | `DryRunDetector` | Ermittelt Trockenlauf anhand Füllstand < 10 % oder ΔT > 5 °C/s. | Sensordaten | Trockenlauf-Flag |
| **Steuerlogik** | `HeaterControl` | Steuert Relais/MOSFET zur Heizungsabschaltung bei kritischem Zustand. | Zustand, Sensorwerte | Schaltsignal (Ein/Aus) |
|  | `SafetyManager` | Koordiniert Sicherheitsabschaltung bei Trockenlauf, Überhitzung, Sensorfehler. | Fehlerstatus | Relais Aus, Warnsignal |
|  | `SystemController` | Hauptzyklus: liest Sensoren, aktualisiert Zustände, steuert UI und Heizung. | Alle Daten | Steuerbefehle |
|  | `SelfTestManager` | Führt Start-Selbsttest und zyklische Prüfungen durch. | Sensorstatus | Testresultat / Fehlercode |
| **Benutzerinterface (UI)** | `DisplayController` | Zeigt Werte, Warnungen und Fehler an (Farbcode, Text, Symbole). | Zustand, Messdaten | LCD-Ausgabe |
|  | `BuzzerController` | Erzeugt akustische Warnsignale (2× kurz, 3× lang). | Fehlerzustand | Tonmuster |
|  | `InputHandler` | Liest Taste / Encoder, verarbeitet Quittierungen und Einstellungen. | Benutzereingabe | Befehle an Steuerlogik |
| **Systemdienste** | `TimerService` | Zeitbasis für Messintervalle, Selbsttest, Blinken etc. | Systemzeit | Zeitstempel, Timer-Ereignisse |
|  | `Logger` *(optional)* | Speichert Fehlerhistorie und Betriebsdaten (z. B. Trockenlaufzähler). | Ereignisse | Logdaten |
|  | `CommInterface` *(optional)* | Schnittstelle für serielle Diagnose oder Bluetooth. | Datenpakete | Debug-/Diagnosedaten |

