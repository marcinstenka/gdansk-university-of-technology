package project2Java;

import java.awt.*;
import java.util.Random;

public abstract class Organism {
    public enum Type {
        PLAYER,
        WOLF,
        SHEEP,
        FOX,
        TURTLE,
        ANTELOPE,
        GRASS,
        DANDELION,
        GUARANA,
        BLUEBERRY,
        BORSCH;
    }

    public enum Direction {
        LEFT(0),
        RIGHT(1),
        UP(2),
        DOWN(3),
        ANY(4);

        private final int value;

        private Direction(int value) {
            this.value = value;
        }

        public int getValue() {
            return value;
        }
    }

    private int strength;
    private int initiative;
    private int birthTurn;
    private Color color;
    private boolean didDie;
    private boolean[] direction;
    private boolean didBreed;
    private World world;
    private Position position;
    private Type type;
    private double breedChance;
    private static final int ORGANISMS_TYPE_NUMBER = 11;

    public abstract String getOrganismType();

    public abstract void action();

    public abstract void colision(Organism other);

    public abstract boolean isAnimal();

    public Organism(Type type, World world,
                    Position position, int birthTurn, int strength, int initiative) {
        this.type = type;
        this.world = world;
        this.position = position;
        this.birthTurn = birthTurn;
        this.strength = strength;
        this.initiative = initiative;
        didDie = false;
        direction = new boolean[]{true, true, true, true};
    }

    public int getStrength() {
        return strength;
    }

    public int getinitiative() {
        return initiative;
    }

    public int getBirthTurn() {
        return birthTurn;
    }

    public boolean getdidDie() {
        return didDie;
    }

    public boolean getDidBreed() {
        return didBreed;
    }

    public World getWorld() {
        return world;
    }

    public Position getPosition() {
        return position;
    }

    public Type getType() {
        return type;
    }

    public void setStrength(int strength) {
        this.strength = strength;
    }

    public void setInitiative(int initiative) {
        this.initiative = initiative;
    }

    public void setBirthTurn(int birthTurn) {
        this.birthTurn = birthTurn;
    }

    public void setDidDie(boolean didDie) {
        this.didDie = didDie;
    }

    public void setDidBreed(boolean didBreed) {
        this.didBreed = didBreed;
    }

    public void setWorld(World world) {
        this.world = world;
    }

    public void setPosition(Position position) {
        this.position = position;
    }

    public void setType(Type type) {
        this.type = type;
    }

    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }

    public double getSpreadChance() {
        return breedChance;
    }

    public void setSpreadChance(double breedChance) {
        this.breedChance = breedChance;
    }

    public boolean specialSkillWhenAttacked(Organism attacker, Organism defender) {
        return false;
    }
    public void doMove(Position nextMove) {
        int x = nextMove.getX();
        int y = nextMove.getY();
        world.getBoard()[position.getY()][position.getX()] = null;
        world.getBoard()[y][x] = this;
        position.setX(x);
        position.setY(y);
    }

    static Type randomType() {
        Random rand = new Random();
        int tmp = rand.nextInt(ORGANISMS_TYPE_NUMBER - 1);
        if (tmp == 0) {
            return Type.WOLF;
        }
        else if (tmp == 1) {
            return Type.SHEEP;
        }
        else if (tmp == 2) {
            return Type.FOX;
        }
        else if (tmp == 3) {
            return Type.TURTLE;
        }
        else if (tmp == 4) {
            return Type.ANTELOPE;
        }
        else if (tmp == 5) {
            return Type.GRASS;
        }
        else if (tmp == 6) {
            return Type.DANDELION;
        }
        else if (tmp == 7) {
            return Type.GUARANA ;
        }
        else if (tmp == 8) {
            return Type.BLUEBERRY;
        }
        else {
            return Type.BORSCH;
        }
    }

    public Position randomField(Position position, boolean mustBeFree) {
        enableAllDirectionsPossible();
        int positionX = position.getX();
        int positionY = position.getY();
        int sizeX = world.getSizeX();
        int sizeY = world.getSizeY();
        int possibleDirectionsNumber = 0;

        if (positionX == 0) {
            disableDirection(Direction.LEFT);
        } else if(mustBeFree) {
            if (world.isFieldFree(new Position(positionX - 1, positionY)) == false) {
                possibleDirectionsNumber++;
            } else {
                disableDirection(Direction.LEFT);
            }
        }

        if (positionX == sizeX - 1) {
            disableDirection(Direction.RIGHT);
        }
        else if(mustBeFree){
            if (world.isFieldFree(new Position(positionX + 1, positionY)) == false) {
                possibleDirectionsNumber++;
            } else {
                disableDirection(Direction.RIGHT);
            }
        } else {
            possibleDirectionsNumber++;
        }

        if (positionY == 0) {
            disableDirection(Direction.UP);
        } else if(mustBeFree){
            if (world.isFieldFree(new Position(positionX, positionY - 1)) == false) {
                possibleDirectionsNumber++;
            } else {
                disableDirection(Direction.UP);
            }
        } else {
            possibleDirectionsNumber++;
        }

        if (positionY == sizeY - 1) {
            disableDirection(Direction.DOWN);
        } else if(mustBeFree){
            if (world.isFieldFree(new Position(positionX, positionY + 1)) == false) {
                possibleDirectionsNumber++;
            } else {
                disableDirection(Direction.DOWN);
            }
        } else {
            possibleDirectionsNumber++;
        }
        if (possibleDirectionsNumber == 0 && mustBeFree) {
            return new Position(positionX, positionY);
        } else if (possibleDirectionsNumber == 0){
            return position;
        }
        while (true) {
            Random rand = new Random();
            int upperbound = 100;
            int randomTmp = rand.nextInt(upperbound);
            if (randomTmp < 25 && !isDirectionDisabled(Direction.LEFT)) {
                return new Position(positionX - 1, positionY);
            }
            else if (randomTmp >= 25 && randomTmp < 50 && !isDirectionDisabled(Direction.RIGHT)) {
                return new Position(positionX + 1, positionY);
            }
            else if (randomTmp >= 50 && randomTmp < 75 && !isDirectionDisabled(Direction.UP)) {
                return new Position(positionX, positionY - 1);
            }
            else if (randomTmp >= 75 && !isDirectionDisabled(Direction.DOWN)) {
                return new Position(positionX, positionY + 1);
            }
        }
    }

    protected void disableDirection(Direction direction) {
        this.direction[direction.getValue()] = false;
    }

    protected void enableDirection(Direction direction) {
        this.direction[direction.getValue()] = true;
    }

    protected void enableAllDirectionsPossible() {
        enableDirection(Direction.LEFT);
        enableDirection(Direction.RIGHT);
        enableDirection(Direction.UP);
        enableDirection(Direction.DOWN);
    }

    protected boolean isDirectionDisabled(Direction direction) {
        return !(this.direction[direction.getValue()]);
    }


}