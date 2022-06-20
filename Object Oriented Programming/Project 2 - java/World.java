package project2Java;

import java.io.IOException;
import java.util.*;
import java.io.File;
import java.io.PrintWriter;

import project2Java.animals.Player;

public class World {
    private int sizeX;
    private int sizeY;
    private int turnNumber;
    private Organism[][] board;
    private boolean isPlayerAlive;
    private boolean isGameOver;
    private boolean pause;
    private ArrayList<Organism> organisms;
    private Player player;
    private GameInterface gameInterface;

    public World(GameInterface gameInterface) {
        this.sizeX = 0;
        this.sizeY = 0;
        turnNumber = 0;
        isPlayerAlive = true;
        isGameOver = false;
        pause = true;
        organisms = new ArrayList<>();
        this.gameInterface = gameInterface;
    }

    public World(int sizeX, int sizeY, GameInterface gameInterface) {
        this.sizeX = sizeX;
        this.sizeY = sizeY;
        turnNumber = 0;
        isPlayerAlive = true;
        isGameOver = false;
        pause = true;
        board = new Organism[sizeY][sizeX];
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                board[i][j] = null;
            }
        }
        organisms = new ArrayList<>();
        this.gameInterface = gameInterface;
    }

    public int getSizeX() {
        return sizeX;
    }

    public int getSizeY() {
        return sizeY;
    }

    public int getTurnNumber() {
        return turnNumber;
    }

    public Organism[][] getBoard() {
        return board;
    }

    public boolean getIsPlayerAlive() {
        return isPlayerAlive;
    }

    public boolean getIsGameOver() {
        return isGameOver;
    }

    public ArrayList<Organism> getOrganisms() {
        return organisms;
    }

    public Player getPlayer() {
        return player;
    }

    public void setPlayer(Player player) {
        this.player = player;
    }

    public void setIsPlayerAlive(boolean isPlayerAlive) {
        this.isPlayerAlive = isPlayerAlive;
    }

    public void setIsGameOver(boolean isGameOver) {
        this.isGameOver = isGameOver;
    }

    public boolean isPaused() {
        return pause;
    }

    public void setPause(boolean pause) {
        this.pause = pause;
    }

    public GameInterface getGameInterface() {
        return gameInterface;
    }

    public void setGameInterface(GameInterface gameInterface) {
        this.gameInterface = gameInterface;
    }



    public void generateWorld() {
        int organismsNumber = (int) Math.floor(sizeX * sizeY * 0.3);
        Position position = randomField();
        Organism tmpOrganism = Spawner.SpawnNewOrganism(Organism.Type.PLAYER, this, position);
        addOrganism(tmpOrganism);
        player = (Player) tmpOrganism;
        
        for (int i = 0; i < organismsNumber - 1; i++) {
            position = randomField();
            if (position != new Position(-1, -1)) {
                addOrganism(Spawner.SpawnNewOrganism(Organism.randomType(), this, position));
            } else {
                return;
            }
        }
    }

    public void doTurn() {
        if (isGameOver) {
            return;
        }
        turnNumber++;
        Event.addEvent("\nTURN " + turnNumber);

        sortOrganismsByInitiative();
        for (int i = 0; i < organisms.size(); i++) {
            if (organisms.get(i).getBirthTurn() != turnNumber && organisms.get(i).getdidDie() == false) {
                organisms.get(i).action();
            }
        }
        for (int i = 0; i < organisms.size(); i++) {
            if (organisms.get(i).getdidDie() == true) {
                organisms.remove(i);
                i--;
            }
        }
        for (int i = 0; i < organisms.size(); i++) {
            organisms.get(i).setDidBreed(false);
        }
    }

    private void sortOrganismsByInitiative() {
        Collections.sort(organisms, new Comparator<Organism>() {
            @Override
            public int compare(Organism o1, Organism o2) {
                if (o1.getinitiative() != o2.getinitiative())
                    return Integer.valueOf(o2.getinitiative()).compareTo(o1.getinitiative());
                else
                    return Integer.valueOf(o1.getBirthTurn()).compareTo(o2.getBirthTurn());
            }
        });
    }

    public Position randomField() {
        Random rand = new Random();
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                if (board[i][j] == null) {
                    while (true) {
                        int x = rand.nextInt(sizeX);
                        int y = rand.nextInt(sizeY);
                        if (board[y][x] == null) return new Position(x, y);
                    }
                }
            }
        }
        return new Position(-1, -1);
    }

    public boolean isFieldFree(Position pole) {
        if (board[pole.getY()][pole.getX()] == null) {
            return false;
        }
        else {
            return true;
        }
    }

    public Organism whatIsOnTheField(Position pole) {
        return board[pole.getY()][pole.getX()];
    }

    public void addOrganism(Organism organism) {
        organisms.add(organism);
        board[organism.getPosition().getY()][organism.getPosition().getX()] = organism;
    }

    public void deleteOrganism(Organism organism) {
        board[organism.getPosition().getY()][organism.getPosition().getX()] = null;
        organism.setDidDie(true);
        if (organism.getType() == Organism.Type.PLAYER) {
            isPlayerAlive = false;
            player = null;
        }
    }



    public boolean isThereAnyBorscht() {
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                if (board[i][j] != null && board[i][j].getType() == Organism.Type.BORSCH) {
                    return true;
                }
            }
        }
        return false;
    }
    public void save(String nameOfFile) {
        try {
            nameOfFile += ".txt";
            File file = new File(nameOfFile);
            file.createNewFile();

            PrintWriter pw = new PrintWriter(file);
            pw.print(sizeX + " ");
            pw.print(sizeY + " ");
            pw.print(turnNumber + " ");
            pw.print(isPlayerAlive + " ");
            pw.print(isGameOver + "\n");
            for (int i = 0; i < organisms.size(); i++) {
                pw.print(organisms.get(i).getType() + " ");
                pw.print(organisms.get(i).getPosition().getX() + " ");
                pw.print(organisms.get(i).getPosition().getY() + " ");
                pw.print(organisms.get(i).getStrength() + " ");
                pw.print(organisms.get(i).getBirthTurn() + " ");
                pw.print(organisms.get(i).getdidDie());
                if (organisms.get(i).getType() == Organism.Type.PLAYER) {
                    pw.print(" " + player.getSpecialSkill().getSpecialSkillDuration() + " ");
                    pw.print(player.getSpecialSkill().getCooldown() + " ");
                    pw.print(player.getSpecialSkill().getIsSpecialSkillActive() + " ");
                    pw.print(player.getSpecialSkill().getCanBeActivated());
                }
                pw.println();
            }
            pw.close();
        } catch (IOException e) {
            System.out.println("Error: " + e);
        }
    }

    public static World load(String nameOfFile) {
        try {
            nameOfFile += ".txt";
            File file = new File(nameOfFile);

            Scanner scanner = new Scanner(file);
            String line = scanner.nextLine();
            String[] properties = line.split(" ");
            int sizeX = Integer.parseInt(properties[0]);
            int sizeY = Integer.parseInt(properties[1]);
            World tmpWorld = new World(sizeX, sizeY, null);
            int turnNumber = Integer.parseInt(properties[2]);
            tmpWorld.turnNumber = turnNumber;
            boolean isPlayerAlive = Boolean.parseBoolean(properties[3]);
            tmpWorld.isPlayerAlive = isPlayerAlive;
            boolean isGameOver = Boolean.parseBoolean(properties[4]);
            tmpWorld.isGameOver = isGameOver;
            tmpWorld.player = null;

            while (scanner.hasNextLine()) {
                line = scanner.nextLine();
                properties = line.split(" ");
                Organism.Type type = Organism.Type.valueOf(properties[0]);
                int x = Integer.parseInt(properties[1]);
                int y = Integer.parseInt(properties[2]);

                Organism tmpOrganism = Spawner.SpawnNewOrganism
                        (type, tmpWorld, new Position(x, y));
                int strength = Integer.parseInt(properties[3]);
                tmpOrganism.setStrength(strength);
                int birthTurn = Integer.parseInt(properties[4]);
                tmpOrganism.setBirthTurn(birthTurn);
                boolean didDie = Boolean.parseBoolean(properties[5]);
                tmpOrganism.setDidDie(didDie);

                if (type == Organism.Type.PLAYER) {
                    tmpWorld.player = (Player) tmpOrganism;
                    int duration = Integer.parseInt(properties[6]);
                    tmpWorld.player.getSpecialSkill().setDuration(duration);
                    int cooldown = Integer.parseInt(properties[7]);
                    tmpWorld.player.getSpecialSkill().setCooldown(cooldown);
                    boolean isActive = Boolean.parseBoolean(properties[8]);
                    tmpWorld.player.getSpecialSkill().setIsActive(isActive);
                    boolean canBeActivated = Boolean.parseBoolean(properties[9]);
                    tmpWorld.player.getSpecialSkill().setCanBeActivated(canBeActivated);
                }
                tmpWorld.addOrganism(tmpOrganism);
            }
            scanner.close();
            return tmpWorld;
        } catch (
                IOException e) {
            System.out.println("Error: " + e);
        }
        return null;
    }
}
