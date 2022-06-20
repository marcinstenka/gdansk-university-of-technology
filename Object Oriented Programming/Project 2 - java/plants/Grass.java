package project2Java.plants;

import project2Java.Plant;
import project2Java.World;
import project2Java.Position;

import java.awt.*;

public class Grass extends Plant {
    private static final int STRENGTH = 0;
    private static final int INITIATIVE = 0;

    public Grass(World world, Position position, int birthTurn) {
        super(Type.GRASS, world, position, birthTurn, STRENGTH, INITIATIVE);
        setColor(new Color(33, 255, 13));
    }

    @Override
    public String getOrganismType() {
        return "Grass";
    }
}
