import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GameManager {
  private World world;
  private boolean quit;

  private JFrame f;
  private JButton[][] buttons;
  private JTextArea gameInfo;

  public GameManager(World world) {
    this.quit = false;
    this.world = world;
    f = new JFrame("Simulation - Filip Pawlicki 198371");
  }
  private void PrintTheWorld() {
    f.setLayout(new BorderLayout());

    // Create a panel for the buttons
    JPanel buttonPanel = new JPanel();
    buttonPanel.setLayout(new FlowLayout());

    // Create the buttons and add them to the panel
    JButton saveButton = new JButton("Save");
    buttonPanel.add(saveButton);

    JButton quitButton = new JButton("Quit");
    buttonPanel.add(quitButton);

    JButton superpowerButton = new JButton("Use Superpower");
    buttonPanel.add(superpowerButton);

    // Add the panel to the top of the frame
    f.add(buttonPanel, BorderLayout.NORTH);

    // Create a text area for the game information
    gameInfo = new JTextArea();
    gameInfo.setColumns(25);
    gameInfo.setEditable(true); // Make the text area modifiable

    // Add the text area to the right side of the frame
    f.add(new JScrollPane(gameInfo), BorderLayout.EAST);

    // Create a panel for the game grid
    JPanel gridPanel = new JPanel();
    gridPanel.setLayout(new GridLayout(world.GetWidth(), world.GetHeight()));
    buttons = new JButton[world.GetWidth()][world.GetHeight()];

    for (int x = 0; x < world.GetWidth(); x++) {
      for (int y = 0; y < world.GetHeight(); y++) {
        JButton button = new JButton();
        Organism organism = world.GetOrganism(x, y);
        if (organism != null) {
          button.setText(String.valueOf(organism.GetSymbol()));
          button.setBackground(organism.GetColor());
        }
        int finalX = x;
        int finalY = y;
        button.addActionListener(new ActionListener() {
          @Override
          public void actionPerformed(ActionEvent e) {
            JOptionPane.showMessageDialog(f, "Clicked: " + finalX + " , " + finalY);
          }
        });
        buttons[x][y] = button;
        gridPanel.add(button);
      }
    }

    // Add the grid panel to the center of the frame
    f.add(gridPanel, BorderLayout.CENTER);

    f.pack();
    f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    f.setVisible(true);
  }

  public void GameLoop() {
//    while (!quit) {
//      // Game logic
//    }
    this.PrintTheWorld();
  }

}
