class Milestone4 {
    private int value;
    private Milestone4 next;

    public Milestone4(int value) {
        this(value, null);
    }
    public Milestone4(int value, Milestone4 next) {
        this.value = value;
        this.next = next;
    }

    public Milestone4 find(int value) {
        if (value == this.value) {
            return this;
        } else if (this.next != null) {
            return this.next.find(value);
        } else {
            return null;
        }
    }

    static Milestone4 list = new Milestone4(98, new Milestone4(12, new Milestone4(3)));
    static boolean contains(int n) {
        return list.find(n) != null;
    }
}

