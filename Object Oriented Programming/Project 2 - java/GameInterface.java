package project2Java;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class GameInterface implements ActionListener, KeyListener {
    private Toolkit toolkit;
    private Dimension dimension;
    private JFrame jFrame;
    private JMenuBar menuBar;
    private JMenu menu;
    private JMenuItem newGame, load, save, exit;
    private boardGraphics boardGraphics = null;
    private EventGraphics eventGraphics = null;
    private Signs signs = null;
    private JPanel mainPanel;
    private final int SPACE;
    private World world;

    public GameInterface(String title) {
        toolkit = Toolkit.getDefaultToolkit();
        dimension = toolkit.getScreenSize();
        SPACE = dimension.height / 100;

        jFrame = new JFrame(title);
        jFrame.setBounds((dimension.width - 800) / 2, (dimension.height - 600) / 2, 1000, 800);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JMenuBar menuBar = new JMenuBar();
        menu = new JMenu("OPTIONS");
        menu.setBackground(new Color(0, 100, 0));
        menu.setForeground(Color.WHITE);
        menu.setOpaque(true);
        menuBar.setLayout(new GridBagLayout());
        menuBar.setBorder(BorderFactory.createLineBorder(Color.WHITE, 0));

        newGame = new JMenuItem("New game");
        load = new JMenuItem("Load");
        save = new JMenuItem("Save");
        exit = new JMenuItem("Exit");
        newGame.addActionListener(this);
        newGame.setForeground(new Color(0, 120, 0));
        load.addActionListener(this);
        load.setForeground(new Color(0, 120, 0));
        save.addActionListener(this);
        save.setForeground(new Color(0, 120, 0));
        exit.addActionListener(this);
        exit.setForeground(new Color(0, 120, 0));
        menu.add(newGame);
        menu.add(load);
        menu.add(save);
        menu.add(exit);
        menuBar.add(menu);
        jFrame.setJMenuBar(menuBar);
        jFrame.setLayout(new CardLayout());
        menuBar.setBackground(new Color(0, 120, 0));


        mainPanel = new JPanel();
        mainPanel.setBackground(new Color(0, 120, 0));
        mainPanel.setLayout(null);


        jFrame.addKeyListener(this);
        jFrame.add(mainPanel);
        jFrame.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == newGame) {
            Event.ClearEvent();
            int sizeX = Integer.parseInt(JOptionPane.showInputDialog(jFrame,
                    "Set world Y size", "10"));
            int sizeY = Integer.parseInt(JOptionPane.showInputDialog(jFrame,
                    "Set world X size", "10"));

            world = new World(sizeX, sizeY, this);
            world.generateWorld();
            if (boardGraphics != null){
                mainPanel.remove(boardGraphics);
            }
            if (eventGraphics != null){
                mainPanel.remove(eventGraphics);
            }
            if (signs != null){
                mainPanel.remove(signs);
            }
            startGame();
        }
        if (e.getSource() == load) {
            Event.ClearEvent();
            String nameOfFile = JOptionPane.showInputDialog(jFrame, "From which file (only name, no extension)?", "game");
            world = World.load(nameOfFile);
            world.setGameInterface(this);
            boardGraphics = new boardGraphics(world);
            eventGraphics = new EventGraphics();
            signs = new Signs();
            if (boardGraphics != null){
                mainPanel.remove(boardGraphics);
            }
            if (eventGraphics != null){
                mainPanel.remove(eventGraphics);
            }
            if (signs != null){
                mainPanel.remove(signs);
            }
            startGame();
        }
        if (e.getSource() == save) {
            String nameOfFile = JOptionPane.showInputDialog(jFrame, "To which file (only name, no extension)", "game");
            world.save(nameOfFile);
            Event.addEvent("Game saved");
            eventGraphics.refreshEvents();
        }
        if (e.getSource() == exit) {
            jFrame.dispose();
        }
    }

    @Override
    public void keyPressed(KeyEvent e) {
        if (world != null && world.isPaused()) {
            int keyCode = e.getKeyCode();
            if (keyCode == KeyEvent.VK_SPACE) {

            } else if (world.getIsPlayerAlive()) {
                if (keyCode == KeyEvent.VK_UP) {
                    world.getPlayer().setMoveDirection(Organism.Direction.UP);
                } else if (keyCode == KeyEvent.VK_DOWN) {
                    world.getPlayer().setMoveDirection(Organism.Direction.DOWN);
                } else if (keyCode == KeyEvent.VK_LEFT) {
                    world.getPlayer().setMoveDirection(Organism.Direction.LEFT);
                } else if (keyCode == KeyEvent.VK_RIGHT) {
                    world.getPlayer().setMoveDirection(Organism.Direction.RIGHT);
                } else if (keyCode == KeyEvent.VK_X) {
                    SpecialSkill tmpSpecialSkill = world.getPlayer().getSpecialSkill();
                    if (tmpSpecialSkill.getCanBeActivated()) {
                        tmpSpecialSkill.activateSpecialSkill();
                        Event.addEvent("Special skill 'Immoratlity' activated (turns to end: " + tmpSpecialSkill.getSpecialSkillDuration() + ")");

                    } else if (tmpSpecialSkill.getIsSpecialSkillActive()) {
                        Event.addEvent("Special skill 'Immoratlity' is active (turns to end: " + tmpSpecialSkill.getSpecialSkillDuration() + ")");
                        eventGraphics.refreshEvents();
                        return;
                    } else {
                        Event.addEvent("Special skill 'Immoratlity' can be activated in " + tmpSpecialSkill.getSpecialSkillDuration() + " turns)");
                        eventGraphics.refreshEvents();
                        return;
                    }
                } else {
                    eventGraphics.refreshEvents();
                    return;
                }
            } else if (!world.getIsPlayerAlive() && (keyCode == KeyEvent.VK_UP ||
                    keyCode == KeyEvent.VK_DOWN || keyCode == KeyEvent.VK_LEFT ||
                    keyCode == KeyEvent.VK_RIGHT || keyCode == KeyEvent.VK_P)) {
                Event.addEvent("Player died - you can only watch");
                eventGraphics.refreshEvents();
                return;
            } else {
                eventGraphics.refreshEvents();
                return;
            }
            Event.ClearEvent();
            world.setPause(false);
            world.doTurn();
            refreshWorld();
            world.setPause(true);
        }
    }

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyReleased(KeyEvent e) {
    }

    private class boardGraphics extends JPanel {
        private final int sizeX;
        private final int sizeY;
        private BoardFields[][] boardFields;
        private World WORLD;

        public boardGraphics(World world) {
            super();
            setBounds(mainPanel.getX() + SPACE, 80+mainPanel.getY() + SPACE,
                    mainPanel.getHeight() * 5 / 6 + 10 * SPACE, mainPanel.getHeight() * 5 / 6 + 2 * SPACE);
            WORLD = world;
            this.sizeX = world.getSizeX();
            this.sizeY = world.getSizeY();

            boardFields = new BoardFields[sizeY][sizeX];
            for (int i = 0; i < sizeY; i++) {
                for (int j = 0; j < sizeX; j++) {
                    boardFields[i][j] = new BoardFields(j, i);
                    boardFields[i][j].addActionListener(new ActionListener() {
                        @Override
                        public void actionPerformed(ActionEvent e) {
                            if (e.getSource() instanceof BoardFields) {
                                BoardFields tmpPole = (BoardFields) e.getSource();
                                if (tmpPole.isEmpty == true) {
                                    OrganismList organismList = new OrganismList
                                            (tmpPole.getX() + jFrame.getX(),
                                                    tmpPole.getY() + jFrame.getY(),
                                                    new Position(tmpPole.getPositionX(), tmpPole.getPositionY()));
                                }
                            }
                        }
                    });
                }
            }

            for (int i = 0; i < sizeY; i++) {
                for (int j = 0; j < sizeX; j++) {
                    this.add(boardFields[i][j]);
                }
            }
            this.setLayout(new GridLayout(sizeY, sizeX));

        }

        private class BoardFields extends JButton {
            private boolean isEmpty;
            private Color color;
            private final int positionX;
            private final int positionY;

            public BoardFields(int X, int Y) {
                super();
                color = Color.WHITE;
                setBackground(color);
                isEmpty = true;
                positionX = X;
                positionY = Y;
            }

            public boolean isEmpty() {
                return isEmpty;
            }

            public void setEmpty(boolean empty) {
                isEmpty = empty;
            }


            public Color getColor() {
                return color;
            }

            public void setColor(Color color) {
                this.color = color;
                setBackground(color);
            }

            public int getPositionX() {
                return positionX;
            }

            public int getPositionY() {
                return positionY;
            }
        }

        public void refreshBoard() {
            for (int i = 0; i < sizeY; i++) {
                for (int j = 0; j < sizeX; j++) {
                    Organism tmpOrganism = world.getBoard()[i][j];
                    if (tmpOrganism != null) {
                        boardFields[i][j].setEmpty(false);
                        boardFields[i][j].setEnabled(false);
                        boardFields[i][j].setColor(tmpOrganism.getColor());
                    } else {

                        boardFields[i][j].setEmpty(true);
                        boardFields[i][j].setEnabled(true);
                        boardFields[i][j].setColor(Color.WHITE);
                        boardFields[i][j].setBackground(new Color(172, 242, 157));
                    }
                }
            }
        }

        public int getSizeX() {
            return sizeX;
        }

        public int getSizeY() {
            return sizeY;
        }

        public BoardFields[][] getBoardFields() {
            return boardFields;
        }
    }

    private class EventGraphics extends JPanel {
        private String text;

        private final String instruction = "Space - Next turn\nArrows - human moving\nX - immortality\n";
        private JTextArea textArea;

        public EventGraphics() {
            super();
            setBounds(boardGraphics.getX() + boardGraphics.getWidth() + SPACE,
                    80+ mainPanel.getY() + SPACE,
                    mainPanel.getWidth() - boardGraphics.getWidth() - SPACE * 3,
                    mainPanel.getHeight() * 5 / 6 +2 * SPACE);
            text = Event.getText();
            textArea = new JTextArea(text);
            textArea.setEditable(false);
            setLayout(new CardLayout());
            textArea.setBackground(new Color(172, 242, 157));
            textArea.setLineWrap(true);
            textArea.setWrapStyleWord(true);
            textArea.setMargin(new Insets(5, 5, 5, 5));
            JScrollPane sp = new JScrollPane(textArea);
            add(sp);
        }

        public void refreshEvents() {
            String actualPlayerStrength;
            if (getWorld().getIsPlayerAlive()){
                actualPlayerStrength =getWorld().getPlayer().getStrength()+" - player strength\n\n";
            } else{
                actualPlayerStrength ="";

            }
            text = instruction + actualPlayerStrength + Event.getText();
            textArea.setText(text);
        }
    }

    private class OrganismList extends JFrame {
        private String[] organismList;
        private Organism.Type[] typeList;
        private JList JList;

        public OrganismList(int x, int y, Position position) {
            super("Organisms List");
            setBounds(x, y, 100, 300);
            organismList = new String[]{"Antelope", "Fox", "Sheep", "Wolf", "Turtle", "Borscht", "Guarana", "Dandelion", "Grass", "Blueberry"};
            typeList = new Organism.Type[]{Organism.Type.ANTELOPE, Organism.Type.FOX, Organism.Type.SHEEP, Organism.Type.WOLF,Organism.Type.TURTLE,  Organism.Type.BORSCH, Organism.Type.GUARANA, Organism.Type.DANDELION, Organism.Type.GRASS, Organism.Type.BLUEBERRY};

            JList = new JList(organismList);
            JList.setVisibleRowCount(organismList.length);
            JList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
            JList.addListSelectionListener(new ListSelectionListener() {
                @Override
                public void valueChanged(ListSelectionEvent e) {
                    Organism tmpOrganism = Spawner.SpawnNewOrganism(typeList[JList.getSelectedIndex()], world, position);
                    world.addOrganism(tmpOrganism);
                    Event.addEvent("New organism spawned:  " + tmpOrganism.getOrganismType());
                    refreshWorld();
                    dispose();

                }
            });

            JScrollPane sp = new JScrollPane(JList);
            add(sp);
            setVisible(true);
        }
    }

    private class Signs extends JPanel {
        private final int ORGANISMS_TYPE_NUMBER = 11;
        private JButton[] jButtons;

        public Signs() {
            super();
            setBounds(mainPanel.getX() + SPACE, mainPanel.getY() + SPACE,mainPanel.getWidth() - SPACE * 2,mainPanel.getHeight() * 1 / 19 );
            setBackground(new Color(172, 242, 157));
            setLayout(new FlowLayout(FlowLayout.CENTER));
            jButtons = new JButton[ORGANISMS_TYPE_NUMBER];

            jButtons[0] = new JButton("Player");
            jButtons[0].setBackground(Color.BLACK);

            jButtons[1] = new JButton("Antelope");
            jButtons[1].setBackground(new Color(208, 219, 2));

            jButtons[2] = new JButton("Fox");
            jButtons[2].setBackground(new Color(250, 126, 0));

            jButtons[3] = new JButton("Sheep");
            jButtons[3].setBackground(new Color(124, 133, 148));

            jButtons[4] = new JButton("Wolf");
            jButtons[4].setBackground(new Color(3, 60, 156));

            jButtons[5] = new JButton("Turtle");
            jButtons[5].setBackground(new Color(4, 48, 0));

            jButtons[6] = new JButton("Borscht");
            jButtons[6].setBackground(new Color(65, 2, 84));

            jButtons[7] = new JButton("Guarana");
            jButtons[7].setBackground(new Color(252, 3, 15));

            jButtons[8] = new JButton("Dandelion");
            jButtons[8].setBackground(new Color(240, 252, 68));

            jButtons[9] = new JButton("Grass");
            jButtons[9].setBackground(new Color(33, 255, 13));

            jButtons[10] = new JButton("Blueberry");
            jButtons[10].setBackground(new Color(102, 5, 237));

            for (int i = 0; i < ORGANISMS_TYPE_NUMBER; i++) {
                jButtons[i].setForeground(Color.WHITE);
                jButtons[i].setEnabled(false);
                add(jButtons[i]);
            }

        }
    }

    private void startGame() {
        boardGraphics = new boardGraphics(world);
        mainPanel.add(boardGraphics);

        eventGraphics = new EventGraphics();
        mainPanel.add(eventGraphics);

        signs = new Signs();
        mainPanel.add(signs);

        refreshWorld();
    }

    public void refreshWorld() {
        boardGraphics.refreshBoard();
        eventGraphics.refreshEvents();
        SwingUtilities.updateComponentTreeUI(jFrame);
        jFrame.requestFocusInWindow();
    }

    public World getWorld() {
        return world;
    }

    public boardGraphics getBoardGraphics() {
        return boardGraphics;
    }

    public EventGraphics getEventGraphics() {
        return eventGraphics;
    }
}