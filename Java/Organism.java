import java.awt.Color;
public abstract class Organism {
  private final char symbol;
  private Point position;
  private int age;
  private int strength;
  private final int initiative;
  private boolean canAction;
  private final Color color;
  private final String name;
  final World world;

  Organism(World world, Point position, char symbol, int strength, int initiative, Color color, String name) {
    this.world = world;
    this.position = position;
    this.symbol = symbol;
    this.strength = strength;
    this.initiative = initiative;
    this.color = color;
    this.age = 0;
    this.canAction = false;
    this.name = name;
  }

  // Returns false if organism frees the field and true if it keeps its place
  protected abstract boolean Collision(Organism other);
  public abstract void Action();

  public final char GetSymbol() {
    return symbol;
  }

  final String GetName() { return name; }

  public final Color GetColor() {
    return color;
  }

  public final Point GetPosition() {
    return position;
  }
  public final void SetPosition(Point position) {
    this.position = position;
  }

  public final int GetAge() {
    return age;
  }
  public final void IncrementAge() {
    age++;
  }

  public final int GetStrength() {
    return strength;
  }
  public final void SetStrength(int strength) {
    this.strength = strength;
  }

  public final int GetInitiative() {
    return initiative;
  }

  final boolean CanAction() {
    return canAction;
  }
  public final void SetCanAction(boolean canAction) {
    this.canAction = canAction;
  }

  final void Die() {
    this.world.RemoveOrganism(this);
  }

  protected abstract Organism Clone(Point position);
}
