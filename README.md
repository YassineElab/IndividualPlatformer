# Individual-Project
# use arrow keys for movement and Q,D to shoot
# als de textures niet willen loaden ze zitten in MenuState.cpp, LevelMenuState.cpp, ConcreteFactory en RenderSystem.cpp

#installeer sfml, clone het project, vergeet niet om de juiste working dir in te voeren, compileer het project.

# De game start met een menu waar dat je op PLAY kan drukken, dan kom je terecht bij de levelmenu, waar dat je kan starten bij level 1, de levelstate wordt aangemaakt in /ecsFolder/Game/LevelState.cpp, in die update functie kan je zien hoe die wordt aangemaakt, dus wij roepen de world::init aan, daar gaan wij eerst de startinit (in een init1, 2, 3) oproepen dit is waar dat ik alle systems initializeer, ik maak ook unordered maps <Entity, Component> om alle components die bij bepaalde entities horen bij te houden, en dan kan je die component van een entity makkelijk oproepen aangezien de entity gewoon een id is(in mijn geval 0-249). de init1, 2, 3(hangt er van af op welke level je bent) gaat dan ook de level aanmaken via de builders.
# Dan wordt de gameloop aangemaakt die de update functie gaat oproepen, dit gebeurt elke frame en alle update functies van de systems worden dan ook opgeroepen en er wordt ook nog gedrawt.
# De builders maken gebruik van de concretefactory, dit zorgt voor gestructureerdere code en het is makkelijk om te lezen. je kan ook via builders een functie maken om bijvoorbeeld texture aan te passen zodat bijvoorbeeld niet elke wall dezelfde texture heeft en het gaat er vlot uitzien.
# In de concretefactory maken wij de entity en geven wij die components volgens de ECS, en de systems gaan dan kijken of dat die entity de component heeft om de logica uit te voeren bijvoorbeeld player heeft een gravity component en physicsystem heeft gravitycomponent nodig om op een entity gravity te zetten.
# De quadtree splits de scherm recursief op in 4 delen, ik gebruik de quadtree.retrieve zodat ik alle possible collisions krijg in plaats van dat ik bijvoorbeeld mijn player met alle entities ga vergelijken dit zorgt voor een goede performance boost.
