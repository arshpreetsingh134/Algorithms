import java.util.LinkedList;

abstract class Animal
{
    private int order;
    public String name;

    public Animal(String name)
    {
        this.name = name;
    }

    public void setOrder(int order)
    {
        this.order = order;
    }

    public int getOrder()
    {
        return order;
    }

    // Compare the order of 2 animals and return 
    // the one who is the oldest (smallest order)
    public boolean isOlderThan(Animal a)
    {
        return this.order < a.getOrder();
    }
}

class Dog extends Animal
{
    public Dog(String name)
    {
        super(name);
    }
}

class Cat extends Animal
{
    public Cat(String name)
    {
        super(name);
    }
}

class Animal_Shelter
{
    LinkedList<Dog> dogs = new LinkedList<Dog>();
    LinkedList<Cat> cats = new LinkedList<Cat>();
    private int order = 0;  // Universal Time Stamp for both cats and dogs

    public void Enqueue(Animal a)
    {
        a.setOrder(order);
        order++;

        if(a instanceof Dog)
            dogs.addLast((Dog) a);
        else
            cats.addLast((Cat) a);
    }

    public Animal dequeAny()
    {
        // Look at the top of Dog and Cat classes and pop the
        // queue with the oldest value
        if(dogs.size()==0)
            return dequeCats();
        else if(cats.size()==0)
            return dequeDogs();

        Dog dog = dogs.peek();
        Cat cat = cats.peek();

        if(cat.isOlderThan(dog))
            return dequeCats();
        else
            return dequeDogs();
    }

    Animal dequeCats()
    {
        return (cats.removeFirst());
    }

    Animal dequeDogs()
    {
        return (dogs.removeFirst());
    }

    public static void main(String[] args)
    {
        Animal_Shelter as = new Animal_Shelter();

        as.Enqueue(new Cat("Cat1"));
        as.Enqueue(new Dog("Dog1"));

        as.Enqueue(new Cat("Cat2"));
        as.Enqueue(new Dog("Dog2"));
        as.Enqueue(new Dog("Dog3"));

        as.Enqueue(new Cat("Cat3"));
        as.Enqueue(new Cat("Cat4"));
        as.Enqueue(new Dog("Dog4"));
        as.Enqueue(new Dog("Dog5"));
    
        System.out.println(as.dequeDogs().name+" adopted.");
        System.out.println(as.dequeCats().name+" adopted.");
        System.out.println(as.dequeAny().name+" adopted.");
    }
}