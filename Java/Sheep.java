public class Sheep extends Animal {
  public Sheep(World world, Point position) {
    super(world, position, Constants.SHEEP_SYMBOL, Constants.SHEEP_STRENGTH, Constants.SHEEP_INITIATIVE, Constants.SHEEP_COLOR, Constants.SHEEP_NAME, Constants.ANIMAL_RANGE);
  }

  @Override
  public final Organism Clone(Point position) {
    return new Sheep(this.world, position);
  }
}
