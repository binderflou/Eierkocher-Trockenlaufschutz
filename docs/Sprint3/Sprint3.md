# Sprint 3 Planung
Zu bearbeitende Requirements in Sprint 3 sind:
- R5.3 Warnanzeige
- R5.4 Fehlermeldung Trockenlauf, Quittierung
- R5.5 Akustisches Warnsignal
- R5.6 Einstellbare Warnschwelle

# Retrospektive – Sprint 3

## Positives
- Die sicherheitsrelevanten Anforderungen (R5.3–R5.6) konnten vollständig umgesetzt werden.
- Durch die Einführung eines manuellen Recovery-Prozesses (Füllen + Quittierung) wurde das Systemverhalten deutlich realistischer und sicherer.
- Die Warn- und Fehlerlogik (Anzeige und Buzzer) ist nun stabil und deterministisch.
- Die Architektur blieb übersichtlich und konnte ohne grundlegende Umstrukturierung erweitert werden.
- Die Konsolenausgabe wurde benutzerfreundlicher und besser nachvollziehbar gestaltet.

## Herausforderungen
- Die zyklische Simulation führte zunächst zu instabilem Verhalten (z. B. toggelnder Buzzer).
- Das Zusammenspiel von Sicherheitslogik, Anzeige und Benutzerinteraktion erforderte mehrere Iterationen.
- Die klare Trennung zwischen Normalbetrieb und Recovery-Zuständen musste explizit modelliert werden.

## Verbesserungen
- Einführung gelatchter Sicherheitszustände (Trockenlauf bleibt aktiv bis Quittierung).
- Klare Zustandsübergänge durch WAIT_FOR_FILL und WAIT_FOR_ACK.
- Reduktion von Seiteneffekten durch bessere Entkopplung von Anzeige und Steuerlogik.

## Erkenntnisse
- Sicherheitskritische Systeme benötigen explizite Zustandsmodelle.
- Automatische Wiederanläufe nach Fehlern sind zu vermeiden.
- Eine saubere Traceability (Requirement → Design → Code → Test) erleichtert Bewertung und Wartung erheblich.

---

# Baseline – Sprint 3

## Funktionaler Stand
- Trockenlauf wird zuverlässig erkannt und sicher behandelt.
- Warn- und Fehlermeldungen werden visuell und akustisch ausgegeben.
- Der Benutzer muss Trockenlauf aktiv quittieren, bevor das System neu startet.
- Die Warnschwelle ist zur Laufzeit einstellbar und persistent gespeichert.

## Architektur-Stand
- Bestehende Schichtenarchitektur bleibt erhalten.
- Erweiterung um eine explizite Recovery-Zustandsmaschine.
- Keine Brüche oder Inkonsistenzen zur Architektur aus Sprint 2.

## Qualitätsstand
- Alle Sprint-3-Requirements (R5.3–R5.6) sind implementiert und getestet.
- Modul- und Integrationstests wurden erfolgreich durchgeführt.
- Die Traceability Matrix wurde vollständig aktualisiert.

# Baseline (kurz)
- Trockenlauf wird sicher erkannt und führt zu einem stabilen Fehlerzustand mit abgeschalteter Heizung.
- Wiederinbetriebnahme erfolgt ausschließlich über manuelle Benutzerinteraktion (Füllen und Quittierung).
- Warn- und Fehlermeldungen werden konsistent visuell und akustisch ausgegeben.
- Die Warnschwelle kann zur Laufzeit eingestellt und persistent gespeichert werden.
- Das Systemverhalten ist deterministisch und frei von instabilen Zustandswechseln.