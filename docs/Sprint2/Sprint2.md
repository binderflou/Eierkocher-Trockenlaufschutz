# Sprint 2 Planung

Im zweiten Sprint liegt der Fokus darauf, die sicherheitsrelevante Logik des Systems deutlich zu erweitern und das Verhalten des Eierkochers robuster sowie zuverlässiger zu gestalten. Aufbauend auf der funktionierenden Grundimplementierung aus Sprint 1 werden in diesem Sprint insbesondere Anforderungen umgesetzt, die für die Stabilität und Fehlertoleranz des Gesamtsystems entscheidend sind. Dazu gehören sowohl eine verbesserte Fehlererkennung als auch der Ausbau sicherheitskritischer Funktionen wie Plausibilitätsprüfungen, kontinuierliche Überwachung und systematische Fehlerklassifizierung.

Ziel des Sprints ist es, das System in Richtung eines vollwertigen Sicherheits- und Überwachungsmoduls weiterzuentwickeln, das Fehler frühzeitig erkennt, korrekt klassifiziert und geeignete Maßnahmen einleitet.

Im Mittelpunkt stehen dabei die folgenden Anforderungen:

- R2.2  Kontinuierlicher Soll/Ist-Vergleich, Sicherheitsmodus
- R2.3  Fehleranalyse: Sensorfehler, Überhitzung
- R4.1  Plausibilitätsprüfung beim Einschalten
- R4.2  Fehlerklassifizierung | ControlLogic / UI
- R4.3  Zyklischer Selbsttest

# Retrospektive

Was lief gut

Die Erweiterung des SafetyManagers um Fehlerklassifizierung, Überhitzungserkennung und Sensorfehleranalyse wurde erfolgreich umgesetzt.

Der kontinuierliche Soll/Ist-Vergleich (R2.2) funktioniert zuverlässig und ist sauber in den SystemController integriert.

Die Plausibilitätsprüfung beim Einschalten (R4.1) wurde logisch und klar umgesetzt und verhindert Start in fehlerhaften Zuständen.

Der zyklische Selbsttest (R4.3) wurde implementiert und löst wie geplant aus.

Die Testfälle zur Modul- und Integrationsebene decken die neuen Features gut ab und verliefen erfolgreich.

Das Zusammenspiel zwischen SafetyManager, Anzeige und Buzzer ist nun deutlich besser strukturiert und nachvollziehbar.



## Was lief gut?
- Alle ausgewählten Requirements für Sprint 2 wurden in Sprint 2 erledigt
- Tests wurden erfolgreich durchgeführt
- An der gewählten Architektur konnte festgehalten werden
- Klassendiagramm konnte in Code überführt werden
- Code wurde konsequent kommentiert

## Was lief weniger gut?

- Die Wiederverwendbarkeit der Fehlercodes und Fehlertexte ist noch nicht ideal gelöst; teilweise sind die Meldungen noch „hardcoded“

- Die Abstimmung zwischen SystemController und SafetyManager ist recht eng gekoppelt, was langfristig zu Pflegeaufwand führen kann

- Der Selbsttest ist funktionsfähig, aber noch nicht vollständig modularisiert (z. B. könnte er in eine eigene Komponente ausgelagert werden)

- Die Plausibilitätslogik ist aktuell noch relativ einfach und könnte in einem späteren Sprint robuster gestaltet werden

## Lessons Learned
- nicht von der Vielzahl an Anforderungen überfordern lassen
- Startpunkt für Programmierung festlegen
- Traceability Matrix konsequent pflegen

## Baseline Sprint 2

Mit Abschluss von Sprint 2 liegt eine funktionale und stabilisierte Version des Trockenlaufschutzsystems vor, die alle sicherheitsrelevanten Erweiterungen aus diesem Sprint integriert. Die Basisfunktionalität aus Sprint 1 ist weiterhin vollständig vorhanden, wurde aber durch zusätzliche Prüfmechanismen, Fehlerklassifikation und Selbsttests deutlich robuster gemacht.

### Folgende Komponenten bilden den gesicherten Stand (Baseline) von Sprint 2:

- SafetyManager wurde erfolgreich erweitert um:

    - kontinuierlichen Soll/Ist-Vergleich (R2.2)

    - Überhitzungserkennung und Sensorfehleranalyse (R2.3)

    - Fehlerklassifizierung (R4.2)

    - Plausibilitätsprüfung beim Einschalten (R4.1)

    - zyklischen Selbsttest (R4.3)

- SystemController ist nun in der Lage, Fehlerzustände korrekt zu verarbeiten, zwischen Normalbetrieb und Sicherheitsmodus zu unterscheiden und UI-/Heater-Komponenten entsprechend anzusteuern

- DisplayController und BuzzerController sind vollständig in die Fehler- und Warnkommunikation integriert und reagieren konsistent auf jede klassifizierte Fehlersituation

- Sensoren (Temperatur- und Füllstandsensor) unterstützen nun alle für Fehleranalysen benötigten Werte bzw. Validitätsprüfungen

- Testabdeckung wurde um sechs neue Modul- und Integrationstests erweitert, die alle Anforderungen dieses Sprints erfolgreich prüfen