class Shirt {
    public int shirtID = 0;
    public String description = "-description required-";
    public char colorCode = 'B';
    public double price = 20.0;
    public int quantityInStock = 50;
    public void displayShirtInformation(){
        System.out.println("ShirtID:"+shirtID);
        System.out.println("Shirt description:"+description);
        System.out.println("Color Code"+colorCode);
        System.out.println("Shirt price"+price);
        System.out.println("Quantity in stock"+quantityInStock);
    }
}

public class ShirtTest {
    public static void main(String args[]){
        Shirt myShirt = new Shirt();
        myShirt.displayShirtInformation();
    }
}
