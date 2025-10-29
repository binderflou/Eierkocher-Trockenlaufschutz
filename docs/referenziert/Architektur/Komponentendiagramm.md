````mermaid
%%-------------------------------------------------
%% Trockenlaufschutz – Vereinfachtes Schichtenmodell
%%-------------------------------------------------
graph TD
UI["Benutzerinterface (Display & Summer)"] --> ST["Steuerlogik"]
ST --> AW["Auswertelogik"]
AW --> SE["Sensorik"]

%% Styles
style UI fill:#e6f3ff,stroke:#4a90e2,stroke-width:2px
style ST fill:#fff9e6,stroke:#d1a800,stroke-width:2px
style AW fill:#f9e6e6,stroke:#d9534f,stroke-width:2px
style SE fill:#f4e6ff,stroke:#8e44ad,stroke-width:2px
````
