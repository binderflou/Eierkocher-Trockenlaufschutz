## Teilfunktionalitäten
| **Nr.** | **Hauptfunktion** | **Teilfunktionalität** | **Beschreibung** |
|----------|-------------------|------------------------|------------------|
| 1 | Sensordatenerfassung | Füllstandsmessung | Misst Wasserstand über kapazitiven Sensor |
|   |   | Temperaturmessung | Erfasst Heizplattentemperatur |
|   |   | Zeiterfassung | Zeitstempel für Plausibilitätsprüfungen |
| 2 | Zustandsüberwachung | Soll-Ist-Vergleich | Vergleich mit Warnschwellen |
|   |   | Zustandserkennung | Erkennung: Bereit, Warnung, Kritisch, Trockenlauf |
|   |   | Fehleranalyse | Sensorfehler, Überhitzung |
| 3 | Steuerlogik & Sicherheit | Heizungssteuerung | Heizung aktivieren/deaktivieren |
|   |   | Trockenlaufschutz | Verhindert Betrieb ohne Wasser |
|   |   | Fehlerbehandlung | Quittierung durch Benutzer |
| 4 | Fehlerdiagnose & Überwachung | Plausibilitätsprüfung | Prüft Sensorwerte auf Gültigkeit |
|   |   | Selbsttest | Funktionsprüfung beim Start |
|   |   | Watchdog | Reaktion auf Ausfälle |
| 5 | Benutzerinterface | Füllstandsanzeige | Darstellung ml/% mit Ampelsystem |
|   |   | Fehlermeldungen | Priorisierte Fehlerausgabe |
|   |   | Akustische Warnung | Summer bei Warnung |
|   |   | Schwelle einstellen | Benutzerdefinierbare Warnwerte |
|   |   | Quittierung | Freigabe nach Fehler |

