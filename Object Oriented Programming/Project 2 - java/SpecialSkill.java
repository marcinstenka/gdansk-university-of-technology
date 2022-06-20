package project2Java;

public class SpecialSkill {
    private final int SPECIAL_SKILL_DURATION = 5;
    private final int COOLDOWN_SPECIAL_SKILL = 10;
    private boolean canBeActivated;
    private boolean isActive;
    private int duration;
    private int cooldown;

    public SpecialSkill() {
        cooldown = 0;
        duration = 0;
        isActive = false;
        canBeActivated = true;
    }
    public boolean getCanBeActivated() {
        return canBeActivated;
    }

    public void setCanBeActivated(boolean canBeActivated) {
        this.canBeActivated = canBeActivated;
    }

    public boolean getIsSpecialSkillActive() {
        return isActive;
    }

    public void setIsActive(boolean isActive) {
        this.isActive = isActive;
    }

    public int getSpecialSkillDuration() {
        return duration;
    }

    public void setDuration(int duration) {
        this.duration = duration;
    }

    public int getCooldown() {
        return cooldown;
    }

    public void setCooldown(int cooldown) {
        this.cooldown = cooldown;
    }
    
    public void checkCondtions() {
        if (cooldown > 0) {
            cooldown--;
        }
        if (duration > 0) {
            duration--;
        }
        if (duration == 0) {
            deactivateSpecialSkill();
        }
        if (cooldown == 0) {
            canBeActivated = true;
        }
    }

    public void activateSpecialSkill() {
        if (cooldown == 0) {
            isActive = true;
            canBeActivated = false;
            cooldown = COOLDOWN_SPECIAL_SKILL;
            duration = SPECIAL_SKILL_DURATION;
        }
    }

    public void deactivateSpecialSkill() {
        isActive = false;
    }

   
}
