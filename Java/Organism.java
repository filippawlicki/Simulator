import java.awt.Color;
public abstract class Organism {
  private char symbol;
  private Point position;
  private int age;
  private int strength;
  private int initiative;
  private boolean canAction;
  private Color color;
  private String name;
  protected World world;

  public Organism(World world, Point position, char symbol, int strength, int initiative, Color color, String name) {
    this.world = world;
    this.position = position;
    this.symbol = symbol;
    this.strength = strength;
    this.initiative = initiative;
    this.color = color;
    this.age = 0;
  }

  // Returns false if organism frees the field and true if it keeps its place
  public abstract boolean Collision(Organism other);
  public abstract void Action();

  public char GetSymbol() {
    return symbol;
  }

  public String GetName() { return name; }

  public Color GetColor() {
    return color;
  }

  public Point GetPosition() {
    return position;
  }
  public void SetPosition(Point position) {
    this.position = position;
  }

  public int GetAge() {
    return age;
  }
  public void IncrementAge() {
    age++;
  }

  public int GetStrength() {
    return strength;
  }
  public void SetStrength(int strength) {
    this.strength = strength;
  }

  public int GetInitiative() {
    return initiative;
  }

  public boolean CanAction() {
    return canAction;
  }
  public void SetCanAction(boolean canAction) {
    this.canAction = canAction;
  }

  public void Die() {
    this.world.RemoveOrganism(this);
  }

  public abstract Organism Clone(Point position);
}
