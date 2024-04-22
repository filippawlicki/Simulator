import java.util.Random;

public class Turtle extends Animal {
  public Turtle(World world, Point position) {
    super(world, position, Constants.TURTLE_SYMBOL, Constants.TURTLE_STRENGTH, Constants.TURTLE_INITIATIVE, Constants.TURTLE_COLOR, Constants.TURTLE_NAME, Constants.ANIMAL_RANGE);
  }

  @Override
  public Organism Clone(Point position) {
    return new Turtle(this.world, position);
  }

  @Override
  public boolean Collision(Organism other) {
    if (other.GetStrength() < 5) {
      this.world.messageManager.AddAttactRepelledMessage(other.GetName(), this.GetName());
      return true;
    }
    return super.Collision(other);
  }

  @Override
  public void Action() {
    Random random = new Random();
    if (random.nextInt(4) == 0) {
      super.Action();
    }
  }
}
