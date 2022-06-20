package project2Java;

import project2Java.plants.*;
import project2Java.animals.*;


public class Spawner {
    public static Organism SpawnNewOrganism (Organism.Type type, World world, Position position) {
        switch (type) {
            case ANTELOPE:
                return new Antelope(world, position, world.getTurnNumber());
            case WOLF:
                return new Wolf(world, position, world.getTurnNumber());
            case SHEEP:
                return new Sheep(world, position, world.getTurnNumber());
            case FOX:
                return new Fox(world, position, world.getTurnNumber());
            case TURTLE:
                return new Turtle(world, position, world.getTurnNumber());
            case PLAYER:
                return new Player(world, position, world.getTurnNumber());
            case GRASS:
                return new Grass(world, position, world.getTurnNumber());
            case DANDELION:
                return new Dandelion(world, position, world.getTurnNumber());
            case GUARANA:
                return new Guarana(world, position, world.getTurnNumber());
            case BLUEBERRY:
                return new Blueberry(world, position, world.getTurnNumber());
            case BORSCH:
                return new Borscht(world, position, world.getTurnNumber());
            default:
                return null;
        }
    }
}
