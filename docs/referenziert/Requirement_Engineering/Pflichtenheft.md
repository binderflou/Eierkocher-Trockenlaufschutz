# Pflichtenheft
1.	Anzeige Füllstand
  a.	Darstellung über mehrfarbige Anzeige (rot, gelb, grün) auf dem Display
  b.	Füllstand in ml auf Display angezeigt
  c.	Anzeige ist schlicht und einfach gehalten
  d.	Aktualisierung der Anzeige in Echtzeit
  e.	Farbkodierung: 
    i.	Grün: ausreichend Wasser (>50%)
    ii.	Gelb: Warnung (10-50%)
    iii.	Rot: kritisch (<10%, Trockenlauf droht)
2.	Warnfunktion bei niedrigem Füllstand
  a.	Benutzerdefinierbare Warnschwelle einstellbar auf Display (10%-50%)
  b.	Bei Unterschreitung: 
    i.	Visuelles Signal: Rotes Segment blinkt
    ii.	Akustisch: Piepton mit Summer
  c.	Automatische Abschaltung der Heizung, wenn kritischer Pegelstand erreicht wird
3.	Informationen bei Fehlern
  a.	Klare Fehlermeldungen bei erkannten Störungen:
    i.	Trockenlauf erkannt, Quittierung nötig
    ii.	Überhitzung/Sicherheitsabschaltung Heizwendel (>120 C)
    iii.	Sensorfehler (z. B. Sensorwert unrealistisch, Fehlermeldung Display -> Reparatur)
4.	Sensordatenerfassung/Zustandsüberwachung/Steuerlogik
  a.	Füllstand Sensorik
    i.	Erfassung Füllstand mit kapazitivem Sensor (Messbereich: 5ml=0%; 200ml=100% +-5%)
    ii.	Abtastrate 5 Hz (200ms)
    iii.	Ausgangssignal analog: 0-3,3V
  b.	Temperaturerfassung:
    i.	Messung an Heizplatte
    ii.	Messbereich: 30-150C
    iii.	Abtastung 5 Hz
    iv.	Überwachung auf schnellen Temperaturanstieg: >5C/s Schwellwert für Trockenlauf
  c.	Sensorüberwachung
    i.	Keine Änderung des Sensorwertes über feste Zeitspanne (10s) führt zu Fehlermeldung auf Display
    ii.	Überprüfung auf plausible Wertebereiche bei Boot des Gerätes
  d.	Zustandserkennung:
    i.	Bereit: (genug Wasser, ordnungsgemäßer Betrieb, grün)
    ii.	Warnung 1 (niedriger Füllstand, gelb)
    iii.	Warnung 2 (sehr niedriger Füllstand, rot)
    iv.	Trockenlauf erkannt (Heizung stopp, rot blinken, Pieps Ton)
    v.	Überhitzung (Temperatur >120C, Warnung Display Überhitzung, Abschaltung)
vi.	Sensorfehler (Warnung Display Sensorfehler)
e.	Steuerung/Auswertung Logik übernimmt Arduino Nano
