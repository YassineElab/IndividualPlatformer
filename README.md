# Individual-Project
# use arrow keys for movement and Q,D to shoot
# als de textures niet willen loaden ze zitten in MenuState.cpp, LevelMenuState.cpp, ConcreteFactory en RenderSystem.cpp

#installeer sfml, clone het project, vergeet niet om de juiste working dir in te voeren, compileer het project.

# De game start met een menu waar dat je op PLAY kan klikken. Daarna kom je terecht in het levelmenu, waar je bijvoorbeeld vanaf level 1 kan beginnen, de levelstate wordt aangemaakt in /ecsFolder/Game/LevelState.cpp, in die update functie kan je zien hoe die wordt aangemaakt, dus wij roepen de world::init aan, daar gaan wij eerst de startinit (in init1, init2 of init3) oproepen dit is waar dat ik alle systems initializeer, ik maak ook unordered maps <Entity, Component> om alle components die bij bepaalde entities horen bij te houden, en dan kan je die component van een entity makkelijk oproepen aangezien de entity gewoon een id is(in mijn geval 0-249). de init1, 2, 3(hangt er van af op welke level je bent) gaat dan ook de level aanmaken via de builders.
# Dan wordt de gameloop aangemaakt die de update functie gaat oproepen, dit gebeurt elke frame en alle update functies van de systems worden dan ook opgeroepen en er wordt ook nog gedrawt.
# De init-functies maken ook het level aan met behulp van builders. Die builders gebruiken op hun beurt de ConcreteFactory om componenten toe te voegen aan een entity. Dit zorgt voor een overzichtelijke en gestructureerde code. Builders maken het bovendien mogelijk om logica toe te voegen, zoals het instellen van verschillende textures per wall.
# In de concretefactory maken wij de entity en geven wij die components volgens de ECS, en de systems gaan dan kijken of dat die entity de component heeft om de logica uit te voeren bijvoorbeeld player heeft een gravity component en physicsystem heeft gravitycomponent nodig om op een entity gravity te zetten.
# De quadtree splits de scherm recursief op in 4 delen, ik gebruik de quadtree.retrieve zodat ik alle possible collisions krijg in plaats van dat ik bijvoorbeeld mijn player met alle entities ga vergelijken dit zorgt voor een goede performance boost.
