package project2Java.plants;

import project2Java.Plant;
import project2Java.Organism;
import project2Java.Event;
import project2Java.World;
import project2Java.Position;

import java.awt.*;

public class Guarana extends Plant {
    private static final int STRENGTH_INCREASE = 3;
    private static final int STRENGTH = 0;
    private static final int INITIATIVE = 0;

    public Guarana(World world, Position position, int birthTurn) {
        super(Type.GUARANA, world, position, birthTurn, STRENGTH, INITIATIVE);
        setColor(new Color(252, 3, 15));
    }

    @Override
    public String getOrganismType() {
        return "Guarana";
    }

    @Override
    public boolean specialSkillWhenAttacked(Organism attacker, Organism defender) {
        Position tmpPosition = this.getPosition();
        getWorld().deleteOrganism(this);
        attacker.doMove(tmpPosition);
        Event.addEvent(attacker.getOrganismType() + " eats " + this.getOrganismType() + "  and increase its strength by " + Integer.toString(STRENGTH_INCREASE));
        attacker.setStrength(attacker.getStrength() + STRENGTH_INCREASE);
        return true;
    }
}

