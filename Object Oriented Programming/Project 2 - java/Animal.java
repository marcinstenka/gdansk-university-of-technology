package project2Java;

import java.util.Random;

import static project2Java.Organism.Type.GRASS;
import static project2Java.Organism.Type.PLAYER;

public abstract class Animal extends Organism {
    private int moveRange;
    private double moveChance;

    public Animal(Type type, World world,
                   Position position, int birthTurn, int strength, int initiative) {
        super(type, world, position, birthTurn, strength, initiative);
        setDidBreed(false);
        setSpreadChance(0.5);
    }

    @Override
    public void action() {
        for (int i = 0; i < moveRange; i++) {
            Position nextMove = move();
            if (getWorld().isFieldFree(nextMove) && getWorld().whatIsOnTheField(nextMove) != this) {
                colision(getWorld().whatIsOnTheField(nextMove));
                break;
            } else if (getWorld().whatIsOnTheField(nextMove) != this) {
                doMove(nextMove);
            }
        }
    }

    @Override
    public void colision(Organism other) {
        if (getType() == other.getType()) {
            Random rand = new Random();
            int randomTmp = rand.nextInt(100);
            if (randomTmp < getSpreadChance() * 100) breeding(other);

        } else if(getOrganismType() == "Player" && getWorld().getIsPlayerAlive() && getWorld().getPlayer().getSpecialSkill().getIsSpecialSkillActive()){
             Event.addEvent("Player is immortal. " + other.getOrganismType() + " was killed.");
             getWorld().deleteOrganism(other);
             doMove(other.getPosition());
        }
        else {
            if(other.getOrganismType() == "Player") {
                    if(getWorld().getIsPlayerAlive()&&getWorld().getPlayer().getSpecialSkill().getIsSpecialSkillActive()){
                        Event.addEvent("Player is immortal. " + getOrganismType() + " couldn't killed him.");
                        return;
                    }
            }
            if (other.specialSkillWhenAttacked(this, other)){
                return;
            }
            if (specialSkillWhenAttacked(this, other)) {
                return;
            }
            if (getStrength() >= other.getStrength()) {
                getWorld().deleteOrganism(other);
                doMove(other.getPosition());
                Event.addEvent(getOrganismType() + " kills " + other.getOrganismType());
            } else {
                getWorld().deleteOrganism(this);
                Event.addEvent(other.getOrganismType() + " kills " + getOrganismType());
            }
        }
    }

    @Override
    public boolean isAnimal() {
        return true;
    }

    protected Position move() {
        Random rand = new Random();
        int upperbound = 100;
        int randomTmp = rand.nextInt(upperbound);
        if (randomTmp >= (int) (moveChance * 100)) {
            return getPosition();
        }
        else {
            return randomField(getPosition(), false);
        }
    }

    private void breeding(Organism other) {
        if (this.getDidBreed() || other.getDidBreed()) {
            return;
        }
        Position tmp1Position = this.randomField(getPosition(), true);
        if (tmp1Position.equals(getPosition())) {
            Position tmp2Position = other.randomField(other.getPosition(), true);
            if (tmp2Position.equals(other.getPosition())) {
                return;
            }
            else {
                Organism tmpOrganism = Spawner.SpawnNewOrganism(getType(), this.getWorld(), tmp2Position);
                Event.addEvent(tmpOrganism.getOrganismType() + " was borned");
                getWorld().addOrganism(tmpOrganism);
                setDidBreed(true);
                other.setDidBreed(true);
            }
        } else {
            Organism tmpOrganism = Spawner.SpawnNewOrganism(getType(), this.getWorld(), tmp1Position);
            Event.addEvent(tmpOrganism.getOrganismType() + " was borned");
            getWorld().addOrganism(tmpOrganism);
            setDidBreed(true);
            other.setDidBreed(true);
        }
    }

    public int getMoveRange() {
        return moveRange;
    }

    public void setMoveRange(int moveRange) {
        this.moveRange = moveRange;
    }

    public double getMoveChance() {
        return moveChance;
    }

    public void setMoveChance(double moveChance) {
        this.moveChance = moveChance;
    }
}
