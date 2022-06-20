package project2Java.plants;

import project2Java.Organism;
import project2Java.Plant;
import project2Java.Event;
import project2Java.World;
import project2Java.Position;

import java.awt.*;
import java.util.Random;

public class Borscht extends Plant {
    private static final int STRENGTH = 10;
    private static final int INITIATIVE = 0;

    public Borscht(World world, Position position, int birthTurn) {

        super(Type.BORSCH, world, position,
                birthTurn, STRENGTH, INITIATIVE);
        setColor(new Color(65, 2, 84));
        setSpreadChance(0.05);
    }

    @Override
    public void action() {
        int positionX = getPosition().getX();
        int positionY = getPosition().getY();
        randomField(getPosition(), false);
        for (int i = 0; i < 4; i++) {
            Organism tmpOrganism = null;
            if (i == 0 && !isDirectionDisabled(Direction.DOWN)){
                tmpOrganism = getWorld().whatIsOnTheField(new Position(positionX, positionY + 1));
            }
            else if (i == 1 && !isDirectionDisabled(Direction.UP)){
                tmpOrganism = getWorld().whatIsOnTheField(new Position(positionX, positionY - 1));
            }
            else if (i == 2 && !isDirectionDisabled(Direction.LEFT)){
                tmpOrganism = getWorld().whatIsOnTheField(new Position(positionX - 1, positionY));
            }
            else if (i == 3 && !isDirectionDisabled(Direction.RIGHT)){
                tmpOrganism = getWorld().whatIsOnTheField(new Position(positionX + 1, positionY));
            }
            if (tmpOrganism != null && tmpOrganism.isAnimal()) {
                if(getWorld().getIsPlayerAlive()&& getWorld().getPlayer().getSpecialSkill().getIsSpecialSkillActive()){
                    Event.addEvent("Player is immortal so he is not afraid of borscht");
                } else{
                    getWorld().deleteOrganism(tmpOrganism);
                    Event.addEvent(getOrganismType() + " kills " + tmpOrganism.getOrganismType());
                }

            }
        }
        Random rand = new Random();
        int randomTmp = rand.nextInt(100);
        if (randomTmp < getSpreadChance() * 100) {
            spread();
        }
    }

    @Override
    public String getOrganismType() {
        return "Borsch";
    }

    @Override
    public boolean specialSkillWhenAttacked(Organism attacker, Organism defender) {
        if (attacker.getStrength() >= 10) {
            getWorld().deleteOrganism(this);
            Event.addEvent(attacker.getOrganismType() + " eats " + this.getOrganismType());
            attacker.doMove(defender.getPosition());
        }
        if ((attacker.isAnimal()) || attacker.getStrength() < 10) {
            getWorld().deleteOrganism(attacker);
            Event.addEvent(this.getOrganismType() + " kills " + attacker.getOrganismType());
        }
        return true;
    }
}
