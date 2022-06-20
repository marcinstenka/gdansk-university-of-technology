package project2Java.animals;

import project2Java.Animal;
import project2Java.World;
import project2Java.Position;

import java.awt.*;

public class Wolf extends Animal {
    private static final int MOVE_RANGE = 1;
    private static final int MOVE_CHANCE = 1;
    private static final int STRENGTH = 9;
    private static final int INITIATIVE = 5;

    public Wolf(World world, Position position, int birthTurn) {
        super(Type.WOLF, world, position, birthTurn, STRENGTH, INITIATIVE);
        this.setMoveRange(MOVE_RANGE);
        this.setMoveChance(MOVE_CHANCE);
        setColor(new Color(3, 60, 156));
    }

    @Override
    public String getOrganismType() {
        return "Wolf";
    }
}
