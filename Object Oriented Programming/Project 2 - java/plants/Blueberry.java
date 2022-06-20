package project2Java.plants;

import project2Java.Plant;
import project2Java.Organism;
import project2Java.Event;
import project2Java.World;
import project2Java.Position;

import java.util.Random;
import java.awt.*;

public class Blueberry extends Plant {
    private static final int STRENGTH = 99;
    private static final int INITIATIVE = 0;

    public Blueberry(World world, Position position, int birthTurn) {
        super(Type.BLUEBERRY, world, position, birthTurn, STRENGTH, INITIATIVE);
        setColor(new Color(102, 5, 237));
        setSpreadChance(0.05);
    }


    @Override
    public void action() {
        Random rand = new Random();
        int randomTmp = rand.nextInt(100);
        if (randomTmp < getSpreadChance() * 100) {
            spread();
        }
    }

    @Override
    public String getOrganismType() {
        return "Blueberry";
    }

    @Override
    public boolean specialSkillWhenAttacked(Organism attacker, Organism defender) {
        Event.addEvent(attacker.getOrganismType() + " eats " + this.getOrganismType());
        if (attacker.getStrength() >= 99) {
            getWorld().deleteOrganism(this);
            Event.addEvent(attacker.getOrganismType() + " destroys blueberry");
        }
        if (attacker.isAnimal()) {
            getWorld().deleteOrganism(attacker);
            Event.addEvent(attacker.getOrganismType() + " dies after eating blueberry");
        }
        return true;
    }
}
