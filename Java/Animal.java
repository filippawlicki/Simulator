import java.awt.*;

public abstract class Animal extends Organism {

  private final int moveRange;
  public Animal(World world, Point position, char symbol, int strength, int initiative, Color color, String name, int moveRange) {
    super(world, position, symbol, strength, initiative, color, name);
    this.moveRange = moveRange;
  }

  @Override
  public boolean Collision(Organism other) {
    if(this.GetSymbol() == other.GetSymbol()) {
      this.Breed(other);
      return true;
    } else {
      this.Die();
      this.world.messageManager.AddDeathMessage(this.GetName(), other.GetName());
      return false;
    }
  }

  @Override
  public void Action() {
    if(CanAction()) {
      Point newPosition = world.GetRandomPositionAround(this.GetPosition(), false, moveRange);
      if (newPosition != null) {
        Organism other = world.GetOrganismAt(newPosition);
        if (other == null) {
          this.world.MoveOrganism(this, newPosition);
        } else { // Collision
          other.SetCanAction(false);
          if (this.GetSymbol() == other.GetSymbol()) {
            this.Collision(other); // Breed
          } else {
            if (this.GetStrength() >= other.GetStrength()) {
              boolean takenField = other.Collision(this); // Kill
              if (!takenField && other.GetSymbol() != Constants.HOGWEED_SYMBOL && other.GetSymbol() != Constants.NIGHTSHADE_BERRIES_SYMBOL) {
                this.world.MoveOrganism(this, newPosition);
              }
            } else {
              if (other.GetSymbol() == Constants.HOGWEED_SYMBOL || other.GetSymbol() == Constants.NIGHTSHADE_BERRIES_SYMBOL) { // Hogweed and Nightshade Berries kill the attacker, but they are also eaten
                other.Collision(this);
              } else {
                this.Collision(other); // Killed
              }
            }
          }
        }
      }
    }
  }

  public final void Breed(Organism other) {
    Point newPosition = world.GetRandomPositionForChild(this.GetPosition(), other.GetPosition());
    if (newPosition != null) {
      Organism newOrganism = this.Clone(newPosition);
      this.world.messageManager.AddReproductionMessage(this.GetName(), other.GetName(), newOrganism.GetName());
      world.AddOrganism(newOrganism);
    }
  }
}
