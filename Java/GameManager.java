import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Vector;

public class GameManager {
  private World world;
  private boolean quit;
  private char input;

  private JFrame f;
  private JButton[][] buttons;
  private JTextArea gameInfo;

  public GameManager(World world) {
    this.quit = false;
    this.world = world;
    f = new JFrame("Simulation - Filip Pawlicki 198371");
  }

  private void SetHumanInfo(JTextArea humanInfo) {
    humanInfo.setText(""); // Clear the text area
    switch(input) {
      case 'U':
        humanInfo.append("Up move selected");
        break;
      case 'D':
        humanInfo.append("Down move selected");
        break;
      case 'R':
        humanInfo.append("Right move selected");
        break;
      case 'L':
        humanInfo.append("Left move selected");
        break;
      default:
        humanInfo.append("No move selected");
        break;
    }
    humanInfo.append("\n");
    humanInfo.append("Superpower: ");
    if(world.GetHumanSuperPowerDuration() > 0) {
      humanInfo.append("Active - " + world.GetHumanSuperPowerDuration() + " turns left");
    } else if (world.GetHumanSuperPowerCooldown() == 0) {
      humanInfo.append("Ready");
    } else {
      humanInfo.append("Cooldown - " + world.GetHumanSuperPowerCooldown() + " turns left");
    }
  }

  private void SaveGame() {
    // Save the game
  }
  private void PrintTheWorld() {
    f.setLayout(new BorderLayout());

    // Create a panel for the buttons
    JPanel buttonPanel = new JPanel();
    buttonPanel.setLayout(new FlowLayout());

    f.addKeyListener(new KeyAdapter() { // Add a key listener to the frame to get the input
      @Override
      public void keyPressed(KeyEvent e) {
        switch(e.getKeyCode()) {
          case KeyEvent.VK_UP:
            input = 'U';
            world.SetHumanInput(input);
            f.revalidate();
            f.repaint();
            break;
          case KeyEvent.VK_DOWN:
            input = 'D';
            world.SetHumanInput(input);
            f.revalidate();
            f.repaint();
            break;
          case KeyEvent.VK_LEFT:
            input = 'L';
            world.SetHumanInput(input);
            f.revalidate();
            f.repaint();
            break;
          case KeyEvent.VK_RIGHT:
            input = 'R';
            world.SetHumanInput(input);
            f.revalidate();
            f.repaint();
            break;
          default:
            break;
        }
      }
    });

    // Create the buttons and add them to the panel
    JButton saveButton = new JButton("Save");
    buttonPanel.add(saveButton);
    saveButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        SaveGame();
      }
    });

    JButton quitButton = new JButton("Quit");
    buttonPanel.add(quitButton);
    quitButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        System.exit(0);
      }
    });

    JButton superpowerButton = new JButton("Use Superpower");
    buttonPanel.add(superpowerButton);
    superpowerButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        if(world.GetHumanSuperPowerCooldown() == 0) {
          world.SetHumanSuperPowerDuration(Constants.HUMAN_SUPERPOWER_DURATION);
          world.SetHumanSuperPowerCooldown(Constants.HUMAN_SUPERPOWER_COOLDOWN);
          f.revalidate();
          f.repaint();
        }
      }
    });

    JButton nextTurnButton = new JButton("Next Turn");
    buttonPanel.add(nextTurnButton);
    nextTurnButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        if(world.IsHumanMoveLegal(input)) {
          world.MakeTurn();
          f.revalidate();
          f.repaint();
        } else {
          JOptionPane.showMessageDialog(f, "Invalid move");
        }
      }
    });

    JTextArea humanInfo = new JTextArea();
    humanInfo.setRows(2);
    humanInfo.setColumns(25);
    humanInfo.setEditable(false);
    SetHumanInfo(humanInfo);
    buttonPanel.add(humanInfo);

    // Add the panel to the top of the frame
    f.add(buttonPanel, BorderLayout.NORTH);

    // Create a text area for the game information
    gameInfo = new JTextArea();
    gameInfo.setColumns(25);
    gameInfo.setEditable(false); // Make the text area not modifiable
    Vector<String> messages = world.messageManager.GetMessages();
    if(messages != null) {
      for (String message : messages) {
        gameInfo.append(message + "\n"); // Add the message to the text area
      }
    }


    // Add the text area to the right side of the frame
    f.add(new JScrollPane(gameInfo), BorderLayout.EAST);

    // Create a panel for the game grid
    JPanel gridPanel = new JPanel();
    gridPanel.setLayout(new GridLayout(world.GetHeight(), world.GetWidth()));
    buttons = new JButton[world.GetWidth()][world.GetHeight()];

    for (int y = 0; y < world.GetHeight(); y++) {
      for (int x = 0; x < world.GetWidth(); x++) {
        JButton button = new JButton();
        Organism organism = world.GetOrganismAt(x, y);
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
