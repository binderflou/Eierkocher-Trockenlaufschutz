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



# Requirements Matrix

| **ID** | **Requirement**                                           | **Parameter/Criteria**                                           | **Min/Max/Target**        | **Test/Verification**        | **Related Subfunction**                |
|--------|----------------------------------------------------------|------------------------------------------------------------------|---------------------------|------------------------------|----------------------------------------|
| 1.1.1  | Füllstandsmessung: Messbereich                           | Messbereich                                                      | 0–100 % (250 ml)          | Messung, Datenblatt          | Sensordatenerfassung / Füllstand       |
| 1.1.2  | Füllstandsmessung: Auflösung                             | Messauflösung                                                    | ≤ 5 %                     | Messung, Datenblatt          | Sensordatenerfassung / Füllstand       |
| 1.1.3  | Füllstandsmessung: Reaktionszeit                         | Messwertaktualisierung                                           | ≤ 200 ms                  | Messung, Test                | Sensordatenerfassung / Füllstand       |
| 1.1.4  | Füllstandsmessung: Sensorfehlererkennung                 | Fehlermeldung bei Messwert außerhalb 0–110 %                     | Fehlerausgabe             | Test, Simulation             | Sensordatenerfassung / Füllstand       |
| 1.1.5  | Füllstandsmessung: Genauigkeit                           | Genauigkeit                                                      | ± 5 %                     | Messung, Kalibrierung        | Sensordatenerfassung / Füllstand       |
| 1.2.1  | Temperaturmessung: Messbereich                           | Messbereich                                                      | 0–150 °C                  | Messung, Datenblatt          | Sensordatenerfassung / Temperatur      |
| 1.2.2  | Temperaturmessung: Genauigkeit                           | Messgenauigkeit                                                  | ± 1 °C                    | Messung, Kalibrierung        | Sensordatenerfassung / Temperatur      |
| 1.2.3  | Temperaturmessung: Abtastrate                            | Abtastrate                                                       | ≥ 5 Hz                    | Messung, Test                | Sensordatenerfassung / Temperatur      |
| 1.2.4  | Temperaturmessung: Überhitzungserkennung                 | Temperaturanstieg > 5 °C/s → Trockenlaufverdacht                 | Detektion                 | Test, Simulation             | Zustandsüberwachung / Fehleranalyse    |
| 1.2.5  | Temperaturmessung: Sicherheitsabschaltung                | Abschalten bei Temperatur > 110 °C                               | Abschaltung               | Test, Simulation             | Steuerlogik / Trockenlaufschutz        |
| 1.3.1  | Zeiterfassung: Genauigkeit                               | Zeitbasis Genauigkeit                                            | ± 0,1 s                   | Messung, Datenblatt          | Sensordatenerfassung / Zeiterfassung   |
| 1.3.2  | Zeiterfassung: Messintervall                             | Messintervall                                                    | ≤ 200 ms                  | Messung, Test                | Sensordatenerfassung / Zeiterfassung   |
| 2.1.1  | Zustandsüberwachung: Soll-Ist-Abweichung                 | Statuswarnung bei Abweichung > 10 %                              | Erkennung                 | Simulation, Test             | Zustandsüberwachung / Soll-Ist-Vergleich|
| 2.1.2  | Zustandsüberwachung: Berechnungszyklus                   | Berechnungszyklus                                                | ≤ 500 ms                  | Messung, Test                | Zustandsüberwachung                   |
| 2.2.1  | Kontinuierlicher Soll/Ist-Vergleich                      | Update-Rate Entscheidungslogik                                   | ≥ 2 Hz (2×/s)             | Messung, Test                | Zustandsüberwachung                   |
| 2.2.2  | Sicherheitsmodus bei Fehler                              | Falscher/fehlender Wert → Sicherheitsmodus                       | Umschaltung               | Test, Simulation             | Fehlerdiagnose                        |
| 3.1.1  | Abschalten der Heizung: Füllstand                        | Abschaltung bei Füllstand < 10 %                                 | Abschaltung               | Test, Simulation             | Steuerlogik / Heizungssteuerung        |
| 3.1.2  | Abschalten der Heizung: Temperaturanstieg                | Abschaltung bei ΔT > 5 °C/s über 500 ms                          | Abschaltung               | Test, Simulation             | Steuerlogik / Trockenlaufschutz        |
| 3.1.3  | Abschalt-Reaktionszeit                                   | Reaktionszeit Abschaltung                                        | ≤ 1 s                     | Messung, Test                | Steuerlogik                            |
| 3.1.4  | Wiedereinschalten                                        | Füllstand > 20 % und Temperatur < 70 °C                          | Wiedereinschalten         | Test, Simulation             | Steuerlogik                            |
| 3.2.1  | Anzeigewechsel bei Warnung/Fehler                        | Wechsel Normal → Warnung/Fehler                                  | ≤ 300 ms                  | Test, Messung                | Benutzerinterface / Fehlermeldungen     |
| 3.2.2  | Akustisches Signal                                       | 2× kurz (Warnung), 3× lang (Fehler), Wiederholung alle 10 s      | Signaltyp, Frequenz       | Test, Messung                | Benutzerinterface / Akustische Warnung  |
| 3.3.1  | Füllstandsberechnung                                     | Glättung (Mittelwert über 3 Messungen), Kompensation, Zeit ≤100ms| Algorithmen, Dauer        | Test, Review                 | Steuerlogik / Füllstandsanzeige         |
| 4.1.1  | Selbsttest: Plausibilitätsprüfung                        | Temperatur 0–50 °C, Füllstand 0–100 %, Dauer ≤ 2 s               | Testkriterien, Zeit       | Test, Simulation             | Fehlerdiagnose / Selbsttest             |
| 4.2.1  | Fehlerklassifikation                                     | Warnung (<20 %), Fehler (Trockenlauf), Kritisch (Sensor/Überhitzung)| Anzeige                  | Test, Simulation             | Fehlerdiagnose / Fehlermeldungen        |
| 4.2.2  | Fehleranzeige Reaktionszeit                              | Fehleranzeige nach Erkennung                                     | < 300 ms                  | Test, Messung                | Fehlerdiagnose / Fehlermeldungen        |
| 4.3.1  | Zyklischer Selbsttest                                    | Überprüfung alle 30 s, Warnung bei Wertkonstanz >10 s            | Intervall, Detektion      | Test, Messung                | Fehlerdiagnose / Selbsttest             |
| 5.1.1  | Füllstandsanzeige Auflösung                              | Anzeige: 5 Stufen oder Prozentwert                               | Auflösung                 | Test, Review                 | Benutzerinterface / Füllstandsanzeige   |
| 5.1.2  | Füllstandsanzeige Update                                 | Aktualisierung alle 500 ms, Genauigkeit ±5 %                     | Intervall                 | Test, Messung                | Benutzerinterface / Füllstandsanzeige   |
| 5.2.1  | Warnanzeige Farbcodierung                                | Farbcode: Grün/Gelb/Rot, Symbol für Farbfehlsichtige             | Farbschema, Symbole       | Review, Test                 | Benutzerinterface / Warnanzeige         |
| 5.2.2  | Warnanzeige Helligkeit                                   | Helligkeit < 300 cd/m²                                           | Maximalwert               | Messung                      | Benutzerinterface / Warnanzeige         |
| 5.3.1  | Fehlermeldung Trockenlauf                                | Text/Symbol „Trockenlauf erkannt“, Anzeige bleibt bis behoben    | Anzeige                   | Test, Simulation             | Benutzerinterface / Fehlermeldungen     |
| 5.4.1  | Akustische Signalstärke                                  | Lautstärke 60–80 dB(A) bei 0,5 m                                 | Messwert                  | Messung, Test                | Benutzerinterface / Akustische Warnung  |
| 5.4.2  | Akustische Signalreaktion                                | Reaktionszeit ≤ 300 ms nach Ereignis                             | Zeit                      | Test, Messung                | Benutzerinterface / Akustische Warnung  |

**Legende:**
- **ID**: Nummerierung der Einzelanforderung (Referenz für Traceability)
- **Requirement**: Kurzbeschreibung der Anforderung
- **Parameter/Criteria**: Messbarer Wert, Grenzwert oder Kriterium
- **Min/Max/Target**: Ziel-/Grenzwert, sofern angegeben
- **Test/Verification**: Methode der Überprüfung (Test, Messung, Simulation, Review)
- **Related Subfunction**: Zuordnung zu Teilfunktionalität im System
