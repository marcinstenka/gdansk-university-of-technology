package project2Java.animals;

import project2Java.Animal;
import project2Java.Organism;
import project2Java.Event;
import project2Java.World;
import project2Java.Position;

import java.awt.*;

public class Turtle extends Animal {
    private static final int MOVE_RANGE = 1;
    private static final double MOVE_CHANCE = 0.25;
    private static final int STRENGTH = 2;
    private static final int INITIATIVE = 1;

    public Turtle(World world, Position position, int birthTurn) {
        super(Type.TURTLE, world, position, birthTurn, STRENGTH, INITIATIVE);
        this.setMoveRange(MOVE_RANGE);
        this.setMoveChance(MOVE_CHANCE);
        setColor(new Color(4, 48, 0));
    }

    @Override
    public String getOrganismType() {
        return "Turtle";
    }

    @Override
    public boolean specialSkillWhenAttacked(Organism attacker, Organism defender) {
        if (this == defender) {
            if (attacker.getStrength() < 5 && attacker.isAnimal()) {
                Event.addEvent(getOrganismType() + " fights off " + attacker.getOrganismType());
                return true;
            } else {
                return false;
            }
        } else {
            if (attacker.getStrength() >= defender.getStrength()) {
                return false;
            } else {
                if (defender.getStrength() < 5 && defender.isAnimal()) {
                    Event.addEvent(getOrganismType() + " fights off " + defender.getOrganismType());
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
}
