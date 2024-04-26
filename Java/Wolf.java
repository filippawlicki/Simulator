public class Wolf extends Animal {
  public Wolf(World world, Point position) {
    super(world, position, Constants.WOLF_SYMBOL, Constants.WOLF_STRENGTH, Constants.WOLF_INITIATIVE, Constants.WOLF_COLOR, Constants.WOLF_NAME, Constants.ANIMAL_RANGE);
  }

  @Override
  public final Organism Clone(Point position) {
    return new Wolf(this.world, position);
  }
}
