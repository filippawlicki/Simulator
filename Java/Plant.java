import java.awt.*;

public abstract class Plant extends Organism {
  private final double spreadChance;

  Plant(World world, Point position, char symbol, int strength, Color color, String name) {
    super(world, position, symbol, strength, Constants.PLANT_INITIATIVE, color, name);
    this.spreadChance = Constants.SPREAD_PROBABILITY;
  }

  private void TryToSpread() {
    Point newPosition = world.GetRandomPositionAround(this.GetPosition(), true, 1);
    if (newPosition != null) {
      Organism newOrganism = this.Clone(newPosition);
      world.AddOrganism(newOrganism);
    }
  }

  @Override
  public void Action() {
    if(CanAction()) {
      if (Math.random() < spreadChance) {
        this.TryToSpread();
      }
    }
  }

  @Override
  public boolean Collision(Organism other) {
    this.Die();
    this.world.messageManager.AddPlantEatingMessage(other.GetName(), this.GetName());
    return false;
  }
}
