public class Grass extends Plant {
  public Grass(World world, Point position) {
    super(world, position, Constants.SYMBOL_GRASS, Constants.STRENGTH_GRASS, Constants.COLOR_GRASS, Constants.NAME_GRASS);
  }

  @Override
  public Organism Clone(Point position) {
    return new Grass(this.world, position);
  }
}
