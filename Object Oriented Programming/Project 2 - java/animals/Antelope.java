package project2Java.animals;

import project2Java.Animal;
import project2Java.Organism;
import project2Java.Event;
import project2Java.World;
import project2Java.Position;

import java.util.Random;
import java.awt.*;

public class Antelope extends Animal {
    private static final int MOVE_RANGE = 2;
    private static final int MOVE_CHANCE = 1;
    private static final int STRENGTH = 4;
    private static final int INITIATIVE = 4;


    public Antelope(World world, Position position, int birthTurn) {
        super(Type.ANTELOPE, world, position, birthTurn, STRENGTH, INITIATIVE);
        this.setMoveRange(MOVE_RANGE);
        this.setMoveChance(MOVE_CHANCE);
        setColor(new Color(208, 219, 2));
    }

    @Override
    public String getOrganismType() {
        return "Antelope";
    }

    @Override
    public boolean specialSkillWhenAttacked(Organism attacker, Organism defender) {
        Random rand = new Random();
        int randomTmp = rand.nextInt(100);
        if (randomTmp < 50) {
            if (this == attacker) {
                Event.addEvent(getOrganismType() + " runs away from " + defender.getOrganismType());
                Position tmpPosition = randomField(defender.getPosition(), true);
                if (!tmpPosition.equals(defender.getPosition()))
                    doMove(tmpPosition);
            } else if (this == defender) {
                Event.addEvent(getOrganismType() + " runs away from " + attacker.getOrganismType());
                Position tmpPosition = this.getPosition();
                doMove(randomField(this.getPosition(), true));
                if (getPosition().equals(tmpPosition)) {
                    getWorld().deleteOrganism(this);
                    Event.addEvent(attacker.getOrganismType() + " kills " + getOrganismType());
                }
                attacker.doMove(tmpPosition);
            }
            return true;
        } else {
            return false;
        }
    }
}
