public class Guarana extends Plant {
  public Guarana(World world, Point position) {
    super(world, position, Constants.GUARANA_SYMBOL, Constants.GUARANA_STRENGTH, Constants.GUARANA_COLOR, Constants.GUARANA_NAME);
  }

  @Override
  public final Organism Clone(Point position) {
    return new Guarana(this.world, position);
  }

  @Override
  public final boolean Collision(Organism other) {
    other.SetStrength(other.GetStrength() + 3);
    this.Die();
    this.world.messageManager.AddPlantEatingMessage(other.GetName(), this.GetName());
    return false;
  }
}
