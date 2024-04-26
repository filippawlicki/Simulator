public class Human extends Animal {
  public Human(World world, Point position) {
    super(world, position, Constants.HUMAN_SYMBOL, Constants.HUMAN_STRENGTH, Constants.HUMAN_INITIATIVE, Constants.HUMAN_COLOR, Constants.HUMAN_NAME, Constants.ANIMAL_RANGE);
  }

  @Override
  public final Organism Clone(Point position) {
    return new Human(this.world, position);
  }

  @Override
  public final void Action() {
    char input = this.world.GetHumanInput();
    if(CanAction()) {
      Point newPosition = this.GetPosition();
      switch(input) {
        case 'U':
          newPosition = new Point(this.GetPosition().GetX(), this.GetPosition().GetY() - 1);
          break;
        case 'D':
          newPosition = new Point(this.GetPosition().GetX(), this.GetPosition().GetY() + 1);
          break;
        case 'L':
          newPosition = new Point(this.GetPosition().GetX() - 1, this.GetPosition().GetY());
          break;
        case 'R':
          newPosition = new Point(this.GetPosition().GetX() + 1, this.GetPosition().GetY());
          break;
        default:
          break;
      }
      Organism other = world.GetOrganismAt(newPosition);
      if (other == null) {
        this.world.MoveOrganism(this, newPosition);
      } else { // Collision
        other.SetCanAction(false);
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
