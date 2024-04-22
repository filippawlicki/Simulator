import java.util.Arrays;
import java.util.Vector;

public class World {
  private static World instance;
  private int width;
  private int height;

  private Organism[][] mapOfTheWorld;
  private Vector<Organism> organismsList;
  private Vector<Organism> organismsToRemove;
  public MessageManager messageManager = new MessageManager();


  public int GetWidth() {
    return width;
  }

  public int GetHeight() {
    return height;
  }

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
          break;
        }
      }
    }
    return newPosition; // Return null if no position is found
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
        break;
      }
    }
    return newPosition; // Return null if no position is found
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
    mapOfTheWorld[organism.GetPosition().GetX()][organism.GetPosition().GetY()] = null;
    organismsList.remove(organism);
    organismsToRemove.add(organism);
  }
}
