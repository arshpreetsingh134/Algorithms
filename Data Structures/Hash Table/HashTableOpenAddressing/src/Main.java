public class Main {
    public static void main(String[] args) {
        HashTableLinearProbing<String, Integer> ht = new HashTableLinearProbing<>();
        // HashTableQuadraticProbing<String, Integer> ht = new HashTableQuadraticProbing<>();
        // HashTableDoubleHashing<String, Integer> ht = new HashTableDoubleHashing<>();

        ht.insert("Apples", 3);
        ht.insert("Mangoes", 10);
        ht.insert("Oranges", 7);
        ht.insert("Bananas", 25);

        System.out.println(ht.get("Bananas"));

        System.out.println(ht.get("Mangoes"));

        ht.remove("Oranges");

        System.out.println(ht.get("Oranges"));
    }
}
