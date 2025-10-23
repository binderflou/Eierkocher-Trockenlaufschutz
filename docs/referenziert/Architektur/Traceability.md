# Requirements-Verwaltung & Testfall-Nachverfolgung – Trockenlaufschutz Eierkocher

Diese Tabelle stellt die Verbindung zwischen den Anforderungen (Requirements), den zugehörigen Teilfunktionalitäten und den vorgesehenen Testfällen her.  
So ist jederzeit nachvollziehbar, welche Funktionalität welche Anforderung erfüllt und wie sie überprüft wird.

---

| **Req-ID** | **Anforderung / Requirement** | **Teilfunktionalität** | **Akzeptanzkriterium** | **Test-ID** | **Testbeschreibung** |
|-------------|-------------------------------|--------------------------|-------------------------|--------------|----------------------|
| RQ-01 | Der Füllstand des Wassers soll in ml angezeigt werden. | Sensordatenerfassung / Benutzerinterface | Anzeige zeigt Füllstand ±5 % genau an. | T-01 | Prüfe, ob der gemessene Füllstand mit Referenzwert (Messzylinder) übereinstimmt. |
| RQ-02 | Füllstandsanzeige wird alle 500 ms aktualisiert. | Sensordatenerfassung | Anzeige reagiert ohne spürbare Verzögerung (< 0,5 s). | T-02 | Beobachte Anzeige bei fallendem Wasserstand, messe Reaktionszeit. |
| RQ-03 | System zeigt Füllstand über Ampelfarben (Grün/Gelb/Rot/Rot blinkend) an. | Benutzerinterface | Farbanzeige wechselt entsprechend Füllstand. | T-03 | Simuliere Wasserstände 100 %, 40 %, 5 %, 0 % und prüfe Farbwechsel. |
| RQ-04 | Warnung bei niedrigem Füllstand unter benutzerdefinierter Schwelle (10–50 %). | Steuerlogik / Benutzerinterface | Warnung erfolgt optisch und akustisch innerhalb 1 s nach Erreichen der Schwelle. | T-04 | Stelle Warnschwelle auf 30 %, senke Wasserstand und prüfe Reaktionszeit und Signal. |
| RQ-05 | Gerät schaltet automatisch ab, wenn kein Wasser mehr vorhanden ist. | Steuerlogik & Sicherheitsabschaltung | Heizung deaktiviert innerhalb 2 s nach Trockenlauf-Erkennung. | T-05 | Simuliere Betrieb ohne Wasser, beobachte Abschaltung und Fehlermeldung. |
| RQ-06 | Trockenlauf wird visuell und akustisch signalisiert (rot blinkend + Pieps). | Benutzerinterface | Warnsignal aktiviert nach Trockenlauf-Erkennung. | T-06 | Überprüfe Display- und Tonsignal nach Trockenlauf. |
| RQ-07 | Nach Wiedereinfüllen muss Fehlermeldung quittiert werden. | Steuerlogik / Benutzerinterface | Gerät bleibt im Sperrmodus, bis Nutzer quittiert. | T-07 | Führe Trockenlauf herbei, fülle Wasser nach, prüfe Quittierungsprozess. |
| RQ-08 | Temperaturüberwachung stoppt Heizung bei > 120 °C. | Fehlerdiagnose & Überwachung | Heizung wird abgeschaltet, Fehlercode angezeigt. | T-08 | Simuliere Überhitzung (Temperatursignal > 120 °C), prüfe Reaktion. |
| RQ-09 | Sensorfehler werden erkannt und als Fehlermeldung angezeigt. | Fehlerdiagnose & Überwachung | Anzeige „Sensorfehler“, Heizung deaktiviert. | T-09 | Simuliere defekten Sensor (z. B. konstantes Signal), prüfe Fehlermeldung. |
| RQ-10 | Selbsttest wird beim Einschalten automatisch durchgeführt. | Fehlerdiagnose & Überwachung | Nach Selbsttest zeigt System „Bereit“ (grün). | T-10 | Gerät einschalten, prüfe Selbsttestsequenz (Display- und Tonindikator). |
| RQ-11 | Anzeige muss auch bei schlechten Lichtverhältnissen gut ablesbar sein. | Benutzerinterface | Anzeige ist kontrastreich, Symbole klar erkennbar. | T-11 | Test unter 20 lx Umgebungslicht (Dämmerlicht). |
| RQ-12 | Akustische Signale dürfen 70 dB nicht überschreiten. | Benutzerinterface | Schalldruckpegel ≤ 70 dB. | T-12 | Messe Lautstärke in 1 m Abstand bei Warnsignal. |
| RQ-13 | Bei Sensorwert-Stagnation (>10 s keine Änderung) → Fehlermeldung. | Fehlerdiagnose & Überwachung | Meldung „Sensorfehler“ wird ausgegeben. | T-13 | Simuliere eingefrorenen Sensorwert, prüfe Fehlermeldung. |
| RQ-14 | Datenaktualisierung alle 200 ms (Abtastrate 5 Hz). | Sensordatenerfassung | Sensorwerte werden mit 5 Hz eingelesen. | T-14 | Logge Sensordaten über 10 s, prüfe Abtastfrequenz. |
| RQ-15 | Nach erfolgreicher Quittierung springt Anzeige zurück auf Grün. | Steuerlogik / Benutzerinterface | Gerät betriebsbereit nach Quittierung. | T-15 | Nach Fehlermeldung „Trockenlauf“, fülle Wasser und quittiere – prüfe Anzeige. |

---

## Teilfunktions-Zuordnung 

| **Teilfunktionalität** | **Abgedeckte Requirements** | **Verknüpfte Testfälle** |
|--------------------------|-----------------------------|---------------------------|
| Sensordatenerfassung | RQ-01, RQ-02, RQ-14 | T-01, T-02, T-14 |
| Zustandsüberwachung | RQ-03, RQ-04, RQ-05 | T-03, T-04, T-05 |
| Steuerlogik & Sicherheitsabschaltung | RQ-05, RQ-07, RQ-15 | T-05, T-07, T-15 |
| Fehlerdiagnose & Überwachung | RQ-08, RQ-09, RQ-10, RQ-13 | T-08, T-09, T-10, T-13 |
| Benutzerinterface | RQ-03, RQ-06, RQ-11, RQ-12, RQ-15 | T-03, T-06, T-11, T-12, T-15 |

# Traceability Matrix – Sensordatensystem

| **Requirement ID** | **Requirement Beschreibung** | **Teilfunktion** | **Unterfunktion** | **Systemkomponente** | **Verfolgbarkeit / Kommentar** |
|-------------------|-----------------------------|-----------------|-----------------|-------------------|-------------------------------|
| R1.1 | Füllstandsmessung: 0–100 %, Auflösung ≤5 %, Reaktionszeit ≤200 ms, Sensorfehlererkennung, Genauigkeit ±5 % | Sensordatenerfassung | Füllstandsmessung | Füllstandssensor | Misst Wasserstand über kapazitiven Sensor |
| R1.2 | Temperaturmessung: 0–150 °C, Genauigkeit ±1 °C, Abtastrate ≥5 Hz, Überhitzungserkennung, Sicherheitsabschaltung >110 °C | Sensordatenerfassung | Temperaturmessung | Temperatursensor | Erfasst Heizplattentemperatur und schützt vor Überhitzung |
| R1.3 | Zeitmessung: interne Echtzeituhr ±0,1 s, Messintervall ≤200 ms | Sensordatenerfassung | Zeiterfassung | RTC/Timer | Liefert Zeitstempel für Plausibilitätsprüfungen und Verlaufsauswertung |
| R2.1 | Auswertung Sensorwerte: Sollwertvergleich, Statuswarnung bei Abweichung >10 %, Berechnungszyklus ≤500 ms | Zustandsüberwachung | Soll-Ist-Vergleich | Steuerlogik | Vergleicht Sensorwerte kontinuierlich mit Sollwerten |
| R2.2 | Vergleich Soll/Ist kontinuierlich, Update ≥2×/s, Sicherheitsmodus bei fehlendem Messwert | Zustandsüberwachung | Zustandserkennung | Steuerlogik | Entscheidet Betriebszustand: Bereit, Warnung, Kritisch, Trockenlauf |
| R2.3 | Fehleranalyse: Sensorfehler, Überhitzung | Zustandsüberwachung | Fehleranalyse | Steuerlogik | Erkennung und Klassifizierung von Fehlern |
| R3.1 | Heizungssteuerung: Abschalten bei Füllstand <10 % oder Temperaturanstieg >5 °C/s, Reaktionszeit ≤1 s, Wiedereinschalten bei Füllstand >20 % und Temp <70 °C | Steuerlogik & Sicherheit | Heizungssteuerung | Heizsystem | Automatisches Ein-/Ausschalten der Heizung |
| R3.2 | Warnungen: Anzeigewechsel ≤300 ms, akustisches Signal bei kritischem Zustand, Wiederholung alle 10 s | Steuerlogik & Sicherheit | Fehlerbehandlung | Display & Summer | Informiert Benutzer über kritische Zustände |
| R3.3 | Berechnung tatsächlicher Füllstand: Sensordaten + Temperaturkompensation, Berechnungszeit ≤100 ms, gleitender Mittelwert | Steuerlogik & Sicherheit | Trockenlaufschutz | Steuerlogik | Genauigkeitsverbesserung und Schutz vor Trockenlauf |
| R4.1 | Plausibilitätsprüfung beim Einschalten: Temperatur 0–50 °C, Füllstand 0–100 %, Dauer ≤2 s | Fehlerdiagnose & Überwachung | Plausibilitätsprüfung | Steuerlogik | Prüft Sensorwerte beim Systemstart |
| R4.2 | Fehlerklassifizierung: Warnung (Füllstand <20 %), Fehler (Trockenlauf), Kritisch (Sensorfehler/Überhitzung), Anzeige <300 ms | Fehlerdiagnose & Überwachung | Selbsttest | Steuerlogik | Zeigt Fehlerprioritäten und sorgt für schnelle Meldung |
| R4.3 | Zyklischer Selbsttest: alle 30 s, unveränderte Werte >10 s → Plausibilitätswarnung | Fehlerdiagnose & Überwachung | Watchdog | Steuerlogik | Überwacht laufend Sensorfunktionen |
| R5.1 | Füllstandsanzeige: 5 Stufen oder 0–100 %, Aktualisierung alle 500 ms, Genauigkeit ±5 % | Benutzerinterface | Füllstandsanzeige | Display | Visualisiert Wasserstand für Benutzer |
| R5.2 | Warnanzeige: Farbcode (Grün/Gelb/Rot), Helligkeit <300 cd/m², Symbole bei Farbfehlsichtigkeit | Benutzerinterface | Fehlermeldungen | Display | Anzeige von Warnungen und Fehlern |
| R5.3 | Fehlermeldung bei Trockenlauf: Text oder Symbol, Anzeige aktiv bis behoben | Benutzerinterface | Fehlermeldungen | Display | Zeigt kritische Zustände persistent an |
| R5.4 | Akustische Signalisierung: 60–80 dB(A), Signaltyp 2× kurz bei Warnung, 3× lang bei Fehler, Reaktionszeit ≤300 ms | Benutzerinterface | Akustische Warnung | Summer | Akustische Benutzerwarnung bei kritischen Zuständen |
| R5.5 | Schwelle einstellen: benutzerdefinierbare Warnwerte, Quittierung möglich | Benutzerinterface | Schwelle einstellen / Quittierung | Display & Eingabefeld | Benutzer kann Warnschwellen definieren und Fehler freigeben |

