import java.util.Vector;

public class World {
  private static World instance;
  private int width;
  private int height;

  private Organism[][] mapOfTheWorld;
  private Vector<Organism> organismsList;


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
  }

  public static World GetInstance(int w, int h) { // Singleton pattern
    // Lazy initialization: create the instance only when needed
    if (instance == null) {
      instance = new World(w, h);
    }
    return instance;
  }

  public Organism GetOrganism(int x, int y) {
    return mapOfTheWorld[x][y];
  }
}
