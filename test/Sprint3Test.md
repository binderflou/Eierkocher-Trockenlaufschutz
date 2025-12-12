# Testfälle Sprint 3

Alle folgenden Testfälle wurden im Rahmen von Sprint 3 manuell in der Entwicklungsumgebung "per Hand" durchgeführt.
Die folgenden Testfälle erweitern die bereits in Sprint 1 und Sprint 2 definierten Modul- und Integrationstests um sicherheitsrelevante Funktionen aus den Anforderungen **R5.3–R5.6**. 

Zusätzlich zu den neu definierten Testfällen für Sprint 3 wurden alle relevanten Testfälle aus Sprint 1 und Sprint 2 erneut ausgeführt. Ziel war es sicherzustellen, dass die im dritten Sprint erweiterten sicherheitsrelevanten Funktionen keine negativen Auswirkungen auf bereits implementierte Basisfunktionen haben. Sämtliche wiederholten Tests aus Sprint 1 und 2 wurden erfolgreich durchgeführt, sodass die Funktionalität und Stabilität der bestehenden Systemkomponenten weiterhin gewährleistet ist.

---

## 1. Modultests (algorithmische Korrektheit)

### **M7 – SafetyManager: Gelatchter Trockenlauf**
**Requirement:** R5.4  

- **Vorbedingung:** `SafetyManager` ist initialisiert, kein Trockenlauf aktiv.
- **Aktion:** Trockenlaufbedingung wird einmal ausgelöst (`fillLevel < 5`, `deltaT > 5`).
- **Erwartete Reaktion:** Trockenlauf bleibt aktiv, auch wenn die Bedingung im nächsten Zyklus nicht mehr erfüllt ist.
- **Nachbedingung:** Trockenlauf wird erst nach explizitem Reset deaktiviert.
- **Status:**  **bestanden**

---

### **M8 – FillLevelSensor: Auto-Refill deaktiviert**
**Requirement:** R5.4  

- **Vorbedingung:** Auto-Refill ist deaktiviert.
- **Aktion:** Füllstand fällt auf 0 %, anschließend mehrere Sensorzyklen.
- **Erwartete Reaktion:** Füllstand bleibt bei 0 % und springt nicht automatisch auf 100 %.
- **Nachbedingung:** Nach manuellem `refillToFull()` ist der Füllstand wieder 100 %.
- **Status:**  **bestanden**

---

### **M9 – DisplayController: Warnanzeige setzen und löschen**
**Requirement:** R5.3  

- **Vorbedingung:** DisplayController ist initialisiert.
- **Aktion:** Warnung wird angezeigt und anschließend gelöscht.
- **Erwartete Reaktion:** Warntext wird korrekt angezeigt und nach `clearWarning()` entfernt.
- **Nachbedingung:** Füllstand- und Temperaturanzeige bleiben unverändert.
- **Status:**  **bestanden**

---

### **M10 – ThresholdManager: Warnschwelle setzen und abfragen**
**Requirement:** R5.6  

- **Vorbedingung:** `ThresholdManager` ist initialisiert, Standard-Warnschwelle aktiv.
- **Aktion:** Warnschwelle wird auf einen neuen Wert gesetzt (z. B. 40 %).
- **Erwartete Reaktion:** `getWarningThreshold()` liefert den neu gesetzten Wert.
- **Nachbedingung:** Interner Schwellenwert ist korrekt aktualisiert.
- **Status:**  **bestanden**

---

## 2. Integrations-Testfälle (Zusammenarbeit von Komponenten)

### **I7 – Trockenlauf → WAIT_FOR_FILL**
**Requirements:** R5.4, R5.5  

- **Vorbedingung:** Sensorwerte erfüllen Trockenlaufbedingung.
- **Aktion:** `SystemController.executeCycle()` wird ausgeführt.
- **Erwartete Reaktion:**  
  - Heizung wird abgeschaltet  
  - Fehlermeldung wird angezeigt  
  - Buzzer spielt Fehlerton  
  - System wartet auf Benutzeraktion (`WAIT_FOR_FILL`)
- **Nachbedingung:** Kein automatischer Neustart.
- **Status:**  **bestanden**

---

### **I8 – Taste F: Manuelles Füllen**
**Requirement:** R5.4  

- **Vorbedingung:** System befindet sich in `WAIT_FOR_FILL`.
- **Aktion:** Benutzer drückt Taste **F**.
- **Erwartete Reaktion:**  
  - Füllstand wird auf 100 % gesetzt  
  - System wechselt zu `WAIT_FOR_ACK`
- **Nachbedingung:** Heizung bleibt aus, System wartet auf Bestätigung.
- **Status:**  **bestanden**

---

### **I9 – Taste A: Quittierung und Neustartfreigabe**
**Requirements:** R5.4, R5.5  

- **Vorbedingung:** System befindet sich in `WAIT_FOR_ACK`.
- **Aktion:** Benutzer drückt Taste **A**.
- **Erwartete Reaktion:**  
  - Trockenlauf wird zurückgesetzt  
  - Warnung und Buzzer werden deaktiviert  
  - Normalbetrieb wird freigegeben
- **Nachbedingung:** System läuft wieder regulär weiter.
- **Status:**  **bestanden**

---

### **I10 – Laufzeitänderung der Warnschwelle beeinflusst Anzeige und Buzzer**
**Requirement:** R5.6, R5.5, R5.3  

- **Vorbedingung:**  
  - System läuft im Normalbetrieb.  
  - Aktueller Füllstand liegt zwischen alter und neuer Warnschwelle (z. B. 45 %).
- **Aktion:**  
  - Benutzer drückt Taste **W**  
  - Neue Warnschwelle wird auf **40 %** gesetzt.
- **Erwartete Reaktion:**  
  - Warnschwelle wird sofort im `ThresholdManager` aktualisiert.  
  - Bei Füllstand **≤ 40 %** erscheint die Warnanzeige.  
  - Der Buzzer gibt ein akustisches Warnsignal aus.
- **Nachbedingung:**  
  - Warnschwelle bleibt aktiv, bis sie erneut geändert wird.  
  - System reagiert konsistent auf den neuen Schwellenwert.
- **Status:**  **bestanden**

---

## 3. Traceability-Zuordnung (Sprint 3)

| Testfall | Requirement |
|--------|-------------|
| M7 | R5.4 |
| M8 | R5.4 |
| M9 | R5.3 |
| M10 | R5.6 |
| I7 | R5.4, R5.5 |
| I8 | R5.4 |
| I9 | R5.4, R5.5 |
| I10 | R5.6, R5.5, R5.3 |

Alle Requirements **R5.3–R5.6** sind damit vollständig durch **Modul- und Integrationstests** abgedeckt.

Alle Testfälle wurden erfolgreich durchgeführt und erfüllen die zugeordneten Requirements vollständig.