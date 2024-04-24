import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Vector;

public class World {
  private static World instance;
  private int width;
  private int height;
  private char humanInput;
  private int humanSuperPowerDuration;
  private int humanSuperPowerCooldown;

  private Organism[][] mapOfTheWorld;
  private Vector<Organism> organismsList;
  private Vector<Organism> organismsToRemove;
  public MessageManager messageManager = new MessageManager();

  private World(final int width, int height) { // Private constructor
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


  public int GetWidth() {
    return width;
  }

  public int GetHeight() {
    return height;
  }

  public static World GetInstance(int w, int h) { // Singleton pattern
    // Lazy initialization: create the instance only when needed
    if (instance == null) {
      instance = new World(w, h);
    }
    return instance;
  }

  public Organism GetOrganismAt(int x, int y) {
    return mapOfTheWorld[x][y];
  }

  public Organism GetOrganismAt(Point position) {
    return mapOfTheWorld[position.GetX()][position.GetY()];
  }

  public void AddOrganism(Organism organism) {
    mapOfTheWorld[organism.GetPosition().GetX()][organism.GetPosition().GetY()] = organism;
    organismsList.add(organism);
  }

  public void MoveOrganism(Organism organism, Point newPosition) {
    mapOfTheWorld[organism.GetPosition().GetX()][organism.GetPosition().GetY()] = null;
    mapOfTheWorld[newPosition.GetX()][newPosition.GetY()] = organism;
    organism.SetPosition(newPosition);
  }

  public boolean IsPositionWithinBounds(Point position) {
    return position.GetX() >= 0 && position.GetX() < width && position.GetY() >= 0 && position.GetY() < height;
  }

  public boolean IsPositionFree(Point position) {
    return mapOfTheWorld[position.GetX()][position.GetY()] == null;
  }

  public boolean IsAnyPositionFree() {
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        if (mapOfTheWorld[i][j] == null) {
          return true;
        }
      }
    }
    return false;
  }

  public Point GetRandomPositionAround(Point position, boolean onlyEmpty, int distance) {
    Point newPosition = null;
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

  public Point GetRandomPositionForChild(Point position1, Point position2) {
    Point newPosition = null;
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

  public Vector<Point> GetPositionsAround(Point position) {
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

  public Point GetRandomFreePosition() {
    if(!IsAnyPositionFree()) {
      return null;
    }
    Point position = new Point((int) (Math.random() * width), (int) (Math.random() * height));
    while (!IsPositionFree(position)) {
      position = new Point((int) (Math.random() * width), (int) (Math.random() * height));
    }
    return position;
  }

  public void RemoveOrganism(Organism organism) {
    organismsToRemove.add(organism);
  }

  public Point FindNearestOrganism(Point position, char symbol) {
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

  public char GetHumanInput() {
    return humanInput;
  }

  public void SetHumanInput(char input) {
    humanInput = input;
  }

  public void SetHumanSuperPowerDuration(int duration) {
    humanSuperPowerDuration = duration;
  }

  public void SetHumanSuperPowerCooldown(int cooldown) {
    humanSuperPowerCooldown = cooldown;
  }

  public int GetHumanSuperPowerDuration() {
    return humanSuperPowerDuration;
  }

  public int GetHumanSuperPowerCooldown() {
    return humanSuperPowerCooldown;
  }

  public void HandleSuperPower() {
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

  public boolean IsHumanMoveLegal(char input) {
    Organism human = null;
    for(Organism organism : organismsList) {
      if(organism instanceof Human) {
        human = organism;
        break;
      }
    }
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
        break;
    }
    return IsPositionWithinBounds(newPosition);
  }

  public void MakeTurn() {
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
      mapOfTheWorld[organism.GetPosition().GetX()][organism.GetPosition().GetY()] = null;
      organismsList.remove(organism);
    }
    organismsCopy.clear();
    organismsToRemove.clear();

    SetHumanSuperPowerDuration(Math.max(-1, GetHumanSuperPowerDuration() - 1));
    if(GetHumanSuperPowerDuration() == -1) {
      SetHumanSuperPowerCooldown(Math.max(0, GetHumanSuperPowerCooldown() - 1));
    }
  }

  public boolean IsHumanDead() {
    for(Organism organism : organismsList) {
      if(organism instanceof Human) {
        return false;
      }
    }
    return true;
  }

}
