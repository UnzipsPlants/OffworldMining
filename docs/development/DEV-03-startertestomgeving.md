# DEV-03 — Startertestomgeving

Werkpakket uit OffworldMining 1.0, §3.4: "Startertestomgeving — startpositie raket, HIVE en robots" (afhankelijk van DEV-01 en DEV-02; OS-01, OS-02).

## Ontwerpbasis

- [Vastgelegd] De raket klapt gedeeltelijk uit, met een uitvoer voor robots en een invoer voor grondstoffen (§2.5).
- [Vastgelegd] De HIVE main unit is 3 m breed, 3 m hoog en 5 m lang, staat op een vaste positie in de gedeeltelijk geopende raket en kan zich niet zelfstandig voortbewegen of boren (§2.6).
- [Vastgelegd] Bij de start zijn één Digger en één Builder aan boord (§2.6, V1-01).
- [Besluit projecteigenaar, 20-11-2026] DEV-03 omvat alleen de startopstelling. Landing, boren en uitklappen (OS-02) vallen erbuiten.
- [Besluit projecteigenaar, 20-11-2026] De Digger en Builder staan bij de start zichtbaar bij de robotuitvoer.
- [Besluit projecteigenaar, 20-11-2026] De opstelling wordt via C++ in de testkaart gezet.

## Implementatie

- `UOSRMSStarterSetupSubsystem` (WorldSubsystem): plaatst de opstelling alleen in de kaart uit `TargetMap` (`/Game/Maps/L_Test_HIVE`), uitsluitend in Game en PIE.
  - `BP_Rocket` wordt zo geplaatst dat de marker `HIVE_Position` samenvalt met de bestaande `BP_HIVE_Placeholder` in de kaart. Staat er al een `BP_Rocket` in de kaart, dan wordt die gebruikt en niet verplaatst.
  - Er wordt één Digger- en één Builder-placeholder geplaatst bij `RobotExit_Position`.
  - De aanwezigheid van `ResourceInput_Position` wordt alleen gelogd.
  - De bestaande HIVE-placeholder en `BP_HIVE_CameraPawn` worden niet gewijzigd. De GameMode is niet aangepast.
- `AOSRMSRobotPlaceholder`: een zichtbare kubus met `RobotRole`, zonder besturing, AI of taken.
- Instellingen: `Config/DefaultGame.ini`, sectie `[/Script/OffworldMining.OSRMSStarterSetupSubsystem]`.
- Logcategorie: `LogOSRMSStart`.

## Technische aannames

- [Aanname] `HIVE_Position` geeft de plek aan waar de actorpivot van `BP_HIVE_Placeholder` hoort. Dit is niet uit de Blueprint vastgesteld.
- [Aanname] De placeholders zijn kubussen van 1 × 1 × 1 m, met de Digger op Y −100 cm en de Builder op Y +100 cm in de lokale ruimte van `RobotExit_Position`. Dit zijn tijdelijke testwaarden zonder ontwerpstatus.
- [Aanname] `UWorldSubsystem::OnWorldBeginPlay` wordt in UE 5.8.3 vóór de BeginPlay-dispatch van actors aangeroepen. De tijdelijke meetraket wordt daardoor verwijderd voordat haar BeginPlay draait.
- [Aanname] De markers in `BP_Rocket` zijn SceneComponents met exact de namen `HIVE_Position`, `RobotExit_Position` en `ResourceInput_Position`. De namen zijn uit het asset gelezen; de componenttypes niet.

## Status

| Onderdeel | Geïmplementeerd | Op bestandsniveau gecontroleerd | Gecompileerd | In Unreal getest |
|---|---|---|---|---|
| Raket op HIVE-positie | ja (C++) | ja | nee | nee |
| HIVE op vaste positie in de raket | via raketplaatsing | ja | nee | nee |
| Digger en Builder zichtbaar bij de robotuitvoer | ja (C++) | ja | nee | nee |
| Grondstofinvoer aanwezig | alleen logcontrole | ja | nee | nee |
| Bestaande HIVE-camera ongewijzigd | ja | ja | nee | nee |

DEV-03 is niet afgerond zolang de lokale controles hieronder niet zijn bevestigd.

## Lokale controles

1. Bouw het target `OffworldMiningEditor` (Development Editor, Win64). Verwacht: de build slaagt zonder fouten.
2. Open `L_Test_HIVE` en start PIE. Verwacht: de Output Log bevat regels van `LogOSRMSStart`, zonder Error-regels.
3. Lees in de log de afstand van `HIVE_Position` tot de HIVE-actor af. Verwacht: 0,0 cm. HIVE staat zichtbaar in de raket.
4. Kijk tijdens PIE in de Outliner. Verwacht: één `BP_Rocket`, één HIVE-placeholder, twee `OSRMSRobotPlaceholder`-actors (`RobotRole` Digger en Builder) bij de robotuitvoer en geen tweede raket.
5. Controleer de camera. Verwacht: de HIVE-camera wordt bestuurd en de orbit met de muis werkt zoals voorheen.
6. Stop PIE. Verwacht: de kaart in de editor is onveranderd, want de actors worden alleen tijdens het spelen geplaatst.

## Wijzigingen

- 20-11-2026 18:29 CET (UTC+01:00): document aangemaakt in branch `dev/DEV-03-startertestomgeving`. Het legt de DEV-03-ontwerpbasis, de C++-startopstelling, de aannames, de status en de lokale controles vast.
