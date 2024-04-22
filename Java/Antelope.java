import java.util.Random;

public class Antelope extends Animal {
  public Antelope(World world, Point position) {
    super(world, position, Constants.ANTELOPE_SYMBOL, Constants.ANTELOPE_STRENGTH, Constants.ANTELOPE_INITIATIVE, Constants.ANTELOPE_COLOR, Constants.ANTELOPE_NAME, Constants.ANTELOPE_RANGE);
  }

  @Override
  public Organism Clone(Point position) {
    return new Antelope(this.world, position);
  }

  @Override
  public boolean Collision(Organism other) {
    if(this.GetSymbol() == other.GetSymbol()) {
      this.Breed(other);
      return true;
    } else {
      Random random = new Random();
      if(random.nextInt(2) == 0 && other instanceof Animal) {
        Point newPosition = this.world.GetRandomPositionAround(this.GetPosition(), true, 1);
        if(newPosition != null) {
          this.world.messageManager.AddAttackRunawayMessage(other.GetName(), this.GetName());
          this.world.MoveOrganism(this, newPosition);
        } else {
          this.Die();
          this.world.messageManager.AddDeathMessage(this.GetName(), other.GetName());
        }
      } else { // Die from plant or failed escape
        this.Die();
        this.world.messageManager.AddDeathMessage(this.GetName(), other.GetName());
      }
      return false;
    }
  }
}
