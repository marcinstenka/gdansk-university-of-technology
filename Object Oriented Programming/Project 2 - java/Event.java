package project2Java;

public class Event {
    private static String text = "";

    public static void addEvent(String event) {
        text += event + "\n";
    }

    public static String getText() {
        return text;
    }

    public static void ClearEvent() {
        text = "";
    }
}
