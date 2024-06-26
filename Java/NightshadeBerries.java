public class NightshadeBerries extends Plant {
  public NightshadeBerries(World world, Point position) {
    super(world, position, Constants.NIGHTSHADE_BERRIES_SYMBOL, Constants.NIGHTSHADE_BERRIES_STRENGTH, Constants.NIGHTSHADE_BERRIES_COLOR, Constants.NIGHTSHADE_BERRIES_NAME);
  }

  @Override
  public final Organism Clone(Point position) {
    return new NightshadeBerries(this.world, position);
  }

  @Override
  public final boolean Collision(Organism other) {
    this.world.messageManager.AddPlantEatingMessage(other.GetName(), this.GetName());
    this.world.messageManager.AddDeathMessage(other.GetName(), this.GetName());
    this.Die();
    other.Die();
    return false;
  }
}
