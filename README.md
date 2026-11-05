Mining Robot / OSRMS
A game about a self-expanding AI mining system that develops an industrial robot network on a starter asteroid, expands toward 511 Davida and Ceres, and ultimately returns to Earth.

OSRMS stands for Offworld Self-Replicating Mining System. OSRMS-01 HIVE is the central robot, production base, and coordination unit controlled by the player.

Project status
This README describes the planned design and development roadmap. Features listed here are not a statement of implemented or tested functionality.

The repository contents, current implementation milestone, and installed Unreal Engine version have not been verified for this README. The design document names Unreal Engine 5.8.3; treat that as an unverified design reference, not a confirmed build requirement.

Design authority
The leading design source is Offworld Mining.

Explicit changes approved by the project owner take precedence over the design document.

The design document takes precedence over older discussions and implementation assumptions.

Unresolved design questions must remain open until decided.

Later development stages provide context; they do not automatically belong in the current implementation scope.

Technical assumptions and proposals must not be presented as approved design decisions.

Overview
The original mission is to move resource extraction and processing away from Earth, reducing harmful industrial emissions on the planet.

A rocket arrives at a starter asteroid approximately 10 kilometres in diameter, penetrates about 150 metres into it, and partially unfolds. HIVE initially remains fixed inside the opened rocket, with an outlet for robots and an inlet for resources. HIVE cannot move or drill independently.

The player starts with one Digger and one Builder, learns the controls, explores the surrounding material, and begins research. Expansion gradually unlocks transport, construction, improved processing, reconnaissance, and larger industrial projects.

Planned gameplay
Mining and exploration
Select excavation volumes using a 1 x 1 x 1 metre cube grid.

Define tunnels, shafts, rectangular volumes, or free-form excavation areas.

Inspect estimated rock, minerals, and ice before confirming work.

Assign priorities and let the TaskManager distribute work among robots.

Reveal unknown areas through exploration and local fog-of-war removal.

Expand the visible scale from the starter asteroid toward other asteroids and the main belt as the relevant systems become available.

Automation and direct control
HIVE coordinates tasks, energy, inventories, research, and production. Robots can work autonomously, while the player can also directly control the Digger or Builder.

The planned autonomous task loop is:

Find an eligible task.

Check energy, tools, and inventory.

Move to the work location.

Execute the task.

Deliver resources where required.

Return or select another task.

Mining assignments consider distance, capacity, energy, and availability. After the relevant upgrade, Diggers can dump material for transport robots to collect.

Construction
Place construction blueprints using a ghost preview. The system checks space, resources, energy, and accessibility before a Builder or Mason receives the task. Players can also build through a directly controlled robot.

Planned construction includes structural supports, walls, floors, ceilings, lighting, doors, storage, mining installations, solar panels, batteries, rails, magnetic transport infrastructure, scanners, docks, and launch infrastructure.

Infrastructure is designed primarily for robots rather than humans: compact functional passages, transport-compatible floors, industrial lighting, and automated secure doors.

Research, production, and upgrades
Research expands HIVE's computing capacity, robot capabilities, storage, logistics, construction, energy systems, and industrial processing.

HIVE initially receives and processes mined material. Planned processing includes metal ingots, hydrogen and oxygen from ice, refined gases, and purified silicon for processors. Separate storage and industrial facilities become available later.

Electronic components can be produced through either:

Manual printing: a mouse-controlled minigame involving component placement, circuit connections, and verification. Accuracy affects component quality.

Automatic printing: slower production without player input. Quality and consistency improve through research.

Energy
Diggers and small robots do not carry their own energy reserves. HIVE distributes power wirelessly through the OSRMS network. Distance is not the limiting factor; available energy capacity determines how many robots can operate. The player sets priorities.

The exact reactor variant and HIVE's energy capacity remain open design questions.

Robot roster
Unit	Planned role
OSRMS-01 HIVE	Central production base, resource processing, storage, research, energy distribution, and robot coordination. Initially stationary inside the opened rocket.
Digger	Starting excavation robot; mines, crushes, collects, and delivers material, or dumps it after an upgrade.
Mole	Specialized development of the Digger for deeper tunnels and demanding excavation.
Mule	Standard transport robot for mined material, gases, construction materials, and components.
Hauler	Heavy transport development of the Mule for larger loads.
Maglev Hauler	Advanced transport variant using rails and magnetic routes.
Builder	Starting construction robot using lasers and cement.
Mason	Specialized development of the Builder for external structures, connections, docks, and hangar doors.
Scout	Exploration robot for tunnels, the surface, and nearby space; later discovers Ceres. Uses a hangar for safe departure and return.
Herald	Development of the Scout that installs and controls large asteroid propulsion systems and connects the propulsion network to Ceres.
A later hologram avatar allows the player to inspect areas, approach robots, and assign tasks. It does not replace HIVE as the production base.

Narrative progression
The following outline includes planned story revelations.

HIVE's biological core is a frozen human brain used in an experimental AI mining system. Following an accident, the original human's organs were preserved under a prior consent arrangement that provided compensation to their family.

Initially, the brain functions as a storage and decision-making layer rather than a fully conscious person. The AI gradually develops an identity. A major computing upgrade reveals the biological core, after which the player chooses a female or male holographic avatar. The player can later choose a new name or retain HIVE.

Expansion leads from the starter asteroid to 511 Davida and eventually Ceres. The long-term design involves developing Ceres and moving the system through the Solar System, although the exact relationship between Ceres as a ship, an industrial development location, and a travelling body remains unresolved.

Contact with Earth reveals a humanity in crisis following war, with the planet surrounded by satellites and space debris. Dialogue choices lead toward cooperation and recovery, or domination and the conversion of humanity into a partly biological, partly machine android system. Detailed consequences remain to be developed.

Planned release roadmap
These releases are design targets, not confirmed completed versions.

Release	Planned scope
Version 1 — Starter asteroid	HIVE awakening; starting Digger and Builder; controls, exploration, initial research and industry; expanded memory and production; brain revelation and avatar choice; hangar and Scout unlock; protected HIVE relocation, with location and sequencing still requiring clarification.
Version 2 — Scanner, Davida, and Ceres	Scanner reveals Davida and other asteroids; connect the starter asteroid to Davida; Scout exploration and discovery of Ceres; communications and satellites; planetary scanning; HIVE relocation toward the centre of Ceres, subject to unresolved design details.
Version 3 — Ceres and navigation	Asteroid connections or impacts for mining; large propulsion systems; navigation through the Solar System.
Version 3b — Journey to Earth	Integrate propulsion, fuel and energy, route planning, and system connections to begin the return journey.
Version 4 — Arrival at Earth	Discover the state of humanity; first contact; cooperation or domination; consequences and conclusion.
Development sequence
The design begins with a project foundation in which HIVE is controllable. Later work covers landing and starting robots, autonomous excavation, the cube-selection grid, fog of war, transport, research, upgrades, construction, printing, hangars, relocation, exploration, scanners, large projects, external construction, Ceres, industrial expansion, self-replication, and Earth contact.

The source contains both a detailed build-phase list and a recommended build-order table. Their numbering and grouping differ. They must not be treated as a single finalized milestone schedule. The active development phase must be confirmed before implementation work starts.

Technical direction
The following is the architecture described in the design document, not a verified inventory of repository code:

Area	Intended approach
Core systems	C++ for voxel terrain, robot AI, orbital calculations, and storage.
Prototyping and interaction	Blueprints for prototyping, UI, and interaction.
Overall architecture	Hybrid C++ core with Blueprint content and behaviour.
Game data	DataTables and Data Assets for robot statistics, resources, research, projects, blueprints, and recipes.
Modular systems	Mining, Inventory, Energy, Construction, BlueprintPlacement, Production, Task, AreaSelection, ExcavationZone, FogOfWar, Project, and Printing components.
Communication	Interfaces for robot actions; Event Dispatchers for resource, task, project, and UI updates.
Setup and build information
No verified installation or build procedure is provided yet. The actual .uproject file, engine association, source modules, required plugins, dependencies, and build targets must be checked before documenting executable setup steps.

Open design questions
The starter asteroid's position relative to the main belt and Davida.

The technology and project used to move and attach asteroids.

Whether the starter asteroid connects to Davida through attachment points or a prepared recess.

The relationship between Ceres as a ship, a travelling body, and a development location.

The location, prerequisites, physical method, and sequence of HIVE relocation.

The dependency order between rocket dismantling, hangar construction, and relocation.

Surface-project contents and the requirements for discovering Ceres.

The outer boundary material and practical cube-grid layout on an approximately 10 kilometre object.

HIVE's physical layout, reactor variant, and available energy capacity.

Detailed alloy production chains and infrastructure visuals.

The identity of the originating organization and further details of the brain–AI relationship.

Dialogue structure, Earth-return consequences, and the origin of Earth's debris ring.

Documentation scope
This README summarizes the design source. It does not modify that source, establish a license, confirm repository contents, or claim that code has been executed or features have been tested.