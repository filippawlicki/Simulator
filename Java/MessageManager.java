import java.util.Vector;

public class MessageManager {
  private final Vector<String> messages;

  public MessageManager() {
    messages = new Vector<>();
  }

  public final void AddDeathMessage(String dead, String killer) {
    messages.add(dead + " was killed by " + killer + ".");
  }

  public final void AddReproductionMessage(String parent1, String parent2, String child) {
    messages.add(parent1 + " and " + parent2 + " reproduced. " + child + " was born.");
  }

  public final void AddPlantEatingMessage(String eater, String eaten) {
    messages.add(eater + " ate " + eaten + ".");
  }

  public final void AddAttackRepelledMessage(String attacker, String defender) {
    messages.add(attacker + " attacked " + defender + " but was repelled.");
  }

  public final void AddAttackRunawayMessage(String attacker, String defender) {
    messages.add(attacker + " attacked " + defender + " but, " + defender + " ran away.");
  }

  public final Vector<String> GetMessages() {
    return messages;
  }

  public final void ClearMessages() {
    messages.clear();
  }


}
