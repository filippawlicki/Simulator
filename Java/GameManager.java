import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.Vector;

class GameManager {
  private final World world;
  private char input;
  private final JFrame f;
  private JLabel gameInfo;

  public GameManager(World world) {
    this.world = world;
    f = new JFrame("Simulation - Filip Pawlicki 198371");
  }

  private void SetHumanInfo(JLabel humanInfo) {
    StringBuilder info = new StringBuilder();
    switch(input) {
      case 'U':
        info.append("Up move selected");
        break;
      case 'D':
        info.append("Down move selected");
        break;
      case 'R':
        info.append("Right move selected");
        break;
      case 'L':
        info.append("Left move selected");
        break;
      default:
        info.append("No move selected");
        break;
    }
    info.append("<br>");
    info.append("Superpower: ");
    if(world.GetHumanSuperPowerDuration() > 0) {
      info.append("Active - ").append(world.GetHumanSuperPowerDuration()).append(" turns left");
    } else if (world.GetHumanSuperPowerCooldown() == 0) {
      info.append("Ready");
    } else {
      info.append("Cooldown - ").append(world.GetHumanSuperPowerCooldown()).append(" turns left");
    }
    humanInfo.setText("<html>" + info + "</html>"); // Set the text of the JLabel
  }

  private void SaveGame() {
    String fileName = JOptionPane.showInputDialog(f, "Enter the file name:");
    if (fileName == null || fileName.trim().isEmpty()) {
      JOptionPane.showMessageDialog(f, "Invalid file name.");
      return;
    }

    Path filePath = Paths.get(Constants.SAVES_DIRECTORY, fileName);
    if (Files.exists(filePath)) {
      int result = JOptionPane.showConfirmDialog(f, "File already exists. Do you want to overwrite it?", "Confirm overwrite", JOptionPane.YES_NO_OPTION);
      if (result != JOptionPane.YES_OPTION) {
        return;
      }
    }

    try (BufferedWriter writer = Files.newBufferedWriter(filePath, StandardCharsets.UTF_8, StandardOpenOption.CREATE)) {
      writer.write(world.GetWidth() + " " + world.GetHeight());
      writer.newLine();

      Vector<Organism> organisms = world.GetOrganisms();
      writer.write(String.valueOf(organisms.size()));
      writer.newLine();

      for (Organism organism : organisms) {
        writer.write(organism.GetPosition().GetX() + " " + organism.GetPosition().GetY() + " " + organism.GetSymbol() + " " + organism.GetStrength());
        if (organism instanceof Human) {
          writer.write(" " + world.GetHumanSuperPowerCooldown() + " " + world.GetHumanSuperPowerDuration());
        }
        writer.newLine();
      }

      JOptionPane.showMessageDialog(f, "Game saved successfully.");
    } catch (IOException e) {
      JOptionPane.showMessageDialog(f, "Error saving game: " + e.getMessage());
    }
  }

  private void UpdateGameInfo(JLabel gameInfo) {
    StringBuilder info = new StringBuilder();
    Vector<String> messages = world.messageManager.GetMessages();
    if(messages != null) {
      for (String message : messages) {
        info.append(message).append("<br>"); // Add the message to the string builder
      }
    }
    gameInfo.setText("<html>" + info + "</html>"); // Set the text of the JLabel
  }

  private void AddNewOrganism(int x, int y) {
    // Define the organisms
    String[] organisms = {"Wolf", "Sheep", "Fox", "Turtle", "Antelope", "CyberSheep", "Sow Thistle", "Guarana", "Hogweed", "Nightshade Berries", "Grass"};

    // Create a JComboBox with the organisms array
    JComboBox<String> organismBox = new JComboBox<>(organisms);

    // Create a panel to hold the JComboBox
    JPanel panel = new JPanel(new GridLayout(0, 1));
    panel.add(new JLabel("Select an organism:"));
    panel.add(organismBox);

    // Show the dialog
    int result = JOptionPane.showConfirmDialog(f, panel, "Add Organism", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

    // If the user clicked OK, add the selected organism
    if (result == JOptionPane.OK_OPTION) {
      String selectedOrganism = (String) organismBox.getSelectedItem();
      switch (selectedOrganism) {
        case "Wolf":
          world.AddOrganism(new Wolf(world, new Point(x, y)));
          break;
        case "Sheep":
          world.AddOrganism(new Sheep(world, new Point(x, y)));
          break;
        case "Fox":
          world.AddOrganism(new Fox(world, new Point(x, y)));
          break;
        case "Turtle":
          world.AddOrganism(new Turtle(world, new Point(x, y)));
          break;
        case "Antelope":
          world.AddOrganism(new Antelope(world, new Point(x, y)));
          break;
        case "CyberSheep":
          world.AddOrganism(new CyberSheep(world, new Point(x, y)));
          break;
        case "Sow Thistle":
          world.AddOrganism(new SowThistle(world, new Point(x, y)));
          break;
        case "Guarana":
          world.AddOrganism(new Guarana(world, new Point(x, y)));
          break;
        case "Hogweed":
          world.AddOrganism(new Hogweed(world, new Point(x, y)));
          break;
        case "Nightshade Berries":
          world.AddOrganism(new NightshadeBerries(world, new Point(x, y)));
          break;
        case "Grass":
          world.AddOrganism(new Grass(world, new Point(x, y)));
          break;
        case null, default:
          break;
      }
    }
  }

  private void UpdateGameGrid(JPanel gridPanel) {
    gridPanel.removeAll(); // Remove all existing buttons

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
        button.addActionListener(e -> {
          if(world.GetOrganismAt(finalX, finalY) == null) {
            AddNewOrganism(finalX, finalY);
            UpdateGameGrid(gridPanel); // Refresh the game grid after clicking the button
          } else {
            JOptionPane.showMessageDialog(f, "You cannot place an organism on an occupied field!");
          }
        });
        gridPanel.add(button);
      }
    }

    gridPanel.revalidate();
    gridPanel.repaint();
  }
  public final void GameLoop() {
    f.setLayout(new BorderLayout());

    // Create a panel for the buttons
    JPanel buttonPanel = new JPanel();
    buttonPanel.setLayout(new FlowLayout());

    JLabel humanInfo = new JLabel();
    humanInfo.setPreferredSize(new Dimension(300, 50));
    SetHumanInfo(humanInfo);
    buttonPanel.add(humanInfo);

    // Define the action for the UP key
    f.getRootPane().getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(KeyStroke.getKeyStroke(KeyEvent.VK_UP, 0), "UP");
    f.getRootPane().getActionMap().put("UP", new AbstractAction() {
      @Override
      public void actionPerformed(ActionEvent e) {
        input = 'U';
        world.SetHumanInput(input);
        SetHumanInfo(humanInfo);
      }
    });

    // Define the action for the DOWN key
    f.getRootPane().getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(KeyStroke.getKeyStroke(KeyEvent.VK_DOWN, 0), "DOWN");
    f.getRootPane().getActionMap().put("DOWN", new AbstractAction() {
      @Override
      public void actionPerformed(ActionEvent e) {
        input = 'D';
        world.SetHumanInput(input);
        SetHumanInfo(humanInfo);
      }
    });

    // Define the action for the LEFT key
    f.getRootPane().getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, 0), "LEFT");
    f.getRootPane().getActionMap().put("LEFT", new AbstractAction() {
      @Override
      public void actionPerformed(ActionEvent e) {
        input = 'L';
        world.SetHumanInput(input);
        SetHumanInfo(humanInfo);
      }
    });

    // Define the action for the RIGHT key
    f.getRootPane().getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, 0), "RIGHT");
    f.getRootPane().getActionMap().put("RIGHT", new AbstractAction() {
      @Override
      public void actionPerformed(ActionEvent e) {
        input = 'R';
        world.SetHumanInput(input);
        SetHumanInfo(humanInfo);
      }
    });

    // Create the buttons and add them to the panel
    JButton saveButton = new JButton("Save");
    buttonPanel.add(saveButton);
    saveButton.addActionListener(e -> SaveGame());

    JButton quitButton = new JButton("Quit");
    buttonPanel.add(quitButton);
    quitButton.addActionListener(e -> System.exit(0));

    JButton superpowerButton = new JButton("Use Superpower");
    buttonPanel.add(superpowerButton);
    superpowerButton.addActionListener(e -> {
      if(world.GetHumanSuperPowerCooldown() == 0) {
        world.SetHumanSuperPowerDuration(Constants.HUMAN_SUPERPOWER_DURATION);
        world.SetHumanSuperPowerCooldown(Constants.HUMAN_SUPERPOWER_COOLDOWN);
        SetHumanInfo(humanInfo);
      }
    });

    // Add the panel to the top of the frame
    f.add(buttonPanel, BorderLayout.NORTH);

    // Create a text area for the game information
    gameInfo = new JLabel();
    gameInfo.setPreferredSize(new Dimension(200, 500)); // Set the preferred size
    UpdateGameInfo(gameInfo);


    // Add the text area to the right side of the frame
    f.add(new JScrollPane(gameInfo), BorderLayout.EAST);

    // Create a panel for the game grid
    JPanel gridPanel = new JPanel();
    gridPanel.setLayout(new GridLayout(world.GetHeight(), world.GetWidth()));

    UpdateGameGrid(gridPanel);

    // Add the grid panel to the center of the frame
    f.add(gridPanel, BorderLayout.CENTER);

    JButton nextTurnButton = new JButton("Next Turn");
    buttonPanel.add(nextTurnButton);
    nextTurnButton.addActionListener(e -> {
      if(world.IsHumanMoveLegal(input)) {
        world.MakeTurn();
        UpdateGameGrid(gridPanel);
        SetHumanInfo(humanInfo);
        UpdateGameInfo(gameInfo);
        if(world.IsHumanDead()) {
          JOptionPane.showMessageDialog(f, "Game over\n" + world.GetHumanCauseOfDeath());
          System.exit(0);
        }
      } else {
        JOptionPane.showMessageDialog(f, "Invalid move");
      }
    });

    f.pack();
    f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    f.setVisible(true);
  }
}
