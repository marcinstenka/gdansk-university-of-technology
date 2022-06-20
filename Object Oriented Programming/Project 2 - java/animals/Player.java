package project2Java.animals;

import project2Java.Animal;
import project2Java.Organism;
import project2Java.Event;
import project2Java.World;
import project2Java.Position;
import project2Java.SpecialSkill;

import java.awt.*;

public class Player extends Animal {
    private static final int MOVE_RANGE = 1;
    private static final int MOVE_CHANCE = 1;
    private static final int STRENGTH = 5;
    private static final int INITIATIVE = 4;
    private Direction moveDirection;
    private SpecialSkill specialSkill;

    public Player(World world, Position position, int birthTurn) {
        super(Type.PLAYER, world, position, birthTurn, STRENGTH, INITIATIVE);
        this.setMoveRange(MOVE_RANGE);
        this.setMoveChance(MOVE_CHANCE);
        moveDirection = Direction.ANY;
        setColor(Color.BLACK);
        specialSkill = new SpecialSkill();
    }

    @Override
    protected Position move() {
        int x = getPosition().getX();
        int y = getPosition().getY();
        randomField(getPosition(), false);
        if (moveDirection == Direction.ANY ||
                isDirectionDisabled(moveDirection)) {
            return getPosition();
        } else {
            if (moveDirection == Direction.DOWN) {
                return new Position(x, y + 1);
            }
            else if (moveDirection == Direction.UP) {
                return new Position(x, y - 1);
            }
            else if (moveDirection == Direction.LEFT) {
                return new Position(x - 1, y);
            }
            else if (moveDirection == Direction.RIGHT) {
                return new Position(x + 1, y);
            }
            else {
                return new Position(x, y);
            }
        }
    }

    @Override
    public void action() {
        if (specialSkill.getIsSpecialSkillActive()) {
            Event.addEvent(getOrganismType() + " 'Immoratlity' is active (" + specialSkill.getSpecialSkillDuration() + " turns remaining)");
        }
        for (int i = 0; i < getMoveRange(); i++) {
            Position nextMove = move();
            if (getWorld().isFieldFree(nextMove) && getWorld().whatIsOnTheField(nextMove) != this) {
                colision(getWorld().whatIsOnTheField(nextMove));
                break;
            } else if (getWorld().whatIsOnTheField(nextMove) != this) {
                doMove(nextMove);
            }
        }
        moveDirection = Direction.ANY;
        specialSkill.checkCondtions();
    }

    @Override
    public String getOrganismType() {
        return "Player";
    }

    public SpecialSkill getSpecialSkill() {
        return specialSkill;
    }

    public void setMoveDirection(Direction moveDirection) {
        this.moveDirection = moveDirection;
    }
}
