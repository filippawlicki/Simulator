import java.awt.*;

public final class Constants {
  // Prevent instantiation
  private Constants() {}

  public static final double SPREAD_PROBABILITY = 0.1;
  public static final int PLANT_INITIATIVE = 0;

  public static final int ANIMAL_RANGE = 1;
  public static final int ANTELOPE_RANGE = 2;

  public static final char SYMBOL_GRASS = 'G';
  public static final Color COLOR_GRASS = new Color(0, 255, 0);
  public static final String NAME_GRASS = "Grass";
  public static final int STRENGTH_GRASS = 0;

  public static final char SOW_THISTLE_SYMBOL = 'T';
  public static final Color SOW_THISTLE_COLOR = new Color(255, 255, 0);
  public static final String SOW_THISTLE_NAME = "Sow Thistle";
  public static final int SOW_THISTLE_STRENGTH = 0;

  public static final char GUARANA_SYMBOL = 'U';
  public static final Color GUARANA_COLOR = new Color(255, 0, 0);
  public static final String GUARANA_NAME = "Guarana";
  public static final int GUARANA_STRENGTH = 0;

  public static final char HOGWEED_SYMBOL = 'H';
  public static final Color HOGWEED_COLOR = new Color(255, 0, 255);
  public static final String HOGWEED_NAME = "Hogweed";
  public static final int HOGWEED_STRENGTH = 10;

  public static final char NIGHTSHADE_BERRIES_SYMBOL = 'N';
  public static final Color NIGHTSHADE_BERRIES_COLOR = new Color(102, 52, 161);
  public static final String NIGHTSHADE_BERRIES_NAME = "Nightshade Berries";
  public static final int NIGHTSHADE_BERRIES_STRENGTH = 99;

  public static final char WOLF_SYMBOL = 'W';
  public static final Color WOLF_COLOR = new Color(97, 97, 97);
  public static final String WOLF_NAME = "Wolf";
  public static final int WOLF_STRENGTH = 9;
  public static final int WOLF_INITIATIVE = 5;

  public static final char TURTLE_SYMBOL = 'T';
  public static final Color TURTLE_COLOR = new Color(1, 86, 1);
  public static final String TURTLE_NAME = "Turtle";
  public static final int TURTLE_STRENGTH = 2;
  public static final int TURTLE_INITIATIVE = 1;

  public static final char SHEEP_SYMBOL = 'E';
  public static final Color SHEEP_COLOR = new Color(255, 255, 255);
  public static final String SHEEP_NAME = "Sheep";
  public static final int SHEEP_STRENGTH = 4;
  public static final int SHEEP_INITIATIVE = 4;

  public static final char FOX_SYMBOL = 'F';
  public static final Color FOX_COLOR = new Color(255, 128, 0);
  public static final String FOX_NAME = "Fox";
  public static final int FOX_STRENGTH = 3;
  public static final int FOX_INITIATIVE = 7;

  public static final char CYBERSHEEP_SYMBOL = 'C';
  public static final Color CYBERSHEEP_COLOR = new Color(0, 0, 0);
  public static final String CYBERSHEEP_NAME = "CyberSheep";
  public static final int CYBERSHEEP_STRENGTH = 11;
  public static final int CYBERSHEEP_INITIATIVE = 4;

  public static final char ANTELOPE_SYMBOL = 'A';
  public static final Color ANTELOPE_COLOR = new Color(238, 2, 255);
  public static final String ANTELOPE_NAME = "Antelope";
  public static final int ANTELOPE_STRENGTH = 4;
  public static final int ANTELOPE_INITIATIVE = 4;
}
