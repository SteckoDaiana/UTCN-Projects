package orderManagement.Model;
/**
 *
 */
public class Product {
    /**
     *
     */
    private int id;
    private String name;
    private String supplier;
    private int stock;
    /**
     *
     * @param id
     * @param name
     * @param supplier
     * @param stock
     */
    public Product(int id, String name, String supplier, int stock) {
        this.id = id;
        this.name = name;
        this.supplier = supplier;
        this.stock = stock;
    }
    public Product(){

    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSupplier() {
        return supplier;
    }

    public void setSupplier(String supplier) {
        this.supplier = supplier;
    }

    public int getStock() {
        return stock;
    }

    public void setStock(int stock) {
        this.stock = stock;
    }

}
