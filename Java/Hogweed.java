import java.util.Vector;
public class Hogweed extends Plant {
  public Hogweed(World world, Point position) {
    super(world, position, Constants.HOGWEED_SYMBOL, Constants.HOGWEED_STRENGTH, Constants.HOGWEED_COLOR, Constants.HOGWEED_NAME);
  }

  @Override
  public Organism Clone(Point position) {
    return new Hogweed(this.world, position);
  }

  @Override
  public boolean Collision(Organism other) {
    this.world.messageManager.AddPlantEatingMessage(other.GetName(), this.GetName());
    this.world.messageManager.AddDeathMessage(other.GetName(), this.GetName());
    this.Die();
    if(other.GetSymbol() != Constants.CYBERSHEEP_SYMBOL) {
      other.Die();
    }
    return false;
  }

  @Override
  public void Action() {
    if(CanAction()) {
      Vector<Point> positions = world.GetPositionsAround(this.GetPosition());
      for(Point position : positions) {
        Organism other = world.GetOrganismAt(position);
        // Check if there is an animal on the field, and it is not a cyber-sheep
        if(other instanceof Animal && other.GetSymbol() != Constants.CYBERSHEEP_SYMBOL) {
          other.Die();
          this.world.messageManager.AddDeathMessage(other.GetName(), this.GetName());
        }
      }

    }
  }
}
