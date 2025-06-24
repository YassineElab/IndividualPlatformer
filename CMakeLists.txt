cmake_minimum_required(VERSION 3.24)
project(IndividualPlatformer)

set(CMAKE_CXX_STANDARD 20)

add_executable(IndividualPlatformer main.cpp ecsFolder/System/Types.h ecsFolder/System/System.h ecsFolder/Systems/InputSystem.h ecsFolder/Systems/CollisionSystem.h ecsFolder/Systems/CameraSystem.h ecsFolder/Factories/AbstractFactory.h ecsFolder/Factories/ConcreteFactory.h ecsFolder/World/World.cpp ecsFolder/World/World.h ecsFolder/World/Stopwatch.cpp ecsFolder/World/Stopwatch.h ecsFolder/Systems/RenderSystem.h ecsFolder/Game/Controller.h ecsFolder/Game/ControllerV.h ecsFolder/Game/Game.cpp ecsFolder/Game/StateManager.cpp ecsFolder/Game/State.h ecsFolder/Components/Components.h ecsFolder/Game/Controller.cpp ecsFolder/Game/MenuState.cpp ecsFolder/Game/LevelState.cpp ecsFolder/Builder/PlayerBuilder.h ecsFolder/Systems/MovementSystem.h ecsFolder/Systems/PhysicsSystem.h ecsFolder/Collision/Quadtree.h ecsFolder/Builder/WallBuilder.h ecsFolder/Builder/SpringBuilder.h ecsFolder/Systems/RenderSystem.cpp ecsFolder/Systems/CameraSystem.cpp ecsFolder/Systems/InputSystem.cpp ecsFolder/Systems/CollisionSystem.cpp ecsFolder/Systems/MovementSystem.cpp ecsFolder/Systems/PhysicsSystem.cpp ecsFolder/Builder/PlayerBuilder.cpp ecsFolder/Builder/SpringBuilder.cpp ecsFolder/Builder/WallBuilder.cpp ecsFolder/Factories/ConcreteFactory.cpp ecsFolder/Builder/SpikeBuilder.cpp ecsFolder/Builder/SpikeBuilder.h ecsFolder/Systems/JumpSystem.cpp ecsFolder/Systems/JumpSystem.h ecsFolder/Game/LevelMenuState.cpp ecsFolder/Game/LevelMenuState.h ecsFolder/Builder/GoalBuilder.cpp ecsFolder/Builder/GoalBuilder.h ecsFolder/Systems/ProjectileSystem.cpp ecsFolder/Systems/ProjectileSystem.h ecsFolder/Systems/ShootSystem.cpp ecsFolder/Systems/ShootSystem.h ecsFolder/Builder/ProjectileBuilder.cpp ecsFolder/Builder/ProjectileBuilder.h ecsFolder/Builder/TargetBuilder.cpp ecsFolder/Builder/TargetBuilder.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS audio system graphics window network REQUIRED)

include_directories(C:/SFML-2.5.1/include)
target_link_libraries(IndividualPlatformer sfml-system sfml-graphics sfml-audio sfml-window sfml-network)