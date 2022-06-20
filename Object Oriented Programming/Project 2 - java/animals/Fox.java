package project2Java.animals;

import project2Java.Animal;
import project2Java.Organism;
import project2Java.World;
import project2Java.Position;

import java.util.Random;
import java.awt.*;

public class Fox extends Animal {
    private static final int MOVE_RANGE = 1;
    private static final int MOVE_CHANCE = 1;
    private static final int STRENGTH = 3;
    private static final int INITIATIVE = 7;

    public Fox(World world, Position position, int birthTurn) {
        super(Type.FOX, world, position, birthTurn, STRENGTH, INITIATIVE);
        this.setMoveRange(MOVE_RANGE);
        this.setMoveChance(MOVE_CHANCE);
        setColor(new Color(250, 126, 0));
    }

    @Override
    public String getOrganismType() {
        return "Fox";
    }

    @Override
    public Position randomField(Position position, boolean mustBeFree) {
        enableAllDirectionsPossible();
        int positionX = position.getX();
        int positionY = position.getY();
        int sizeX = getWorld().getSizeX();
        int sizeY = getWorld().getSizeY();
        int possibleDirectionsNumber = 0;
        Organism tmpOrganism;
        if (positionX == 0) {
            disableDirection(Direction.LEFT);
        } else {
            tmpOrganism = getWorld().getBoard()[positionY][positionX - 1];
            if (tmpOrganism != null && tmpOrganism.getStrength() > this.getStrength()) {
                disableDirection(Direction.LEFT);
            } else possibleDirectionsNumber++;
        }
        if (positionX == sizeX - 1) {
            disableDirection(Direction.RIGHT);
        } else {
            tmpOrganism = getWorld().getBoard()[positionY][positionX + 1];
            if (tmpOrganism != null && tmpOrganism.getStrength() > this.getStrength()) {
                disableDirection(Direction.RIGHT);
            } else possibleDirectionsNumber++;
        }
        if (positionY == 0) {
            disableDirection(Direction.UP);
        } else {
            tmpOrganism = getWorld().getBoard()[positionY - 1][positionX];
            if (tmpOrganism != null && tmpOrganism.getStrength() > this.getStrength()) {
                disableDirection(Direction.UP);
            } else possibleDirectionsNumber++;
        }
        if (positionY == sizeY - 1) {
            disableDirection(Direction.DOWN);
        } else {
            tmpOrganism = getWorld().getBoard()[positionY + 1][positionX];
            if (tmpOrganism != null && tmpOrganism.getStrength() > this.getStrength()) {
                disableDirection(Direction.DOWN);
            } else possibleDirectionsNumber++;
        }
        if (possibleDirectionsNumber == 0) {
            return new Position(positionX, positionY);
        }
        while (true) {
            Random rand = new Random();
            int upperbound = 100;
            int randomTmp = rand.nextInt(upperbound);
            if (randomTmp < 25 && !isDirectionDisabled(Direction.LEFT)){
                return new Position(positionX - 1, positionY);
            }
            else if (randomTmp >= 25 && randomTmp < 50 && !isDirectionDisabled(Direction.RIGHT)){
                return new Position(positionX + 1, positionY);
            }
            else if (randomTmp >= 50 && randomTmp < 75 && !isDirectionDisabled(Direction.UP)){
                return new Position(positionX, positionY - 1);
            }
            else if (randomTmp >= 75 && !isDirectionDisabled(Direction.DOWN)){
                return new Position(positionX, positionY + 1);
            }
        }
    }
}
