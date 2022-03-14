package orderManagement.Model;
/**
 *
 */
public class ProductOrder {
    /**
     *
     */
    private int id;
    private String client;
    private String product;
    private int quantity;
    /**
     *
     * @param id
     * @param client
     * @param product
     * @param quantity
     */
    public ProductOrder(int id, String client, String product, int quantity) {
        this.id = id;
        this.client = client;
        this.product = product;
        this.quantity = quantity;
    }

    public ProductOrder(){}

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getClient() {
        return client;
    }

    public void setClient(String client) {
        this.client = client;
    }

    public String getProduct() {
        return product;
    }

    public void setProduct(String product) {
        this.product = product;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
}
