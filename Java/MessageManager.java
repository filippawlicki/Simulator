import java.util.Vector;

public class MessageManager {
  private Vector<String> messages;

  public MessageManager() {
    messages = new Vector<>();
  }

  public void AddDeathMessage(String dead, String killer) {
    messages.add(dead + " was killed by " + killer + ".");
  }

  public void AddReproductionMessage(String parent1, String parent2, String child) {
    messages.add(parent1 + " and " + parent2 + " reproduced. " + child + " was born.");
  }

  public void AddPlantEatingMessage(String eater, String eaten) {
    messages.add(eater + " ate " + eaten + ".");
  }

  public void AddAttackRepelledMessage(String attacker, String defender) {
    messages.add(attacker + " attacked " + defender + " but was repelled.");
  }

  public void AddAttackRunawayMessage(String attacker, String defender) {
    messages.add(attacker + " attacked " + defender + " but, " + defender + " ran away.");
  }

  public Vector<String> GetMessages() {
    return messages;
  }

  public void ClearMessages() {
    messages.clear();
  }


}
