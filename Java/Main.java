import javax.swing.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;

class Main {

  private void AddStartingOrganisms(World world) {
    world.AddOrganism(new Grass(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Grass(world, world.GetRandomFreePosition()));
    world.AddOrganism(new SowThistle(world, world.GetRandomFreePosition()));
    world.AddOrganism(new SowThistle(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Guarana(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Guarana(world, world.GetRandomFreePosition()));
    world.AddOrganism(new NightshadeBerries(world, world.GetRandomFreePosition()));
    world.AddOrganism(new NightshadeBerries(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Hogweed(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Hogweed(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Wolf(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Wolf(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Sheep(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Sheep(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Fox(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Fox(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Turtle(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Turtle(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Antelope(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Antelope(world, world.GetRandomFreePosition()));
    world.AddOrganism(new CyberSheep(world, world.GetRandomFreePosition()));
    world.AddOrganism(new CyberSheep(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Human(world, world.GetRandomFreePosition()));
  }

  private void NewGame() {
    JFrame f=new JFrame();
    f.setSize(400,500);
    f.setLayout(null);
    f.setVisible(true);

    JTextField widthTextField = new JTextField();
    widthTextField.setBounds(130, 100, 200, 40);
    f.add(widthTextField);

    JLabel widthLabel = new JLabel("Width of the board: ");
    widthLabel.setBounds(10, 100, 200, 40);
    f.add(widthLabel);

    JTextField heightTextField = new JTextField();
    heightTextField.setBounds(130, 150, 200, 40);
    f.add(heightTextField);

    JLabel heightLabel = new JLabel("Height of the board: ");
    heightLabel.setBounds(10, 150, 200, 40);
    f.add(heightLabel);

    JButton startButton = new JButton("Start");
    startButton.setBounds(130, 200, 100, 40);
    f.add(startButton);

    startButton.addActionListener(e -> {
      try {
        Integer.parseInt(widthTextField.getText());
        Integer.parseInt(heightTextField.getText());
      } catch (NumberFormatException ex) {
        JOptionPane.showMessageDialog(f, "Width and height of the board should be numbers");
        return;
      }

      if(widthTextField.getText().isEmpty() || heightTextField.getText().isEmpty()) {
        JOptionPane.showMessageDialog(f, "Please enter the width and height of the board");
        return;
      } else if(Integer.parseInt(widthTextField.getText()) < 5 || Integer.parseInt(heightTextField.getText()) < 5) {
        JOptionPane.showMessageDialog(f, "Width and height of the board should be greater than 5");
        return;
      }

      int width = Integer.parseInt(widthTextField.getText());
      int height = Integer.parseInt(heightTextField.getText());
      f.setVisible(false);
      World world = World.GetInstance(width, height);
      this.AddStartingOrganisms(world);
      GameManager gameManager = new GameManager(world);
      gameManager.GameLoop();
    });

  }

  private void LoadGame(JFrame f) {
    JFileChooser fileChooser = new JFileChooser();
    fileChooser.setCurrentDirectory(new File(Constants.SAVES_DIRECTORY));
    File selectedFile;

    int result = fileChooser.showOpenDialog(f);
    if (result == JFileChooser.APPROVE_OPTION) {
      selectedFile = fileChooser.getSelectedFile();
    } else {
      JOptionPane.showMessageDialog(f, "No file selected.");
      System.exit(0);
      return;
    }
    Path filePath = Path.of(selectedFile.getAbsolutePath());

    try (BufferedReader reader = Files.newBufferedReader(filePath, StandardCharsets.UTF_8)) {
      String line = reader.readLine();
      String[] dimensions = line.split(" ");
      int width = Integer.parseInt(dimensions[0]);
      int height = Integer.parseInt(dimensions[1]);

      World world = World.GetInstance(width, height);

      line = reader.readLine();
      int organismCount = Integer.parseInt(line);

      for (int i = 0; i < organismCount; i++) {
        line = reader.readLine();
        String[] organismData = line.split(" ");
        int x = Integer.parseInt(organismData[0]);
        int y = Integer.parseInt(organismData[1]);
        char symbol = organismData[2].charAt(0);
        int strength = Integer.parseInt(organismData[3]);

        switch (symbol) {
          case 'W':
            world.AddOrganism(new Wolf(world, new Point(x, y)));
            break;
          case 'T':
            world.AddOrganism(new Turtle(world, new Point(x, y)));
            break;
          case 'E':
            world.AddOrganism(new Sheep(world, new Point(x, y)));
            break;
          case 'F':
            world.AddOrganism(new Fox(world, new Point(x, y)));
            break;
          case 'A':
            world.AddOrganism(new Antelope(world, new Point(x, y)));
            break;
          case 'C':
            world.AddOrganism(new CyberSheep(world, new Point(x, y)));
            break;
          case 'P':
            world.AddOrganism(new Human(world, new Point(x, y)));
            break;
          case 'G':
            world.AddOrganism(new Grass(world, new Point(x, y)));
            break;
          case 'S':
            world.AddOrganism(new SowThistle(world, new Point(x, y)));
            break;
          case 'U':
            world.AddOrganism(new Guarana(world, new Point(x, y)));
            break;
          case 'H':
            world.AddOrganism(new Hogweed(world, new Point(x, y)));
            break;
          case 'N':
            world.AddOrganism(new NightshadeBerries(world, new Point(x, y)));
            break;
        }
        world.GetOrganismAt(x, y).SetStrength(strength);

        if (symbol == 'P' && organismData.length > 4) {
          int superPowerCooldown = Integer.parseInt(organismData[4]);
          int superPowerDuration = Integer.parseInt(organismData[5]);
          world.SetHumanSuperPowerCooldown(superPowerCooldown);
          world.SetHumanSuperPowerDuration(superPowerDuration);
        }
      }

      GameManager gameManager = new GameManager(world);
      gameManager.GameLoop();

    } catch (IOException e) {
      JOptionPane.showMessageDialog(f, "Error loading game: " + e.getMessage());
    }
  }
  private void Menu() {
    JFrame f=new JFrame();

    JButton newGameButton=new JButton("New Game");
    newGameButton.setBounds(130,100,100, 40);
    f.add(newGameButton);

    JButton loadGameButton=new JButton("Load Game");
    loadGameButton.setBounds(130,150,100, 40);
    f.add(loadGameButton);

    JButton quitButton=new JButton("Quit");
    quitButton.setBounds(130,200,100, 40);
    f.add(quitButton);

    f.setSize(400,500);
    f.setLayout(null);
    f.setVisible(true);

    newGameButton.addActionListener(e -> {
      f.setVisible(false);
      this.NewGame();
    });

    loadGameButton.addActionListener(e -> {
      f.setVisible(false);
      LoadGame(f);
    });

    quitButton.addActionListener(e -> System.exit(0));
  }
  public static void main(String[] args) {
    Main mainObject = new Main();
    mainObject.Menu();
  }
}
