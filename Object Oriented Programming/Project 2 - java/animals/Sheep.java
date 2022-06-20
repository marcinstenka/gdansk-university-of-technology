package project2Java.animals;

import project2Java.Animal;
import project2Java.World;
import project2Java.Position;

import java.awt.*;

public class Sheep extends Animal {
    private static final int MOVE_RANGE = 1;
    private static final int MOVE_CHANCE = 1;
    private static final int STRENGTH = 4;
    private static final int INITIATIVE = 4;

    public Sheep(World world, Position position, int birthTurn) {
        super(Type.SHEEP, world, position, birthTurn, STRENGTH, INITIATIVE);
        this.setMoveRange(MOVE_RANGE);
        this.setMoveChance(MOVE_CHANCE);
        setColor(new Color(124, 133, 148));
    }

    @Override
    public String getOrganismType() {
        return "Sheep";
    }
}
