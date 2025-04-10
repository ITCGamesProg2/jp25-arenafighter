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
