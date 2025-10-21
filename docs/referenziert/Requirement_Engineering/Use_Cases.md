# Use Cases: Trockenlaufschutz Eierkocher

## 1. Sensor-Datenerfassung (Input-Modul)

Zweck:

  Erfassen und Bereitstellen aller relevanten Messwerte für den Trockenlaufschutz.

Funktionen:

  Kontinuierliche Erfassung des Wasserfüllstands über Füllstandssensor.

  Messung der Temperatur am Heizelement zur Erkennung von Überhitzung.

  Zeitstempelung der Messwerte zur Verlaufsauswertung (z. B. Temperaturanstieg über Zeit).

  Datenvorverarbeitung (z. B. Mittelwertbildung, Filterung von Ausreißern).

Schnittstellen:

  → Liefert Messdaten an die Zustandsüberwachung.

## 2. Zustandsüberwachung und Analyse

Zweck:
  
  Bewertung der erfassten Sensorwerte und Erkennung kritischer Zustände.

Funktionen:

  Vergleich der Ist-Werte mit definierten Soll- und Grenzwerten (z. B. Mindestfüllstand, Maximaltemperatur).

  Erkennung von unplausiblen Messwerten oder fehlenden Sensoren.

  Ableitung des aktuellen Systemzustands (Normalbetrieb, Warnung, Trockenlauf, Fehler).

  Übergabe des Zustands an die Steuerlogik zur weiteren Entscheidung.

Schnittstellen:

  ← Sensor-Datenerfassung
  → Steuerlogik

## 3. Steuerlogik und Abschaltmanagement

Zweck:

  Sichere Regelung des Heizvorgangs und Verhinderung von Trockenlauf oder Überhitzung.

Funktionen:

  Entscheidungsfindung: Abschalten der Heizung bei erkanntem Trockenlauf oder Sensorfehler.

  Aktivierung von Warnsignalen (optisch/akustisch) über Peripherie.

  Berechnung des tatsächlichen Füllstandes und dynamische Anpassung von Schwellwerten.

  Steuerung der Betriebszustände (Heizen ↔ Abschalten ↔ Fehler).

Schnittstellen:
  ← Zustandsüberwachung
  → Benutzerinterface, Heizelement

## 4. Selbsttest und Fehlerdiagnose

Zweck:
  Sicherstellen der Systemintegrität und Erkennen von Hardware-/Softwarefehlern.

Funktionen:

  Selbsttest beim Start (Sensorprüfung, LED-Test, Temperaturcheck).

  Plausibilitätsprüfung der Sensorwerte im laufenden Betrieb.

  Erkennung von Kurzschluss, Wackelkontakt oder Sensorausfall.

  Ausgabe eindeutiger Fehlermeldungen an das Benutzerinterface.

Schnittstellen:
  ↔ Sensor-Datenerfassung
  → Benutzerinterface

## 5. Benutzerinterface und Warnsystem

Zweck:
  Informieren des Benutzers über aktuelle Zustände und Fehler in klar verständlicher Form.

Funktionen:

  Anzeige des Füllstandes über LED, Display oder Symbol.

  Warnanzeige bei niedrigem Füllstand oder beginnendem Trockenlauf.

  Fehlermeldung (z. B. „Wasser nachfüllen“, „Sensorfehler“).

  Akustische Signale bei kritischen Zuständen.

  Rückmeldung an Benutzer nach Selbsttest (z. B. kurzes Signal „System bereit“).

Schnittstellen:
  ← Steuerlogik
  ← Selbsttest

## Kurzüberblick (Zusammenfassung)
Nr.	Teilfunktionalität	                Hauptaufgabe
1  	Sensor-Datenerfassung	              Messung von Wasserstand, Temperatur, Zeit
2	  Zustandsüberwachung	                Analyse der Sensorwerte und Zustandserkennung
3	  Steuerlogik und Abschaltmanagement	Entscheidung über Heizung/Warnung/Abschaltung
4	  Selbsttest und Fehlerdiagnose	      Prüfung auf Plausibilität und Systemfehler
5	  Benutzerinterface und Warnsystem	  Anzeige, Signalisierung, Nutzerinformation
