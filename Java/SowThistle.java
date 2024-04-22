public class SowThistle extends Plant {
  public SowThistle(World world, Point position) {
    super(world, position, Constants.SOW_THISTLE_SYMBOL, Constants.SOW_THISTLE_STRENGTH, Constants.SOW_THISTLE_COLOR, Constants.SOW_THISTLE_NAME);
  }

  @Override
  public Organism Clone(Point position) {
    return new SowThistle(this.world, position);
  }

  @Override
  public void Action() {
    for (int i = 0; i < 3; i++) {
      super.Action();
    }
  }
}
