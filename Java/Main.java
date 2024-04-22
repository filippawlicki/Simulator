import javax.swing.*;

public class Main {

  private void AddStartingOrganisms(World world) {
    world.AddOrganism(new Grass(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Grass(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Wolf(world, world.GetRandomFreePosition()));
    world.AddOrganism(new Wolf(world, world.GetRandomFreePosition()));
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
    });

    quitButton.addActionListener(e -> {
      System.exit(0);
    });
  }
  public static void main(String[] args) {
    Main mainObject = new Main();
    mainObject.Menu();
  }
}
