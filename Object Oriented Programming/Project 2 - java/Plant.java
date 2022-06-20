package project2Java;

import java.util.Random;

public abstract class Plant extends Organism {

    protected Plant(Type type, World world,
                      Position position, int birthTurn, int strength, int initiative) {
        super(type, world, position, birthTurn, strength, initiative);
        setSpreadChance(0.3);
    }

    @Override
    public void action() {
        Random rand = new Random();
        int upperbound = 100;
        int randomTmp = rand.nextInt(upperbound);
        if (randomTmp < getSpreadChance() * 100) spread();
    }

    @Override
    public boolean isAnimal() {
        return false;
    }


    protected void spread() {
        Position tmp1Position = this.randomField(getPosition(), true);
        if (tmp1Position.equals(getPosition())) return;
        else {
            Organism tmpOrganism = Spawner.SpawnNewOrganism(getType(), this.getWorld(), tmp1Position);
            Event.addEvent("New " + tmpOrganism.getOrganismType() + "has grown");
            getWorld().addOrganism(tmpOrganism);
        }
    }

    @Override
    public void colision(Organism other) {
    }
}
