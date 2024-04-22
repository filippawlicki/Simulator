public class CyberSheep extends Animal {
  public CyberSheep(World world, Point position) {
    super(world, position, Constants.CYBERSHEEP_SYMBOL, Constants.CYBERSHEEP_STRENGTH, Constants.CYBERSHEEP_INITIATIVE, Constants.CYBERSHEEP_COLOR, Constants.CYBERSHEEP_NAME, Constants.ANIMAL_RANGE);
  }

  @Override
  public Organism Clone(Point position) {
    return new CyberSheep(this.world, position);
  }

  @Override
  public void Action() {
    Point nearest = this.world.FindNearestOrganism(this.GetPosition(), Constants.HOGWEED_SYMBOL);
    if (nearest != null) {
      Point newPosition = this.GetPosition();
      if (nearest.GetX() > this.GetPosition().GetX()) {
        newPosition.SetX(newPosition.GetX() + 1);
      } else if (nearest.GetX() < this.GetPosition().GetX()) {
        newPosition.SetX(newPosition.GetX() - 1);
      } else if (nearest.GetY() > this.GetPosition().GetY()) {
        newPosition.SetY(newPosition.GetY() + 1);
      } else if (nearest.GetY() < this.GetPosition().GetY()) {
        newPosition.SetY(newPosition.GetY() - 1);
      }
      Organism other = world.GetOrganismAt(newPosition);
      if (other == null) {
        this.world.MoveOrganism(this, newPosition);
      } else { // Collision
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
    } else {
      super.Action();
    }
  }
}
