Our code follows SRP (Single Resposibility Principle) by splitting pickups and potions up, 
the potions only responsibilty is to set the texture rect, 
the pickup class will initialise the potion and determine what potion to create, the actual damage is dealt by the health system

This affected our code in a positive manner as we were able to keep the code neat and easy to understand as it grew.



Our code follows OCP (open/closed principle) 
by seperating the code of pickups and potions so that its very easy to add another potion and not have to change any of the code, 

This affected our code positively, as adding new pickups is very simple and causes no issues as you dont need to modify code.



Our code follows DIP (Dependecy inversion principle) In our health system as our health (high level)
 is seperate from our player and orc (low level).

This made it very easy to add health for the orc and player as we can now add new entities with health without needing to change very much at all
it also kept our code clean and seperated and independent which helped with preventing and solving any bugs we ran into.


Our SRP, OCP and DIP are built into out observer and strategy patterns so the UML Diagrams are the same for this section also:

```mermaid
classDiagram
    %% === Strategy Pattern (Pickups System) ===
    class PickupStrategy {
        <<interface>>
        +applyEffect()
        +getTextureRect() sf::IntRect
    }

    class HealthPotion {
        +applyEffect()
        +getTextureRect() sf::IntRect
    }

    class PoisonPotion {
        +applyEffect()
        +getTextureRect() sf::IntRect
    }

    class Pickup {
        -unique_ptr<PickupStrategy> strategy
        +initPickups()
        +applyPickupEffect()
        +renderPickups(sf::RenderWindow&, bool)
    }

    Pickup --> PickupStrategy : uses
    HealthPotion ..|> PickupStrategy
    PoisonPotion ..|> PickupStrategy

    %% === Observer Pattern (Game Event System) ===
    class Subject {
        <<interface>>
        +attach(Observer)
        +detach(Observer)
        +notify()
    }

    class Observer {
        <<interface>>
        +update()
    }

    class PlayerHealthSystem {
        +increaseHealth()
        +takeDamage()
    }

    class UIHealthBar {
        +update()
    }

    class GameStatsTracker {
        +update()
    }

    Subject <|-- PlayerHealthSystem
    Observer <|-- UIHealthBar
    Observer <|-- GameStatsTracker
    PlayerHealthSystem --> Observer : notifies
