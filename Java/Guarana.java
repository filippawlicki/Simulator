public class Guarana extends Plant {
  public Guarana(World world, Point position) {
    super(world, position, Constants.GUARANA_SYMBOL, Constants.GUARANA_STRENGTH, Constants.GUARANA_COLOR, Constants.GUARANA_NAME);
  }

  @Override
  public Organism Clone(Point position) {
    return new Guarana(this.world, position);
  }

  @Override
  public boolean Collision(Organism other) {
    other.SetStrength(other.GetStrength() + 3);
    this.Die();
    this.world.messageManager.AddPlantEatingMessage(this.GetName(), other.GetName());
    return false;
  }
}
