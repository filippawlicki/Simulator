import java.util.Arrays;
import java.util.Vector;

public class World {
  private static World instance;
  private final int width;
  private final int height;
  private char humanInput;
  private int humanSuperPowerDuration;
  private int humanSuperPowerCooldown;

  private final Organism[][] mapOfTheWorld;
  private final Vector<Organism> organismsList;
  private final Vector<Organism> organismsToRemove;
  private String humanCauseOfDeath;
  public MessageManager messageManager = new MessageManager();

  private World(final int width, final int height) { // Private constructor
    this.width = width;
    this.height = height;
    mapOfTheWorld = new Organism[width][height];
    for(int i = 0; i < width; i++) {
      for(int j = 0; j < height; j++) {
        mapOfTheWorld[i][j] = null; // Initialize the map with null values
      }
    }
    organismsList = new Vector<>(); // Initialize the Vector
    organismsToRemove = new Vector<>(); // Initialize the Vector
    humanSuperPowerCooldown = 0;
    humanSuperPowerDuration = -1;
  }


  public final int GetWidth() {
    return width;
  }

  public final int GetHeight() {
    return height;
  }

  public static World GetInstance(int w, int h) { // Singleton pattern
    // Lazy initialization: create the instance only when needed
    if (instance == null) {
      instance = new World(w, h);
    }
    return instance;
  }

  public final Organism GetOrganismAt(int x, int y) {
    return mapOfTheWorld[x][y];
  }

  public final Organism GetOrganismAt(Point position) {
    return mapOfTheWorld[position.GetX()][position.GetY()];
  }

  public final void AddOrganism(Organism organism) {
    mapOfTheWorld[organism.GetPosition().GetX()][organism.GetPosition().GetY()] = organism;
    organismsList.add(organism);
  }

  public final Vector<Organism> GetOrganisms() {
    return organismsList;
  }

  public final void MoveOrganism(Organism organism, Point newPosition) {
    mapOfTheWorld[organism.GetPosition().GetX()][organism.GetPosition().GetY()] = null;
    mapOfTheWorld[newPosition.GetX()][newPosition.GetY()] = organism;
    organism.SetPosition(newPosition);
  }

  public final boolean IsPositionWithinBounds(Point position) {
    return position.GetX() >= 0 && position.GetX() < width && position.GetY() >= 0 && position.GetY() < height;
  }

  public final boolean IsPositionFree(Point position) {
    return mapOfTheWorld[position.GetX()][position.GetY()] == null;
  }

  public final boolean IsAnyPositionFree() {
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        if (mapOfTheWorld[i][j] == null) {
          return true;
        }
      }
    }
    return false;
  }

  public final Point GetRandomPositionAround(Point position, boolean onlyEmpty, int distance) {
    Point newPosition;
    int x = position.GetX();
    int y = position.GetY();
    Vector<Point> positionsAround = new Vector<>(Arrays.asList(
      new Point(x - distance, y),
      new Point(x + distance, y),
      new Point(x, y - distance),
      new Point(x, y + distance)
    ));
    while (!positionsAround.isEmpty()) {
      int randomIndex = (int) (Math.random() * positionsAround.size());
      newPosition = positionsAround.get(randomIndex);
      positionsAround.remove(randomIndex);
      if (IsPositionWithinBounds(newPosition)) {
        if (!onlyEmpty || IsPositionFree(newPosition)) { // If the position is free, or we don't care if it's free break the loop
          return newPosition;
        }
      }
    }
    return null; // Return null if no position is found
  }

  public final Point GetRandomPositionForChild(Point position1, Point position2) {
    Point newPosition;
    int x1 = position1.GetX();
    int y1 = position1.GetY();
    int x2 = position2.GetX();
    int y2 = position2.GetY();
    Vector<Point> positionsAround = new Vector<>(Arrays.asList(
      new Point(x1 - 1, y1),
      new Point(x1 + 1, y1),
      new Point(x1, y1 - 1),
      new Point(x1, y1 + 1),
      new Point(x2 - 1, y2),
      new Point(x2 + 1, y2),
      new Point(x2, y2 - 1),
      new Point(x2, y2 + 1)
    ));
    while (!positionsAround.isEmpty()) {
      int randomIndex = (int) (Math.random() * positionsAround.size());
      newPosition = positionsAround.get(randomIndex);
      positionsAround.remove(randomIndex);
      if (IsPositionWithinBounds(newPosition) && IsPositionFree(newPosition)) {
        return newPosition;
      }
    }
    return null; // Return null if no position is found
  }

  public final Vector<Point> GetPositionsAround(Point position) {
    int x = position.GetX();
    int y = position.GetY();
    Vector<Point> positionsAround = new Vector<>(Arrays.asList(
      new Point(x - 1, y),
      new Point(x + 1, y),
      new Point(x, y - 1),
      new Point(x, y + 1)
    ));
    positionsAround.removeIf(p -> !IsPositionWithinBounds(p));
    return positionsAround;
  }

  public final Point GetRandomFreePosition() {
    if(!IsAnyPositionFree()) {
      return null;
    }
    Point position = new Point((int) (Math.random() * width), (int) (Math.random() * height));
    while (!IsPositionFree(position)) {
      position = new Point((int) (Math.random() * width), (int) (Math.random() * height));
    }
    return position;
  }

  public final void RemoveOrganism(Organism organism) {
    organismsToRemove.add(organism);
  }

  public final Point FindNearestOrganism(Point position, char symbol) {
    Point nearest = null;
    int minDistance = Integer.MAX_VALUE;
    for (Organism organism : organismsList) {
      if (organism.GetSymbol() == symbol) {
        int distance = Math.abs(organism.GetPosition().GetX() - position.GetX()) + Math.abs(organism.GetPosition().GetY() - position.GetY());
        if (distance < minDistance) {
          minDistance = distance;
          nearest = organism.GetPosition();
        }
      }
    }
    return nearest;
  }

  public final char GetHumanInput() {
    return humanInput;
  }

  public final void SetHumanInput(char input) {
    humanInput = input;
  }

  public final void SetHumanSuperPowerDuration(int duration) {
    humanSuperPowerDuration = duration;
  }

  public final void SetHumanSuperPowerCooldown(int cooldown) {
    humanSuperPowerCooldown = cooldown;
  }

  public final int GetHumanSuperPowerDuration() {
    return humanSuperPowerDuration;
  }

  public final int GetHumanSuperPowerCooldown() {
    return humanSuperPowerCooldown;
  }

  public final void HandleSuperPower() {
    if(humanSuperPowerCooldown == 5 && humanSuperPowerDuration == 5) { // Increase the strength of human
      for(Organism organism : organismsList) {
        if(organism instanceof Human) {
          organism.SetStrength(organism.GetStrength() + 5);
        }
      }
    } else if(humanSuperPowerDuration >= 0) { // Lower the strength of human
      for(Organism organism : organismsList) {
        if(organism instanceof Human) {
          organism.SetStrength(organism.GetStrength() - 1);
        }
      }
    }
  }

  public final boolean IsHumanMoveLegal(char input) {
    Organism human = null;
    for(Organism organism : organismsList) {
      if(organism instanceof Human) {
        human = organism;
        break;
      }
    }
    assert human != null;
    Point newPosition = new Point(human.GetPosition().GetX(), human.GetPosition().GetY());
    switch(input) {
      case 'U':
        newPosition.SetY(newPosition.GetY() - 1);
        break;
      case 'D':
        newPosition.SetY(newPosition.GetY() + 1);
        break;
      case 'L':
        newPosition.SetX(newPosition.GetX() - 1);
        break;
      case 'R':
        newPosition.SetX(newPosition.GetX() + 1);
        break;
      default:
        return false;
    }
    return IsPositionWithinBounds(newPosition);
  }

  public final void MakeTurn() {
    messageManager.ClearMessages();
    HandleSuperPower();
    organismsList.sort((o1, o2) -> {
      // Compare initiative
      int initiativeComparison = Integer.compare(o2.GetInitiative(), o1.GetInitiative());
      if (initiativeComparison != 0) {
        return initiativeComparison;
      }

      // If initiative is the same, compare age
      return Integer.compare(o2.GetAge(), o1.GetAge());
    });
    Vector<Organism> organismsCopy = new Vector<>(organismsList);
    for(Organism organism : organismsCopy) {
      organism.SetCanAction(true);
    }
    for(Organism organism : organismsCopy) {
      organism.Action();
    }
    for(Organism organism : organismsCopy) {
      organism.IncrementAge();
    }
    for(Organism organism : organismsToRemove) { // Remove dead organisms
      if(GetOrganismAt(organism.GetPosition()) == organism) { // Check if the organism is still at its position
        mapOfTheWorld[organism.GetPosition().GetX()][organism.GetPosition().GetY()] = null;
      }
      organismsList.remove(organism);
    }
    organismsCopy.clear();
    organismsToRemove.clear();

    SetHumanSuperPowerDuration(Math.max(-1, GetHumanSuperPowerDuration() - 1));
    if(GetHumanSuperPowerDuration() == -1) {
      SetHumanSuperPowerCooldown(Math.max(0, GetHumanSuperPowerCooldown() - 1));
    }
  }

  public final boolean IsHumanDead() {
    for(Organism organism : organismsList) {
      if(organism instanceof Human) {
        return false;
      }
    }
    // Searching for the cause of death
    for(String message : messageManager.GetMessages()) {
      if(message.contains("Human was killed by")) {
        humanCauseOfDeath = message;
        break;
      }
    }
    return true;
  }

  public final String GetHumanCauseOfDeath() {
    return humanCauseOfDeath;
  }

}
