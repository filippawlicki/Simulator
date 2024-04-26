import java.util.Vector;
import java.util.Collections;
public class Fox extends Animal {
  public Fox(World world, Point position) {
    super(world, position, Constants.FOX_SYMBOL, Constants.FOX_STRENGTH, Constants.FOX_INITIATIVE, Constants.FOX_COLOR, Constants.FOX_NAME, Constants.ANIMAL_RANGE);
  }

  @Override
  public final Organism Clone(Point position) {
    return new Fox(this.world, position);
  }

  @Override
  public final void Action() {
    if (CanAction()) {
      Vector<Point> possibleMoves = this.world.GetPositionsAround(this.GetPosition());
      Collections.shuffle(possibleMoves);
      Point newPosition = null;
      for (Point move : possibleMoves) {
        Organism other = world.GetOrganismAt(move);
        if (other == null || other.GetStrength() < this.GetStrength()) {
          newPosition = move;
          break;
        }
      }
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
}
