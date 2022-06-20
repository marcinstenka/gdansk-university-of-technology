package project2Java.plants;

import project2Java.Plant;
import project2Java.World;
import project2Java.Position;

import java.util.Random;
import java.awt.*;

public class Dandelion extends Plant {
    private static final int STRENGTH = 0;
    private static final int INITIATIVE = 0;
    private static final int TRIAL_NUMBER = 3;

    public Dandelion(World world, Position position, int birthTurn) {
        super(Type.DANDELION, world, position, birthTurn, STRENGTH, INITIATIVE);
        setColor(Color.YELLOW);
    }

    @Override
    public void action() {
        Random rand = new Random();
        for (int i = 0; i < TRIAL_NUMBER; i++) {
            int randomTmp = rand.nextInt(100);
            if (randomTmp < getSpreadChance()) {
                spread();
            }
        }
    }

    @Override
    public String getOrganismType() {
        return "Dandelion";
    }
}
